#include <bits/stdc++.h>
#include <conio.h> // console input output
#include <windows.h>

using namespace std;

//Snake game.

bool GAMEOVER;

const int width = 40;
const int height = 20;

int headX, headY, fruitX, fruitY, score;

int tailX[100], tailY[100];
int tailLength;

enum snakeDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
snakeDirection dir;

void init() {
	GAMEOVER = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width; // random number from 0 to WIDTH-1
	fruitY = rand() % height; // random number from 0 to HEIGHT-1
	score = 0;
}

void draw() {
	system("cls"); // terminal command to clear console
	
	//print the top border

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << "\n";

	//print game content

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) cout << "#";
			if (i == headY && j == headX) {
				cout << "O";
			} else if (i == fruitY && j == fruitX) {
				cout << "F";
			} else {
				bool isTailPrinted = false;
				for (int k = 0; k < tailLength; k++) {
					if (i == tailY[k] && j == tailX[k]) {
						cout << "o";
						isTailPrinted = true;
					}
				}
				if (!isTailPrinted) cout << " ";
			}
 			if (j == width-1) cout << "#";
		}
		cout << "\n";
	}


	//print the bottom border

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	printf("\nScore:%d\n", score);
}

void input() {
	//uses async functions from conio.h
	if (_kbhit()) {
		// positive number returns if char in keyboard is pressed
		switch(_getch()) {
			case 'w':
				dir = UP;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				GAMEOVER = true;
				break;
		}
	}
}

void displayDieMessage() {
	GAMEOVER = true;
	MessageBoxA(nullptr, TEXT( "Game Over!!" ), TEXT( "You Died" ), MB_OK | MB_ICONEXCLAMATION);
}

void logic() {
	int prevX = tailX[0]; // previous x and y coord of the tail
	int prevY = tailY[0];
	int prevTempX, prevTempY;

	tailX[0] = headX;
	tailY[0] = headY;

	for (int i = 1; i < tailLength; i++) { // start from 1 because the 1st segment is head
		prevTempX = tailX[i];
		prevTempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevTempX;
		prevY = prevTempY;
	}

	switch(dir) {
		case UP:
			headY--;
			break;
		case LEFT:
			headX--;
			break;
		case DOWN:
			headY++;
			break;
		case RIGHT:
			headX++;
			break;
		default:
			break;
	}
	if (headX > width || headX < 0 || headY > height || headY < 0) {
		displayDieMessage();
	}
	if (headX == fruitX && headY == fruitY) {
		score+=10;
		fruitX = rand() % width; // random number from 0 to WIDTH-1
		fruitY = rand() % height; // random number from 0 to HEIGHT-1
		tailLength++;
	}
	for (int i = 0; i < tailLength; i++) {
		if (tailX[i] == headX && tailY[i] == headY) {
			displayDieMessage();
		}
	}
}

int main() {
	init();
	while (!GAMEOVER) {
		draw();
		input();
		logic();
		Sleep(100);
	}
}