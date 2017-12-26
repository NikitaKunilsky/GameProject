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
	float w, h, dx, dy, speed; //���������� ������ (�,�), ������ � ������, 
							   //��������� (�� ��� � �� ��), ���� ��������
	int  playerScore, health;//����� ���������� �health�, �������� ����� ������
	float CurrentFrame = 0;//������ ������� ����
	bool life;//���������� �life� �����, ����������
	enum { left, right, up, down, stay } state;//������������ - ��������� �������
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 

				  ////////////////////////////////////////////������������////////////////////////////////////////////
	Player(std::string F, float X, float Y, float W, float H) {
		playerScore = 0;
		dx = 0; dy = 0; speed = 0; state = stay;
		health = 100;
		//���������������� ���������� ����� � ������������
		life = true;//���������������� ���������� ���������� �����, ����� ���
		File = F; //��� �����+����������
		w = W; h = H; //������ � ������
		image.loadFromFile("Sprites/" + File);//��������� � image �����������, 
		image.createMaskFromColor(Color(41, 33, 59)); //������� �������� �����-����� ����
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
		x = X; y = Y; //���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));
		//������ ������� ���� ������������� ���
		//������ ������ ����. IntRect � ��� ���������� �����
	}
	//////////////////��������////////////////////
	void control() {
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
	}



	void update(float time) //����� "���������/����������" ������� ������.
	{
		if (life) {//���������, ��� �� �����
			control();//������� ���������� ����������
			switch (state)//�������� ��������� �������� � ����������� �� ���������
			{
			case right: {//��������� ���� ������
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
				break;
			}
			case left: {//��������� ���� �����
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
				break;
			}
			case up: {//���� �����
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
				break;
			}
			case down: {//���� ����
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
				break;
			}
			case stay: {//�����
				dy = speed;
				dx = speed;
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
	}

	//����� �������� ������������ � ���������� �����
	void checkCollisionWithMap(float Dx, float Dy) {
		for (int i = y / 64; i < (y + h) / 64; i++)//���������� �� ��������� �����
			for (int j = x / 64; j<(x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//���� ������� ������ �����
				{
					if (Dy > 0) { y = i * 64 - h;  dy = 0; }//�� Y 
					if (Dy < 0) { y = i * 64 + 64; dy = 0; }//������������ � �������� ������ 
					if (Dx > 0) { x = j * 64 - w; dx = 0; }//� ������ ����� �����
					if (Dx < 0) { x = j * 64 + 64; dx = 0; }// � ����� ����� �����
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //���� ����� ������
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//���� ����� �������� ������	
					TileMap[i][j] = ' ';//������ ������
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������
					TileMap[i][j] = ' ';//������ ��������
				}
			}
	}

	FloatRect getRect() {//����� ��������� ��������������. ��� �����, ������� (���,�����).
		FloatRect FR(x, y, w, h);
		return FR;
		//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� �����������	
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


		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

		window.clear();

		/////////////////////////////����������� �����/////////////////////
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

		std::ostringstream playerScoreString, playerHealthString, gameTimeString;//�������� ���������� �������� � �������
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//��������� ������
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str());//������ ������ ������
		text.setPosition(1054, 500);//������ ������� ������
		window.draw(text);//������ ���� ����n



		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}