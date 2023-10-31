#include "Spaceship.h"

#include "header/raymath.h"

namespace Asteroids
{
	Spaceship InitSpaceship(Vector2 position)
	{
		Spaceship player;

		Texture2D spaceshipTexture = LoadTexture("assets/magiccat.png");

		player.position = position;
		player.velocity = { 0, 0 };
		player.dest = { position.x, position.y, static_cast<float>(spaceshipTexture.width) * player.scale, static_cast<float>(spaceshipTexture.height) * player.scale};
		player.texture = spaceshipTexture;
		
		return player;
	}

	void SpaceshipMovement(Spaceship& player, Rectangle& spaceship, Vector2& origin, Vector2& mousePos, float& angle, int screenWidth, int screenHeight)
	{
		player.dest.x = player.position.x;
		player.dest.y = player.position.y;

		spaceship.width = static_cast<float>(player.texture.width);
		spaceship.height = static_cast<float>(player.texture.height);
		spaceship.x = 0;
		spaceship.y = 0;

		origin = { spaceship.width / 2, spaceship.height / 2 };

		mousePos = GetMousePosition();

		angle = static_cast<float>(atan2(static_cast<double>(player.direction.y), static_cast<double>(player.direction.x)) * RAD2DEG);

		float accelerationBoost = 2.0f;

		player.direction = Vector2Normalize(Vector2Subtract(mousePos, player.position));
		player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetFrameTime()));

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			player.velocity.x += player.direction.x * player.acceleration.x * accelerationBoost * GetFrameTime();
			player.velocity.y += player.direction.y * player.acceleration.y * accelerationBoost * GetFrameTime();
		}

		SpaceshipReturnToScreen(player, screenWidth, screenHeight);
	}

	void PlayerDrawing(Spaceship player, Rectangle source, float angle)
	{
		Vector2 origin = { (player.dest.width) / 2, (player.dest.height) / 2 };
		DrawCircleLines((int)player.dest.x, (int)player.dest.y, player.radius, RED);
		DrawTexturePro(player.texture, source, player.dest, origin, angle, RAYWHITE);
	}

	void SpaceshipReturnToScreen(Spaceship& player, int screenWidth, int screenHeight)
	{
		if (player.position.x + player.velocity.x * GetFrameTime() > screenWidth)
		{
			player.position.x = 0;
			if (player.velocity.y > 0)
			{
				if (player.position.y > screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
			else if (player.velocity.y < 0)
			{
				if (player.position.y < screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
		}
		else if (player.position.x + player.velocity.x * GetFrameTime() < 0)
		{
			player.position.x = static_cast<float>(screenWidth);
			if (player.velocity.y > 0)
			{
				if (player.position.y > screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
			else if (player.velocity.y < 0)
			{
				if (player.position.y < screenHeight / 2)
					player.position.y = screenHeight - player.position.y;
			}
		}

		if (player.position.y + player.velocity.y * GetFrameTime() > screenHeight)
		{
			player.position.y = 0;
			if (player.velocity.x > 0)
			{
				if (player.position.x > screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
			else if (player.velocity.x < 0)
			{
				if (player.position.x < screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
		}
		else if (player.position.y + player.velocity.y * GetFrameTime() < 0)
		{
			player.position.y = static_cast<float>(screenHeight);
			if (player.velocity.x > 0)
			{
				if (player.position.x > screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
			else if (player.velocity.x < 0)
			{
				if (player.position.x < screenWidth / 2)
					player.position.x = screenWidth - player.position.x;
			}
		}
	}

}