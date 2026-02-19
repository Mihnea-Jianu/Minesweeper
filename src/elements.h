#pragma once

#include <cstdint>

#define hidden 0
#define marked 1
#define discovered 2

struct _position
{
	uint16_t i = 0, j = 0;

	_position operator+(_position& position);
};

struct _color
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
};

struct _sprite
{
	uint8_t colorCount = 0;
	uint8_t blockCount = 0;

	_color color[5];

	struct
	{
		_position topLeft;
		_position bottomRight;

		uint8_t colorIndex = 0;

	}block[59];

	void load(const char* src);
	void draw(_position& position);
};

struct _casing
{
	_position position;
	_sprite sprite;

	void loadSprite();
	void drawSprite();
};

struct _resetButton
{
	_position position;
	_sprite sprite;

	void loadSprite(bool gameLost = false, bool gameWon = false);
	void drawSprite();
};

struct _flagCounter
{
	int16_t remainingFlags = 0;

	_position position;
	_sprite sprite[3];

	void loadSprite();
	void drawSprite();
};

struct _timer
{
	double startTimeStamp = 0.0;
	bool   enabled = false;
	bool   frozen  = false;

	_position position;
	_sprite sprite[3];

	void loadSprite();
	void drawSprite();
	void start();
	uint16_t getCurrentTimeStamp();
};

struct _tile
{
	uint8_t state = hidden;
	uint8_t bombCount = 0;

	_position position;
	_sprite sprite;

	void loadSprite(bool gameLost = false);
	void drawSprite();
};