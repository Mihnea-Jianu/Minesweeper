#pragma once

#include <cstdint>

extern uint8_t gamemode;

extern uint16_t windowSize;
extern double   windowPX;

extern uint8_t  tileMatrixHeight;
extern uint8_t  tileMatrixWidth;
extern uint16_t tileMatrixBombCount;
extern uint16_t tileMatrixSafeCount;
extern double   tileMatrixBombChance;

extern uint8_t tileSize;
extern uint8_t borderWidth;
extern uint8_t scoreBoardHeight;
extern uint8_t resetButtonSize;

extern uint16_t pixelMatrixHeight;
extern uint16_t pixelMatrixWidth;
extern uint16_t pixelMatrixSize;
extern double   px;

extern uint16_t unusedVerticalSpace;
extern uint16_t unusedHorizontalSpace;

extern uint16_t globalVerticalOffset;
extern uint16_t globalHorizontalOffset;

extern uint16_t casingVerticalOffset;
extern uint16_t casingHorizontalOffset;

extern uint16_t resetButtonVerticalOffset;
extern uint16_t resetButtonHorizontalOffset;

extern uint16_t flagCounterVerticalOffset;
extern uint16_t flagCounterHorizontalOffset;

extern uint16_t timerVerticalOffset;
extern uint16_t timerHorizontalOffset;

extern uint16_t tileMatrixVerticalOffset;
extern uint16_t tileMatrixHorizontalOffset;

void setupUtilities();
void updatePersonalBest(uint8_t gamemode, uint16_t time);