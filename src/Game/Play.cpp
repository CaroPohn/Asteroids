#include "Game/Play.h"

#include "header/raymath.h"

#include "Objects/Spaceship.h"
#include "Game/Pause.h"
#include "Objects/Button.h"

namespace Asteroids
{
	Spaceship player;

	static const int MAX_ASTEROIDS = 8;
	static const int MAX_PROJECTILES = 20;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };
	AsteroidSize asteroidSizes[] = { Small, Medium, Large };

	Projectile static projectiles[MAX_PROJECTILES];

	Vector2 mousePos;
	float angle;
	Rectangle spaceship;
	Vector2 origin;

	static Button pauseButton;

	void Init()
	{
		Vector2 playerInitPosition = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
		player = InitSpaceship(playerInitPosition);

		Texture2D pauseButtonTexture = LoadTexture("assets/pausebutton.png");
		const float buttonWidth = static_cast<float>(pauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(pauseButtonTexture.height);
		float buttonXPos = 20;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(pauseButton, pauseButtonTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			asteroidsArr[i].isActive = false;
		}

		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			projectiles[i].isActive = false;
		}
	}

	void Update(Scenes& scene)
	{
		HideCursor();

		CheckPauseInput(scene);
		
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

		DrawButton(pauseButton);

		EndDrawing();
	}

	void CheckPauseInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), pauseButton))
		{
			pauseButton.isSelected = true;

			if (CheckMouseInput(pauseButton))
			{
				scene = Scenes::Pause;
			}
		}
		else
			pauseButton.isSelected = false;
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

	void RunGame(Scenes& scene, bool isNewScene, Scenes previousScene)
	{
		if (isNewScene && previousScene != Scenes::Pause)
		{
			Init();
		}
		
		Update(scene);
		Drawing();
	}

}