#include <DX3D/Game/Game.h>
#include <Windows.h>

/**
 * @brief Runs the main Windows message loop for the game.
 *
 * Pumps Windows messages (PeekMessage / TranslateMessage / DispatchMessage)
 * and repeatedly calls the game's internal update function while m_isRunning
 * remains true. When a WM_QUIT message is received the loop terminates.
 */
void dx3d::Game::run()
{
	MSG msg;
	while (m_isRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		onInternalUpdate();
	}
}
