#pragma once
#include "GraphicComponents.h"

#include <d3d12.h>
#include <array>
#include <vector>

namespace {
    using std::array;
    using std::vector;
}

vector<vertex_t> RectangleWall(wall_t wall) {
	coordinate_t BL = wall.BL;
	coordinate_t UR = wall.UR;
	coordinate_t TBL = wall.TBL;
	coordinate_t TUR = wall.TUR;
	coordinate_t NumOfTextures = wall.NumOfTextures;
	FLOAT normal_sign = wall.normal_sign;
	if (NumOfTextures.x <= 1) {
		TUR.x = TBL.x + (TUR.x - TBL.x) * NumOfTextures.x;
		NumOfTextures.x = 1;
	}
	if (NumOfTextures.y <= 1) {
		TUR.y = TBL.y + (TUR.y - TBL.y) * NumOfTextures.y;
		NumOfTextures.y = 1;
	}
	bool invert_triangles = wall.invert_triangles;
    vector<vertex_t> vertices;
	FLOAT normal[3];
	if (!invert_triangles) {
		if (BL.z == UR.z) {
			normal[0] = 0.0f;
			normal[1] = 0.0f;
			normal[2] = normal_sign;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y},	{normal[0], normal[1], normal[2]}
					};
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
				}
			}
		}
		else if (BL.x == UR.x) {
			normal[0] = normal_sign;
			normal[1] = 0.0f;
			normal[2] = 0.0f;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * i},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y}, {normal[0], normal[1], normal[2]}
					};
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * i},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y},{normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * i},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
				}
			}
		}
		else if (BL.y == UR.y) {
			normal[0] = 0.0f;
			normal[1] = normal_sign;
			normal[2] = 0.0f;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y}, {normal[0], normal[1], normal[2]}
					};
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
				}
			}
		}
	}
	else {
		if (BL.z == UR.z) {
			normal[0] = 0.0f;
			normal[1] = 0.0f;
			normal[2] = normal_sign;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y}, {normal[0], normal[1], normal[2]}
					};
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);

				}
			}
		}
		else if (BL.x == UR.x) {
			normal[0] = normal_sign;
			normal[1] = 0.0f;
			normal[2] = 0.0f;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * i},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y}, {normal[0], normal[1], normal[2]},
					};
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * i},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * j, BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * (i + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x, BL.y + (UR.y - BL.y) / NumOfTextures.y * (j + 1), BL.z + (UR.z - BL.z) / NumOfTextures.x * i},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y},{normal[0], normal[1], normal[2]}};
					vertices.push_back(v);

				}
			}
		}
		else if (BL.y == UR.y) {
			normal[0] = 0.0f;
			normal[1] = normal_sign;
			normal[2] = 0.0f;
			for (int i = 0; i < NumOfTextures.x; i++) {
				for (int j = 0; j < NumOfTextures.y; j++) {
					vertex_t v = {
						{BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TUR.y}, {normal[0], normal[1], normal[2]}
					};
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * j},   {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TUR.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * (i + 1), BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},    {1.0f, 1.0f, 1.0f, 1.0f},    {TUR.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
					v = { {BL.x + (UR.x - BL.x) / NumOfTextures.x * i, BL.y, BL.z + (UR.z - BL.z) / NumOfTextures.y * (j + 1)},   {1.0f, 1.0f, 1.0f, 1.0f},    {TBL.x, TBL.y}, {normal[0], normal[1], normal[2]} };
					vertices.push_back(v);
				}
			}
		}
	}
	

    return vertices;
}
vector<vertex_t> RectangleWalls(vector<wall_t> walls) {
	vector<vertex_t> vertices;
	for (int i = 0; i < walls.size(); i++) {
		vector<vertex_t> wall_vertices = RectangleWall(walls[i]);
		vertices.insert(vertices.end(), wall_vertices.begin(), wall_vertices.end());
	}
	return vertices;
}

vector<vertex_t> FirstRoom() {
	vector<wall_t> walls = {
		//Floor (first room)
		{BLF_ROOM_CORNER, {URB_ROOM_CORNER.x, BLF_ROOM_CORNER.y, URB_ROOM_CORNER.z}, WOOD_BL, WOOD_UR, {2.0f, 5.0f}, false, 1.0f},
		//Left wall (first room)
		{{BLF_ROOM_CORNER.x, BLF_ROOM_CORNER.y, BLF_ROOM_CORNER.z}, {BLF_LEFT_WINDOW.x, URB_ROOM_CORNER.y, BLF_LEFT_WINDOW.z}, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, false, 1.0f},
		{{URB_LEFT_WINDOW.x, BLF_ROOM_CORNER.y, URB_LEFT_WINDOW.z}, {BLF_ROOM_CORNER.x, URB_ROOM_CORNER.y, URB_ROOM_CORNER.z}, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, false, 1.0f},
		{{BLF_LEFT_WINDOW.x, URB_LEFT_WINDOW.y, BLF_LEFT_WINDOW.z}, {URB_LEFT_WINDOW.x, URB_ROOM_CORNER.y, URB_LEFT_WINDOW.z}, BRICK_BL, BRICK_UR, {0.5f, 0.5f}, false, 1.0f},
		{{BLF_LEFT_WINDOW.x, BLF_ROOM_CORNER.y, BLF_LEFT_WINDOW.z}, {URB_LEFT_WINDOW.x, BLF_LEFT_WINDOW.y, URB_LEFT_WINDOW.z}, BRICK_BL, BRICK_UR, {0.5f, 0.5f}, false, 1.0f},
		{BLF_LEFT_WINDOW, URB_LEFT_WINDOW, WINDOW_BL, WINDOW_UR, {1.0f, 1.0f}, false, 1.0f},
		//Back wall (first room)
		{BLF_ROOM_CORNER, {URB_ROOM_CORNER.x, URB_ROOM_CORNER.y, BLF_ROOM_CORNER.z}, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, true, 1.0f},
		//Right wall (first room)
		{{URB_ROOM_CORNER.x, BLF_ROOM_CORNER.y, BLF_ROOM_CORNER.z}, {URB_RIGHT_WINDOW.x, URB_ROOM_CORNER.y, BLF_RIGHT_WINDOW.z}, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, true, -1.0f},
		{{URB_RIGHT_WINDOW.x, BLF_ROOM_CORNER.y, URB_RIGHT_WINDOW.z}, URB_ROOM_CORNER, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, true, -1.0f},
		{{BLF_RIGHT_WINDOW.x, URB_RIGHT_WINDOW.y, BLF_RIGHT_WINDOW.z}, {URB_RIGHT_WINDOW.x, URB_ROOM_CORNER.y, URB_RIGHT_WINDOW.z}, BRICK_BL, BRICK_UR, {0.5f, 0.5f}, true, -1.0f},
		{{BLF_RIGHT_WINDOW.x, BLF_ROOM_CORNER.y, BLF_RIGHT_WINDOW.z}, {URB_RIGHT_WINDOW.x, BLF_RIGHT_WINDOW.y, URB_RIGHT_WINDOW.z}, BRICK_BL, BRICK_UR, {0.5f, 0.5f}, true, -1.0f}, 
		{BLF_RIGHT_WINDOW, URB_RIGHT_WINDOW, WINDOW_BL, WINDOW_UR, {1.0f, 1.0f}, true, -1.0f},
		//Ceiling (first room)
		{{BLF_ROOM_CORNER.x, URB_ROOM_CORNER.y, BLF_ROOM_CORNER.z}, URB_ROOM_CORNER, WOOD_BL, WOOD_UR, {2.0f, 2.0f}, true, -1.0f},
		//Front wall (exit to corridor)
		{{BLF_ROOM_CORNER.x, BLF_ROOM_CORNER.y, URB_ROOM_CORNER.z}, {BLF_CORRIDOR_CORNER.x, URB_ROOM_CORNER.y, BLF_CORRIDOR_CORNER.z}, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, false, -1.0f},
		{{URB_CORRIDOR_CORNER.x, BLF_ROOM_CORNER.y, URB_ROOM_CORNER.z}, URB_ROOM_CORNER, BRICK_BL, BRICK_UR, {2.0f, 2.0f}, false, -1.0f},
		{{BLF_CORRIDOR_CORNER.x, URB_CORRIDOR_CORNER.y, URB_ROOM_CORNER.z}, {URB_CORRIDOR_CORNER.x, URB_ROOM_CORNER.y, URB_ROOM_CORNER.z} , BRICK_BL, BRICK_UR, {2.0f, 1.0f}, false, -1.0f},

	};
	return RectangleWalls(walls);
}
vector<vertex_t> Corridor() {
	vector<wall_t> walls = {
		//Corridor left wall
		{{BLF_CORRIDOR_CORNER.x, BLF_ROOM_CORNER.y, BLF_CORRIDOR_CORNER.z}, {BLF_CORRIDOR_CORNER.x, URB_CORRIDOR_CORNER.y, URB_CORRIDOR_CORNER.z}, BRICK_BL, BRICK_UR, {3.0f, 1.0f}, false, 1.0f},
		//Corridor ceiling
		{{BLF_CORRIDOR_CORNER.x, URB_CORRIDOR_CORNER.y, BLF_CORRIDOR_CORNER.z}, URB_CORRIDOR_CORNER, WOOD_BL, WOOD_UR, {3.0f, 1.0f}, true, -1.0f},
		//Corridor floor
		{BLF_CORRIDOR_CORNER, {URB_CORRIDOR_CORNER.x, BLF_ROOM_CORNER.y, URB_CORRIDOR_CORNER.z}, WOOD_BL, WOOD_UR, {3.0f, 4.0f}, false, 1.0f},
		//Corridor right wall
		{{URB_CORRIDOR_CORNER.x, BLF_ROOM_CORNER.y, BLF_CORRIDOR_CORNER.z}, URB_CORRIDOR_CORNER, BRICK_BL, BRICK_UR, {3.0f, 1.0f}, true, -1.0f},
	};
	return RectangleWalls(walls);
}
vector<vertex_t> SecondRoom() {
	vector<wall_t> walls = {
		//Corridor front wall
		{{BLF_CORRIDOR_CORNER.x, BLF_ROOM_2_CORNER.y, URB_CORRIDOR_CORNER.z}, {BLF_ROOM_2_CORNER.x, URB_ROOM_2_CORNER.y, BLF_ROOM_2_CORNER.z}, BRICK_BL, BRICK_UR, {1.0f, 1.0f}, false, 1.0f},
		{{URB_ROOM_2_CORNER.x, BLF_ROOM_2_CORNER.y, URB_CORRIDOR_CORNER.z}, URB_CORRIDOR_CORNER, BRICK_BL, BRICK_UR, {1.0f, 1.0f}, false, 1.0f},
		{{URB_ROOM_2_CORNER.x, URB_CORRIDOR_CORNER.y, URB_CORRIDOR_CORNER.z}, {BLF_CORRIDOR_CORNER.x, URB_ROOM_2_CORNER.y, URB_CORRIDOR_CORNER.z}, BRICK_BL, BRICK_UR, {1.0f, 1.0f}, false, 1.0f},
		//Second room floor
		{BLF_ROOM_2_CORNER, {URB_ROOM_2_CORNER.x, BLF_ROOM_2_CORNER.y, URB_ROOM_2_CORNER.z}, WOOD_BL, WOOD_UR, {4.0f, 4.0f}, false, 1.0f},
		//Second room left wall
		{BLF_ROOM_2_CORNER, {BLF_ROOM_2_CORNER.x, URB_ROOM_2_CORNER.y, URB_ROOM_2_CORNER.z}, BRICK_BL, BRICK_UR, {5.0f, 1.0f}, false, 1.0f},
		//Second room right wall
		{{URB_ROOM_2_CORNER.x, BLF_ROOM_2_CORNER.y, BLF_ROOM_2_CORNER.z}, URB_ROOM_2_CORNER, BRICK_BL, BRICK_UR, {5.0f, 1.0f}, true, -1.0f},
		//Second room ceiling
		{{BLF_ROOM_2_CORNER.x, URB_ROOM_2_CORNER.y, BLF_ROOM_2_CORNER.z}, URB_ROOM_2_CORNER, WOOD_BL, WOOD_UR, {5.0f, 1.0f}, true, -1.0f},
		//Second room back wall
		{{BLF_ROOM_2_CORNER.x, BLF_ROOM_2_CORNER.y, URB_ROOM_2_CORNER.z}, {URB_ROOM_2_CORNER.x, URB_ROOM_2_CORNER.y, URB_ROOM_2_CORNER.z}, BRICK_BL, BRICK_UR, {5.0f, 1.0f}, false, -1.0f}

	};
	return RectangleWalls(walls);
}

vector<vertex_t> DivideIntoSmallerTriangles(vector<vertex_t> vertices) {
	vector<vertex_t> new_vertices;
	for (int i = 0; i < vertices.size(); i += 3) {
		//Divide the triangle into 4 smaller triangles
		vertex_t v1 = vertices[i];
		vertex_t v2 = vertices[i + 1];
		vertex_t v3 = vertices[i + 2];
		vertex_t v1v2 = { { (v1.position[0] + v2.position[0]) / 2, (v1.position[1] + v2.position[1]) / 2, (v1.position[2] + v2.position[2]) / 2 }, {1.0f, 1.0f, 1.0f, 1.0f}, {(v1.tex_coord[0] + v2.tex_coord[0]) / 2, (v1.tex_coord[1] + v2.tex_coord[1]) / 2}, {v1.normal[0], v1.normal[1], v1.normal[2]} };
		vertex_t v2v3 = { { (v2.position[0] + v3.position[0]) / 2, (v2.position[1] + v3.position[1]) / 2, (v2.position[2] + v3.position[2]) / 2 }, {1.0f, 1.0f, 1.0f, 1.0f}, {(v2.tex_coord[0] + v3.tex_coord[0]) / 2, (v2.tex_coord[1] + v3.tex_coord[1]) / 2}, {v2.normal[0], v2.normal[1], v2.normal[2]} };
		vertex_t v1v3 = { { (v1.position[0] + v3.position[0]) / 2, (v1.position[1] + v3.position[1]) / 2, (v1.position[2] + v3.position[2]) / 2 }, {1.0f, 1.0f, 1.0f, 1.0f}, {(v1.tex_coord[0] + v3.tex_coord[0]) / 2, (v1.tex_coord[1] + v3.tex_coord[1]) / 2}, {v1.normal[0], v1.normal[1], v1.normal[2]} };
		new_vertices.push_back(v1);
		new_vertices.push_back(v1v2);
		new_vertices.push_back(v1v3);
		new_vertices.push_back(v1v2);
		new_vertices.push_back(v2);
		new_vertices.push_back(v2v3);
		new_vertices.push_back(v1v3);
		new_vertices.push_back(v2v3);
		new_vertices.push_back(v3);
		new_vertices.push_back(v1v2);
		new_vertices.push_back(v2v3);
		new_vertices.push_back(v1v3);
	}
	return new_vertices;
}
vector<vertex_t> RoomModel() {


	vector <vertex_t> firstRoom = FirstRoom();
	vector <vertex_t> corridor = Corridor();
	firstRoom.insert(firstRoom.end(), corridor.begin(), corridor.end());
	vector<vertex_t> secondRoom = SecondRoom();
	firstRoom.insert(firstRoom.end(), secondRoom.begin(), secondRoom.end());
	for (int i = 0; i < 5; i++) {
		firstRoom = DivideIntoSmallerTriangles(firstRoom);
	}
	return firstRoom;
}