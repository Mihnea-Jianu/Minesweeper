#include <fstream>
#include <cstring>

#include <GLFW/glfw3.h>

#include "utilities.h"
#include "elements.h"

void _sprite::load(const char* src)
{
	std::fstream spriteSource(src);

	if(!spriteSource.is_open())
	{
		glfwTerminate();
		exit(1);
	}

	unsigned short spriteColorCount, spriteBlockCount;

	spriteSource >> spriteColorCount >> spriteBlockCount;

	colorCount = spriteColorCount;
	blockCount = spriteBlockCount;

	for(uint8_t i = 0; i < colorCount; i++)
		spriteSource >> color[i].r >> color[i].g >> color[i].b;

	unsigned short spriteTopLeftI, spriteTopLeftJ, spriteBottomRightI, spriteBottomRightJ, spriteColorIndex;

	for(uint8_t i = 0; i < blockCount; i++)
	{
		spriteSource >> spriteTopLeftI >> spriteTopLeftJ >> spriteBottomRightI >> spriteBottomRightJ >> spriteColorIndex;
		
		block[i].topLeft.i     = spriteTopLeftI;
		block[i].topLeft.j     = spriteTopLeftJ;
		block[i].bottomRight.i = spriteBottomRightI;
		block[i].bottomRight.j = spriteBottomRightJ;
		block[i].colorIndex    = spriteColorIndex;
	}

	spriteSource.close();
}

void _sprite::draw(_position& position)
{
	for(uint8_t i = 0; i < blockCount; i++)
	{
		_position& topLeftPosition     = position + block[i].topLeft;
		_position& bottomRightPosition = position + block[i].bottomRight;

		uint8_t& colorIndex = block[i].colorIndex;

		if(bottomRightPosition.i >= pixelMatrixSize || bottomRightPosition.j >= pixelMatrixSize)
		{
			glfwTerminate();
			exit(1);
		}

		double topLeftX     = -1.0 + px * topLeftPosition.j;
		double topLeftY     =  1.0 - px * topLeftPosition.i;
		double bottomRightX = -1.0 + px * (bottomRightPosition.j + 1);
		double bottomRightY =  1.0 - px * (bottomRightPosition.i + 1);

		glBegin(GL_POLYGON);
			glColor3f(color[colorIndex].r, color[colorIndex].g, color[colorIndex].b);
			glVertex2d(topLeftX    , topLeftY	 );
			glVertex2d(bottomRightX, topLeftY    );
			glVertex2d(bottomRightX, bottomRightY);
			glVertex2d(topLeftX    , bottomRightY);
		glEnd();
	}
}

void _casing::loadSprite()
{
	sprite.load("sprites/casing/casing.txt");

	for(uint8_t i = 0; i < sprite.blockCount - 10; i++)
	{
		sprite.block[i].bottomRight.i = pixelMatrixHeight - sprite.block[i].bottomRight.i - 1;
		sprite.block[i].bottomRight.j = pixelMatrixWidth - sprite.block[i].bottomRight.j - 1;
	}

	for(uint8_t i = sprite.blockCount - 10; i < sprite.blockCount; i++)
		sprite.block[i].bottomRight.j = pixelMatrixWidth - sprite.block[i].bottomRight.j - 1;
}

void _casing::drawSprite()
{
	sprite.draw(position);
}

void _resetButton::loadSprite(bool gameLost, bool gameWon)
{
	char src[31];

	if(gameLost)      strcpy_s(src, 31, "sprites/resetButton/dead.txt");
	else if(gameWon)  strcpy_s(src, 31, "sprites/resetButton/cool.txt");
	else              strcpy_s(src, 31, "sprites/resetButton/smiley.txt");

	sprite.load(src);
}

void _resetButton::drawSprite()
{
	sprite.draw(position);
}

void _flagCounter::loadSprite()
{
	char src[21];

	strcpy_s(src, 21, "sprites/digits/#.txt");

	int16_t count = remainingFlags;
	if(count > 999) count = 999;
	if(count < 0)   count = 0;

	for(int8_t i = 2; i >= 0; i--)
	{	
		src[15] = '0' + count % 10;

		sprite[i].load(src);

		count /= 10;
	}

	for(uint8_t i = 1; i < 3; i++)
	{
		for(uint8_t j = 0; j < sprite[i].blockCount; j++)
		{
			sprite[i].block[j].topLeft.j     += 13 * i;
			sprite[i].block[j].bottomRight.j += 13 * i;
		}
	}
}

void _flagCounter::drawSprite()
{
	for(uint8_t i = 0; i < 3; i++)
		sprite[i].draw(position);
}

void _timer::loadSprite()
{
	if(frozen) return;

	char src[21];

	strcpy_s(src, 21, "sprites/digits/#.txt");
	
	uint64_t count;

	if(!enabled) count = 0;
	else
	{
		count = glfwGetTime() - startTimeStamp;
		if(count > 999) count = 999;
	}

	for(int8_t i = 2; i >= 0; i--)
	{	
		src[15] = '0' + count % 10;

		sprite[i].load(src);

		count /= 10;
	}

	for(uint8_t i = 1; i < 3; i++)
	{
		for(uint8_t j = 0; j < sprite[i].blockCount; j++)
		{
			sprite[i].block[j].topLeft.j     += 13 * i;
			sprite[i].block[j].bottomRight.j += 13 * i;
		}
	}
}

void _timer::drawSprite()
{
	for(uint8_t i = 0; i < 3; i++)
		sprite[i].draw(position);
}

void _timer::start()
{
	startTimeStamp = glfwGetTime();
	enabled = true;
}

uint16_t _timer::getCurrentTimeStamp()
{
	uint64_t count;

	if(!enabled) count = 0;
	else
	{
		count = glfwGetTime() - startTimeStamp;
		if(count > 999) count = 999;
	}

	return count;
}

void _tile::loadSprite(bool gameLost)
{
	char src[31];

	if(!gameLost)
	{
		if(state == hidden) strcpy_s(src, 31, "sprites/tiles/hidden.txt");
		if(state == marked) strcpy_s(src, 31, "sprites/tiles/marked.txt");
		if(state == discovered)
		{
			strcpy_s(src, 31, "sprites/tiles/discovered#.txt");
			src[24] = '0' + bombCount;
		}
	}
	else
	{
		if(state == hidden && bombCount == 9) strcpy_s(src, 31, "sprites/tiles/hiddenBomb.txt");
		if(state == marked && bombCount != 9) strcpy_s(src, 31, "sprites/tiles/markedPoorly.txt");
	}

	sprite.load(src);
}

void _tile::drawSprite()
{
	sprite.draw(position);
}