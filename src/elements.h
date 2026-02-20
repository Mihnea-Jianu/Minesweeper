#pragma once

#include <cstdint>

#define hidden     0
#define marked     1
#define discovered 2

struct Position
{
	uint16_t i = 0, j = 0;

	Position operator+(Position& position);
};

struct Color
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
};

struct Sprite
{
	uint8_t colorCount = 0;
	uint8_t blockCount = 0;

	Color color[5];

	struct
	{
		Position topLeft;
		Position bottomRight;

		uint8_t colorIndex = 0;

	}block[59];

	void load(const char* src);
	void draw(Position& position);
};

struct Casing
{
	Position position;
	Sprite   sprite;

	void loadSprite();
	void drawSprite();
};

struct ResetButton
{
	Position position;
	Sprite   sprite;

	void loadSprite(bool gameLost = false, bool gameWon = false);
	void drawSprite();
};

struct FlagCounter
{
	int16_t remainingFlags = 0;

	Position position;
	Sprite   sprite[3];

	void loadSprite();
	void drawSprite();
};

struct Timer
{
	double startTimeStamp = 0.0;
	bool   enabled = false;
	bool   frozen  = false;

	Position position;
	Sprite   sprite[3];

	void loadSprite();
	void drawSprite();
	void start();
	uint16_t getCurrentTimeStamp();
};

struct Tile
{
	uint8_t state = hidden;
	uint8_t bombCount = 0;

	Position position;
	Sprite   sprite;

	void loadSprite(bool gameLost = false);
	void drawSprite();
};
