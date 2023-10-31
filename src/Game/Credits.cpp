#include "Credits.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D creditsTexture;

	static Button backMenuCreditsButton;
	Texture2D backMenuCreditsButtonTexture;

	void InitCredits()
	{
		creditsTexture = LoadTexture("assets/credits.png");
		backMenuCreditsButtonTexture = LoadTexture("assets/backmenubutton.png");

		const float buttonWidth = static_cast<float>(backMenuCreditsButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuCreditsButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuCreditsButton, backMenuCreditsButtonTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawCredits()
	{
		BeginDrawing();

		DrawTexture(creditsTexture, 0, 0, RAYWHITE);
		DrawButton(backMenuCreditsButton);

		EndDrawing();
	}

	void CreditsInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuCreditsButton))
		{
			backMenuCreditsButton.isSelected = true;

			if (CheckMouseInput(backMenuCreditsButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuCreditsButton.isSelected = false;
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