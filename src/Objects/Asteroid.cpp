#include "Asteroid.h"

#include <iostream>
#include "header/raymath.h"

namespace Asteroids
{
	Asteroid InitAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
	{
		Asteroid asteroid;

		Texture2D smallTexture = LoadTexture("assets/catsoul.png");
		Texture2D mediumTexture = LoadTexture("assets/catghost.png");
		Texture2D largeTexture = LoadTexture("assets/cattomb.png");

		asteroid.isActive = true;
		asteroid.size = size;

		if (asteroid.size == Small)
		{
			asteroid.asteroidRadius = 20;
			asteroid.texture = smallTexture;
		}
		else if (asteroid.size == Medium)
		{
			asteroid.asteroidRadius = 30;
			asteroid.texture = mediumTexture;
		}
		else if (asteroid.size == Large)
		{
			asteroid.asteroidRadius = 46;
			asteroid.texture = largeTexture;
		}

		asteroid.position = position;
		asteroid.velocity = velocity;
		asteroid.rotation = static_cast<float>(rand() % 360);
		asteroid.rotationSpeed = static_cast<float>(GetRandomValue(MIN_ROT_SPEED, MAX_ROT_SPEED));
		asteroid.creationTime = static_cast<float>(GetFrameTime());

		return asteroid;
	}

	void AsteroidUpdate(Asteroid& asteroid)
	{
		if (!asteroid.isActive)
		{
			return;
		}

		AsteroidsReturnToScreen(asteroid, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
		
		asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, GetFrameTime()));
		asteroid.rotation += asteroid.rotationSpeed * GetFrameTime();
	}

	void AsteroidDraw(Asteroid& asteroid)
	{
		if (!asteroid.isActive)
		{
			return;
		}

		float asteroidScale = 0.25f;

		asteroid.dest.x = asteroid.position.x;
		asteroid.dest.y = asteroid.position.y;
		asteroid.dest.width = static_cast<float>(asteroid.texture.width) * asteroidScale;
		asteroid.dest.height = static_cast<float>(asteroid.texture.height) * asteroidScale;
		
		asteroid.source.width = static_cast<float>(asteroid.texture.width);
		asteroid.source.height = static_cast<float>(asteroid.texture.height);
		asteroid.source.x = 0;
		asteroid.source.y = 0;

		Vector2 origin = { asteroid.dest.width / 2, asteroid.dest.height / 2 };

		DrawCircleLines(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.asteroidRadius, WHITE);
		DrawTexturePro(asteroid.texture, asteroid.source, asteroid.dest, origin, asteroid.rotation, RAYWHITE);
	}

	void AsteroidsReturnToScreen(Asteroid& asteroid, float screenWidth, float screenHeight)
	{
		if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() > screenWidth)
		{
			asteroid.position.x = 0;
			if (asteroid.velocity.y > 0)
			{
				if (asteroid.position.y > screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
			else if (asteroid.velocity.y < 0)
			{
				if (asteroid.position.y < screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
		}
		else if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() < 0)
		{
			asteroid.position.x = screenWidth;
			if (asteroid.velocity.y > 0)
			{
				if (asteroid.position.y > screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
			else if (asteroid.velocity.y < 0)
			{
				if (asteroid.position.y < screenHeight / 2)
					asteroid.position.y = screenHeight - asteroid.position.y;
			}
		}

		if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() > screenHeight)
		{
			asteroid.position.y = 0;
			if (asteroid.velocity.x > 0)
			{
				if (asteroid.position.x > screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
			else if (asteroid.velocity.x < 0)
			{
				if (asteroid.position.x < screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
		}
		else if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() < 0)
		{
			asteroid.position.y = screenHeight;
			if (asteroid.velocity.x > 0)
			{
				if (asteroid.position.x > screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
			else if (asteroid.velocity.x < 0)
			{
				if (asteroid.position.x < screenWidth / 2)
					asteroid.position.x = screenWidth - asteroid.position.x;
			}
		}
	}
}