#pragma once

#include<vector>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<ctime>
#include<conio.h>
#include<iostream>
#include<Windows.h>
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<dos.h>
#include<iomanip>

using namespace std;
using namespace sf;

class Car
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::VideoMode videomode;
	sf::Texture texture1;
	sf::Sprite carsprite;
	sf::Texture texture2;
	sf::Sprite enemy;
	vector<Sprite>enemies;

	int enemycar = 0;
	int enemymaxcar = 5;
	int timer = 0;
	float m, n;

	bool gameover;
	int points;
	float movementspeed = 10.f;


	void initvariable();
	void initwindow();
	void inittexture();
	void initsprite();
	void initenemy();



public:
	Car();
	~Car();
	bool running();
	void pollevents();
	void updateinput();
	void collisionwall(sf::RenderTarget* target);
	void spawnenemy();
	void updateenemies();
	void collision();

	void update();

	void rendercar(sf::RenderTarget& target);
	void renderbg(sf::RenderTarget& target);
	void render();


};

