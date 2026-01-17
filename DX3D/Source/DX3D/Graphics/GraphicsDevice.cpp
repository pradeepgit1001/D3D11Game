#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>

using namespace dx3d;

dx3d::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc): Base(desc.base)
{
	std::clog << "GraphicsDevice CONSTRUCTOR" << "\n";
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	const D3D_FEATURE_LEVEL requestedLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	DX3DGraphicsLogThrowOnFail(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&featureLevel,
		&m_d3dContext
		),
		"Direct3d11 initialization failed.");

	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),"QueryInterface failed to retrieve IDXGIDevice");
	DX3DGraphicsLogThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)), "QueryInterface failed to retrieve IDXGIAdapter");
	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)), "QueryInterface failed to retrieve IDXGIFactory");
}

dx3d::GraphicsDevice::~GraphicsDevice()
{
	std::clog << "GraphicsDevice destructor" << "\n";
}

SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList failed.");
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get()};
}
