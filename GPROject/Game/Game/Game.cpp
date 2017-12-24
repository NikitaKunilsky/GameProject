// Game.cpp: ���������� ����� ����� ��� ����������� ����������.
//

/*#include "stdafx.h"
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
			herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(67, 0, 25, 57));
		}

		//���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(34, 0, 25, 57));
		}

		//���������� Y �� ������� ����� ��������� ������ ����� ����� 288
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(99, 0, 25, 57));
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
}*/
/*#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "Lesson 5");

	Texture herotexture;
	herotexture.loadFromFile("Sprites/hero1.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 25, 57));
	herosprite.setPosition(250, 250);

	float heroteleporttimer = 0; //��������� ������������ ����� ����� 3 �������
	Clock clock; //������� ���������� ������� � ������������ ��������� ����! 

	while (window.isOpen())
	{
		// ���� ����� � ���������� ����������� �����, � ������ ������ �����, ��������� �             		//���������� �������� � ������ restart();
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); //���������� �����
		time = time / 800; //�������� ����
		std::cout << time << "\n";//�������, ��� ������ ����� (���������������)

		heroteleporttimer = heroteleporttimer + time;//���������� � ����� ���������� time

		if (heroteleporttimer > 3000) {
			herosprite.setPosition(0, 120); heroteleporttimer = 0;
		} //���� ������ ��������� ������ 3000 (��� �������� 3 �������),
		  //�� ������������� ����� � ���������� (0, 120) � �������� ������ ������������

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//���������� Y, �� ������� ����� ��������� ������ ����� ����� 96
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			herosprite.move(-0.1*time, 0); herosprite.setTextureRect(IntRect(67, 0, 25, 57));
		}

		//���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			herosprite.move(0.1*time, 0); herosprite.setTextureRect(IntRect(34, 0, 25, 57));
		}

		//���������� Y �� ������� ����� ��������� ������ ����� ����� 288
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			herosprite.move(0, -0.1*time); herosprite.setTextureRect(IntRect(99, 0, 25, 57));
		}

		//���������� 0, ��� ������� ����� ����������� � ������, �� ��� � ������������� 			//������� ������������ �� 96.
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			herosprite.move(0, 0.1*time); herosprite.setTextureRect(IntRect(0, 0, 25, 57));
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
}*/

#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
#include <sstream> //�����

using namespace sf;
////////////////////////////����� ������////////////////////////
////////////////////////////////////////////////////����� ������////////////////////////
class Player { // ����� ������
private: float x, y;
public:
	float w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������, 
							   //��������� (�� � � �� �), ���� ��������
	int dir, playerScore; //����� ����������, �������� ���� ������ 
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 


				  //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� //��� �����, ���������� � � �, ������ � ������
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; playerScore = 0;
		dx = 0; dy = 0; speed = 0;
		File = F; //��� �����+����������
		w = W; h = H; //������ � ������
		image.loadFromFile("Sprites/" + File);//��������� � image �����������, ������ File
											 //��������� ��, ��� �������� ��� �������� �������. � ����� ������ ��� "hero.png". ���������
											 //������, ���������� image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59)); //������� �������� �����-����� ����
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
		x = X; y = Y; //���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));
		//������ ������� ���� ������������� ���
		//������ ������ ����. IntRect � ��� ���������� �����
	}

	void update(float time) //������� "���������/����������" ������� ������. ��������� � ���� 
							//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. ������ �����
					//������������� �����������.
		{
		case 0: dx = speed; dy = 0; break; //�� �X� ������ ������������� ��������, �� �Y� - 0. 
										   //�������� ���� ������ ������.
		case 1: dx = -speed; dy = 0; break;//�� �X� ������ ������������� ��������, �� � �Y� � 0.
										   //�������� ���� ������ �����.
		case 2: dx = 0; dy = speed; break;//�� �X� ������ ������� ��������, �� �Y�
										  //�������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;//�� �X� ������ ������� ��������, �� �Y�
										   //�������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx*time; //�������� �� �X�
		y += dy*time; //�������� �� �Y�
		speed = 0;    //�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� (x, y). 
								  //���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		interactionWithMap();//�������� �������, ���������� �� �������������� � ������
	}


	void interactionWithMap()//�-��� �������������� � ������
	{
		//�������� ������ �� ��� ������ (����������� ������� 32*32), ������� ������������ � �������.
		//�������� ��� ��������� ��������� ��� ������������ ������! 
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++) {
				//�x� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. 
				//�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ������
				//����� ����, j<(x + w)/32 - ������� ����������� ��������� �� �x�, �.�. ���������� ������
				//������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� �����
				// ������� �� ����, ������� �� ������ �������� (���������������� � ������), �� �������
				// �������� (���������������� � ������)
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�
										 //(�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0) {//���� �� ��� ����,
						y = i * 32 - h;//�� �������� (-h) ���������� �y� ���������. 
									   //������� �������� ���������� �i� ������ ���������� �� ����� � 
									   //����� �������� �� ������ ������� ���������.
					}
					if (dy<0) {
						y = i * 32 + 32;//���������� � ��������� �����.	
					}
					if (dx>0) {
						x = j * 32 - w;//���� ���� ������, �� ���������� �x� ����� 
									   //����� (������ 0) ����� ������ ���������
					}
					if (dx < 0) {
						x = j * 32 + 32; //���������� ���� �����
					}
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //���� ����� ������, ���������� playerScore=playerScore+1;
					TileMap[i][j] = ' ';
				}

			}
	}

};


int main()
{
	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "Lesson 7");

	Font font;//����� 
	font.loadFromFile("CyrillicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	
	text.setStyle(Text::Bold);//������ �����.



	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("Sprites/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������


	float CurrentFrame = 0;//������ ������� ����
	Clock clock;

	Player p("hero1.png", 50, 40, 25.0, 57.0);//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/////////////////////////���������� ���������� � ���������//////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
									 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(67 * int(CurrentFrame), 0, 25, 57)); //����� ������ p
																				 //������ player ������ ������, ����� �������� 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;//����������� ������
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(34 * int(CurrentFrame), 0, 25, 57)); //����� ������ p 								//������ player ������ ������, ����� �������� 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//����������� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(99 * int(CurrentFrame), 0, 25, 57)); //����� ������ p 				//������ player ������ ������, ����� �������� (��������� �������� �����)

		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.1;//����������� �����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(0 * int(CurrentFrame), 0, 25, 57));
		}

		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //����
																						//��������� ������ ������, �� ������ 1-� ���������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//����
																						//��������� ������ s, �� ������ 2� ���������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//����
																						 //��������� ������ 0, �� ������ 3� ���������

				s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����.

				window.draw(s_map);//������ ���������� �� �����
			}

		std::ostringstream playerScoreString;  // �������� ����������
		playerScoreString << p.playerScore;//������� � ��� ����� �����, �� ���� ��������� ������
		text.setString("������� ������:" + playerScoreString.str());//������ ������ ������ �
																	// �������� �������������� ���� ������ ������� .str() 
		text.setPosition(50, 50);//������ ������� ������, �������� �� ������ ������
		window.draw(text);//����� ���� �����

		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}
