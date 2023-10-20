#pragma once
#include "Objects/Button.h"
#include "Game/Scenes.h"

namespace Asteroids
{
	void InitMenu();
	void InitMenuButtons();
	void DrawMenu();
	void MenuInput(Scenes& scene);
	void RunMenu(Scenes& scene, bool isNewScene);
}
