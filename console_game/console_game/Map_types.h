#pragma once
#include <array>

#include "Defines.h"

typedef char Pixel;
typedef std::array<std::array<Pixel, FIELD_HEIGHT>, FIELD_WIDTH> Field_type;

typedef struct {
	unsigned int x;
	unsigned int y;
} Position;
