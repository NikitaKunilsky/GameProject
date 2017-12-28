#ifndef _ENTITY_HEADER_H_
#define _ENTITY_HEADER_H_
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class Entity {
public:
	enum { left, right, up, down, stay } state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
					 //������� ����� ���� ���� �������� � update() � ����������� �� �����
	virtual void update(float time) = 0;
	Entity(Image &image, float X, float Y, int W, int H, std::string Name);
	FloatRect getRect();
	virtual ~Entity()
	{
		std::cout << "Parent died" << endl;
	};

};
#endif