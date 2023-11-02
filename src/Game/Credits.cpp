#include "Credits.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D creditsTexture;

	static Button backMenuCreditsButton;
	Texture2D backMenuCreditsButtonTexture;
	Texture2D backMenuCreditsButtonPressedTexture;

	Music creditsMusic;
	Sound clickCreditButton;

	static float creditsMusicVolume = 0.3f;

	void InitCredits()
	{
		creditsTexture = LoadTexture("assets/credits.png");
		backMenuCreditsButtonTexture = LoadTexture("assets/backmenubutton.png");
		backMenuCreditsButtonPressedTexture = LoadTexture("assets/backmenubuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuCreditsButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuCreditsButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuCreditsButton, backMenuCreditsButtonTexture, backMenuCreditsButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);

		creditsMusic = LoadMusicStream("assets/secondmenumusic.mp3");
		clickCreditButton = LoadSound("assets/button.mp3");
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
				PlaySound(clickCreditButton);
				StopMusicStream(creditsMusic);
				scene = Scenes::Menu;
			}
		}
		else
			backMenuCreditsButton.isSelected = false;
	}

	void UpdateCreditsMusic()
	{
		SetMusicVolume(creditsMusic, creditsMusicVolume);
		PlayMusicStream(creditsMusic);
		UpdateMusicStream(creditsMusic);
	}

	void RunCredits(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitCredits();
		}
	
		UpdateCreditsMusic();
		DrawCredits();
		CreditsInput(scene);
	}
}