#include "game_state.h"
#include <algorithm>
#include <vector>
#include <math.h>
#include <random>
#include <iostream>


namespace {
	float getRandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
	bool collision(Asteroid asteroid, Bullet bullet) {
		return sqrt(pow(asteroid.get_coords().x - bullet.get_coords().x, 2) + pow(asteroid.get_coords().y - bullet.get_coords().y, 2)) < asteroid.get_radius();
	}
	bool collision(Asteroid asteroid, Rocket rocket) {
		return sqrt(pow(asteroid.get_coords().x - (rocket.get_coords().x), 2) + pow(asteroid.get_coords().y - (rocket.get_coords().y), 2)) < asteroid.get_radius() + 50;
	}
}
Rocket::Rocket() {
	x_pos = 500;
	y_pos = 800;
	x_speed = 0;
	y_speed = 0;
	size = 10;
}
Bullet Rocket::shoot_left() {
	return Bullet(x_pos + 8, y_pos + 80, this->consts.BULLET_SPEED);
}
Bullet Rocket::shoot_right() {
	return Bullet(x_pos + 80, y_pos + 80, this->consts.BULLET_SPEED);
}
void Rocket::update(PressedKeys keys, int time) {
	float x_speed_change = 0;
	float y_speed_change = 0;
	x_speed_change += keys.right;
	x_speed_change -= keys.left;
	y_speed_change += keys.down;
	y_speed_change -= keys.up;
	x_speed += x_speed_change * time * consts.X_ROCKET_SPEED_CHANGE_COEFF;
	y_speed += y_speed_change * time * consts.Y_ROCKET_SPEED_CHANGE_COEFF; 
	x_pos += x_speed * time;
	x_pos = std::max(x_pos, 0.0f);
	x_pos = std::min(x_pos, consts.SCREEN_WIDTH - 90);
	if (x_pos == 0.0f || x_pos == consts.SCREEN_WIDTH - 90) {
		x_speed = -x_speed * consts.BOUNCE_COEFF;
	}
	y_pos += y_speed * time;
	y_pos = std::max(y_pos, 0.0f);
	y_pos = std::min(y_pos, consts.SCREEN_HEIGHT - 80);
	if (y_pos == 0.0f || y_pos == consts.SCREEN_WIDTH - 80) {
		y_speed = -y_speed * consts.BOUNCE_COEFF;
	}
	y_speed = std::max(y_speed, -consts.MAX_ROCKET_SPEED);
	y_speed = std::min(y_speed, consts.MAX_ROCKET_SPEED);
	x_speed = std::max(x_speed, -consts.MAX_ROCKET_SPEED);
	x_speed = std::min(x_speed, consts.MAX_ROCKET_SPEED);
	if (keys.right == 0 && keys.left == 0) {
		if (x_speed > 0) {
			x_speed -= consts.ROCKET_FRICTION * time;
			x_speed = std::max(x_speed, 0.0f);
		}
		else {
			x_speed += consts.ROCKET_FRICTION * time;
			x_speed = std::min(x_speed, 0.0f);
		}
	}
	if (keys.up == 0 && keys.down == 0) {
		if (y_speed > 0) {
			y_speed -= consts.ROCKET_FRICTION * time;
			y_speed = std::max(y_speed, 0.0f);
		}
		else {
			y_speed += consts.ROCKET_FRICTION * time;
			y_speed = std::min(y_speed, 0.0f);
		}
	}
}

Bullet::Bullet(float x_pos, float y_pos, float bullet_speed) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->bullet_speed = bullet_speed;
}

void Bullet::update(int time) {
	y_pos -= bullet_speed * time;
}

Coords Bullet::get_coords() {
	return Coords(x_pos, y_pos);
}
float Asteroid::get_rotation() {
	return rotation;
}
void Asteroid::update(int time) {
	x_pos += x_speed * time;
	y_pos += y_speed * time;
	if (x_pos < 0 || x_pos > consts.SCREEN_WIDTH) {
		x_speed = -x_speed;
	}
	rotation += rotation_speed * time;
}
Asteroid::Asteroid(float x_pos, float y_pos, float x_speed, float y_speed, float size, float rotation_speed) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->x_speed = x_speed;
	this->y_speed = y_speed;
	this->size = size;
	this->rotation_speed = rotation_speed;
	this->rotation = 0.0f;
}
Asteroid & Asteroid::operator =(const Asteroid & other){
	x_pos = other.x_pos;
	y_pos = other.y_pos;
	x_speed = other.x_speed;
	y_speed = other.y_speed;
	rotation = other.rotation;
	rotation_speed = other.rotation_speed;
	radius = other.radius;
	size = other.size;
	return *this;
}
void Asteroid::remove() {
	x_pos = -1000;
	y_pos = -1000;
	x_speed = 0;
	y_speed = 0;
	size = 0;
}
Coords Asteroid::get_coords() {
	return Coords(x_pos, y_pos);
}
float Asteroid::get_radius() {
	return size;
}
Coords Rocket::get_coords() {
	return Coords(x_pos, y_pos);
}
GameState::GameState() {
	lives = 3;
	time_from_start = 0;
	last_shoot_time = -consts.SHOOT_COOLDOWN;
	score = 0;
}

void GameState::update(PressedKeys keys, int time) {
	time_from_start += time;
	rocket.update(keys, time);
	if(time_from_start % 400 == 0)
		add_random_asteroid();
	if ((keys.space) && (time_from_start - last_shoot_time) > consts.SHOOT_COOLDOWN) {
		last_shoot_time = time_from_start;
		bullets.push_back(rocket.shoot_left());
		bullets.push_back(rocket.shoot_right());
	}
	for (auto& bullet : bullets) {
		bullet.update(time);
	}
	for (auto& asteroid : asteroids) {
		asteroid.update(time);
	}
	for (int i = 0; i < asteroids.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (collision(asteroids[i], bullets[j])) {
				remove_asteroid(i);
				remove_bullet(j);
				score += 10;
			}
		}
	}
	for (int i = 0; i < asteroids.size(); i++) {
		if (collision(asteroids[i], rocket)) {
			remove_asteroid(i);
			if(lives >= 0)
			lives--;
			else {
				exit(0);
			}
		}
	}

}
Rocket GameState::get_rocket() {
	return rocket;
}
std::vector<Bullet> GameState::get_bullets() {
	return bullets;
}
std::vector<Asteroid> GameState::get_asteroids() {
	return asteroids;
}
void GameState::remove_asteroid(int index) {
	asteroids[index].remove();
}
void GameState::remove_bullet(int index) {
	bullets.erase(bullets.begin() + index);
}
void GameState::add_random_asteroid() {
	float radius = getRandomFloat(40, 150);
	asteroids.push_back(Asteroid(500, -radius, 0.4f * getRandomFloat(-2,2), 0.4f * getRandomFloat(0,2), radius, getRandomFloat(0, 0.5f)));
}
int GameState::get_score() {
	return score;
}
int GameState::get_lives() {
	return lives;
}
