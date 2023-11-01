#include "PowerUp.h"

namespace Asteroids
{
	void ChooseRandPosition(PowerUp& powerUp)
	{
		const int maxX = GetScreenWidth();
		const int maxY = GetScreenHeight();

		powerUp.position = { static_cast<float>(GetRandomValue(0, maxX)), static_cast<float>(GetRandomValue(0, maxY)) };
	}

	void PowerUpController(PowerUp& powerUp)
	{
		powerUp.timer -= GetFrameTime();

		if (powerUp.timer <= 0)
		{
			ChooseRandPosition(powerUp);
			powerUp.timer = static_cast<float>(powerUp.maxTime);
			powerUp.isActive = true;
		}
	}

	void DrawPowerUp(PowerUp powerUp)
	{
		if(powerUp.isActive)
		{
			DrawRectangle(static_cast<int>(powerUp.position.x), static_cast<int>(powerUp.position.y), 10, 10, PINK);
		}
	}
}