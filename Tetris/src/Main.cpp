#include "Core/SpikeEngine.h"
#include <iostream>
#include <array>


//Defines
#define WIDTH 402
#define HEIGHT 802
#define SQUARE 40
#define H_SQUARE_COUNT 10
#define V_SQUARE_COUNT 20
#define STEP_TIME 800


using namespace Spike;

//Global variables
std::array<Color, 9> COLORS
{
	Color(20, 20, 20),
	Color(40, 40, 40),
	Color(23, 192, 235),
	Color(254, 211, 48),
	Color(142, 68, 173),
	Color(211, 84, 0),
	Color(9, 132, 227),
	Color(76, 209, 55),
	Color(180, 10, 180)
};
int table[V_SQUARE_COUNT + 4][H_SQUARE_COUNT];

//Function and class declarations
enum class BlockType;
void DrawTable();
void DrawCurrentBlock(int* currentBlock);
int SpawnShape(BlockType type, int* newBlock);
bool Step(int* block);
bool Move(int* block, int dir);
bool Rotate(int* block, BlockType type, int rotation, int rowCount, int columnCount);
int HandleLines();
void SpliceTable(int index);
bool CheckLoss();
void CalculateEndPosition(int(&block)[8], int(&endPos)[8]); //Must pass arrays like this in order for memcpy to work
void DrawEndPosition(int* endPos, BlockType type);

//Application entry point
int main(void)
{
	srand(time(0));

	//Variables
	int currentBlock[8];
	int currentBlockEndPosition[8];
	int stepCount = 0;
	int rowCount = -1;
	int columnCount = 4;
	int rotation = 1;
	BlockType currentBlockType;
	bool inGame = true;

	//Initialization
	Application::Init("Tetris by Progmaster", 400, 800);
	Application::SetMaxFPS(60);
	memset(table, 0, sizeof(table));
	memset(currentBlock, 0, sizeof(currentBlock));
	memset(currentBlockEndPosition, 0, sizeof(currentBlockEndPosition));
	int randomShape = rand() % 7 + 1;
	currentBlockType = (BlockType)randomShape;
	rowCount = SpawnShape(currentBlockType, currentBlock);
	CalculateEndPosition(currentBlock, currentBlockEndPosition);
	Time::Bind("StepTime");
	Renderer2D::SetTextAlign(SpikeTextAlign::CENTER);
	Renderer2D::SetTextRenderMode(SpikeTextRenderMode::ANTIALIASED);
	Renderer2D::SetFont("assets/FreeMono.ttf", 24);

	//Audio
	int vol = 10;
	bool muted = false;
	Music& music = AudioManager::LoadMusic("assets/tetris.mp3");
	Sound& down = AudioManager::LoadSound("assets/down.wav");
	Sound& nying = AudioManager::LoadSound("assets/nying.wav");
	Sound& gameOver = AudioManager::LoadSound("assets/game_over.wav");
	music.Loop();
	music.SetVolume(vol);
	down.SetVolume(100);
	nying.SetVolume(50);

	//Game loop
	while (Application::IsRunning())
	{
		//Update
		Application::Update();

		//Clear the screen
		Renderer2D::Clear(COLORS[0]);

		if (inGame)
		{
			//Check for input
			music.SetVolume(vol = Math::Clamp(vol + Input::GetMouseWheel() * 10, 0, 100));
			if (Input::GetKeyDown(SPIKE_KEYCODE_ESCAPE))
			{
				muted = !muted;
				music.Mute(muted);
			}

			if (Input::GetKeyDown(SPIKE_KEYCODE_LEFT))
			{
				Move(currentBlock, -1);
				columnCount--;
				CalculateEndPosition(currentBlock, currentBlockEndPosition);
			}
			else if (Input::GetKeyDown(SPIKE_KEYCODE_RIGHT))
			{
				Move(currentBlock, 1);
				columnCount++;
				CalculateEndPosition(currentBlock, currentBlockEndPosition);
			}
			if (Input::GetKeyDown(SPIKE_KEYCODE_UP))
			{
				for (int i = 0; i < 7; i += 2)
					table[currentBlock[i]][currentBlock[i + 1]] = 0;

				if (Rotate(currentBlock, currentBlockType, rotation % 4 + 1, rowCount, columnCount))
					rotation = rotation % 4 + 1;

				for (int i = 0; i < 7; i += 2)
					table[currentBlock[i]][currentBlock[i + 1]] = (int)currentBlockType;

				CalculateEndPosition(currentBlock, currentBlockEndPosition);
			}
			if (Input::GetKey(SPIKE_KEYCODE_DOWN))
			{
				//Step
				if (Step(currentBlock))
				{
					if (HandleLines() > 0)
						nying.Play();
					else
						down.Play();
					if (CheckLoss())
					{
						inGame = false;
						music.Stop();
						gameOver.Play();
						Renderer2D::SetFont("assets/FreeMono.ttf", 40);
						Application::SetWindowSize(Vector2(Application::GetWindowSize().X, 160));
					}
					randomShape = rand() % 7 + 1;
					currentBlockType = (BlockType)randomShape;
					rowCount = SpawnShape(currentBlockType, currentBlock);
					CalculateEndPosition(currentBlock, currentBlockEndPosition);
					Time::SetReferenceTime("StepTime");
					stepCount = 0;
					columnCount = 4;
					rotation = 1;
				}
				else
					rowCount++;
			}

			//Update time and check if it has to step
			if (Time::GetElapsedMillis("StepTime") / STEP_TIME > stepCount)
			{
				stepCount = Time::GetElapsedMillis("StepTime") / STEP_TIME;

				//Step
				if (Step(currentBlock))
				{
					if (HandleLines() > 0)
						nying.Play();
					else
						down.Play();
					if (CheckLoss())
					{
						inGame = false;
						music.Stop();
						gameOver.Play();
						Renderer2D::SetFont("assets/FreeMono.ttf", 40);
						Application::SetWindowSize(Vector2(Application::GetWindowSize().X, 160));
					}
					randomShape = rand() % 7 + 1;
					currentBlockType = (BlockType)randomShape;
					rowCount = SpawnShape(currentBlockType, currentBlock);
					CalculateEndPosition(currentBlock, currentBlockEndPosition);
					Time::SetReferenceTime("StepTime");
					stepCount = 0;
					columnCount = 4;
					rotation = 1;
				}
				else
					rowCount++;
			}

			//Draw the shapes
			DrawTable();
			DrawEndPosition(currentBlockEndPosition, currentBlockType);
			DrawCurrentBlock(currentBlock);
			Renderer2D::RenderText("Points: 0", Application::GetWindowSize().X / 2, 10, Color::White());
		}
		else
			Renderer2D::RenderText("Game Over!", Application::GetWindowSize().X * 0.5f, 60, Color::White());

		//Render
		Application::Render();
	}

	Application::Close();
}

//Enums
enum class BlockType
{
	I = 1, O, T, L, J, S, Z
};

//Functions
void DrawTable()
{
	for (int i = 4; i < V_SQUARE_COUNT + 4; i++)
	{
		for (int j = 0; j < H_SQUARE_COUNT; j++)
		{
			if (table[i][j] == 0)
			{
				Renderer2D::FillRect(j * SQUARE, (i - 4) * SQUARE, SQUARE, SQUARE, COLORS[0]);
				Renderer2D::DrawRect(j * SQUARE, (i - 4) * SQUARE, SQUARE + 1, SQUARE + 1, COLORS[1]);
			}
			else if (table[i][j] < 0)
			{
				Renderer2D::FillRect(j * SQUARE + 1, (i - 4) * SQUARE + 1, SQUARE - 2, SQUARE - 2, COLORS[Math::Abs(table[i][j]) + 1]);
				Renderer2D::DrawRect(j * SQUARE, (i - 4) * SQUARE, SQUARE, SQUARE, COLORS[Math::Abs(table[i][j]) + 1] * 0.8f);
			}
		}
	}
}

void DrawCurrentBlock(int* currentBlock)
{
	for (int i = 0; i < 7; i += 2)
	{
		Renderer2D::FillRect(currentBlock[i + 1] * SQUARE + 1, (currentBlock[i] - 4) * SQUARE + 1, SQUARE - 2, SQUARE - 2, COLORS[(size_t)table[currentBlock[i]][currentBlock[i + 1]] + 1]);
		Renderer2D::DrawRect(currentBlock[i + 1] * SQUARE, (currentBlock[i] - 4) * SQUARE, SQUARE, SQUARE, COLORS[(size_t)table[currentBlock[i]][currentBlock[i + 1]] + 1] * 0.8f);
	}
}

int SpawnShape(BlockType type, int* newBlock)
{
	switch (type)
	{
	case BlockType::I:
		table[0][5] = (int)type;
		table[1][5] = (int)type;
		table[2][5] = (int)type;
		table[3][5] = (int)type;
		newBlock[0] = 0;
		newBlock[1] = 5;
		newBlock[2] = 1;
		newBlock[3] = 5;
		newBlock[4] = 2;
		newBlock[5] = 5;
		newBlock[6] = 3;
		newBlock[7] = 5;
		return 0;
	case BlockType::O:
		table[2][4] = (int)type;
		table[2][5] = (int)type;
		table[3][4] = (int)type;
		table[3][5] = (int)type;
		newBlock[0] = 2;
		newBlock[1] = 4;
		newBlock[2] = 2;
		newBlock[3] = 5;
		newBlock[4] = 3;
		newBlock[5] = 4;
		newBlock[6] = 3;
		newBlock[7] = 5;
		return 2;
	case BlockType::T:
		table[2][5] = (int)type;
		table[3][4] = (int)type;
		table[3][5] = (int)type;
		table[3][6] = (int)type;
		newBlock[0] = 2;
		newBlock[1] = 5;
		newBlock[2] = 3;
		newBlock[3] = 4;
		newBlock[4] = 3;
		newBlock[5] = 5;
		newBlock[6] = 3;
		newBlock[7] = 6;
		return 2;
	case BlockType::L:
		table[1][5] = (int)type;
		table[2][5] = (int)type;
		table[3][5] = (int)type;
		table[3][6] = (int)type;
		newBlock[0] = 1;
		newBlock[1] = 5;
		newBlock[2] = 2;
		newBlock[3] = 5;
		newBlock[4] = 3;
		newBlock[5] = 5;
		newBlock[6] = 3;
		newBlock[7] = 6;
		return 1;
	case BlockType::J:
		table[1][5] = (int)type;
		table[2][5] = (int)type;
		table[3][5] = (int)type;
		table[3][4] = (int)type;
		newBlock[0] = 1;
		newBlock[1] = 5;
		newBlock[2] = 2;
		newBlock[3] = 5;
		newBlock[4] = 3;
		newBlock[5] = 5;
		newBlock[6] = 3;
		newBlock[7] = 4;
		return 1;
	case BlockType::S:
		table[2][5] = (int)type;
		table[2][6] = (int)type;
		table[3][4] = (int)type;
		table[3][5] = (int)type;
		newBlock[0] = 2;
		newBlock[1] = 5;
		newBlock[2] = 2;
		newBlock[3] = 6;
		newBlock[4] = 3;
		newBlock[5] = 4;
		newBlock[6] = 3;
		newBlock[7] = 5;
		return 2;
	case BlockType::Z:
		table[3][4] = (int)type;
		table[3][5] = (int)type;
		table[4][5] = (int)type;
		table[4][6] = (int)type;
		newBlock[0] = 3;
		newBlock[1] = 4;
		newBlock[2] = 3;
		newBlock[3] = 5;
		newBlock[4] = 4;
		newBlock[5] = 5;
		newBlock[6] = 4;
		newBlock[7] = 6;
		return 2;
	}
}

bool Step(int* block)
{
	bool collision = false;
	int n = table[block[0]][block[1]];

	//Check collision
	for (int i = 0; i < 7; i += 2)
	{
		if (block[i] == V_SQUARE_COUNT + 3)
			collision = true;
		else if (table[block[i] + 1][block[i + 1]] < 0)
			collision = true;
	}
	if (collision)
	{
		for (int i = 0; i < 7; i += 2)
			table[block[i]][block[i + 1]] = -n;
	}
	else
	{
		//Move down
		for (int i = 0; i < 7; i += 2)
		{
			table[block[i]++][block[i + 1]] = 0;
		}
		for (int i = 0; i < 7; i += 2)
		{
			table[block[i]][block[i + 1]] = n;
		}
	}

	return collision;
}

bool Move(int* block, int dir)
{
	int n = table[block[0]][block[1]];
	for (int i = 0; i < 7; i += 2)
	{
		if (dir == -1 && block[i + 1] == 0)
			return true;
		else if (dir == 1 && block[i + 1] == H_SQUARE_COUNT - 1)
			return true;
		else if (dir == -1 && table[block[i]][block[i + 1] - 1] < 0)
			return true;
		else if (dir == 1 && table[block[i]][block[i + 1] + 1] < 0)
			return true;
	}
	for (int i = 0; i < 7; i += 2)
	{
		table[block[i]][block[i + 1]] = 0;
	}
	for (int i = 0; i < 7; i += 2)
	{
		table[block[i]][block[i + 1] += dir] = n;
	}
	return false;
}

bool Rotate(int* block, BlockType type, int rotation, int rowCount, int columnCount)
{
	int temporaryBlock[8] = { 0 };

	//Choose the rotation
	switch (type)
	{
	case BlockType::I:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 2;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 2;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 3;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 2:
			temporaryBlock[0] = rowCount + 2;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 2;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 3;
			break;
		case 3:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 3;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 4:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 3;
			break;
		default:
			break;
		}
		break;
	case BlockType::O:
		temporaryBlock[0] = rowCount;
		temporaryBlock[1] = columnCount;
		temporaryBlock[2] = rowCount;
		temporaryBlock[3] = columnCount + 1;
		temporaryBlock[4] = rowCount + 1;
		temporaryBlock[5] = columnCount;
		temporaryBlock[6] = rowCount + 1;
		temporaryBlock[7] = columnCount + 1;
		break;
	case BlockType::T:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 2:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 3:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 4:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		default:
			break;
		}
		break;
	case BlockType::L:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 2:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount;
			break;
		case 3:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 4:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 2;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 2;
			break;
		default:
			break;
		}
		break;
	case BlockType::J:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 2:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 3:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount;
			temporaryBlock[3] = columnCount + 2;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 4:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 2;
			break;
		default:
			break;
		}
		break;
	case BlockType::S:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 2;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 2:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 3:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount;
			temporaryBlock[3] = columnCount + 2;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 1;
			break;
		case 4:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 2;
			break;
		default:
			break;
		}
		break;
	case BlockType::Z:
		switch (rotation)
		{
		case 1:
			temporaryBlock[0] = rowCount + 1;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 2;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 2:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 1;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount;
			break;
		case 3:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount;
			temporaryBlock[2] = rowCount;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 1;
			temporaryBlock[6] = rowCount + 1;
			temporaryBlock[7] = columnCount + 2;
			break;
		case 4:
			temporaryBlock[0] = rowCount;
			temporaryBlock[1] = columnCount + 2;
			temporaryBlock[2] = rowCount + 1;
			temporaryBlock[3] = columnCount + 1;
			temporaryBlock[4] = rowCount + 1;
			temporaryBlock[5] = columnCount + 2;
			temporaryBlock[6] = rowCount + 2;
			temporaryBlock[7] = columnCount + 1;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	//Check if can't rotate
	for (int i = 0; i < 7; i += 2)
	{
		if (temporaryBlock[i] > V_SQUARE_COUNT + 3)
			return false;
		else if (temporaryBlock[i + 1] < 0 || temporaryBlock[i + 1] > H_SQUARE_COUNT - 1)
			return false;
		else if (table[temporaryBlock[i]][temporaryBlock[i + 1]] < 0)
			return false;
	}

	//Apply rotation
	for (int i = 0; i < 7; i += 2)
	{
		block[i] = temporaryBlock[i];
		block[i + 1] = temporaryBlock[i + 1];
	}

	return true;
}

int HandleLines()
{
	int lineCount = 0;

	//Check for filled lines
	for (int i = V_SQUARE_COUNT + 3; i >= 0; i--)
	{
		for (int j = 0; j < H_SQUARE_COUNT; j++)
		{
			if (table[i][j] >= 0)
				break;
			if (j == H_SQUARE_COUNT - 1)
			{
				SpliceTable(i);
				j = 0;
				lineCount++;
			}
		}
	}

	return lineCount;
}

void SpliceTable(int index)
{
	for (int i = index - 1; i >= 4; i--)
	{
		for (int j = 0; j < H_SQUARE_COUNT; j++)
		{
			if (table[i][j] <= 0)
			{
				if (table[i + 1][j] <= 0)
				{
					table[i + 1][j] = table[i][j];
					table[i][j] = 0;
				}
			}
			else
				table[i + 1][j] = 0;
		}
	}
}

bool CheckLoss()
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < H_SQUARE_COUNT; j++)
		{
			if (table[i][j] < 0)
				return true;
		}
	}

	return false;
}

void CalculateEndPosition(int(&block)[8], int(&endPos)[8])
{
	bool collision = false;
	memcpy(endPos, block, sizeof(endPos));

	do
	{
		for (int i = 0; i < 7; i += 2)
		{
			if (++endPos[i] == V_SQUARE_COUNT + 4 || table[endPos[i]][endPos[i + 1]] < 0)
				collision = true;
		}
	} while (!collision);

	for (int i = 0; i < 7; i += 2)
		endPos[i] -= 5;
}

void DrawEndPosition(int* endPos, BlockType type)
{
	for (int i = 0; i < 7; i += 2)
	{
		//Two drawing mathods

		Renderer2D::FillRect(endPos[i + 1] * SQUARE, endPos[i] * SQUARE, SQUARE - 1, SQUARE - 1, COLORS[1] * 1.2f);
		/*Renderer2D::DrawRect(endPos[i + 1] * SQUARE, endPos[i] * SQUARE, SQUARE, SQUARE, COLORS[(size_t)type + 1] * 0.8f);
		Renderer2D::DrawRect(endPos[i + 1] * SQUARE - 1, endPos[i] * SQUARE - 1, SQUARE + 2, SQUARE + 2, COLORS[(size_t)type + 1] * 0.8f);*/
	}
}