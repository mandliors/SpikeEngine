/* Game of life source code



#include "SpikeEngine.h"
#include <iostream>

using namespace Spike;

int main(void)
{
	int WINDOW_SIZE, PIXEL_SIZE, SPEED;
	std::cout << "Window size: ";
	std::cin >> WINDOW_SIZE;
	std::cout << "Pixel size: ";
	std::cin >> PIXEL_SIZE;
	std::cout << "Speed (between 1 and 240): ";
	std::cin >> SPEED;
	SPEED = Math::Clamp(SPEED, 1, 240);

	Application::Init("Game of life", WINDOW_SIZE + 1, WINDOW_SIZE + 1);

	const int PIXEL_COUNT = WINDOW_SIZE / PIXEL_SIZE;

	uint8_t** oldMap = new uint8_t * [PIXEL_COUNT];
	uint8_t** newMap = new uint8_t * [PIXEL_COUNT];
	for (size_t i = 0; i < PIXEL_COUNT; i++)
	{
		oldMap[i] = new uint8_t[PIXEL_COUNT];
		newMap[i] = new uint8_t[PIXEL_COUNT];
	}
	for (size_t i = 0; i < PIXEL_COUNT; i++)
	{
		for (size_t j = 0; j < PIXEL_COUNT; j++)
		{
			oldMap[i][j] = 0;
			newMap[i][j] = 0;
		}
	}
	Color emptyColor = { 220, 220, 220 };
	Color fullColor = { 0, 0, 0 };
	bool started = false;
	int count = 0;

	while (Application::IsRunning())
	{
		Application::Update();
		Renderer2D::Clear(240, 240, 240);

		//check input
		if (Input::GetKeyDown(SDL_SCANCODE_RETURN))
		{
			started = !started;
			Application::SetMaxFPS(started ? SPEED : 240);
		}
		else if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			started = false;
			Application::SetMaxFPS(started ? SPEED : 240);
			for (size_t i = 0; i < PIXEL_COUNT; i++)
			{
				for (size_t j = 0; j < PIXEL_COUNT; j++)
				{
					oldMap[i][j] = 0;
					newMap[i][j] = 0;
				}
			}
		}
		//calculate maps
		if (started)
		{
			//copy newMap into oldMap
			for (size_t i = 0; i < PIXEL_COUNT; i++)
			{
				for (size_t j = 0; j < PIXEL_COUNT; j++)
				{
					oldMap[i][j] = newMap[i][j];
				}
			}
			//count neightbours
			for (size_t i = 0; i < PIXEL_COUNT; i++)
			{
				for (size_t j = 0; j < PIXEL_COUNT; j++)
				{
					count = 0;
					count += (i > 0 && j > 0 && oldMap[i - 1][j - 1] == 1);                              //top left
					count += (j > 0 && oldMap[i][j - 1] == 1);                                           //top
					count += (i < PIXEL_COUNT - 1 && j > 0 && oldMap[i + 1][j - 1] == 1);                //top right
					count += (i > 0 && oldMap[i - 1][j] == 1);                                           //left
					count += (i < PIXEL_COUNT - 1 && oldMap[i + 1][j] == 1);                             //right
					count += (i > 0 && j < PIXEL_COUNT - 1 && oldMap[i - 1][j + 1] == 1);                //bottom left
					count += (j < PIXEL_COUNT - 1 && oldMap[i][j + 1] == 1);                             //bottom
					count += (i < PIXEL_COUNT - 1 && j < PIXEL_COUNT - 1 && oldMap[i + 1][j + 1] == 1);  //bottom right
					if (count < 2 || count > 3)
						newMap[i][j] = 0;
					else if (count == 3)
						newMap[i][j] = 1;
				}
			}
		}
		else
		{
			//drawing cells
			if (Input::GetMouseButton(SDL_BUTTON_LEFT))
				newMap[(int)Math::Clamp(Input::GetMousePosition().X / PIXEL_SIZE, 0, PIXEL_COUNT - 1)][(int)Math::Clamp(Input::GetMousePosition().Y / PIXEL_SIZE, 0, PIXEL_COUNT - 1)] = 1;
			else if (Input::GetMouseButton(SDL_BUTTON_RIGHT))
				newMap[(int)Input::GetMousePosition().X / PIXEL_SIZE][(int)Input::GetMousePosition().Y / PIXEL_SIZE] = 0;
		}
		
		//draw map
		for (size_t i = 0; i < PIXEL_COUNT; i++)
		{
			for (size_t j = 0; j < PIXEL_COUNT; j++)
			{
				if (newMap[i][j] == 0)
					Renderer2D::DrawRect(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE + 1, PIXEL_SIZE + 1, emptyColor);
				else
					Renderer2D::FillRect(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, fullColor);
			}
		}

		Application::Render();
	}
	for (size_t i = 0; i < PIXEL_COUNT; i++)
	{
		delete[] oldMap[i];
		delete[] newMap[i];
	}
	delete[] oldMap;
	delete[] newMap;

	Application::Close();
}

*/