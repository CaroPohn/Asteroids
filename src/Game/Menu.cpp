#include "Game/Menu.h"

namespace Asteroids
{
	Texture2D backTexture;
	Texture2D playButtonTexture;
	Texture2D rulesButtonTexture;
	Texture2D creditsButtonTexture;
	Texture2D exitButtonTexture;

	Texture2D playButtonPressedTexture;
	Texture2D rulesButtonPressedTexture;
	Texture2D creditsButtonPressedTexture;
	Texture2D exitButtonPressedTexture;

	static Button playButton;
	static Button rulesButton;
	static Button creditsButton;
	static Button exitButton;

	Music menuMusic;

	void InitMenu()
	{
		backTexture = LoadTexture("assets/backmenu.png");
		InitMenuButtons();

		menuMusic = LoadMusicStream("assets/menumusic.mp3");
	}

	void InitMenuButtons()
	{
		playButtonTexture = LoadTexture("assets/playbutton.png");
		rulesButtonTexture = LoadTexture("assets/rulesbutton.png");
		creditsButtonTexture = LoadTexture("assets/creditsbutton.png");
		exitButtonTexture = LoadTexture("assets/exitbutton.png");

		playButtonPressedTexture = LoadTexture("assets/playbuttonpressed.png");
		rulesButtonPressedTexture = LoadTexture("assets/rulesbuttonpressed.png");
		creditsButtonPressedTexture = LoadTexture("assets/creditsbuttonpressed.png");
		exitButtonPressedTexture = LoadTexture("assets/exitbuttonpressed.png");

		const float buttonWidth = static_cast<float>(playButtonTexture.width);
		const float buttonHeight = static_cast<float>(playButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth / 2;
		const float buttonDistance = buttonHeight + 15;

		float playButtonY = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight / 2;
		float rulesButtonY = playButtonY + buttonDistance;
		float creditsButtonY = rulesButtonY + buttonDistance;
		float exitButtonY = creditsButtonY + buttonDistance;

		Color buttonColor = RAYWHITE;

		InitButton(playButton, playButtonTexture, playButtonPressedTexture, buttonXPos, playButtonY, buttonWidth, buttonHeight, buttonColor);
		InitButton(rulesButton, rulesButtonTexture, rulesButtonPressedTexture, buttonXPos, rulesButtonY, buttonWidth, buttonHeight, buttonColor);
		InitButton(creditsButton, creditsButtonTexture, creditsButtonPressedTexture, buttonXPos, creditsButtonY, buttonWidth, buttonHeight,buttonColor);
		InitButton(exitButton, exitButtonTexture, exitButtonPressedTexture, buttonXPos, exitButtonY, buttonWidth, buttonHeight, buttonColor);
	}

	void DrawMenu()
	{
		BeginDrawing();
		DrawTexture(backTexture, 0, 0, RAYWHITE);

		DrawButton(playButton);
		DrawButton(rulesButton);
		DrawButton(creditsButton);
		DrawButton(exitButton);
		EndDrawing();
	}

	void MenuInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), playButton))
		{
			playButton.isSelected = true;

			if (CheckMouseInput(playButton))
			{
				StopMusicStream(menuMusic);
				scene = Scenes::Play;
			}
		}
		else
			playButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), rulesButton))
		{
			rulesButton.isSelected = true;
			if (CheckMouseInput(rulesButton))
			{
				scene = Scenes::Rules;
			}
		}
		else
			rulesButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), creditsButton))
		{
			creditsButton.isSelected = true;
			if (CheckMouseInput(creditsButton))
			{
				scene = Scenes::Credits;
			}
		}
		else
			creditsButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), exitButton))
		{
			exitButton.isSelected = true;
			if (CheckMouseInput(exitButton))
			{
				scene = Scenes::Exit;
			}
		}
		else
			exitButton.isSelected = false;
	}

	void UpdateMenuMusic()
	{
		PlayMusicStream(menuMusic);
		UpdateMusicStream(menuMusic);
	}

	void RunMenu(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitMenu();
		}
		
		UpdateMenuMusic();
		MenuInput(scene);
		DrawMenu();
	}

}