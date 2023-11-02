#include "Game/Play.h"

#include "header/raymath.h"

#include "Objects/Spaceship.h"
#include "Game/Pause.h"
#include "Objects/Button.h"
#include "Objects/SpecialEnemy.h"
#include "Objects/PowerUp.h"

namespace Asteroids
{
	Texture2D gameBackground;

	Spaceship player;
	static float invulnerabilityTimer = 0;
	static int asteroidsCounter = 0;

	SpecialEnemy specialEnemy;
	PowerUp powerUp;

	static const int MAX_ASTEROIDS = 16;
	static const int MAX_PROJECTILES = 20;

	Asteroid static asteroidsArr[MAX_ASTEROIDS] = { 0 };
	AsteroidSize asteroidSizes[] = { Small, Medium, Large };

	Projectile static projectiles[MAX_PROJECTILES];

	Vector2 mousePos;
	float angle;
	Rectangle spaceship;
	Vector2 origin;

	static Button pauseButton;
	static Button pauseButtonPressed;

	Sound pauseClick;

	Sound shoot;
	static float shootVolume = 0.2f;

	Sound playerDamaged;
	Sound specialEnemyDamaged;
	static float specialEnemyVolume = 0.2f;

	Sound breakAsteroid;
	static float asteroidVolume = 0.2f;

	Sound powerUpSound;

	Music gameMusic;

	static float gameMusicVolume = 0.1f;

	void Init()
	{
		Vector2 playerInitPosition = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
		player = InitSpaceship(playerInitPosition);

		gameBackground = LoadTexture("assets/gameback.png");

		Texture2D pauseButtonTexture = LoadTexture("assets/pausebutton.png");
		Texture2D pauseButtonPressedTexture = LoadTexture("assets/pausebuttonpressed.png");

		const float buttonWidth = static_cast<float>(pauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(pauseButtonTexture.height);
		float buttonXPos = 20;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		gameMusic = LoadMusicStream("assets/gameplaymusic.mp3");

		pauseClick = LoadSound("assets/button.mp3");
		shoot = LoadSound("assets/shooting.mp3");
		playerDamaged = LoadSound("assets/playerhurt.mp3");
		specialEnemyDamaged = LoadSound("assets/specialenemy.mp3");
		breakAsteroid = LoadSound("assets/asteroidbreak.mp3");
		powerUpSound = LoadSound("assets/powerup.mp3");

		specialEnemy = InitSpecialEnemy(GetNextPosition(), player);

		InitButton(pauseButton, pauseButtonTexture, pauseButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			asteroidsArr[i].isActive = false;
			asteroidsArr[i].size = Large;
		}

		asteroidsCounter = 0;

		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			projectiles[i].isActive = false;
		}
	}

	void Update(Scenes& scene)
	{
		HideCursor();

		UpdateGameplayMusic();

		CheckPauseInput(scene);

		UpdateAsteroidArray();

		AsteroidsCreation();

		CheckShottingInput();

		SpaceshipMovement(player, spaceship, origin, mousePos, angle, GetScreenWidth(), GetScreenHeight());

		UpdateProjectileArray();

		CheckGameCollisions();

		SpecialEnemyUpdate(specialEnemy, player);

		PowerUpController(powerUp);

		PlayerLoses(scene);
	}

	void UpdateGameplayMusic()
	{
		SetMusicVolume(gameMusic, gameMusicVolume);
		PlayMusicStream(gameMusic);
		UpdateMusicStream(gameMusic);
	}

	void Drawing()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(gameBackground, 0, 0, RAYWHITE);

		DrawAsteroidArray();

		DrawCircle(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), 5, BLUE); //cursor

		DrawProjectileArray();

		SpecialEnemyDraw(specialEnemy);

		DrawPowerUp(powerUp);

		PlayerDrawing(player, spaceship, angle);

		DrawButton(pauseButton);

		DrawScore();

		DrawLives(player);

		EndDrawing();
	}

	void DrawScore()
	{
		int posX = 10;
		int posY = 10;
		int fontSize = 35;
		int xWordDistance = 120;
		Color color = RAYWHITE;

		DrawText("Points: ", posX, posY, fontSize, color);
		DrawText(TextFormat("%i", player.points), posX + xWordDistance, posY, fontSize, color);
	}

	void CheckPauseInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), pauseButton))
		{
			pauseButton.isSelected = true;

			if (CheckMouseInput(pauseButton))
			{
				PlaySound(pauseClick);
				scene = Scenes::Pause;
			}
		}
		else
			pauseButton.isSelected = false;
	}

	void AddAsteroid(Vector2 position, AsteroidSize size, bool isSpawned)
	{
		Vector2 screenCenter = { static_cast<float>(GetScreenHeight() / 2),  static_cast<float>(GetScreenWidth() / 2) };

		Vector2 velocity = Vector2Subtract(screenCenter, position);

		velocity = Vector2Scale(Vector2Normalize(velocity), static_cast<float>(GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED)));

		if (isSpawned)
		{
			velocity = Vector2Rotate(velocity, static_cast<float>(GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE)));
		}
		else
		{
			velocity = Vector2Rotate(velocity, static_cast<float>(GetRandomValue(0, 359)));
		}

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			if (asteroidsArr[i].isActive) continue;

			asteroidsArr[i] = InitAsteroid(position, velocity, size);
			asteroidsCounter++;
			break;
		}
	}

	void AsteroidsCreation()
	{
		if (GetTime() > lastAsteroidCreationTime + ASTEROID_DELAY && asteroidsCounter < MAX_ASTEROIDS / 4)
		{
			AsteroidSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
			AddAsteroid(GetNextPosition(), nextSize, true);
			lastAsteroidCreationTime = static_cast<float>(GetTime());
		}
	}

	Vector2 GetNextPosition()
	{
		float offscreenDist = 128.0f;
		Vector2 result = { -offscreenDist, -offscreenDist };

		if (GetRandomValue(0, 1))
		{
			if (GetRandomValue(0, 1))
			{
				result.y = GetScreenHeight() + offscreenDist;
			}

			result.x = static_cast<float>(GetRandomValue(static_cast<int>(-offscreenDist), GetScreenWidth() + static_cast<int>(offscreenDist)));
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
			if (projectiles[i].isActive) continue;

			projectiles[i] = CreateProjectile(position, player.direction);
			break;
		}
	}

	void CheckShottingInput()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			SetSoundVolume(shoot, 0.2f);
			PlaySound(shoot);
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

	bool CircleCircleCollision(float circle1x, float circle1y, float circle1r, float circle2x, float circle2y, float circle2r)
	{
		float distX = circle1x - circle2x;
		float distY = circle1y - circle2y;
		float distance = static_cast<float>(sqrt((distX * distX) + (distY * distY)));

		if (distance <= circle1r + circle2r)
		{
			return true;
		}

		return false;
	}

	void CheckGameCollisions()
	{
		if (invulnerabilityTimer <= 0)
		{
			AsteroidPlayerCollision();
			SpecialEnemyPlayerCollision();
		}
		else
		{
			invulnerabilityTimer -= GetFrameTime();
		}

		BulletAsteroidCollision();
		SpecialEnemyBulletCollision();
		PlayerPowerUpCollision();
	}

	void AsteroidPlayerCollision()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			if (!asteroidsArr[i].isActive) continue;

			if (CircleCircleCollision(player.position.x, player.position.y, player.radius, asteroidsArr[i].position.x, asteroidsArr[i].position.y, asteroidsArr[i].asteroidRadius))
			{
				PlaySound(playerDamaged);
				player.lives--;
				invulnerabilityTimer = 1.0f;
			}
		}

		if (player.lives <= 0)
		{
			player.isAlive = false;
		}

	}

	void ReduceAsteroidSize(Asteroid& asteroid)
	{
		asteroid.isActive = false;
		asteroidsCounter--;
		player.points += 10;

		switch (asteroid.size)
		{
		case Large:
			AddAsteroid(asteroid.position, Medium, false);
			AddAsteroid(asteroid.position, Medium, false);
			break;

		case Medium:
			AddAsteroid(asteroid.position, Small, false);
			AddAsteroid(asteroid.position, Small, false);
			break;

		case Small:
			asteroid.isActive = false;
			asteroidsCounter--;
			break;
		}
	}

	void BulletAsteroidCollision()
	{
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			for (int j = 0; j < MAX_PROJECTILES; j++)
			{
				if (!asteroidsArr[i].isActive || !projectiles[j].isActive) continue;

				if (CircleCircleCollision(projectiles[j].position.x, projectiles[j].position.y, projectiles[j].radius, asteroidsArr[i].position.x, asteroidsArr[i].position.y, asteroidsArr[i].asteroidRadius))
				{
					SetSoundVolume(breakAsteroid, asteroidVolume);
					PlaySound(breakAsteroid);
					ReduceAsteroidSize(asteroidsArr[i]);
					projectiles[j].isActive = false;
				}
			}
		}
	}

	void SpecialEnemyBulletCollision()
	{
		for (int i = 0; i < MAX_PROJECTILES; i++) 
		{
			if (!projectiles[i].isActive) continue;

			if (CircleCircleCollision(projectiles[i].position.x, projectiles[i].position.y, projectiles[i].radius, specialEnemy.position.x, specialEnemy.position.y, specialEnemy.radius))
			{
				specialEnemy.lives--;
				SetSoundVolume(specialEnemyDamaged, specialEnemyVolume);
				PlaySound(specialEnemyDamaged);

				if (specialEnemy.lives <= 0)
				{
					player.points += 30;
					specialEnemy.isActive = false;
					specialEnemy = InitSpecialEnemy(GetNextPosition(), player);
				}

				projectiles[i].isActive = false;
			}
		}
	}

	void SpecialEnemyPlayerCollision()
	{
		if (CircleCircleCollision(player.position.x, player.position.y, player.radius, specialEnemy.position.x, specialEnemy.position.y, specialEnemy.radius))
		{
			PlaySound(playerDamaged);
			player.lives--;
			invulnerabilityTimer = 1.0f;
		}

		if (player.lives <= 0)
		{
			player.isAlive = false;
		}
	}

	void PlayerPowerUpCollision()
	{
		if (CircleCircleCollision(player.position.x, player.position.y, player.radius, powerUp.position.x, powerUp.position.y, powerUp.radius))
		{
			if (player.lives < 3 && powerUp.isActive)
			{
				PlaySound(powerUpSound);
				player.lives++;
				powerUp.isActive = false;
			}
		}
	}

	void PlayerLoses(Scenes& scene)
	{
		if (!player.isAlive)
		{
			scene = Scenes::LoseScreen;
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