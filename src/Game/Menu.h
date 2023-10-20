#pragma once
#include "Objects/Button.h"
#include "Game/Scenes.h"

void InitMenu();
void InitMenuButtons(Button& playButton, Button& rulesButton, Button& creditsButton, Button& exitButton);
void DrawMenu();
void MenuInput(Button& playButton, Button& rulesButton, Button& creditsButton, Button& exitButton, Scenes& scene);
void RunMenu(Scenes& scene, bool isNewScene);
