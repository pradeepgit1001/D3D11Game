#include <DX3D/All..h>

int main()
{
	try
	{
		dx3d::Game game({ {1280,720}, dx3d::Logger::LogLevel::Info }); //helps to create the window and change the status flag m_isRunning to true;
		game.run();
	}
	catch (const std::runtime_error&)
	{
		return EXIT_FAILURE;
	}
	catch (const std::exception&)
	{
		return EXIT_FAILURE;
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}