#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
#include <sstream> //�����

#include <list>


using namespace sf;
////////////////////////////����� ��������////////////////////////
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

	Entity(Image &image, float X, float Y, int W, int H, std::string Name) {
		x = X; y = Y; //���������� ��������� �������
		w = W; h = H;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		health = 100;
		life = true; //���������������� ���������� ���������� �����, ����� ���
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
	}

	FloatRect getRect() {//����� ��������� ��������������. ��� �����, ������� (���,�����).
		FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
		return FR;
		//return FloatRect(x, y, w, h);
		//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� ����������� 
	}
	virtual void update(float time) = 0;
};

////////////////////////////////////////////////////����� ������////////////////////////
class Player :public Entity {
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������

	Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		state = stay;
		if (name == "Player1") {
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
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

/////////////////////////////////////////����////////////////////////////////////////////

class Enemy :public Entity {
public:
	int direction;//����������� �������� �����
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % 4; //����������� �������� ����� ����� ��������� �������
									  //����� ��������� ��������� �����
			speed = 0.075;//���� ��������.���� ������ ������ ���������
			dx = speed;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//���������� �� ��������� �����
			for (int j = x / 64; j<(x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//���� ������� - ������ �����
				{
					if (Dy > 0) {
						y = i * 64 - h;  dy = -0.1;
						direction = rand() % 4; //����������� �������� �����
					}//�� Y 
					if (Dy < 0) {
						y = i * 64 + 64; dy = 0.1;
						direction = rand() % 4;//����������� �������� ����� 
					}//������������ � �������� ������ 
					if (Dx > 0) {
						x = j * 64 - w; dx = -0.1;
						direction = rand() % 4;//����������� �������� ����� 
					}//� ������ ����� �����
					if (Dx < 0) {
						x = j * 64 + 64; dx = 0.1;
						direction = rand() % 4; //����������� �������� �����
					}// � ����� ����� �����
				}
			}
	}

	void update(float time) //����� "���������/����������" ������� ������.
	{ 
		if (name == "EasyEnemy") {//��� ��������� � ����� ������ ������ ����� �����
		
			if (life) {//���������, ��� �� �����
				dx = 0;
				dy = 0;
				switch (direction)//�������� ��������� �������� � ����������� �� ���������
				{
				case 0: {//��������� ���� ������

					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
					break;
				}
				case 1: {//��������� ���� �����
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
					break;
				}
				case 2: {//���� �����
					dy = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
					break;
				}
				case 3: {//���� ����
					dy = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
					break;

				}
				}


				x += dx*time; //�������� �� �X�
				checkCollisionWithMap(dx, 0);//������������ ������������ �� �


				y += dy*time; //�������� �� �Y�
				checkCollisionWithMap(0, dy);//������������ ������������ �� Y


				sprite.setPosition(x, y); //������ � ������� (x, y).

				if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
			}
		}

		
	}
};//����� Enemy ������




int main()
{


	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1224, 768, desktop.bitsPerPixel), "Game_lab");

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

	Image heroImage;
	heroImage.loadFromFile("Sprites/hero.png"); // ��������� ����������� ������

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Sprites/enemy.png"); // ��������� ����������� �����

    Player p(heroImage, 100, 100, 42.0, 48.0, "Player1");//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������

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

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}



		if (p.life == true) {//���� ����� ���
			for (it = enemies.begin(); it != enemies.end(); it++) {//����� �� ������ ������
				if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health -= 40;
					std::cout << "YOURE LOSER";
				}
			}
		}


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
		
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			window.draw((*it)->sprite); //������ enemies �������
		}


		window.display();
	}
	return 0;
}