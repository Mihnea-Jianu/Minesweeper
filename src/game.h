#pragma once

#include "utilities.h"
#include "elements.h"

struct _game
{
	_casing casing;
	_resetButton resetButton;
	_flagCounter flagCounter;
	_timer timer;
	_tile tileMatrix[100][100];

	uint16_t safeTilesDiscovered = 0;
	uint8_t  bombTilesDiscovered = 0;

	bool seedGenerated = false;

	void init();
	void reset();

	void positionElements();
	void loadSprites();
	void drawSprites();

	void processMouseEvent(bool button, bool action, _position& position);
	void generateSeed(uint8_t protectedTileI, uint8_t protectedTileJ);
	void flagShortcut(uint8_t shortcutTileI, uint8_t shortcutTileJ);
	void discoverPool(uint8_t discoverTileI, uint8_t discoverTileJ);
	void win();
	void lose();

	_game();
};