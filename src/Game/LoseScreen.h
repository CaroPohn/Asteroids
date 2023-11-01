#pragma once

#include "Game/Scenes.h"

namespace Asteroids
{
	void InitLoseScreen();
	void DrawLoseScreen();
	void InputLoseScreen(Scenes& scene);
	void RunLoseScreen(Scenes& scene, bool isNewScene);
}
