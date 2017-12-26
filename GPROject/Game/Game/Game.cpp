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
	int dir, playerScore,health; 
	bool life;
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 


				  //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� //��� �����, ���������� � � �, ������ � ������
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; playerScore = 0, health = 100;
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
		if (health <= 0) { life = false; speed = 0; }//���� ������ ������, ���� ����� 0, 
													 //�� ������� � ��������� �������� ������ ����� ������

	}


	void interactionWithMap()//�-��� �������������� � ������
	{
		//�������� ������ �� ��� ������ (����������� ������� 32*32), ������� ������������ � �������.
		//�������� ��� ��������� ��������� ��� ������������ ������! 
		for (int i = y / 64; i < (y + h) / 64; i++)
			for (int j = x / 64; j<(x + w) / 64; j++) {
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
						y = i * 64 - h;//�� �������� (-h) ���������� �y� ���������. 
									   //������� �������� ���������� �i� ������ ���������� �� ����� � 
									   //����� �������� �� ������ ������� ���������.
					}
					if (dy<0) {
						y = i * 64 + 64;//���������� � ��������� �����.	
					}
					if (dx>0) {
						x = j * 64 - w;//���� ���� ������, �� ���������� �x� ����� 
									   //����� (������ 0) ����� ������ ���������
					}
					if (dx < 0) {
						x = j * 64 + 64; //���������� ���� �����
					}
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //���� ����� ������, ���������� playerScore=playerScore+1;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
					health -= 20;//���� ����� �������� ����,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ����
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������,�� ���������� health=health+20;
					TileMap[i][j] = ' ';//������ ��������
				}


			}
	}

};


int main()
{
	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1224, 768, desktop.bitsPerPixel), "Lesson 7");

	Font font;//����� 
	font.loadFromFile("Abys-Regular.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setStyle(Text::Bold);//������ �����.
	


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("Sprites/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������


	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.


	Player p("hero.png", 100, 100, 42.0, 48.0);//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ������

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//������� ����� � �������� ��� ������, ���� ��� �����. 
		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����

		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>1600) {
			MapCash();
			createObjectForMapTimer = 0;//�������� ������
		}

		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	


		/////////////////////////���������� ���������� � ���������//////////////////////////////////
		if (p.life) {
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
										 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48)); //����� ������ p
																					 //������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;//����������� ������
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48)); //����� ������ p 								//������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;//����������� ����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48)); //����� ������ p 				//������ player ������ ������, ����� �������� (��������� �������� �����)

			}
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;//����������� �����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
			}
		}

		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 64, 64)); //����
																						//��������� ������ ������, �� ������ 1-� ���������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(64, 0, 64, 64));//����
																						//��������� ������ s, �� ������ 2� ���������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(128, 0, 64, 64));//����
																						 //��������� ������ 0, �� ������ 3� ���������
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(192, 0, 64, 64));//������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(256, 0, 64, 64));//������


				s_map.setPosition(j * 64, i * 64);//������������ ���������� � �����.

				window.draw(s_map);//������ ���������� �� �����
			}

		std::ostringstream playerScoreString,playerHealthString, gameTimeString;//�������� ���������� �������� � �������
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//��������� ������
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str());//������ ������ ������
		text.setPosition(1054, 500);//������ ������� ������
		window.draw(text);//������ ���� ����n


		
		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}
