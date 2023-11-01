#include "SpecialEnemy.h"

#include "header/raymath.h"

namespace Asteroids
{
	SpecialEnemy InitSpecialEnemy(Vector2 position, Spaceship player)
	{
		SpecialEnemy specialEnemy;

		specialEnemy.position = position;
		specialEnemy.direction = player.direction;
		specialEnemy.isActive = true;

		specialEnemy.creationTime = static_cast<float>(GetFrameTime());

		return specialEnemy;
	}

	void SpecialEnemyUpdate(SpecialEnemy& specialEnemy, Spaceship player)
	{
		SpecialEnemyReturnToScreen(specialEnemy, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));

		specialEnemy.position = Vector2Add(specialEnemy.position, Vector2Scale(Vector2Multiply(specialEnemy.velocity, specialEnemy.direction), GetFrameTime()));
		specialEnemy.direction = Vector2Normalize(Vector2Subtract(player.position, specialEnemy.position));
	}

	void SpecialEnemyDraw(SpecialEnemy specialEnemy)
	{
		DrawCircle(static_cast<int>(specialEnemy.position.x), static_cast<int>(specialEnemy.position.y), specialEnemy.radius, GREEN);
	}

	void SpecialEnemyReturnToScreen(SpecialEnemy& specialEnemy, float screenWidth, float screenHeight)
	{
		if (specialEnemy.position.x + specialEnemy.velocity.x * GetFrameTime() > screenWidth)
		{
			specialEnemy.position.x = 0;
			if (specialEnemy.velocity.y > 0)
			{
				if (specialEnemy.position.y > screenHeight / 2)
					specialEnemy.position.y = screenHeight - specialEnemy.position.y;
			}
			else if (specialEnemy.velocity.y < 0)
			{
				if (specialEnemy.position.y < screenHeight / 2)
					specialEnemy.position.y = screenHeight - specialEnemy.position.y;
			}
		}
		else if (specialEnemy.position.x + specialEnemy.velocity.x * GetFrameTime() < 0)
		{
			specialEnemy.position.x = static_cast<float>(screenWidth);
			if (specialEnemy.velocity.y > 0)
			{
				if (specialEnemy.position.y > screenHeight / 2)
					specialEnemy.position.y = screenHeight - specialEnemy.position.y;
			}
			else if (specialEnemy.velocity.y < 0)
			{
				if (specialEnemy.position.y < screenHeight / 2)
					specialEnemy.position.y = screenHeight - specialEnemy.position.y;
			}
		}

		if (specialEnemy.position.y + specialEnemy.velocity.y * GetFrameTime() > screenHeight)
		{
			specialEnemy.position.y = 0;
			if (specialEnemy.velocity.x > 0)
			{
				if (specialEnemy.position.x > screenWidth / 2)
					specialEnemy.position.x = screenWidth - specialEnemy.position.x;
			}
			else if (specialEnemy.velocity.x < 0)
			{
				if (specialEnemy.position.x < screenWidth / 2)
					specialEnemy.position.x = screenWidth - specialEnemy.position.x;
			}
		}
		else if (specialEnemy.position.y + specialEnemy.velocity.y * GetFrameTime() < 0)
		{
			specialEnemy.position.y = static_cast<float>(screenHeight);
			if (specialEnemy.velocity.x > 0)
			{
				if (specialEnemy.position.x > screenWidth / 2)
					specialEnemy.position.x = screenWidth - specialEnemy.position.x;
			}
			else if (specialEnemy.velocity.x < 0)
			{
				if (specialEnemy.position.x < screenWidth / 2)
					specialEnemy.position.x = screenWidth - specialEnemy.position.x;
			}
		}
	}
}