#include "stdafx.h"
#include <SFML\Graphics.hpp> 
#include "bullet.h"
#include "map.h"
	Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		x = X;
		y = Y;
		direction = dir;
		speed = 0.35;
		w = h = 18;
		life = true;
		//���� ������������� � ������������
	};


	void Bullet::update(float time)
	{
		switch (direction)
		{

		case 0: dx = -speed; dy = 0;   break;// state = left
		case 1: dx = speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		case 4: dx = 0; dy = speed;   break;// state = down
		}
		x += dx*time;//���� �������� ���� �� �
		y += dy*time;//�� �

		if (x <= 0) x = 20;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y <= 0) y = 20;

		if (x >= 1024) x = 800;// �������� ���� � ������ �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y >= 768) y = 680;


		for (int i = y / 64; i < (y + h) / 64; i++)//���������� �� ��������� �����
			for (int j = x / 64; j < (x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0') //���� ������� ��� ������ �����, ��
					life = false;// �� ���� �������
			}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	};