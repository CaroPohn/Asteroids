#include "Spaceship.h"
#include "header/raymath.h"

namespace Asteroids
{
	Spaceship InitSpaceship(Vector2 position)
	{
		Spaceship player;

		player.position = position;
		player.velocity = { 0, 0 };
		
		return player;
	}

	void SpaceshipMovement(Spaceship& player, Rectangle& spaceship, Vector2& origin, Vector2& mousePos, float& angle, int screenWidth, int screenHeight)
	{
		spaceship.x = player.position.x;
		spaceship.y = player.position.y;
		spaceship.width = 20;
		spaceship.height = 20;

		origin = { spaceship.width / 2, spaceship.height / 2 };

		mousePos = GetMousePosition();

		angle = static_cast<float>(atan2(static_cast<double>(player.direction.y), static_cast<double>(player.direction.x)) * RAD2DEG + 90.0f);

		player.direction = Vector2Normalize(Vector2Subtract(mousePos, player.position));
		player.position = Vector2Add(player.position, Vector2Scale(player.velocity, GetFrameTime()));

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			player.velocity.x += player.direction.x * player.acceleration.x * GetFrameTime();
			player.velocity.y += player.direction.y * player.acceleration.y * GetFrameTime();
		}

		//if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		//{

		//}

		SpaceshipReturnToScreen(player, screenWidth, screenHeight);
	}

	void SpaceshipDrawing(Rectangle spaceship, Vector2 origin, float angle)
	{
		DrawRectanglePro(spaceship, origin, angle, PINK);
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