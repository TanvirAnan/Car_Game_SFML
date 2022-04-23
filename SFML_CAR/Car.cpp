#include "Car.h"

void Car::initvariable()
{
	points = 0;
	gameover = false;
}

void Car::initwindow()
{
	videomode.height = 800;
	videomode.width = 600;
	window = new sf::RenderWindow(this->videomode, "Game 1", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

void Car::inittexture()
{
	texture.loadFromFile("Textures/background.png");
	texture1.loadFromFile("Textures/car.png");
	texture2.loadFromFile("Textures/enemy.png");
}

void Car::initsprite()
{
	sprite.setTexture(texture);
	sprite.setScale(.75, 1.75);
	carsprite.setTexture(texture1);
	carsprite.setScale(.1, .1);
	carsprite.setPosition(300.f, 600.f);
	enemy.setTexture(texture2);
	enemy.setScale(.17, .17);
	m = sprite.getGlobalBounds().left;
	n = sprite.getGlobalBounds().top;
}

void Car::initenemy()
{
	enemy.setPosition(rand() % window->getPosition().x, 0);
	enemies.push_back(enemy);

	/*for(int i=0;enemycar<enemymaxcar;i++)
	{
		enemies.push_back(enemy);
		enemies[i].setPosition((rand() % window->getSize().x-enemy.getGlobalBounds().width), timer);
		enemycar++;
		timer += 50;
	}*/


}

Car::Car()
{
	initvariable();
	initwindow();
	inittexture();
	initsprite();
	initenemy();
}

Car::~Car()
{

}

bool Car::running()
{
	return window->isOpen();
}

void Car::pollevents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}


	}
}

void Car::updateinput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		carsprite.move(-movementspeed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		carsprite.move(movementspeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		carsprite.move(0, -movementspeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		carsprite.move(0, movementspeed);
	}
}

void Car::collisionwall(sf::RenderTarget* target)
{
	if (carsprite.getGlobalBounds().left <= 0)
	{
		carsprite.setPosition(0.f, carsprite.getPosition().y);
	}
	if (carsprite.getGlobalBounds().left + carsprite.getGlobalBounds().width >= target->getSize().x)
	{
		carsprite.setPosition(target->getSize().x - carsprite.getGlobalBounds().width, carsprite.getGlobalBounds().top);
	}
	if (carsprite.getGlobalBounds().top <= 0)
	{
		carsprite.setPosition(carsprite.getPosition().x, 0.f);
	}
	if (carsprite.getGlobalBounds().top + carsprite.getGlobalBounds().height >= target->getSize().y)
	{
		carsprite.setPosition(carsprite.getGlobalBounds().left, target->getSize().y - carsprite.getGlobalBounds().height);
	}
}

void Car::spawnenemy()
{
	if (enemies.size() < enemymaxcar && timer >= 10)
	{
		enemy.setPosition(rand() % window->getSize().x, 0);
		enemies.push_back(enemy);
		timer = 0;
	}
	else
		timer++;
}

void Car::updateenemies()
{
	spawnenemy();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].move(0, movementspeed);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].getGlobalBounds().top >= window->getSize().y)
		{
			enemies.erase(enemies.begin() + i);
			points++;
		}
	}
	sprite.move(0, -movementspeed + 2);
	if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height < window->getSize().y)
	{
		//printf("aaa\n");
		sprite.setPosition(m, n);
	}


}

void Car::collision()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (carsprite.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
		{
			gameover = true;
			break;
		}
	}

}

void Car::update()
{
	pollevents();
	if (gameover == false)
	{
		updateinput();
		collisionwall(window);
		updateenemies();
		collision();

	}
	else
	{
		window->close();
	}

}

void Car::rendercar(sf::RenderTarget& target)
{
	target.draw(carsprite);
	for (int i = 0; i < enemies.size(); i++)
	{
		target.draw(enemies[i]);
	}
}

void Car::renderbg(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Car::render()
{
	window->clear();


	renderbg(*window);
	rendercar(*window);


	window->display();

}
