#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

/**
 * @brief Construct a DeviceContext (deferred).
 *
 * Creates a deferred ID3D11DeviceContext from the device stored in GraphicsResource.
 * Deferred contexts are used to record command lists on worker threads.
 *
 * @param gDesc GraphicsResourceDesc providing device/factory/logger
 */
dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc): GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferredContext failed");
}

/**
 * @brief Clear the swap chain back buffer and bind it as the current render target.
 *
 * Clears the render target view with the specified color and sets it on the
 * output-merger stage of the deferred context.
 *
 * @param swapChain SwapChain that owns the render target view
 * @param color RGBA clear color
 */
void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	f32 fColor[] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(swapChain.m_rtv.Get(), fColor);
	m_context->OMSetRenderTargets(1, &rtv, nullptr);
}
