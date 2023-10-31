#include "Rules.h"

#include "header/raylib.h"

#include "Objects/Button.h"

namespace Asteroids
{
	Texture2D rulesTexture;

	static Button backMenuRulesButton;
	Texture2D backMenuRulesButtonTexture;

	void InitRules()
	{
		rulesTexture = LoadTexture("assets/rules.png");
		backMenuRulesButtonTexture = LoadTexture("assets/backmenubutton.png");

		const float buttonWidth = static_cast<float>(backMenuRulesButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuRulesButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuRulesButton, backMenuRulesButtonTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawRules()
	{
		BeginDrawing();

		DrawTexture(rulesTexture, 0, 0, RAYWHITE);
		DrawButton(backMenuRulesButton);

		EndDrawing();
	}

	void RulesInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuRulesButton))
		{
			backMenuRulesButton.isSelected = true;

			if (CheckMouseInput(backMenuRulesButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuRulesButton.isSelected = false;
	}

	void RunRules(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitRules();
		}

		DrawRules();
		RulesInput(scene);
	}
}