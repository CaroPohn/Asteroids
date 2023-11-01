#include "GameLoop.h"

#include "header/raylib.h"

#include "Scenes.h"
#include "Game/Menu.h"
#include "Play.h"
#include "Game/Credits.h"
#include "Game/Rules.h"
#include "Game/Pause.h"
#include "LoseScreen.h"

namespace Asteroids
{
	static Scenes scene;

	void GameLoop()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Asteroids");
		SetExitKey(NULL);
		InitAudioDevice();

		scene = Scenes::Menu;
		Scenes previousScene = Scenes::Exit;
		bool isNewScene;
		Scenes auxPrevScene = Scenes::Exit;

		do
		{
			isNewScene = (scene != previousScene);
			previousScene = scene;

			switch (scene)
			{
			case Scenes::Menu:
				RunMenu(scene, isNewScene);
				auxPrevScene = Scenes::Menu;
				break;

			case Scenes::Play:
				RunGame(scene, isNewScene, auxPrevScene);
				auxPrevScene = Scenes::Play;
				break;

			case Scenes::Pause:
				RunPause(scene, isNewScene);
				auxPrevScene = Scenes::Pause;
				break;

			case Scenes::Rules:
				RunRules(scene, isNewScene);
				auxPrevScene = Scenes::Rules;
				break;

			case Scenes::Credits:
				RunCredits(scene, isNewScene);
				auxPrevScene = Scenes::Credits;
				break;

			case Scenes::LoseScreen:
				RunLoseScreen(scene, isNewScene);
				break;

			case Scenes::Exit:
				break;

			default:
				break;
			}
		} while (!WindowShouldClose() && scene != Scenes::Exit);

		CloseAudioDevice();
		CloseWindow();
	}
}