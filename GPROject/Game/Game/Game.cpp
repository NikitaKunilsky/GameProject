#include "stdafx.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
#include <sstream> //текст

#include <list>


using namespace sf;
////////////////////////////КЛАСС СУЩНОСТЬ////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay } state;// тип перечисления - состояние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health; //переменная “health”, хранящая жизни игрока
	bool life; //переменная “life” жизнь, логическая
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
					 //каждому можно дать свое действие в update() в зависимости от имени

	Entity(Image &image, float X, float Y, int W, int H, std::string Name) {
		x = X; y = Y; //координата появления спрайта
		w = W; h = H;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		health = 100;
		life = true; //инициализировали логическую переменную жизни, герой жив
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
	}

	FloatRect getRect() {//метод получения прямоугольника. его коорд, размеры (шир,высот).
		FloatRect FR(x, y, w, h); // переменная FR типа FloatRect
		return FR;
		//return FloatRect(x, y, w, h);
		//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
		//в нашей игре это координаты текущего расположения тайла на карте
		//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
		//эта ф-ция нужна для проверки пересечений 
	}
	virtual void update(float time) = 0;
};

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
	int playerScore;//эта переменная может быть только у игрока

	Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		state = stay;
		if (name == "Player1") {
			//Задаем спрайту один прямоугольник для
			//вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	//////////////////ДВИЖЕНИЕ////////////////////
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



	void update(float time) //метод "оживления/обновления" объекта класса.
	{
		if (life) {//проверяем, жив ли герой
			control();//функция управления персонажем
			switch (state)//делаются различные действия в зависимости от состояния
			{
			case right: {//состояние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
				break;
			}
			case left: {//состояние идти влево
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
				break;
			}
			case up: {//идти вверх
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
				break;
			}
			case down: {//идти вниз
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
				break;
			}
			case stay: {//стоим
				dy = speed;
				dx = speed;
				break;
			}
			}
			if (!(dx == 0)) {
				x += dx*time; //движение по “X”
				checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			}
			else {
				y += dy*time; //движение по “Y”
				checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
			}
			speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
						  //state = stay; //состояние - стоим

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

			if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}

	//Метод проверки столкновений с элементами карты
	void checkCollisionWithMap(float Dx, float Dy) {
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по элементам карты
			for (int j = x / 64; j < (x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//если элемент тайлик земли
				{
					if (Dy > 0) { y = i * 64 - h;  dy = 0; }//по Y 
					if (Dy < 0) { y = i * 64 + 64; dy = 0; }//столкновение с верхними краями 
					if (Dx > 0) { x = j * 64 - w; dx = 0; }//с правым краем карты
					if (Dx < 0) { x = j * 64 + 64; dx = 0; }// с левым краем карты
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //если взяли камень
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//если взяли ядовитый цветок	
					TileMap[i][j] = ' ';//убрали цветок
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//если взяли сердечко
					TileMap[i][j] = ' ';//убрали сердечко
				}
			}
	}

	FloatRect getRect() {//метод получения прямоугольника. его коорд, размеры (шир,высот).
		FloatRect FR(x, y, w, h);
		return FR;
		//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
		//в нашей игре это координаты текущего расположения тайла на карте
		//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
		//эта ф-ция нужна для проверки пересечений	
	}

};

/////////////////////////////////////////ВРАГ////////////////////////////////////////////

class Enemy :public Entity {
public:
	int direction;//направление движения врага
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			//Задаем спрайту один прямоугольник для
			//вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % 4; //Направление движения врага задаём случайным образом
									  //через генератор случайных чисел
			speed = 0.075;//даем скорость.этот объект всегда двигается
			dx = speed;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по элементам карты
			for (int j = x / 64; j<(x + w) / 64; j++)
			{
				if (TileMap[i][j] == '0')//если элемент - тайлик земли
				{
					if (Dy > 0) {
						y = i * 64 - h;  dy = -0.1;
						direction = rand() % 4; //Направление движения врага
					}//по Y 
					if (Dy < 0) {
						y = i * 64 + 64; dy = 0.1;
						direction = rand() % 4;//Направление движения врага 
					}//столкновение с верхними краями 
					if (Dx > 0) {
						x = j * 64 - w; dx = -0.1;
						direction = rand() % 4;//Направление движения врага 
					}//с правым краем карты
					if (Dx < 0) {
						x = j * 64 + 64; dx = 0.1;
						direction = rand() % 4; //Направление движения врага
					}// с левым краем карты
				}
			}
	}

	void update(float time) //метод "оживления/обновления" объекта класса.
	{ 
		if (name == "EasyEnemy") {//для персонажа с таким именем логика будет такой
		
			if (life) {//проверяем, жив ли герой
				dx = 0;
				dy = 0;
				switch (direction)//делаются различные действия в зависимости от состояния
				{
				case 0: {//состояние идти вправо

					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 48, 42, 48));
					break;
				}
				case 1: {//состояние идти влево
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 96, 42, 48));
					break;
				}
				case 2: {//идти вверх
					dy = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 0, 42, 48));
					break;
				}
				case 3: {//идти вниз
					dy = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(42 * int(CurrentFrame), 144, 42, 48));
					break;

				}
				}


				x += dx*time; //движение по “X”
				checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х


				y += dy*time; //движение по “Y”
				checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y


				sprite.setPosition(x, y); //спрайт в позиции (x, y).

				if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			}
		}

		
	}
};//класс Enemy закрыт




int main()
{


	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1224, 768, desktop.bitsPerPixel), "Game_lab");

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



	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	Image heroImage;
	heroImage.loadFromFile("Sprites/hero.png"); // загружаем изображение игрока

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Sprites/enemy.png"); // загружаем изображение врага

    Player p(heroImage, 100, 100, 42.0, 48.0, "Player1");//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка

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


		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
						// передавая время в качестве параметра функции update. 

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}



		if (p.life == true) {//если игрок жив
			for (it = enemies.begin(); it != enemies.end(); it++) {//бежим по списку врагов
				if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health -= 40;
					std::cout << "YOURE LOSER";
				}
			}
		}


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


				s_map.setPosition(j * 64, i * 64);//раскладываем квадратики в карту.

				window.draw(s_map);//рисуем квадратики на экран
			}

		std::ostringstream playerScoreString, playerHealthString, gameTimeString;//объявили переменную здоровья и времени
		playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//формируем строку
		text.setString("AMMO : " + playerScoreString.str() + "\nHP   : " + playerHealthString.str() + "\nTIME  : " + gameTimeString.str());//задаем строку тексту
		text.setPosition(1054, 500);//задаем позицию текста
		window.draw(text);//рисуем этот тексn



		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
		
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			window.draw((*it)->sprite); //рисуем enemies объекты
		}


		window.display();
	}
	return 0;
}