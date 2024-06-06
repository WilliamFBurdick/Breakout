#pragma once

#include "Brick.h"
#include <vector>

class LevelMaker
{
public:
	static std::vector<Brick*> CreateLevel(int level);
};

