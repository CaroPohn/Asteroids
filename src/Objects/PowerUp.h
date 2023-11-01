#pragma once

#include "header/raylib.h"

namespace Asteroids
{
	struct PowerUp
	{
		Vector2 position;
		int maxTime = 10;
		float timer;
		bool isActive;
		float radius = 10.0f;
	};

	void ChooseRandPosition(PowerUp& powerUp); 
	void PowerUpController(PowerUp& powerUp);
	void DrawPowerUp(PowerUp powerUp);
}
