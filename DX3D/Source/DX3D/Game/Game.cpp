#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

/**
 * @brief Construct a new Game object.
 *
 * Initializes the Logger, GraphicsEngine and Display. The Logger instance is
 * created and its reference is passed to Base and other subsystems. The
 * GraphicsEngine is created and a Display (window + swapchain) is constructed
 * using the GraphicsDevice provided by the GraphicsEngine.
 *
 * @param desc Game startup configuration (window size, log level, etc.)
 */
dx3d::Game::Game(const GameDesc& desc):
	Base({ *std::make_unique<Logger>(desc.logLevel).release() }), //released to be used by other classes i.e. loosely coupled
	m_loggerPtr(&m_logger) //again make unique
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{ m_logger });
	m_display = std::make_unique<Display>(DisplayDesc{ {m_logger, desc.windowSize}, m_graphicsEngine->getGraphicsDevice()});
	
	DX3DLogInfo("Game initialized.");
}

/**
 * @brief Internal per-frame update hook.
 *
 * Forwards rendering to the GraphicsEngine using the Display's swap chain.
 * This function is intended to be called from the platform-specific run loop.
 */
void dx3d::Game::onInternalUpdate()
{
	m_graphicsEngine->render(m_display->getSwapChain());
}

/**
 * @brief Game destructor.
 *
 * Performs shutdown logging. Smart pointers and RAII handle resource cleanup.
 */
dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}
