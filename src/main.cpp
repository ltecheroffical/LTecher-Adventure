#include <iostream>
#include <vector>

#include <raylib.h>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LTecher Adventure");

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground({0, 255, 255, 255});

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
