#include <fstream>
#include <cstdint>

#define beginner     0
#define intermediate 1
#define expert       2
#define custom       3

uint8_t gamemode;

uint16_t windowSize;
double   windowPX;

uint8_t  tileMatrixHeight;
uint8_t  tileMatrixWidth;
uint16_t tileMatrixBombCount;
uint16_t tileMatrixSafeCount;
double   tileMatrixBombChance;

uint8_t tileSize;
uint8_t borderWidth;
uint8_t scoreBoardHeight;
uint8_t resetButtonSize;

uint16_t pixelMatrixHeight;
uint16_t pixelMatrixWidth;
uint16_t pixelMatrixSize;
double   px;

uint16_t unusedVerticalSpace;
uint16_t unusedHorizontalSpace;

uint16_t globalVerticalOffset;
uint16_t globalHorizontalOffset;

uint16_t casingVerticalOffset;
uint16_t casingHorizontalOffset;

uint16_t resetButtonVerticalOffset;
uint16_t resetButtonHorizontalOffset;

uint16_t flagCounterVerticalOffset;
uint16_t flagCounterHorizontalOffset;

uint16_t timerVerticalOffset;
uint16_t timerHorizontalOffset;

uint16_t tileMatrixVerticalOffset;
uint16_t tileMatrixHorizontalOffset;

void setupUtilities()
{
	std::ifstream settingsSource("settings.txt");

	if(!settingsSource.is_open()) exit(1);

	char line[5][21];

	for(uint8_t i = 0; i < 5; i++)
		settingsSource.getline(line[i], 20);

	windowSize = atoi(line[0] + 13);
	gamemode   = atoi(line[1] + 10);

	if(gamemode == beginner)
	{
		tileMatrixHeight    = 8;
		tileMatrixWidth     = 8;
		tileMatrixBombCount = 10;
	}
	else if(gamemode == intermediate)
	{
		tileMatrixHeight    = 16;
		tileMatrixWidth     = 16;
		tileMatrixBombCount = 40;
	}
	else if(gamemode == expert)
	{
		tileMatrixHeight    = 16;
		tileMatrixWidth     = 30;
		tileMatrixBombCount = 99;
	}
	else if(gamemode == custom)
	{
		tileMatrixHeight    = atoi(line[2] + 8);
		tileMatrixWidth     = atoi(line[3] + 7);
		tileMatrixBombCount = atoi(line[4] + 7);
	
		if(tileMatrixHeight < 8 || tileMatrixHeight > 100 || tileMatrixWidth < 8 || tileMatrixWidth > 100 || tileMatrixBombCount > tileMatrixHeight * tileMatrixWidth - 9)
			exit(1);
	}

	windowPX = 2.0 / windowSize;

	tileMatrixSafeCount  = tileMatrixHeight * tileMatrixWidth - tileMatrixBombCount;
	tileMatrixBombChance = 100.0 * tileMatrixBombCount / (tileMatrixHeight * tileMatrixWidth);

	tileSize         = 16;
	borderWidth      = 12;
	scoreBoardHeight = 32;
	resetButtonSize  = 26;

	pixelMatrixHeight = tileSize * tileMatrixHeight + 3 * borderWidth + scoreBoardHeight;
	pixelMatrixWidth  = tileSize * tileMatrixWidth  + 2 * borderWidth;
	pixelMatrixSize   = pixelMatrixHeight > pixelMatrixWidth? pixelMatrixHeight : pixelMatrixWidth;
	px = 2.0 / pixelMatrixSize;

	unusedVerticalSpace   = pixelMatrixSize - pixelMatrixHeight;
	unusedHorizontalSpace = pixelMatrixSize - pixelMatrixWidth;

	globalVerticalOffset   = unusedVerticalSpace;
	globalHorizontalOffset = 0;

	casingVerticalOffset   = globalVerticalOffset;
	casingHorizontalOffset = globalHorizontalOffset;

	resetButtonVerticalOffset   = globalVerticalOffset   + borderWidth + 3;
	resetButtonHorizontalOffset = globalHorizontalOffset + pixelMatrixWidth / 2 - resetButtonSize / 2;

	flagCounterVerticalOffset   = globalVerticalOffset   + borderWidth + 4;
	flagCounterHorizontalOffset = globalHorizontalOffset + borderWidth + 4;

	timerVerticalOffset   = globalVerticalOffset   + borderWidth + 4;
	timerHorizontalOffset = globalHorizontalOffset + pixelMatrixWidth - borderWidth - 43;

	tileMatrixVerticalOffset   = globalVerticalOffset   + 2 * borderWidth + scoreBoardHeight;
	tileMatrixHorizontalOffset = globalHorizontalOffset + borderWidth;

	settingsSource.close();
}

void updatePersonalBest(uint8_t gamemode, uint16_t time)
{
	std::fstream pbSource("personal_best.txt", std::ios::in);

	if(!pbSource.is_open()) exit(1);

	char line[3][21];

	for(uint8_t i = 0; i < 3; i++)
		pbSource.getline(line[i], 20);

	unsigned short beginnerBest     = atoi(line[0] + 10);
	unsigned short intermediateBest = atoi(line[1] + 14);
	unsigned short expertBest       = atoi(line[2] + 8);

	if(gamemode == beginner && time < beginnerBest)
		beginnerBest = time;

	if(gamemode == intermediate && time < intermediateBest)
		intermediateBest = time;

	if(gamemode == expert && time < expertBest)
		expertBest = time;

	pbSource.close();

	pbSource.open("personal_best.txt", std::ios::out);

	if(!pbSource.is_open()) exit(1);

	pbSource << "beginner: "     << beginnerBest     << std::endl;
	pbSource << "intermediate: " << intermediateBest << std::endl;
	pbSource << "expert: "       << expertBest       << std::endl;

	pbSource.close();
}