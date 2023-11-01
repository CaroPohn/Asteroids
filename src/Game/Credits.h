#pragma once
#include "Scenes.h"

namespace Asteroids
{
	void InitCredits();
	void DrawCredits();
	void CreditsInput(Scenes& scene);
	void UpdateCreditsMusic();
	void RunCredits(Scenes& scene, bool isNewScene);
}
