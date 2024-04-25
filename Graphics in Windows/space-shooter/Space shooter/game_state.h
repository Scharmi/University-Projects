#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>
#include <set>
struct PressedKeys {
	bool left;
	bool right;
	bool up;
	bool down;
	bool space;
};
struct Coords {
	float x;
	float y;
};
const struct GameConsts {
	const float SCREEN_WIDTH = 1000;
	const float SCREEN_HEIGHT = 1000;
	const int MAX_LIVES = 3;
	const int ASTEROID_ROTATION = 10;
	const int ASTEROID_ROTATION_SPEED = 10;
	const float BULLET_SPEED = 4.0f;
	const int SHOOT_COOLDOWN = 300;
	const float X_ROCKET_SPEED_CHANGE_COEFF = 0.003f;
	const float Y_ROCKET_SPEED_CHANGE_COEFF = 0.003f;
	const float BOUNCE_COEFF = 0.4f;
	const float MAX_ROCKET_SPEED = 0.8f;
	const float ROCKET_FRICTION = 0.0005f;
};
class Bullet {
public:
	Bullet(float, float, float);
	void update(int);
	Coords get_coords();
private:
	float x_pos;
	float y_pos;
	float bullet_speed;
};

class Rocket {
public:
	Rocket();
	Bullet shoot_left();
	Bullet shoot_right();
	void update(PressedKeys, int);
	Coords get_coords();
private:
	GameConsts consts;
	float x_pos;
	float y_pos;
	float x_speed;
	float y_speed;
	int size;
};
class Asteroid {
public:
	Asteroid(float, float, float, float, float, float);
	void update(int);
	Coords get_coords();
	float get_radius();
	float get_rotation();
	Asteroid& operator = (const Asteroid& other);
	void remove();
private:
	GameConsts consts;
	float x_pos;
	float y_pos;
	float x_speed;
	float y_speed;
	float rotation;
	float rotation_speed;
	float radius;
	float size;
};
class GameState {
public:
	GameState();
	void update(PressedKeys, int);
	Rocket get_rocket();
	std::vector<Bullet> get_bullets();
	std::vector<Asteroid> get_asteroids();
	int get_score();
	void add_random_asteroid();
	int get_lives();
private:
	GameConsts consts;
	Rocket rocket;
	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;
	int lives;
	int time_from_start;
	int last_shoot_time;
	int score;
	void remove_asteroid(int);
	void remove_bullet(int);
};


#endif