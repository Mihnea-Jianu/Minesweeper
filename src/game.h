#pragma once

#include "elements.h"

struct Game
{
	Casing      casing;
	ResetButton resetButton;
	FlagCounter flagCounter;
	Timer       timer;
	Tile        tileMatrix[100][100];

	uint16_t safeTilesDiscovered = 0;
	uint8_t  bombTilesDiscovered = 0;

	bool seedGenerated = false;

    Game();

	void init();
	void reset();

	void positionElements();
	void loadSprites();
	void drawSprites();

	void processMouseEvent(bool button, bool action, Position& position);
	void generateSeed(uint8_t protectedTileI, uint8_t protectedTileJ);
	void flagShortcut(uint8_t shortcutTileI, uint8_t shortcutTileJ);
	void discoverPool(uint8_t discoverTileI, uint8_t discoverTileJ);
	void win();
	void lose();
};
