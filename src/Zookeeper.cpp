#include <iostream>
#include "Zookeeper.h"
#include "GUI.h"
#include "config.h"

Vector2 position;
Vector2 shootpos;

bool active = false;

int lifetime = 100;
int currentlifetime = lifetime;


//Initializing Player
void InitPlayer() {
	position = { (float)Game::ScreenWidth / 2 - (PlayerWidth() / 2), 400 };
}

//Player Movement 
void Walk() {
	if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && position.x > 40) {
		position.x -= 3;
	}
	if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && position.x < 920 - PlayerWidth()) {
		position.x += 3;
	}

	//Player Bullets
	if (IsKeyDown(KEY_SPACE)) {
		if (active == false) {
			active = true;
			shootpos = position;
			shootpos.x += PlayerWidth() / 2;
		}
	}
	if (active == true) {
		currentlifetime--;
		shootpos.y -= 10;
	}
	if (currentlifetime < 0) {
		active = false;
		currentlifetime = lifetime;
		shootpos = { 1000, 1000 };
	}
}


//Other Functions
void DeleteShot() { 
	currentlifetime = 0; //sets lifetime to 0 so only 1 enemy can be hit
}

Vector2 GiveBulletPos() {
	return shootpos;
}

Vector2 GivePlayerPos() {
	return position;
}