#include "Game/Play.h"

#include "header/raymath.h"

#include "Objects/Spaceship.h"

namespace Asteroids
{
	Spaceship player;

	static const int MAX_ASTEROIDS = 10;
	static const int MAX_PROJECTILES = 20;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };
	AsteroidSize asteroidSizes[] = { Small, Medium, Large };

	Projectile static projectiles[MAX_PROJECTILES];

	Vector2 mousePos;
	float angle;
	Rectangle spaceship;
	Vector2 origin;

	static bool isPaused = false;

	void Init()
	{
		Vector2 playerInitPosition = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
		player = InitSpaceship(playerInitPosition);
	}

	void Update(Scenes& scene)
	{
		HideCursor();

		scene = scene; //esto no va despues
		
		UpdateAsteroidArray();

		AsteroidsCreation();

		CheckShottingInput();

		SpaceshipMovement(player, spaceship, origin, mousePos, angle, GetScreenWidth(), GetScreenHeight());

		UpdateProjectileArray();
	}

	void Drawing()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawAsteroidArray();

		DrawCircle(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), 5, BLUE); //cursor

		DrawProjectileArray();

		PlayerDrawing(player, spaceship, angle);

		EndDrawing();
	}

	void AddAsteroid(Vector2 position, AsteroidSize size)
	{
		Vector2 screenCenter = { static_cast<float>(GetScreenHeight() / 2),  static_cast<float>(GetScreenWidth() / 2) };

		Vector2 velocity = Vector2Subtract(screenCenter, position);
		velocity = Vector2Scale(Vector2Normalize(velocity), static_cast<float>(GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED)));

		velocity = Vector2Rotate(velocity, static_cast<float>(GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE)));

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			if (asteroidsArr[i].isActive)
			{
				continue;
			}

			asteroidsArr[i] = InitAsteroid(position, velocity, size);
			break;
		}
	}

	void AsteroidsCreation()
	{
		if (GetTime() > lastAsteroidCreationTime + ASTEROID_DELAY)
		{
			AsteroidSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
			AddAsteroid(GetNextAsteroidPosition(), nextSize);
			lastAsteroidCreationTime = static_cast<float>(GetTime());
		}
	}

	Vector2 GetNextAsteroidPosition()
	{
		float offscreenDist = 128.0f;
		Vector2 result = { -offscreenDist, -offscreenDist };

		if (GetRandomValue(0, 1))
		{
			if (GetRandomValue(0, 1))
			{
				result.y = GetScreenHeight() + offscreenDist;
			}

			result.x = static_cast<float>(GetRandomValue(static_cast<int>(- offscreenDist), GetScreenWidth() + static_cast<int>(offscreenDist)));
		}
		else
		{
			if (GetRandomValue(0, 1))
			{
				result.x = GetScreenWidth() + offscreenDist;
			}

			result.y = static_cast<float>(GetRandomValue(static_cast<int>(-offscreenDist), GetScreenHeight() + static_cast<int>(offscreenDist)));
		}

		return result;
	}

	void UpdateAsteroidArray()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidUpdate(asteroidsArr[i]);
		}
	}

	void DrawAsteroidArray()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidDraw(asteroidsArr[i]);
		}
	}

	void AddProjectile(Vector2 position)
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i].isActive)
			{
				continue;
			}

			projectiles[i] = CreateProjectile(position, player.direction);
			break;
		}
	}

	void CheckShottingInput()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			AddProjectile(Vector2Add(player.position, player.direction));
		}
	}

	void UpdateProjectileArray()
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			ProjectileUpdate(projectiles[i]);
		}
	}

	void DrawProjectileArray()
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			ProjectileDraw(projectiles[i]);
		}
	}

	void RunGame(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			Init();
		}
		
		Update(scene);
		Drawing();
	}

}