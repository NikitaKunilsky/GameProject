#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream> 
#include "Enemy.h"
#include "map.h"
#include "Global.h"

using namespace sf;
using namespace std;

	Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			//«адаем спрайту один пр€моугольник дл€
			//вывода одного игрока. IntRect Ц дл€ приведени€ типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % 4; //Ќаправление движени€ врага задаЄм случайным образом
									//через генератор случайных чисел
			speed = 0.075;//даем скорость.этот объект всегда двигаетс€
			dx = speed;
		}
	};


	void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ци€ проверки столкновений с картой
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимс€ по элементам карты
			for (int j = x / 64; j<(x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')  //если элемент - тайлик земли
				{
					if (Dy > 0) {
						y = i * 64 - h;  dy = -0.1;
						direction = rand() % 4; //Ќаправление движени€ врага
					}//по Y 
					if (Dy < 0) {
						y = i * 64 + 64; dy = 0.1;
						direction = rand() % 4;//Ќаправление движени€ врага 
					}//столкновение с верхними кра€ми 
					if (Dx > 0) {
						x = j * 64 - w; dx = -0.1;
						direction = rand() % 4;//Ќаправление движени€ врага 
					}//с правым краем карты
					if (Dx < 0) {
						x = j * 64 + 64; dx = 0.1;
						direction = rand() % 4; //Ќаправление движени€ врага
					}// с левым краем карты
				}
			}
	};

	void Enemy::update(float time) //метод "оживлени€/обновлени€" объекта класса.
	{
		if (name == "EasyEnemy") {//дл€ персонажа с таким именем логика будет такой

			if (life) {//провер€ем, жив ли герой
				dx = 0;
				dy = 0;
				switch (direction)//делаютс€ различные действи€ в зависимости от состо€ни€
				{
				case 0: {//состо€ние идти вправо

					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
					break;
				}
				case 1: {//состо€ние идти влево
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
					break;
				}
				case 2: {//идти вверх
					dy = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
					break;
				}
				case 3: {//идти вниз
					dy = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
					break;

				}
				}


				x += dx*time; //движение по УXФ
				checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’


				y += dy*time; //движение по УYФ
				checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y


				sprite.setPosition(x, y); //спрайт в позиции (x, y).

				if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			}
		}


	};

