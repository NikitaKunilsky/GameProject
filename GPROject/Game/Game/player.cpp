#include "stdafx.h"
#include <SFML\Graphics.hpp> 
#include "player.h"
#include "map.h"
#include "Global.h"

	Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		winStatus = false;
		checkImm = false;
		state = stay;
		if (name == "Player1") {
			//«адаем спрайту один пр€моугольник дл€
			//вывода одного игрока. IntRect Ц дл€ приведени€ типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	};
	//////////////////ƒ¬»∆≈Ќ»≈////////////////////
	void Player::control() {
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			state = left;
			speed = 0.1;
		}
		else
		{
			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				state = right;
				speed = 0.1;
			}
			else
			{
				if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
					state = up;
					speed = 0.1;
				}
				else
				{
					if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
						state = down;
						speed = 0.1;
					}
					else
					{
						state = stay;
					}
				}
			}
		}
	};



	void Player::update(float time) //метод "оживлени€/обновлени€" объекта класса.
	{
		if (life) {//провер€ем, жив ли герой
			control();//функци€ управлени€ персонажем
			switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€
			{
			case right: {//состо€ние идти вправо
				dx = speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
				}
				break;
			}
			case left: {//состо€ние идти влево
				dx = -speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
				}
				break;
			}
			case up: {//идти вверх
				dy = -speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
				}
				break;
			}
			case down: {//идти вниз
				dy = speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
				}
				break;
			}
			case stay: {//стоим
				dy = speed;
				dx = speed;
				if (checkImm == false) {
					sprite.setTextureRect(IntRect(42, 144, 42, 48));
				}
				break;
			}
			}
			if (!(dx == 0)) {
				x += dx*time; //движение по УXФ
				checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
			}
			else {
				y += dy*time; //движение по УYФ
				checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
			}
			speed = 0;    //обнул€ем скорость, чтобы персонаж остановилс€.
						  //state = stay; //состо€ние - стоим

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

			if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	};

	//ћетод проверки столкновений с элементами карты
	void Player::checkCollisionWithMap(float Dx, float Dy) {
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимс€ по элементам карты
			for (int j = x / 64; j < (x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//если элемент тайлик земли
				{
					if (Dy > 0) { y = i * 64 - h;  dy = 0; }//по Y 
					if (Dy < 0) { y = i * 64 + 64; dy = 0; }//столкновение с верхними кра€ми 
					if (Dx > 0) { x = j * 64 - w; dx = 0; }//с правым краем карты
					if (Dx < 0) { x = j * 64 + 64; dx = 0; }// с левым краем карты
				}
				if (TileMap[i][j] == 's') {
					playerScore += 4; //если вз€ли камень
					TileMap[i][j] = ' ';
				}
				if ((TileMap[i][j] == 'f') && (checkImm == false)) {
					health -= 40;//если вз€ли €довитый цветок
					checkImm = true;
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//если вз€ли сердечко
					TileMap[i][j] = ' ';//убрали сердечко
				}
				if (TileMap[i][j] == 'r') {
					winStatus = true;
				}
			}
	};

	void Player::immortality(int time)
	{
		switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case right: {//состо€ние идти вправо
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;

			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));

			break;
		}
		case left: {//состо€ние идти влево
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;

			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));

			break;
		}
		case up: {//идти вверх
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));

			break;
		}
		case down: {//идти вниз
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
			break;
		}
		case stay: {//стоим
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42, 144, 42, 48));



			break;
		}
		}
		life = true;
		health = health;
	};