// Game.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "Lesson 3");

	Texture herotexture;
	herotexture.loadFromFile("Sprites/hero1.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 25, 57));//�������� ������ ������������� 
	herosprite.setPosition(150, 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//���������� Y, �� ������� ����� ��������� ������ ����� ����� 96
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(34, 0, 56, 57));
		}

		//���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(67, 0, 89, 57));
		}

		//���������� Y �� ������� ����� ��������� ������ ����� ����� 288
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(96, 0, 118, 57));
		}

		//���������� 0, ��� ������� ����� ����������� � ������, �� ��� � ������������� 			//������� ������������ �� 96.
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(0, 0, 25, 57));
		}

		// �������� ����� � ������� ���� �� ������� ����� ������� ����
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			herosprite.setColor(Color::Red);
		}

		window.clear();
		window.draw(herosprite);
		window.display();
	}


	return 0;
}

