#ifndef _ENEMY_HEADER_H_
#define _ENEMY_HEADER_H_

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Entity.h"


using namespace sf;
using namespace std;

class Enemy :public Entity {
public:
	int direction;//направление движения врага
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	~Enemy()
	{
		std::cout << "Enemy down";
	};

	void checkCollisionWithMap(float Dx, float Dy);//ф-ция проверки столкновений с картой
    void update(float time); //метод "оживления/обновления" объекта класса.

};//класс Enemy закрыт
#endif