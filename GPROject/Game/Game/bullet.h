#ifndef _BULLET_HEADER_H_
#define _BULLET_HEADER_H_

#include <SFML\Graphics.hpp>

#include "Entity.h"


using namespace sf;
using namespace std;

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����
				  //�� ��� ��, ������ ����� � ����� ��������� ������ (int dir) 
				  //��� ������� ����������� ����� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir); // :Entity(image, X, Y, W, H, Name)
    ~Bullet ()
	{
		std::cout << "Bullet down" << endl;
	};
	void update(float time);

};


#endif