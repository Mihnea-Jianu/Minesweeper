#include <ctime>
#include <cstdlib>

#include "utilities.h"
#include "game.h"

#define leftClick  0
#define rightClick 1
#define release    0
#define press      1

#define gameLost (bombTilesDiscovered != 0)
#define gameWon  (safeTilesDiscovered == tileMatrixSafeCount)

Game::Game()
{
	setupUtilities();
	flagCounter.remainingFlags = tileMatrixBombCount;
}

void Game::init()
{
	srand(time(NULL));

	positionElements();
	loadSprites();
}

void Game::reset()
{
	flagCounter.remainingFlags = tileMatrixBombCount;

	timer.startTimeStamp = 0.0;
	timer.enabled = false;
	timer.frozen  = false;

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
		{
			tileMatrix[i][j].state = hidden;
			tileMatrix[i][j].bombCount = 0;
		}

	safeTilesDiscovered = 0;
	bombTilesDiscovered = 0;

	seedGenerated = false;

	loadSprites();
}

void Game::positionElements()
{
	casing.position.i = casingVerticalOffset;
	casing.position.j = casingHorizontalOffset;

	resetButton.position.i = resetButtonVerticalOffset;
	resetButton.position.j = resetButtonHorizontalOffset;

	flagCounter.position.i = flagCounterVerticalOffset;
	flagCounter.position.j = flagCounterHorizontalOffset;

	timer.position.i = timerVerticalOffset;
	timer.position.j = timerHorizontalOffset;

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
		{
			tileMatrix[i][j].position.i = tileMatrixVerticalOffset   + tileSize * i;
			tileMatrix[i][j].position.j = tileMatrixHorizontalOffset + tileSize * j;
		}
}

void Game::loadSprites()
{
	casing.loadSprite();
	resetButton.loadSprite();
	flagCounter.loadSprite();
	timer.loadSprite();

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
			tileMatrix[i][j].loadSprite();
}

void Game::drawSprites()
{
	casing.drawSprite();
	resetButton.drawSprite();
	flagCounter.drawSprite();
	timer.drawSprite();

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
			tileMatrix[i][j].drawSprite();
}

void Game::processMouseEvent(bool button, bool action, Position& position)
{
	#define positionInsideTileMatrix  (position.i >= tileMatrix[0][0].position.i && position.i < tileMatrix[tileMatrixHeight - 1][tileMatrixWidth - 1].position.i + tileSize && position.j >= tileMatrix[0][0].position.j && position.j < tileMatrix[tileMatrixHeight - 1][tileMatrixWidth - 1].position.j + tileSize)
	#define positionInsideResetButton (position.i >= resetButton.position.i && position.i < resetButton.position.i + resetButtonSize && position.j >= resetButton.position.j && position.j < resetButton.position.j + resetButtonSize)

	if(positionInsideTileMatrix && !gameLost && !gameWon)
	{
		uint8_t tileMatrixI = (position.i - tileMatrixVerticalOffset)   / tileSize;
		uint8_t tileMatrixJ = (position.j - tileMatrixHorizontalOffset) / tileSize;

		Tile& tile = tileMatrix[tileMatrixI][tileMatrixJ];

		if(button == rightClick && action == release && tile.state != discovered)
		{
			tile.state = !(tile.state);

			if(tile.state == marked) flagCounter.remainingFlags--;
			else					 flagCounter.remainingFlags++;

			flagCounter.loadSprite();
		}

		if(button == leftClick && action == release && tile.state != marked)
		{
			if(!seedGenerated)
			{
				generateSeed(tileMatrixI, tileMatrixJ);
				timer.start();
			}

			if(tile.state == hidden)
			{
				tile.state = discovered;

				if(tile.bombCount == 9) bombTilesDiscovered++;
				else					safeTilesDiscovered++;

				if(tile.bombCount == 0) discoverPool(tileMatrixI, tileMatrixJ);
			}
			else if(tile.bombCount != 0)
				flagShortcut(tileMatrixI, tileMatrixJ);
		}

		tile.loadSprite();

		if(gameLost) lose();
		if(gameWon)  win();
	}
	else if(positionInsideResetButton)
	{
		if(button == leftClick && action == release) reset();
	}
}

void Game::generateSeed(uint8_t protectedTileI, uint8_t protectedTileJ)
{
	uint16_t currentBombCount = 0;

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
		{
			#define tileOutsideProtectedArea (i < protectedTileI - 1 || i > protectedTileI + 1 || j < protectedTileJ - 1 || j > protectedTileJ + 1)

			if(tileOutsideProtectedArea && rand() % 100 < tileMatrixBombChance)
			{
				tileMatrix[i][j].bombCount = 9;
				currentBombCount++;
			}
			else tileMatrix[i][j].bombCount = 0;
		}

	if(currentBombCount != tileMatrixBombCount)
	{
		generateSeed(protectedTileI, protectedTileJ);
		return;
	}

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
		{
			if(tileMatrix[i][j].bombCount == 9)
				for(int8_t I = i - 1; I <= i + 1; I++)
					for(int8_t J = j - 1; J <= j + 1; J++)
					{
						#define tileInsideTileMatrix (I >= 0 && I < tileMatrixHeight && J >= 0 && J < tileMatrixWidth)

						if(tileInsideTileMatrix && tileMatrix[I][J].bombCount != 9)
							tileMatrix[I][J].bombCount++;
					}

		}

	seedGenerated = true;
}

void Game::flagShortcut(uint8_t shortcutTileI, uint8_t shortcutTileJ)
{
	uint8_t flagCount = 0;

	for(int8_t I = shortcutTileI - 1; I <= shortcutTileI + 1; I++)
		for(int8_t J = shortcutTileJ - 1; J <= shortcutTileJ + 1; J++)
		{
			#define tileInsideTileMatrix (I >= 0 && I < tileMatrixHeight && J >= 0 && J < tileMatrixWidth)

			if(tileInsideTileMatrix && tileMatrix[I][J].state == marked)
				flagCount++;
		}
				
	if(flagCount == tileMatrix[shortcutTileI][shortcutTileJ].bombCount)
	{
		for(int8_t I = shortcutTileI - 1; I <= shortcutTileI + 1; I++)
			for(int8_t J = shortcutTileJ - 1; J <= shortcutTileJ + 1; J++)
			{
				#define tileInsideTileMatrix (I >= 0 && I < tileMatrixHeight && J >= 0 && J < tileMatrixWidth)

				if(tileInsideTileMatrix && tileMatrix[I][J].state == hidden)
				{
					tileMatrix[I][J].state = discovered;
					tileMatrix[I][J].loadSprite();

					if(tileMatrix[I][J].bombCount == 9) bombTilesDiscovered++;
					else								safeTilesDiscovered++;

					if(tileMatrix[I][J].bombCount == 0) discoverPool(I, J);
				}
			}
	}
}

void Game::discoverPool(uint8_t discoverTileI, uint8_t discoverTileJ)
{
	for(int8_t I = discoverTileI - 1; I <= discoverTileI + 1; I++)
		for(int8_t J = discoverTileJ - 1; J <= discoverTileJ + 1; J++)
		{
			#define tileInsideTileMatrix (I >= 0 && I < tileMatrixHeight && J >= 0 && J < tileMatrixWidth) 

			if(tileInsideTileMatrix && tileMatrix[I][J].state == hidden)
			{
				tileMatrix[I][J].state = discovered;
				tileMatrix[I][J].loadSprite();

				safeTilesDiscovered++;

				if(tileMatrix[I][J].bombCount == 0) discoverPool(I, J);
			}
		}
}

void Game::win()
{
	updatePersonalBest(gamemode, timer.getCurrentTimeStamp());

	resetButton.loadSprite(false, gameWon);
	timer.frozen = true;

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
			if(tileMatrix[i][j].state == hidden)
			{
				tileMatrix[i][j].state = marked;
				tileMatrix[i][j].loadSprite();
			}

	flagCounter.remainingFlags = 0;
	flagCounter.loadSprite();
}

void Game::lose()
{
	resetButton.loadSprite(gameLost, false);
	timer.frozen = true;

	for(uint8_t i = 0; i < tileMatrixHeight; i++)
		for(uint8_t j = 0; j < tileMatrixWidth; j++)
			if(tileMatrix[i][j].state == hidden && tileMatrix[i][j].bombCount == 9 || tileMatrix[i][j].state == marked && tileMatrix[i][j].bombCount != 9)
				tileMatrix[i][j].loadSprite(gameLost);
}
