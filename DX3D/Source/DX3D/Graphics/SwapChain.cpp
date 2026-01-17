#include <DX3D/Graphics/SwapChain.h>

/**
 * @brief Construct a SwapChain wrapper.
 *
 * Creates a DXGI swap chain for the given native window and size, configures
 * the back buffer format/count and creates the initial render target view.
 *
 * @param desc SwapChain descriptor (window handle, size)
 * @param gdesc GraphicsResourceDesc providing device/factory/logger
 */
dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gdesc) : 
	GraphicsResource(gdesc)
{
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	dxgiDesc.BufferDesc.Width = std::max(1, desc.winSize.width);
	dxgiDesc.BufferDesc.Height = std::max(1, desc.winSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiDesc.BufferCount = 2;  
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	dxgiDesc.Windowed = TRUE;

	dxgiDesc.OutputWindow = static_cast<HWND>(desc.winHandle);
	dxgiDesc.SampleDesc.Count = 1;
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	DX3DGraphicsLogThrowOnFail(m_factory.CreateSwapChain(&m_device, &dxgiDesc, &m_swapChain),
		"CreateSwapChainFailed");

	reloadBuffers();
}

/**
 * @brief Present the current back buffer to the screen.
 *
 * @param vsync If true, present is synchronized to vertical refresh (vsync).
 */
void dx3d::SwapChain::present(bool vsync)
{
	DX3DGraphicsLogThrowOnFail(m_swapChain->Present(vsync, 0),
		"Present failed.");
}

/**
 * @brief (Re)load back-buffer resources after swap chain creation or resize.
 *
 * Gets the back buffer texture from the DXGI swap chain and creates an
 * ID3D11RenderTargetView for it.
 */
void dx3d::SwapChain::reloadBuffers()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{};
	DX3DGraphicsLogThrowOnFail(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)),"");
	DX3DGraphicsLogThrowOnFail(m_device.CreateRenderTargetView(buffer.Get(), nullptr, &m_rtv), 
		"CreateRenderTargetView failed");
}
