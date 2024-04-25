#pragma once
#include <d3d12.h>
#include <array>
#include <vector>

namespace {
    using std::array;
    using std::vector;
}
struct coordinate_t {
	FLOAT x;
	FLOAT y;
	FLOAT z;
};

struct vertex_t {
    FLOAT position[3];
    FLOAT color[4];
    FLOAT tex_coord[2];
	FLOAT normal[3];
};
struct wall_t {
	coordinate_t BL;
	coordinate_t UR;
	coordinate_t TBL;
	coordinate_t TUR;
	coordinate_t NumOfTextures;
	bool invert_triangles;
	FLOAT normal_sign;
};

struct prism_t {
	coordinate_t BLF;
	coordinate_t URB;
};

static coordinate_t BLF_ROOM_CORNER = { -10.0f, 0.0f, -10.0f };
static coordinate_t URB_ROOM_CORNER = { 10.0f, 8.0f, 10.0f };
static coordinate_t BLF_CORRIDOR_CORNER = { -5.0f, 0.0f, 10.0f };
static coordinate_t URB_CORRIDOR_CORNER = { 5.0f, 4.0f, 30.0f };
static coordinate_t BLF_ROOM_2_CORNER = { -20.0f, 0.0f, 30.0f };
static coordinate_t URB_ROOM_2_CORNER = { 20.0f, 4.0f, 50.0f };
static coordinate_t BLF_LEFT_WINDOW = { -10.0f, 2.0f, -3.0f };
static coordinate_t URB_LEFT_WINDOW = { -10.0f, 6.0f, 3.0f };
static coordinate_t BLF_RIGHT_WINDOW = { 10.0f, 2.0f, -3.0f };
static coordinate_t URB_RIGHT_WINDOW = { 10.0f, 6.0f, 3.0f };
static coordinate_t WOOD_BL = { 0.5f, 0.0f, 0.0f };
static coordinate_t WOOD_UR = { 1.0f, 0.5f, 1.0f };
static coordinate_t BRICK_BL = {0.0f, 0.0f, 0.0f};
static coordinate_t BRICK_UR = { 0.5f, 0.5f, 0.0f };
static coordinate_t WINDOW_BL = { 0.0f, 0.5f, 0.0f };
static coordinate_t WINDOW_UR = { 0.5f, 1.0f, 1.0f };


constinit size_t const VERTEX_SIZE = sizeof(vertex_t) / sizeof(FLOAT);
vector<vertex_t> RectangleWall(wall_t);
vector<vertex_t> RectangleWalls(vector<wall_t> walls);
vector<vertex_t> RoomModel();
