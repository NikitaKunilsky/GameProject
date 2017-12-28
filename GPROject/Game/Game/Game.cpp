#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <sstream> //�����
#include <list>
#include "map.h" //���������� ��� � ������
#include "Entity.h"
#include "Enemy.h"
#include "bullet.h"
#include "player.h"
#include "Global.h"





using namespace sf;


int main()
{


	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1224, 768, desktop.bitsPerPixel), "Game_lab");

	Font font;//����� 
	font.loadFromFile("Abys-Regular.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setStyle(Text::Bold);//������ �����.
	Text death_text("", font, 100);
	death_text.setStyle(Text::Bold);
	Text win_text("", font, 100);
	win_text.setStyle(Text::Bold);



	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("Sprites/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������



	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	Clock trapClock; // ����� ������������ �������
	Clock immClock; // ����� ������������ �������
	int gameTime = 0;//�������� ������� �����, ����������������.
	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("Sprites/bullet.png");//��������� �������� � ������ �����������
	bool check = true;

	Image heroImage;
	heroImage.loadFromFile("Sprites/hero.png"); // ��������� ����������� ������

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Sprites/enemy.png"); // ��������� ����������� �����

    Player p(heroImage, 100, 600, 42.0, 48.0, "Player1");//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	std::list<Entity*>  BulletsForPlayer;
	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������
	std::list<Entity*>::iterator ip; //�������� ����� ��������� �� ��������� ������
	

	const int ENEMY_COUNT = 3;
	int enemiesCount = 0;

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			float xr = 150 + rand() % 500; //��������� ���������� ����� �� ���� ���� �� ��� �x�
			float yr = 150 + rand() % 350; //��������� ���������� ����� �� ���� ���� �� ��� �y�
										   //������� ������ � �������� � ������
			enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 42.0, 48.0, "EasyEnemy"));
			enemiesCount += 1; //��������� ������� ������
		}
	
	
		while (window.isOpen())
		{
			int sttime = trapClock.getElapsedTime().asMilliseconds();
			float time = clock.getElapsedTime().asMicroseconds();

			int immtime = immClock.getElapsedTime().asMilliseconds();

			if ((p.life) && !(p.winStatus)) gameTime = gameTimeClock.getElapsedTime().asSeconds();
			//������� ����� � �������� ��� ������, ���� ��� �����. 
			//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
			clock.restart();
			time = time / 800;



			if (sttime >= 2000) {
				MapTraps();
				trapClock.restart();
			}


	

			if (immtime <= 2000) {
				if (p.life == true)
					p.checkImm = true;
					p.immortality(time);
				    check = false;
			}
			else
			{
				p.checkImm = false;
				check = true;
			}


			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				//�������� �� ������� ������� "P"
				if (event.type == sf::Event::KeyPressed)
				{
					if (Keyboard::isKeyPressed(Keyboard::P))
						if (p.playerScore > 0)
						{
							//��������� � ������ Bullets ����
							BulletsForPlayer.push_back(new Bullet(BulletImage, p.x, p.y, 18, 18, "Bullet", p.state));
							p.playerScore -= 1;
						}

				}

			}


			p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
							// ��������� ����� � �������� ��������� ������� update. 

			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				(*it)->update(time); //��������� ����� update()
			}

			for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); it++)
			{
				(*it)->update(time); //��������� ����� update()
			}




			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if ((*it)->life) {
					for (ip = BulletsForPlayer.begin(); ip != BulletsForPlayer.end(); ip++)
					{
						if ((*ip)->life)
						{
							if ((*it)->getRect().intersects((*ip)->getRect()))
							{
								(*it)->health -= 50;
								(*ip)->life = false;
								if ((*it)->health <= 0)
									(*it)->life = false;
							}
						}
					}

				}
			}


			//��������� ������ �� ������� "�������" ���� � ������� ��
			for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); )//������� ��� ���������� �� ������ �� �����
			{// ���� ���� ������ �����, �� ������� ���
				if ((*it)->life == false) { delete (*it); it = BulletsForPlayer.erase(it); }
				else
					it++; //� ���� �������� (����������) � ���� �������.
			}

			//��������� ������ �� ������� "�������" ����������� � ������� ��
			for (it = enemies.begin(); it != enemies.end(); )//������� ��� ���������� �� ������ �� �����
			{// ���� ���� ������ �����, �� ������� ���
				if ((*it)->life == false) { delete (*it); it = enemies.erase(it); }
				else
					it++; //� ���� �������� (����������) � ���� �������.
			}

			

			if (!(p.checkImm == true)) {
				if (p.life == true) {//���� ����� ���
					for (it = enemies.begin(); it != enemies.end(); it++) {//����� �� ������ ������
						if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
						{
							p.health -= 40;
							std::cout << "YOU TOOK DMG" << endl;
							p.checkImm = true;

							
						}
					}
				}
			}

			if (p.health > 0)
			if ((p.checkImm == true) && (check == true))
				immClock.restart();

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
				if ((TileMap[i][j] == 'r')) s_map.setTextureRect(IntRect(320, 0, 64, 64));//������


				s_map.setPosition(j * 64, i * 64);//������������ ���������� � �����.
				window.draw(s_map);//������ ���������� �� �����
				
			}


		std::ostringstream playerScoreString, playerHealthString, gameTimeString;//�������� ���������� �������� � �������
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//��������� ������
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str() );//������ ������ ������
		text.setPosition(1054, 500);//������ ������� ������
		window.draw(text);//������ ���� ����n



		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life)
			window.draw((*it)->sprite); //������ enemies �������
		}

		//������ ����
		for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); it++)
		{
			if ((*it)->life) //���� ���� ����, �� ������ �
				window.draw((*it)->sprite);
		}
		if ((p.winStatus == true) && (p.health > 0)) {
			win_text.setString("YOU WON ");//������ ������ ������
			win_text.setPosition((1024 / 2 - 210), (768 / 2 - 50));//������ ������� ������
			window.draw(win_text);//������ ���� �����
		}

		if (p.health <= 0) {
			death_text.setString("YOU DIED");//������ ������ ������
			death_text.setPosition((1024/2 - 210), (768/2 - 50));//������ ������� ������
			window.draw(death_text);//������ ���� �����
		}

		window.display();
	}
	return 0;
}