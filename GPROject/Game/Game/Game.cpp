#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
#include <sstream> //текст

using namespace sf;
////////////////////////////КЛАСС ИГРОКА////////////////////////
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private: float x, y;
public:
	float w, h, dx, dy, speed; //координаты игрока х и у, высота и ширина, 
							   //ускорение (по х и по у), сама скорость
	int dir, playerScore,health; 
	bool life;
	std::string File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 


				  //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать //имя файла, координату Х и У, ширину и высоту
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; playerScore = 0, health = 100;
		dx = 0; dy = 0; speed = 0;
		File = F; //имя файла+расширение
		w = W; h = H; //высота и ширина
		image.loadFromFile("Sprites/" + File);//загружаем в image изображение, вместо File
											 //передадим то, что пропишем при создании объекта. В нашем случае это "hero.png". Получится
											 //запись, идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59)); //убираем ненужный темно-синий цвет
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
		x = X; y = Y; //координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));
		//Задаем спрайту один прямоугольник для
		//вывода одного льва. IntRect – для приведения типов
	}

	void update(float time) //функция "оживления/обновления" объекта класса. Принимает в себя 
							//время SFML, вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. Каждая цифра
					//соответствует направлению.
		{
		case 0: dx = speed; dy = 0; break; //по “X” задаем положительную скорость, по “Y” - 0. 
										   //Персонаж идет только вправо.
		case 1: dx = -speed; dy = 0; break;//по “X” задаем отрицательную скорость, по и “Y” – 0.
										   //Персонаж идет только влево.
		case 2: dx = 0; dy = speed; break;//по “X” задаем нулевое значение, по “Y”
										  //положительное. Получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по “X” задаем нулевое значение, по “Y”
										   //отрицательное. Получается, что персонаж идет только вверх
		}

		x += dx*time; //движение по “X”
		y += dy*time; //движение по “Y”
		speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию (x, y). 
								  //бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <= 0) { life = false; speed = 0; }//если жизней меньше, либо равно 0, 
													 //то умираем и исключаем движение игрока после смерти

	}


	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		//Проходим только по тем тайлам (квадратикам размера 32*32), которые контактируют с игроком.
		//Частично или полностью находятся под изображением игрока! 
		for (int i = y / 64; i < (y + h) / 64; i++)
			for (int j = x / 64; j<(x + w) / 64; j++) {
				//”x” делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. 
				//Он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких тайлах
				//Кроме того, j<(x + w)/32 - условие ограничения координат по “x”, т.е. координата самого
				//правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева
				// направо по иксу, проходя от левого квадрата (соприкасающегося с героем), до правого
				// квадрата (соприкасающегося с героем)
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу “0”
										 //(стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0) {//если мы шли вниз,
						y = i * 64 - h;//то стопорим (-h) координату “y” персонажа. 
									   //сначала получаем координату “i” нашего квадратика на карте и 
									   //затем вычитаем из высоты спрайта персонажа.
					}
					if (dy<0) {
						y = i * 64 + 64;//аналогично с движением вверх.	
					}
					if (dx>0) {
						x = j * 64 - w;//если идем вправо, то координата “x” равна 
									   //стена (символ 0) минус ширина персонажа
					}
					if (dx < 0) {
						x = j * 64 + 64; //аналогично идем влево
					}
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //если взяли камень, переменная playerScore=playerScore+1;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
					health -= 20;//если взяли ядовитые шипы,то переменная health=health-40;
					TileMap[i][j] = ' ';//убрали шипы
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//если взяли сердечко,то переменная health=health+20;
					TileMap[i][j] = ' ';//убрали сердечко
				}


			}
	}

};


int main()
{
	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1224, 768, desktop.bitsPerPixel), "Lesson 7");

	Font font;//шрифт 
	font.loadFromFile("Abys-Regular.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(Text::Bold);//жирный текст.
	


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("Sprites/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом


	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.


	Player p("hero.png", 100, 100, 42.0, 48.0);//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//игровое время в секундах идёт вперед, пока жив игрок. 
		//Перезагружать как time его не надо. оно не обновляет логику игры

		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>1600) {
			MapCash();
			createObjectForMapTimer = 0;//обнуляем таймер
		}

		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	


		/////////////////////////Управление персонажем с анимацией//////////////////////////////////
		if (p.life) {
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения.
										 //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48)); //через объект p
																					 //класса player меняем спрайт, делая анимацию 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;//направление вправо
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48)); //через объект p 								//класса player меняем спрайт, делая анимацию 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;//направление вниз
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48)); //через объект p 				//класса player меняем спрайт, делая анимацию (используя оператор точку)

			}
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;//направление вверх
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
			}
		}

		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
						// передавая время в качестве параметра функции update. 

		window.clear();

		/////////////////////////////Рисуем карту/////////////////////
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


				s_map.setPosition(j * 64, i * 64);//раскладываем квадратики в карту.

				window.draw(s_map);//рисуем квадратики на экран
			}

		std::ostringstream playerScoreString,playerHealthString, gameTimeString;//объявили переменную здоровья и времени
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//формируем строку
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str());//задаем строку тексту
		text.setPosition(1054, 500);//задаем позицию текста
		window.draw(text);//рисуем этот тексn


		
		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
		window.display();
	}
	return 0;
}
