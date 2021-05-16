#include <iostream>
#include "raylib.h"
#include "string"
#include "GUI.h"

typedef struct Enemy {
	Vector2 enemyPos;
	bool alive = true;
	std::string enemyType;
	int enemyLife = 0;
}   Enemy;

bool movement = true; // true = right, false = left

int enemyLife = 0;
Enemy enemies[40];

Vector2 enemyBulPos;
bool bulActive = false;
int enemyBulLifeTime = 120;
int bulType; // 0 = spit , 1 = banana

void InitEnemies() { // REMINDER: change position in GUI too!

	//Monkeys
	for (int i = 0; i < 10; i++) {
		enemies[i].enemyPos = { (float)50 + (i * 64), 100 }; 
		enemies[i].enemyType = "Monkey";
		enemies[i].enemyLife = 1;
		enemies[i].alive = true;
	}

	//Lama
	for (int i = 10; i < 20; i++) {
		enemies[i].enemyPos = { (float)50 + ((i - 10) * 64), 150 }; // -10, dass Position für Sheep wieder bei 0 anfängt, für 10 - 19
		enemies[i].enemyType = "Lama";
		enemies[i].enemyLife = 1;
		enemies[i].alive = true;
	}

	//Lion
	for (int i = 20; i < 30; i++) {
		enemies[i].enemyPos = { (float)50 + ((i - 20) * 64), 200 };
		enemies[i].enemyType = "Lion";
		enemies[i].enemyLife = 3;
		enemies[i].alive = true;
	}

	//Sheeps
	for (int i = 30; i < 40; i++) {
		enemies[i].enemyPos = { (float)50 + ((i - 30) * 64), 240 };
		enemies[i].enemyType = "Sheep";
		enemies[i].enemyLife = 2;
		enemies[i].alive = true;
	}
	movement = true; //causing enemy to moves after game start
}


void UpdateEnemy() {

	if (GiveCurrentScreen() == 1) {

		int chosenOne = GetRandomValue(0, 19); //choosing random enemy

		if (bulActive == false && enemies[chosenOne].alive) { // bulpos = enemypos
			enemyBulPos = enemies[chosenOne].enemyPos;
			enemyBulPos.x += 20;
			bulActive = true;
			enemyBulLifeTime = 120;
			if (chosenOne < 10) { // choosing which enemy shoots
				bulType = 0;
			}
			else {
				bulType = 1;
			}
		}

		//Enemy Bullets
		else {
			enemyBulLifeTime--;
			enemyBulPos.y += 5; // bulletspeed
		}

		if (enemyBulLifeTime <= 0) {
			bulActive = false;
		}

		if (movement == true) {
			if (enemies[9].enemyPos.x <= 850) { // move to right
				for (int i = 0; i < 40; i++) {
					enemies[i].enemyPos.x += 1;
				}
			}
			else { // move down when hitting wall
				for (int i = 0; i < 40; i++) {
					enemies[i].enemyPos.y += 10; // move down
				}
				movement = false;
			}
		}
		else {
			if (enemies[0].enemyPos.x >= 40) { // move to left
				for (int i = 0; i < 40; i++) {
					enemies[i].enemyPos.x -= 1;
				}
			}
			else { // move down when hitting wall
				for (int i = 0; i < 40; i++) {
					enemies[i].enemyPos.y += 10; // move down
				}
				movement = true;
			}
		}
	}
}


void KillEnemy(int index) { //parameter
	enemies[index].enemyLife = enemies[index].enemyLife - 1;
	if (enemies[index].enemyLife == 0) {
		enemies[index].alive = false; // Deleting Enemie -> stops drawing 
	}
}

Vector2 GiveEnemyPos(int index) {
	return enemies[index].enemyPos;
}

Vector2 GiveEnemyShotPos() {
	return enemyBulPos;
}

bool EnemyShotActive() {
	return bulActive;
}

void DestroyEnemyBul() {
	bulActive = false;
	enemyBulPos = { 0, 0 };
}

int GiveEnemyBulType() { 
	return bulType;
}

bool GiveEnemyActive(int index) { 
	return enemies[index].alive;
}
