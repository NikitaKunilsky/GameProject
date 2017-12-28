#ifndef _PLAYER_HEADER_H_
#define _PLAYER_HEADER_H_

#include <SFML\Graphics.hpp>

#include "Entity.h"


using namespace sf;
using namespace std;

class Player :public Entity {
public:
	int playerScore;
	bool checkImm;
	bool winStatus;
	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	~Player() {};
	void control();


	void update(float time);
	void checkCollisionWithMap(float Dx, float Dy);

	FloatRect getRect();

	void immortality(int time);

};


#endif