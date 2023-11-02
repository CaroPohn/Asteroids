#pragma once
#include "Game/Scenes.h"

namespace Asteroids
{
	void InitPause();
	void DrawPause();
	void InputPause(Scenes& scene);
	void UpdatePauseMusic();
	void RunPause(Scenes& scene, bool isNewScene);
}
