#include "Pause.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D pauseTexture;

	static Button resumeButton;
	static Button backMenuPauseButton;
	Texture2D backMenuPauseButtonTexture;
	Texture2D backMenuPauseButtonPressedTexture;
	Texture2D resumeButtonTexture;
	Texture2D resumeButtonPressedTexture;

	Music pauseMusic;
	Sound clickPauseButtons;

	static float pauseMusicVolume = 0.2f;

	void InitPause()
	{
		pauseTexture = LoadTexture("assets/pause.png");

		backMenuPauseButtonTexture = LoadTexture("assets/backmenubutton.png");
		resumeButtonTexture = LoadTexture("assets/resumebutton.png");

		backMenuPauseButtonPressedTexture = LoadTexture("assets/backmenubuttonpressed.png");
		resumeButtonPressedTexture = LoadTexture("assets/resumebuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuPauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuPauseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight - 10;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth - 180;
		float resumeButtonXPos = static_cast<float>(GetScreenWidth()) / 2 + buttonWidth + 40;

		pauseMusic = LoadMusicStream("assets/pausemusic.mp3");
		clickPauseButtons = LoadSound("assets/button.mp3");

		InitButton(backMenuPauseButton, backMenuPauseButtonTexture, backMenuPauseButtonPressedTexture, backMenuPausebuttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(resumeButton, resumeButtonTexture, resumeButtonPressedTexture, resumeButtonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawPause()
	{
		BeginDrawing();

		DrawTexture(pauseTexture, 0, 0, RAYWHITE);

		DrawButton(backMenuPauseButton);
		DrawButton(resumeButton);

		EndDrawing();
	}

	void InputPause(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuPauseButton))
		{
			backMenuPauseButton.isSelected = true;

			if (CheckMouseInput(backMenuPauseButton))
			{
				PlaySound(clickPauseButtons);
				StopMusicStream(pauseMusic);
				scene = Scenes::Menu;
			}
		}
		else
			backMenuPauseButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), resumeButton))
		{
			resumeButton.isSelected = true;

			if (CheckMouseInput(resumeButton))
			{
				PlaySound(clickPauseButtons);
				StopMusicStream(pauseMusic);
				scene = Scenes::Play;
			}
		}
		else
			resumeButton.isSelected = false;
	}

	void UpdatePauseMusic()
	{
		SetMusicVolume(pauseMusic, pauseMusicVolume);
		PlayMusicStream(pauseMusic);
		UpdateMusicStream(pauseMusic);
	}

	void RunPause(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitPause();
		}

		ShowCursor();

		UpdatePauseMusic();
		DrawPause();
		InputPause(scene);
	}

}