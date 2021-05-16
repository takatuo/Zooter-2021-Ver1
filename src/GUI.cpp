#include "raylib.h"
#include <iostream>
#include "Zookeeper.h"
#include "Enemies.h"


//Global Variables
int currentScreen = 0; // 0 = Main Menu, 1 = Ingame, 2 = Credits, 3 = GameOver, 4 = Game Won
int score = 0; 
int zoolife = 3;
Vector2 mousepoint;

Music music;
bool MusicPlaying = false;


//Back Button for Over, Win & Credits
Texture2D backButtonA;
Texture2D backButtonB;

Rectangle backButtonRec {320, 400, 287, 84 };


// Main Menu
Texture2D mainmenuBG;
Texture2D startButtonA;
Texture2D startButtonB;
Texture2D quitButtonA;
Texture2D quitButtonB;
Texture2D creditButtonA;
Texture2D creditButtonB;

Rectangle startButtonRec{ 320, 250, 287, 84 };
Rectangle quitButtonRec{ 320, 350, 287, 84 };
Rectangle creditButtonRec{ 785, 450, 156, 84 };


// Ingame
Texture2D ingameBG;

Texture2D playerChar;
Texture2D heartblack;
Texture2D heart1;
Texture2D heart2;
Texture2D heart3;

Texture2D sheep;
Texture2D monkey;
Texture2D lion;
Texture2D lama;
Texture2D bullet;
Texture2D hedgeL;
Texture2D hedgeR;
Texture2D enemyShot[2]; // 0 = Spit, 1 = Banana

Rectangle enemyRec[40]; // Max. number of Enemies
Rectangle bulletRec;
Rectangle sheepRec;
Rectangle enemyBulRec;
Rectangle playerRec;
Rectangle dangerZone = { 0, 400, 960, 140 };


//Credit Screen
Texture2D backButtonSmallA;
Texture2D backButtonSmallB;

Rectangle backButtonSmallRec{ 785, 450, 156, 84 };


//Game Over
Texture2D gameoverBG;


//Game Won
Texture2D gamewonBG;


void InitTextures() { 

	//Menuscreen
	mainmenuBG = LoadTexture("assets/graphics/Titlescreen.png");
	startButtonA = LoadTexture("assets/graphics/Button_Start_A.png");
	quitButtonA = LoadTexture("assets/graphics/Button_Quit_A.png");
	startButtonB = LoadTexture("assets/graphics/Button_Start_B.png");
	quitButtonB = LoadTexture("assets/graphics/Button_Quit_B.png");
	creditButtonA = LoadTexture("assets/graphics/Button_Credits_A.png");
	creditButtonB = LoadTexture("assets/graphics/Button_Credits_B.png");


	//Ingame
	ingameBG = LoadTexture("assets/graphics/Ingame_Background.png"); 
	playerChar = LoadTexture("assets/graphics/Zookeeper.png");
	bullet = LoadTexture("assets/graphics/Bullet_Player.png");
	heartblack = LoadTexture("assets/graphics/Heartblack.png");
	heart1 = LoadTexture("assets/graphics/Heart.png");
	heart2 = LoadTexture("assets/graphics/Heart.png");
	heart3 = LoadTexture("assets/graphics/Heart.png");

	sheep = LoadTexture("assets/graphics/Sheep.png");
	monkey = LoadTexture("assets/graphics/Monkey.png");
	lion = LoadTexture("assets/graphics/Lion.png");
	lama = LoadTexture("assets/graphics/Lama.png");
	hedgeL = LoadTexture("assets/graphics/Hedge_Left.png");
	hedgeR = LoadTexture("assets/graphics/Hedge_Right.png");
	enemyShot[0] = LoadTexture("assets/graphics/Spit.png");
	enemyShot[1] = LoadTexture("assets/graphics/Banana.png");

	bulletRec = { 0, 0, (float)bullet.width, (float)bullet.height }; // Schuss zeichnen
	enemyBulRec = { 0, 0, (float)enemyShot[0].width, (float)enemyShot[0].height }; // Enemy Schuss
	playerRec = { 0, 0, (float)playerChar.width, (float)playerChar.height };


	//Game Over
	gameoverBG = LoadTexture("assets/graphics/GameOver.png");


	//Game Won
	gamewonBG = LoadTexture("assets/graphics/GameWon.png");


	//Back Button
	backButtonA = LoadTexture("assets/graphics/Button_Back_A.png");
	backButtonB = LoadTexture("assets/graphics/Button_Back_B.png");

	//Credit Textures
	backButtonSmallA = LoadTexture("assets/graphics/Button_smallBack_A.png");
	backButtonSmallB = LoadTexture("assets/graphics/Button_smallBack_B.png");
}

//Music
void InitAudio() {
	music = LoadMusicStream("assets/audio/tracks/DaveJf_Sound70.mp3");
}

//switching between screens
void ScreenHandler() { 

	void MainMenuDraw(void); // need to be initiated here for switch-case
	void MainMenuUpdate(void);

	void IngameDraw();
	void IngameUpdate();

	void CreditScreenDraw();
	void CreditScreenUpdate();

	void GameOverDraw();
	void GameOverUpdate();

	void GameWonDraw();
	void GameWonUpdate(); 

	mousepoint = GetMousePosition(); //realtime mouse position

	//switch-case for screens
	switch (currentScreen) { 
	case 0:
		MainMenuDraw();
		MainMenuUpdate();
		break;
	case 1:
		IngameDraw();
		IngameUpdate();
		break;
	case 2:
		CreditScreenDraw();
		CreditScreenUpdate();
		break;
	case 3:
		GameOverDraw();
		GameOverUpdate();
		break;
	case 4:
		GameWonDraw();
		GameWonUpdate();
		break;
	default: // none of the current screens -> u made a mistake
		std::cout << "Fehler bei den Funktion ScreenHandler in GUI.cpp durch die Variable currentScreen";
		break;
	}
}

// --------------------------------------------------------------------------

void MainMenuUpdate() { 

	//Start Button
	if (CheckCollisionPointRec(mousepoint, startButtonRec)) {
		DrawTexture(startButtonB, 320, 250, WHITE); 
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			currentScreen = 1;
			InitEnemies(); // !!! 
			zoolife = 3;
			score = 0;
		}
	}
	else {
		DrawTexture(startButtonA, 320, 250, WHITE); 
	}

	//Quit Button
	if (CheckCollisionPointRec(mousepoint, quitButtonRec)) { 
		DrawTexture(quitButtonB, 320, 350, WHITE);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			exit(0);
		}
	}
	else {
		DrawTexture(quitButtonA, 320, 350, WHITE); 
	}

	//Credit Button
	if (CheckCollisionPointRec(mousepoint, creditButtonRec)) {
		DrawTexture(creditButtonB, 785, 450, WHITE);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			currentScreen = 2;
		}
	}
	else {
			DrawTexture(creditButtonA, 785, 450, WHITE);
	}
}



void MainMenuDraw() { 
	DrawTexture(mainmenuBG, 0, 0, WHITE);
}

// --------------------------------------------------------------------------

void IngameDraw() {

	DrawTexture(ingameBG, 0, 0, WHITE);

	DrawTexture(playerChar, GivePlayerPos().x, GivePlayerPos().y, WHITE);
	DrawTexture(bullet, GiveBulletPos().x, GiveBulletPos().y, WHITE);

	DrawTexture(hedgeL, 20, 100, WHITE);
	DrawTexture(hedgeR, 920, 100, WHITE);

	DrawText(TextFormat("Score: %04i", score), 770, 470, 20, BLACK);

	DrawTexture(heart1, 810, 495, WHITE);
	DrawTexture(heart2, 790, 495, WHITE);
	DrawTexture(heart3, 770, 495, WHITE);


	if (EnemyShotActive() == true) {
		if (GiveEnemyBulType() == 0) {
			DrawTexture(enemyShot[1], GiveEnemyShotPos().x, GiveEnemyShotPos().y, WHITE);
		}
		else {
			DrawTexture(enemyShot[0], GiveEnemyShotPos().x, GiveEnemyShotPos().y, WHITE);
		}
	}

	// Spawning Enemies - REMEMBER to change in GUI + Enemies
	for (int i = 0; i < 40; i++) {
		if (i < 10 && GiveEnemyActive(i) == true) { 
			enemyRec[i].width = monkey.width;
			enemyRec[i].height = monkey.height;
			DrawTexture(monkey, enemyRec[i].x, enemyRec[i].y, WHITE);
		}
		else if (i < 20 && GiveEnemyActive(i) == true) { 
			enemyRec[i].width = lama.width;
			enemyRec[i].height = lama.height;
			DrawTexture(lama, enemyRec[i].x, enemyRec[i].y, WHITE);
		}
		else if (i < 30 && GiveEnemyActive(i) == true) {
			enemyRec[i].width = lion.width;
			enemyRec[i].height = lion.height;
			DrawTexture(lion, enemyRec[i].x, enemyRec[i].y, WHITE);
		}
		else if (i < 40 && GiveEnemyActive(i) == true) {
			enemyRec[i].width = sheep.width;
			enemyRec[i].height = sheep.height;
			DrawTexture(sheep, enemyRec[i].x, enemyRec[i].y, WHITE);
		}
	}

	// DrawRectangleRec(dangerZone, RED); //DEBUG!!!
}


void IngameUpdate() {

	bulletRec.x = GiveBulletPos().x;
	bulletRec.y = GiveBulletPos().y;

	enemyBulRec.x = GiveEnemyShotPos().x;
	enemyBulRec.y = GiveEnemyShotPos().y;

	playerRec.x = GivePlayerPos().x;
	playerRec.y = GivePlayerPos().y;


	// Enemy++ till 40
	for (int i = 0; i < 40; i++) { 
		enemyRec[i].x = GiveEnemyPos(i).x;
		enemyRec[i].y = GiveEnemyPos(i).y;
	}
	for (int i = 0; i < 40; i++) {
		if (CheckCollisionRecs(enemyRec[i], bulletRec) && GiveEnemyActive(i) == true) { 
			KillEnemy(i); 
			DeleteShot(); 
			score++; 
		}
	}


	//Collision with EnemyBullet & Player
	if (CheckCollisionRecs(playerRec, enemyBulRec)) {
		zoolife--;
		DestroyEnemyBul();
	}


	//hearts
	if (zoolife == 2) {
		DrawTexture(heartblack, 770, 495, WHITE);
	}
	if (zoolife == 1) {
		DrawTexture(heartblack, 790, 495, WHITE);
		DrawTexture(heartblack, 770, 495, WHITE);
	}
	if (zoolife == 0) {
		DrawTexture(heartblack, 810, 495, WHITE);
		DrawTexture(heartblack, 790, 495, WHITE);
		DrawTexture(heartblack, 770, 495, WHITE);
	}


	//Collission with dangerZone (Enemies hit playerPos) 
	for (int i = 0; i < 40; i++) {
		if (CheckCollisionRecs(enemyRec[i], dangerZone) && GiveEnemyActive(i) == true) {
			currentScreen = 3;
		}
	}


	//Loose Condition
	if (zoolife == 0) {
		currentScreen = 3;
	}


	//Win Condition
	if (score == 70) {
		currentScreen = 4;
		score = 0;
	}


	//Music
	if (!MusicPlaying) {
		SetMusicVolume(music, 0.05f);
		PlayMusicStream(music);
		MusicPlaying = true;
	}

	UpdateMusicStream(music);
}

// --------------------------------------------------------------------------

//Credit Screen
void CreditScreenUpdate() {

	if (CheckCollisionPointRec(mousepoint, backButtonSmallRec)) {
		DrawTexture(backButtonSmallB, 785, 450, WHITE);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			currentScreen = 0;
		}
	}
	else {
		DrawTexture(backButtonSmallA, 785, 450, WHITE); //no collision
	}
}


void CreditScreenDraw() {
	DrawTexture(mainmenuBG, 0, 0, WHITE);

	DrawText(TextFormat("CREDITS"), GetScreenWidth() / 2 - 100, 250, 40, BLACK);
	DrawText(TextFormat("Programmer:\nJasmin Fischer"), GetScreenWidth() / 2 - 100, 300, 20, BLACK);
	DrawText(TextFormat("Art Team:\nRebecca Keppel\nMarcel Rettenbacher"), GetScreenWidth() / 2 - 100, 350, 20, BLACK);
	DrawText(TextFormat("Music:\nDaveJf - Sounds 70s\n (freesounds.org)"),GetScreenWidth() / 2 - 100, 450, 20, BLACK);
}

// --------------------------------------------------------------------------

//Game Over 
void GameOverUpdate() {

	if (CheckCollisionPointRec(mousepoint, backButtonRec)) { 
		DrawTexture(backButtonB, 320, 400, WHITE); 
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			currentScreen = 0;
		}
	}
	else {
		DrawTexture(backButtonA, 320, 400, WHITE); //no collision
	}
}

void GameOverDraw() {
	DrawTexture(gameoverBG, 0, 0, WHITE);
}

// --------------------------------------------------------------------------

void GameWonUpdate() {

	if (CheckCollisionPointRec(mousepoint, backButtonRec)) { 
		DrawTexture(backButtonB, 320, 400, WHITE); 
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			currentScreen = 0;
		}
	}
	else {
		DrawTexture(backButtonA, 320, 400, WHITE); //no collison
	}
}

void GameWonDraw() {
	DrawTexture(gamewonBG, 0, 0, WHITE);
}

// --------------------------------------------------------------------------


//Other Functions
int GiveCurrentScreen() {
	return currentScreen;
}

int PlayerWidth() {
	return playerChar.width;
}