#include "LoseScreen.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D loseScreenTexture;

	static Button playAgainButton;
	static Button backMenuLoseButton;

	Texture2D backMenuLoseButtonTexture;
	Texture2D playAgainButtonTexture;

	void InitLoseScreen()
	{
		loseScreenTexture = LoadTexture("assets/losescreen.png");

		backMenuLoseButtonTexture = LoadTexture("assets/backmenubutton.png");
		playAgainButtonTexture = LoadTexture("assets/playagain.png");

		const float buttonWidth = static_cast<float>(backMenuLoseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuLoseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight - 10;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth - 180;
		float playAgainButtonXPos = static_cast<float>(GetScreenWidth()) / 2 + buttonWidth + 40;

		InitButton(backMenuLoseButton, backMenuLoseButtonTexture, backMenuPausebuttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(playAgainButton, playAgainButtonTexture, playAgainButtonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawLoseScreen()
	{
		BeginDrawing();

		DrawTexture(loseScreenTexture, 0, 0, RAYWHITE);

		DrawButton(backMenuLoseButton);
		DrawButton(playAgainButton);

		EndDrawing();
	}

	void InputLoseScreen(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuLoseButton))
		{
			backMenuLoseButton.isSelected = true;

			if (CheckMouseInput(backMenuLoseButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuLoseButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), playAgainButton))
		{
			playAgainButton.isSelected = true;

			if (CheckMouseInput(playAgainButton))
			{
				scene = Scenes::Play;
			}
		}
		else
			playAgainButton.isSelected = false;
	}

	void RunLoseScreen(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitLoseScreen();
		}

		ShowCursor();

		DrawLoseScreen();
		InputLoseScreen(scene);
	}

}