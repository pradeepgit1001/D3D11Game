#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/GraphicsDevice.h>

/**
 * @brief Construct a Display.
 *
 * Initializes the Window base class and creates a SwapChain through the
 * provided GraphicsDevice using the native window handle and size.
 *
 * @param desc Display creation parameters (window descriptor + GraphicsDevice)
 */
dx3d::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
	std::clog << "DISPLAY CONSTRUCTOR" << "\n";
	m_swapChain = desc.GraphicsDevice.createSwapChain({ m_handle, m_size });
}

/**
 * @brief Return the underlying SwapChain reference.
 *
 * The Display holds a SwapChainPtr; this function returns a reference to the
 * owned SwapChain for rendering operations.
 *
 * @return SwapChain& reference to the swap chain
 */
dx3d::SwapChain& dx3d::Display::getSwapChain() noexcept
{
	return *m_swapChain;
}

/**
 * @brief Display destructor.
 *
 * Logs shutdown. RAII of smart pointers handles swap chain cleanup.
 */
dx3d::Display::~Display()
{
	std::clog << "display destructor" << "\n";
}