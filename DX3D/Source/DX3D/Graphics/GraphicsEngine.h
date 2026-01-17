#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d
{
	class GraphicsEngine final: public Base //final is added to stop further derivation of the GraphicsEngine class
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;

		void render(SwapChain& swapChain);
	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
	};
}

