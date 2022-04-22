#include "Car.h"

int main(void)
{
	srand(time(0));
	Car car;
	while (car.running())
	{

		//sf::RenderWindow window (sf::VideoMode(800, 600), "My Game");
		//update
		car.update();

		//render
		car.render();
		//window.clear();


	}

}