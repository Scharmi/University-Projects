#pragma once
#include "HandlingMoves.h"
#include "GraphicComponents.h"
#include <string>

namespace {
	using std::to_string;

}
bool InsideInterval(FLOAT a, FLOAT b, FLOAT c) {
	return (a <= c && c <= b) || (b <= c && c <= a);
}
bool InsidePrism(coordinate_t BLF, coordinate_t URB, coordinate_t point) {
	return InsideInterval(BLF.x, URB.x, -point.x) && InsideInterval(BLF.y, URB.y, point.y) && InsideInterval(BLF.z, URB.z, -point.z);
}
vector<prism_t> OuterPrisms() {
	vector<prism_t> prisms;
	prism_t prism;
	prism.BLF = BLF_ROOM_CORNER;
	prism.URB = URB_ROOM_CORNER;
	prisms.push_back(prism);
	prism.BLF = BLF_CORRIDOR_CORNER;
	prism.URB = URB_CORRIDOR_CORNER;
	prisms.push_back(prism);
	prism.BLF = BLF_ROOM_2_CORNER;
	prism.URB = URB_ROOM_2_CORNER;
	prisms.push_back(prism);
	return prisms;
}
vector<prism_t> InnerPrisms() {
	vector<prism_t> prisms;
	return prisms;
}

bool LegalPosition(coordinate_t point) {
	auto outsidePrisms = OuterPrisms();
	auto insidePrisms = InnerPrisms();
	bool result = false;
	for (int i = 0; i < outsidePrisms.size(); i++) {
		if (InsidePrism(outsidePrisms[i].BLF, outsidePrisms[i].URB, point)) {
			result = true;
		}
	}
	if (!result) {
		return false;
	}
	
	for (int i = 0; i < insidePrisms.size(); i++) {
		if (InsidePrism(insidePrisms[i].BLF, insidePrisms[i].URB, point)) {
			result = false;
		}
	}
	return result;
}