// Game.cpp: определяет точку входа для консольного приложения.
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
	herosprite.setTextureRect(IntRect(0, 0, 25, 57));//получили нужный прямоугольник 
	herosprite.setPosition(150, 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//координата Y, на которой герой изображен идущим влево равна 96
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(34, 0, 56, 57));
		}

		//координата Y, на которой герой изображен идущем вправо равна 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(67, 0, 89, 57));
		}

		//координата Y на которой герой изображен идущим вверх равна 288
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(96, 0, 118, 57));
		}

		//координата 0, это верхняя часть изображения с героем, от нее и отталкиваемся 			//ровными квадратиками по 96.
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(0, 0, 25, 57));
		}

		// закрасим героя в красный цвет по нажатию левой клавиши мыши
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

