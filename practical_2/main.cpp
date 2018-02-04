
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"


using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

const int gameWidth = 800;
const int gameHeight = 600;

std::vector<Ship *> ships;

void load()
{
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load sprite sheet !" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

}


void Update(RenderWindow &window)
{
	// reset clock , recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}
	

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	//handle paddle movement
	

}

void Render(RenderWindow &window)
{
	window.draw(invader);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}