#include "LevelMaker.h"
#include <time.h>
#include <algorithm>

std::vector<Brick*> LevelMaker::CreateLevel(int level)
{
	std::vector<Brick*> bricks = std::vector<Brick*>();
	srand(time(0));
	int numRows = rand() % 5 + 1;
	int numCols = std::max(rand() % 13 + 1, 7);
	if (numCols % 2 != 0)
	{
		numCols++;
	}

	int highestTier = std::min(3, (int)floor(level / 5));
	int highestColor = std::min(5, level % 5 + 3);

	for (int y = 0; y < numRows; y++)
	{
		// Whether to enable skipping for this row
		bool skipPattern = rand() % 2 == 1;
		// Whether this row will have alternating colors
		bool alternatePattern = rand() % 2 == 1;

		// Choose 2 colors to alternate between
		int altColor1;
		int altColor2;
		int solidColor;
		if (highestColor == 0)
		{
			altColor1 = 0;
			altColor2 = 0;
			solidColor = 0;
		}
		else
		{
			altColor1 = rand() % highestColor;
			altColor2 = rand() % highestColor;
			solidColor = rand() % highestColor;
		}
		int altTier1;
		int altTier2;
		int solidTier;
		if (highestTier == 0)
		{
			altTier1 = 0;
			altTier2 = 0;
			solidTier = 0;
		}
		else
		{
			altTier1 = rand() % highestTier;
			altTier2 = rand() % highestTier;
			solidTier = rand() % highestTier;
		}

		// Used only when we wnat to skip a block for skip pattern
		bool skipFlag = rand() % 2 == 1;
		// Used only when we want to alternate a block
		bool altFlag = rand() % 2 == 1;

		for (int x = 0; x < numCols; x++)
		{
			if (skipPattern && skipFlag)
			{
				skipFlag = !skipFlag;
				continue;
			}
			else
			{
				skipFlag = !skipFlag;
			}

			int tier, color;
			if (alternatePattern && altFlag)
			{
				color = altColor1;
				tier = altTier1;
				altFlag = !altFlag;
			}
			else
			{
				color = altColor2;
				tier = altTier2;
				altFlag = !altFlag;
			}

			if (!alternatePattern)
			{
				color = solidColor;
				tier = solidTier;
			}

			Brick* b = new Brick(
				x * 32 + 36 + (13 - numCols) * 16,
				y * 16 + 16, tier, color, true
			);
			bricks.emplace_back(b);
		}
	}

	if (bricks.size() == 0)
	{
		return CreateLevel(level);
	}
	else
	{
		return bricks;
	}
}