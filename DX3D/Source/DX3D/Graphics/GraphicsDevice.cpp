#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>

using namespace dx3d;

/**
 * @brief Construct the GraphicsDevice and initialize D3D11.
 *
 * Creates an ID3D11Device and immediate context via D3D11CreateDevice, then
 * queries DXGI interfaces (IDXGIDevice, IDXGIAdapter, IDXGIFactory) required
 * for swap chain creation and other DXGI operations.
 *
 * Throws on failure via DX3DGraphicsLogThrowOnFail.
 *
 * @param desc GraphicsDevice initialization descriptor (contains Logger)
 */
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

/**
 * @brief GraphicsDevice destructor.
 *
 * Logs destruction. COM smart pointers (WRL::ComPtr) handle resource release.
 */
dx3d::GraphicsDevice::~GraphicsDevice()
{
	std::clog << "GraphicsDevice destructor" << "\n";
}

/**
 * @brief Create and return a SwapChain for the provided descriptor.
 *
 * @param desc SwapChain creation parameters (native window handle, size)
 * @return SwapChainPtr shared pointer to the created swap chain
 */
SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

/**
 * @brief Create a DeviceContext (deferred context) associated with this device.
 *
 * @return DeviceContextPtr shared pointer to a DeviceContext for recording commands
 */
DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

/**
 * @brief Finish a deferred command list and execute it on the immediate context.
 *
 * Calls FinishCommandList on the deferred context to obtain an ID3D11CommandList,
 * then executes it on the immediate context.
 *
 * @param context DeviceContext containing the deferred context to finish
 */
void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList failed.");
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

/**
 * @brief Build a GraphicsResourceDesc used to construct graphics resources.
 *
 * Returns a descriptor bundling the logger, shared GraphicsDevice pointer,
 * and references to the ID3D11Device and IDXGIFactory.
 *
 * @return GraphicsResourceDesc descriptor for resource construction
 */
GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get()};
}
