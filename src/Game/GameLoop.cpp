#include "GameLoop.h"

#include "header/raylib.h"

#include "Scenes.h"
#include "Game/Menu.h"
#include "Play.h"
#include "Game/Credits.h"

namespace Asteroids
{
	static Scenes scene;

	void GameLoop()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Asteroids");
		SetExitKey(NULL);

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
				RunMenu(scene, isNewScene);
				break;

			case Scenes::Play:
				RunGame(scene, isNewScene);
				break;

			case Scenes::Pause:
				break;

			case Scenes::Rules:
				break;

			case Scenes::Credits:
				RunCredits(scene, isNewScene);
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