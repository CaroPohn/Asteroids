#include "Objects/Button.h"

void InitButton(Button& button, Texture2D texture, float x, float y, float width, float height, Color color)
{
	button.texture = texture;
	button.x = x;
	button.y = y;
	button.width = width;
	button.height = height;
	button.color = color;
	button.isSelected = false;
}

void DrawButton(Button& button)
{
	if (button.isSelected)
	{
		button.color = GRAY;
	}
	else
		button.color = RAYWHITE;

	DrawTexture(button.texture, static_cast<int>(button.x), static_cast<int>(button.y), button.color);
}

bool CheckCollisionButtonMouse(Vector2 mousePos, Button button)
{
	return ((mousePos.x >= button.x) && (mousePos.x < (button.x + button.width)) && (mousePos.y >= button.y) && (mousePos.y < (button.y + button.height)));
}

bool CheckMouseInput(Button button)
{
	return (CheckCollisionButtonMouse(GetMousePosition(), button) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
}