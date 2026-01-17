#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

/**
 * @brief Construct the GraphicsEngine.
 *
 * Creates the GraphicsDevice and a DeviceContext used for recording GPU commands.
 * The GraphicsDevice is created with the engine's logger.
 *
 * @param desc Graphics engine initialization parameters
 */
dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	std::clog << "GRAPHICSENGINE CONSTRUCTOR" << "\n";
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_logger });
	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();
}

/**
 * @brief GraphicsEngine destructor.
 *
 * Logs shutdown. Smart pointers clean up graphics resources.
 */
dx3d::GraphicsEngine::~GraphicsEngine()
{
	std::clog << "graphicsEngine destructor" << "\n";
}

/**
 * @brief Return the owned GraphicsDevice.
 *
 * @return GraphicsDevice& reference to the graphics device
 */
GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

/**
 * @brief Render a single frame using the provided swap chain.
 *
 * This function:
 *  - Clears and binds the swap chain's back buffer using the device context,
 *  - Finishes any recorded deferred command list and executes it on the immediate context,
 *  - Presents the swap chain.
 *
 * @param swapChain SwapChain used for rendering/presentation
 */
void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 1, 0, 0, 1 });

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
