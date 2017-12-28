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
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	};
	//////////////////��������////////////////////
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



	void Player::update(float time) //����� "���������/����������" ������� ������.
	{
		if (life) {//���������, ��� �� �����
			control();//������� ���������� ����������
			switch (state)//�������� ��������� �������� � ����������� �� ���������
			{
			case right: {//��������� ���� ������
				dx = speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
				}
				break;
			}
			case left: {//��������� ���� �����
				dx = -speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
				}
				break;
			}
			case up: {//���� �����
				dy = -speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
				}
				break;
			}
			case down: {//���� ����
				dy = speed;
				if (checkImm == false) {
					CurrentFrame += 0.005*time;

					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
				}
				break;
			}
			case stay: {//�����
				dy = speed;
				dx = speed;
				if (checkImm == false) {
					sprite.setTextureRect(IntRect(42, 144, 42, 48));
				}
				break;
			}
			}
			if (!(dx == 0)) {
				x += dx*time; //�������� �� �X�
				checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			}
			else {
				y += dy*time; //�������� �� �Y�
				checkCollisionWithMap(0, dy);//������������ ������������ �� Y
			}
			speed = 0;    //�������� ��������, ����� �������� �����������.
						  //state = stay; //��������� - �����

			sprite.setPosition(x, y); //������ � ������� (x, y).

			if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	};

	//����� �������� ������������ � ���������� �����
	void Player::checkCollisionWithMap(float Dx, float Dy) {
		for (int i = y / 64; i < (y + h) / 64; i++)//���������� �� ��������� �����
			for (int j = x / 64; j < (x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//���� ������� ������ �����
				{
					if (Dy > 0) { y = i * 64 - h;  dy = 0; }//�� Y 
					if (Dy < 0) { y = i * 64 + 64; dy = 0; }//������������ � �������� ������ 
					if (Dx > 0) { x = j * 64 - w; dx = 0; }//� ������ ����� �����
					if (Dx < 0) { x = j * 64 + 64; dx = 0; }// � ����� ����� �����
				}
				if (TileMap[i][j] == 's') {
					playerScore += 4; //���� ����� ������
					TileMap[i][j] = ' ';
				}
				if ((TileMap[i][j] == 'f') && (checkImm == false)) {
					health -= 40;//���� ����� �������� ������
					checkImm = true;
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������
					TileMap[i][j] = ' ';//������ ��������
				}
				if (TileMap[i][j] == 'r') {
					winStatus = true;
				}
			}
	};

	void Player::immortality(int time)
	{
		switch (state)//�������� ��������� �������� � ����������� �� ���������
		{
		case right: {//��������� ���� ������
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;

			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));

			break;
		}
		case left: {//��������� ���� �����
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;

			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));

			break;
		}
		case up: {//���� �����
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));

			break;
		}
		case down: {//���� ����
			CurrentFrame += 0.015*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			if (int(CurrentFrame) % 2 == 0)
				sprite.setTextureRect(IntRect(0, 0, 0, 0));
			else sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
			break;
		}
		case stay: {//�����
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