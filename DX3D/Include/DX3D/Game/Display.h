#pragma once
#include <DX3D/Window/Window.h>

/**
* @class Display
* @brief 
* - This class is derived from Window class.
* - This class will display actual objects on the screen. 
*/

namespace dx3d
{
	class Display final: public Window
	{
	public:
		explicit Display(const DisplayDesc& desc);

		SwapChain& getSwapChain() noexcept;

		virtual ~Display();

	private:
		SwapChainPtr m_swapChain{};
	};
}

