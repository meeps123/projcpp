#include <bits/stdc++.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
using namespace std;

enum eDir {
	STOP = 0, 
	LEFT = 1, 
	UPLEFT = 2,
	DOWNLEFT = 3,
	RIGHT = 4,
	UPRIGHT = 5,
	DOWNRIGHT = 6};

// class for the pong ball
class cBall {
private:
	int ballX, ballY;
	int originalX, originalY;
	eDir ballDir;
public:
	cBall(int posX, int posY) {
		originalX = posX; // starting (x,y)
		originalY = posY;
		ballX = posX; ballY = posY;
		ballDir = STOP;
	}
	void reset() {
		ballX = originalX;
		ballY = originalY;
		ballDir = STOP;
	}
	void changeDir(eDir dir) {
		ballDir = dir;
	}
	void randomDir() {
		ballDir = (eDir) ((rand() % 6) + 1); // number from 1 to 6
	}
	inline int getX() {return ballX;}
	inline int getY() {return ballY;}
	inline eDir getDir() {return ballDir;}
	void move() {
		switch (ballDir) {
			case STOP:
				break;
			case LEFT:
				ballX--;
				break;
			case UPLEFT:
				ballX--; ballY--;
				break;
			case DOWNLEFT:
				ballX--; ballY++;
				break;
			case RIGHT:
				ballX++;
				break;
			case UPRIGHT:
				ballX++; ballY--;
				break;
			case DOWNRIGHT:
				ballX++; ballY++;
				break;
			default:
				break;
		}
	}
	friend ostream & operator<<(ostream & o, cBall c) {
		// a friend function is not a member function of cBall
		// however, it can access all member elements of cBall
		// operator<<() is known as operator overloading
		// overriding the operator << that <iostream> uses
		o << "Ball [" << c.ballX << "," << c.ballY << "][" << c.ballDir << "]";
	}
};
class cPaddle {
private:
	int paddleX, paddleY;
	int originalX, originalY;
public:
	cPaddle() {
		paddleX = paddleY = 0;
	}
	cPaddle(int posX, int posY) : cPaddle() {
		// member initialization list is the weird : thingy
		// this makes it such that 2nd constructor also calls 1st constructor
		originalX = posX;
		originalY = posY;
		paddleX = posX;
		paddleY = posY;
	}
	inline void reset() {paddleX = originalX; paddleY = originalY;}
	inline int getX() {return paddleX;}
	inline int getY() {return paddleY;}
	inline void moveUp() {paddleY--;}
	inline void moveDown() {paddleY++;}
	friend ostream & operator<<(ostream & o, cPaddle c) {
		// a friend function is not a member function of cBall
		// however, it can access all member elements of cBall
		// operator<<() is known as operator overloading
		// overriding the operator << that <iostream> uses
		o << "Paddle [" << c.paddleX << "," << c.paddleY << "]";
	}
};
class cGameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2; // chars to move player 1 up, down and player 2 up, down
	bool quit;
	cBall *ball; // create pointer to ball object
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w/2, h/2);
		player1 = new cPaddle(1, h/2 - 3);
		player2 = new cPaddle(w - 2, h/2 - 3);
	}
	~cGameManager() {
		// destructor because we are taking up dynamic memory for space using the pointers
		delete ball, player1, player2;
	}
	void increaseScore(cPaddle *player) {
		// compare the memory addresses of the param player
		if (player == player1) {
			score1++;
		} else if (player == player2) {
			score2++;
		}
		ball->reset(); // object.member, pointer->member. 
		//Remember that ball here is only a memory address reference to the object
		player1->reset(); 
		player2->reset();
	}
};	
int main() {
	int a;
	cin >> a;

	return 0;
}