#include "Game/Menu.h"

Texture2D backTexture;
Texture2D playButtonTexture;
Texture2D rulesButtonTexture;
Texture2D creditsButtonTexture;
Texture2D exitButtonTexture;

static Button playButton;
static Button rulesButton;
static Button creditsButton;
static Button exitButton;

void InitMenu()
{
	backTexture = LoadTexture("assets/backmenu.png");
	InitMenuButtons();
}

void InitMenuButtons()
{
	playButtonTexture = LoadTexture("assets/playbutton.png");
	rulesButtonTexture = LoadTexture("assets/rulesbutton.png");
	creditsButtonTexture = LoadTexture("assets/creditsbutton.png");
	exitButtonTexture = LoadTexture("assets/exitbutton.png");

	const float buttonWidth = 250;
	const float buttonHeight = 110;
	float buttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth / 2;
	const float buttonDistance = buttonHeight + 20;

	float exitButtonY = static_cast<float>(GetScreenHeight()) - buttonHeight - 50;
	float creditsButtonY = exitButtonY - buttonDistance;
	float rulesButtonY = creditsButtonY - buttonDistance;
	float playButtonY = rulesButtonY - buttonDistance;
	Color buttonColor = RAYWHITE;

	InitButton(playButton, playButtonTexture, buttonXPos, playButtonY, buttonWidth, buttonHeight, buttonColor);
	InitButton(rulesButton, rulesButtonTexture, buttonXPos, rulesButtonY, buttonWidth, buttonHeight, buttonColor);
	InitButton(creditsButton, creditsButtonTexture, buttonXPos, creditsButtonY, buttonWidth, buttonHeight,buttonColor);
	InitButton(exitButton, exitButtonTexture, buttonXPos, exitButtonY, buttonWidth, buttonHeight, buttonColor);
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

void RunMenu(Scenes& scene, bool isNewScene)
{
	if (isNewScene)
	{
		InitMenu();
	}

	MenuInput(scene);
	DrawMenu();
}