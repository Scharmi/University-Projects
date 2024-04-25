#pragma once
#include "GraphicComponents.h"
#include <array>
#include <vector>

namespace {
	using std::array;
	using std::vector;
}

bool InsidePrism(coordinate_t BLF, coordinate_t URB, coordinate_t point);

vector<prism_t> OuterPrisms();
vector<prism_t> InnerPrisms();

bool LegalPosition(coordinate_t point);
