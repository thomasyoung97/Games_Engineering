#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] =
{
	Keyboard::A, // player1 UP
	Keyboard::Z, // player1 Down
	Keyboard::Up, //player2 Up
	Keyboard::Down // Player2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void load()
{
	// set size and origin of paddles
	for (auto &p : paddles)
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}

	// set size and origin or ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	//reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition((gameWidth - 10) - paddleSize.x / 2, gameHeight / 2);

	ball.setPosition(gameWidth / 2 , gameHeight /2 );

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void reset()
{
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition((gameWidth - 10) - paddleSize.x / 2, gameHeight / 2);

	ball.setPosition(gameWidth / 2, gameHeight / 2);

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
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
	float direction = 0.0f;
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}
	if (Keyboard::isKeyPressed(controls[2]))
	{
		direction2--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		direction2++;
	}

//	paddles[1].move(0, direction2 * paddleSpeed * dt);
	paddles[0].move(0, direction * paddleSpeed * dt);
	ball.move(ballVelocity * dt);

	


	//check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by < paddles[1].getPosition().y)
	{
		direction2--;
	}
	if (by > paddles[1].getPosition().y)
	{
		direction2++;
	}
	paddles[1].move(0, direction2 * paddleSpeed * dt);


	//paddle movement constraints
	if (paddles[0].getPosition().y > gameHeight)
	{
		paddles[0].setPosition(paddles[0].getPosition().x, gameHeight);
	}
	else if (paddles[0].getPosition().y < 0)
	{
		paddles[0].setPosition(paddles[0].getPosition().x, 1);
	}
	if (paddles[1].getPosition().y > gameHeight)
	{
		paddles[1].setPosition(paddles[1].getPosition().x, gameHeight);
	}
	else if (paddles[1].getPosition().y < 0)
	{
		paddles[1].setPosition(paddles[1].getPosition().x, 1);
	}

	//ball collision
	if (by > gameHeight)
	{
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0)
	{
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}

	if (bx > gameWidth)
	{
		// right wall
		reset();
	}
	else if (bx < 0)
	{
		//left wall
		reset();
	}
	// ball is inline or behind paddle
	else if (bx < paddles[0].getPosition().x  && 
		//ball is below top edge of the paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
	
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(0, -10);

	}
	else if (bx > paddles[1].getPosition().x &&
		by > paddles[1].getPosition().y - (paddleSize.y * 1) &&
		by < paddles[1].getPosition().y + (paddleSize.y * 1))
	{
	ballVelocity.x *= - 1.1f;
	ballVelocity.y *= 1.1f;
	ball.move(0, -10);
	}

}

void Render(RenderWindow &window)
{
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}
int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
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