#pragma once

#include "Game/Scenes.h"

namespace Asteroids
{
	void InitLoseScreen();
	void DrawLoseScreen();
	void InputLoseScreen(Scenes& scene);
	void UpdateLoseScreenMusic();
	void RunLoseScreen(Scenes& scene, bool isNewScene);
}
