#pragma once

//#define PhysicsTest
//#define UITest
//#define GAME_OF_LIFE
#define TETRIS

class Game
{
public:
	Game() = default;
	
	void Start();
	void Update(float dt);
	void Exit();
};

