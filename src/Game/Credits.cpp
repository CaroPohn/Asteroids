#include "Credits.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D creditsTexture;

	static Button backMenuButton;
	Texture2D backMenuButtonTexture;

	void InitCredits()
	{
		creditsTexture = LoadTexture("assets/credits.png");
		backMenuButtonTexture = LoadTexture("assets/backmenubutton.png");

		const float buttonWidth = static_cast<float>(backMenuButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuButton, backMenuButtonTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawCredits()
	{
		BeginDrawing();

		DrawTexture(creditsTexture, 0, 0, RAYWHITE);
		DrawButton(backMenuButton);

		EndDrawing();
	}

	void CreditsInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuButton))
		{
			backMenuButton.isSelected = true;

			if (CheckMouseInput(backMenuButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuButton.isSelected = false;
	}

	void RunCredits(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitCredits();
		}
	
		DrawCredits();
		CreditsInput(scene);
	}
}