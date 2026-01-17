#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/GraphicsDevice.h>

dx3d::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
	std::clog << "DISPLAY CONSTRUCTOR" << "\n";
	m_swapChain = desc.GraphicsDevice.createSwapChain({ m_handle, m_size });
}

dx3d::SwapChain& dx3d::Display::getSwapChain() noexcept
{
	return *m_swapChain;
}

dx3d::Display::~Display()
{
	std::clog << "display destructor" << "\n";
}