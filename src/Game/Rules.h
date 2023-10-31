#pragma once
#include "Scenes.h"

namespace Asteroids
{
	void InitRules();
	void DrawRules();
	void RulesInput(Scenes& scene);
	void RunRules(Scenes& scene, bool isNewScene);
}
