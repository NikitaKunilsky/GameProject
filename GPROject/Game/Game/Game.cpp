#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <sstream> //текст
#include <list>
#include "map.h" //подключили код с картой
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

	Font font;//шрифт 
	font.loadFromFile("Abys-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(Text::Bold);//жирный текст.
	Text death_text("", font, 100);
	death_text.setStyle(Text::Bold);
	Text win_text("", font, 100);
	win_text.setStyle(Text::Bold);



	Image map_image;//объект изображения для карты
	map_image.loadFromFile("Sprites/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом



	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	Clock trapClock; // время сробатывания ловушки
	Clock immClock; // время сробатывания ловушки
	int gameTime = 0;//объявили игровое время, инициализировали.
	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("Sprites/bullet.png");//загрузили картинку в объект изображения
	bool check = true;

	Image heroImage;
	heroImage.loadFromFile("Sprites/hero.png"); // загружаем изображение игрока

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Sprites/enemy.png"); // загружаем изображение врага

    Player p(heroImage, 100, 600, 42.0, 48.0, "Player1");//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	std::list<Entity*>  BulletsForPlayer;
	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка
	std::list<Entity*>::iterator ip; //итератор чтобы проходить по элементам списка
	

	const int ENEMY_COUNT = 3;
	int enemiesCount = 0;

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			float xr = 150 + rand() % 500; //случайная координата врага на поле игры по оси “x”
			float yr = 150 + rand() % 350; //случайная координата врага на поле игры по оси “y”
										   //создаем врагов и помещаем в список
			enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 42.0, 48.0, "EasyEnemy"));
			enemiesCount += 1; //увеличили счётчик врагов
		}
	
	
		while (window.isOpen())
		{
			int sttime = trapClock.getElapsedTime().asMilliseconds();
			float time = clock.getElapsedTime().asMicroseconds();

			int immtime = immClock.getElapsedTime().asMilliseconds();

			if ((p.life) && !(p.winStatus)) gameTime = gameTimeClock.getElapsedTime().asSeconds();
			//игровое время в секундах идёт вперед, пока жив игрок. 
			//Перезагружать как time его не надо. оно не обновляет логику игры
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
				//стреляем по нажатию клавиши "P"
				if (event.type == sf::Event::KeyPressed)
				{
					if (Keyboard::isKeyPressed(Keyboard::P))
						if (p.playerScore > 0)
						{
							//добавляем в список Bullets пулю
							BulletsForPlayer.push_back(new Bullet(BulletImage, p.x, p.y, 18, 18, "Bullet", p.state));
							p.playerScore -= 1;
						}

				}

			}


			p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
							// передавая время в качестве параметра функции update. 

			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				(*it)->update(time); //запускаем метод update()
			}

			for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); it++)
			{
				(*it)->update(time); //запускаем метод update()
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


			//Проверяем список на наличие "мертвых" пуль и удаляем их
			for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); )//говорим что проходимся от начала до конца
			{// если этот объект мертв, то удаляем его
				if ((*it)->life == false) { delete (*it); it = BulletsForPlayer.erase(it); }
				else
					it++; //и идем курсором (итератором) к след объекту.
			}

			//Проверяем список на наличие "мертвых" противников и удаляем их
			for (it = enemies.begin(); it != enemies.end(); )//говорим что проходимся от начала до конца
			{// если этот объект мертв, то удаляем его
				if ((*it)->life == false) { delete (*it); it = enemies.erase(it); }
				else
					it++; //и идем курсором (итератором) к след объекту.
			}

			

			if (!(p.checkImm == true)) {
				if (p.life == true) {//если игрок жив
					for (it = enemies.begin(); it != enemies.end(); it++) {//бежим по списку врагов
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

		/////////////////////////////ОТОБРАЖЕНИЕ КАРТЫ/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 64, 64)); //если
																						//встретили символ пробел, то рисуем 1-й квадратик
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(64, 0, 64, 64));//если
																						//встретили символ s, то рисуем 2й квадратик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(128, 0, 64, 64));//если
																						  //встретили символ 0, то рисуем 3й квадратик
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(192, 0, 64, 64));//цветок
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(256, 0, 64, 64));//сердце
				if ((TileMap[i][j] == 'r')) s_map.setTextureRect(IntRect(320, 0, 64, 64));//сердце


				s_map.setPosition(j * 64, i * 64);//раскладываем квадратики в карту.
				window.draw(s_map);//рисуем квадратики на экран
				
			}


		std::ostringstream playerScoreString, playerHealthString, gameTimeString;//объявили переменную здоровья и времени
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//формируем строку
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str() );//задаем строку тексту
		text.setPosition(1054, 500);//задаем позицию текста
		window.draw(text);//рисуем этот тексn



		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
		

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life)
			window.draw((*it)->sprite); //рисуем enemies объекты
		}

		//рисуем пули
		for (it = BulletsForPlayer.begin(); it != BulletsForPlayer.end(); it++)
		{
			if ((*it)->life) //если пуля жива, то рисуем её
				window.draw((*it)->sprite);
		}
		if ((p.winStatus == true) && (p.health > 0)) {
			win_text.setString("YOU WON ");//задаем строку тексту
			win_text.setPosition((1024 / 2 - 210), (768 / 2 - 50));//задаем позицию текста
			window.draw(win_text);//рисуем этот текст
		}

		if (p.health <= 0) {
			death_text.setString("YOU DIED");//задаем строку тексту
			death_text.setPosition((1024/2 - 210), (768/2 - 50));//задаем позицию текста
			window.draw(death_text);//рисуем этот текст
		}

		window.display();
	}
	return 0;
}