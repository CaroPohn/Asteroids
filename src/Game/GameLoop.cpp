#include "GameLoop.h"

#include "header/raylib.h"

#include "Scenes.h"

static Scenes scene;

namespace Asteroids
{
	void GameLoop()
	{
		const int screenWidth = 1200;
		const int screenHeight = 900;

		InitWindow(screenWidth, screenHeight, "Asteroids");

		scene = Scenes::Menu;
		Scenes previousScene = Scenes::Exit;
		bool isNewScene;

		do
		{
			isNewScene = (scene != previousScene);
			previousScene = scene;

			switch (scene)
			{
			case Scenes::Menu:
				break;

			case Scenes::Play:
				break;

			case Scenes::Pause:
				break;

			case Scenes::Rules:
				break;

			case Scenes::Credits:
				break;

			case Scenes::WinScreen:
				break;

			case Scenes::LoseScreen:
				break;

			case Scenes::Exit:
				break;

			default:
				break;
			}
		} while (!WindowShouldClose() && scene != Scenes::Exit);

		CloseWindow();
	}
}