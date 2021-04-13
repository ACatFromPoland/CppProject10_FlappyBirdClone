#include <SFML/Graphics.hpp>
#include "Vectors.h"
#include "buttonInput.h"

#define WINDOWX 1500
#define WINDOWY 800

#define getrandom(min, max) ((rand()%(int)(((max) + 1) - (min)))+ (min))


class Player {
public:

	Vector2 position = Vector2(350.f, WINDOWY / 2);
	Vector2 velocity = Vector2(0.f, 0.f);

	float radius = 10.f;
	sf::CircleShape rect;

	Player(){
		rect.setRadius(radius);
		rect.setOrigin(sf::Vector2f(radius/2, radius/2));
	}
	void update(float deltatime) {
		velocity = velocity + (Vector2(0.f, 800.f) * deltatime);
		position = position + (velocity * deltatime);
	}
};


class Walls;
typedef std::vector<Walls> WallArray;
class Walls {
public:

	float holesize = 100.f;
	float displacement = getrandom(200, 600);
	float length = WINDOWY;

	Vector2 dimTop = Vector2(20.f, 100.f + displacement);
	Vector2 positionTop = Vector2(WINDOWX + dimTop.x, 0.f);

	Vector2 dimBottom = Vector2(20.f, WINDOWY - holesize + 100.f + displacement);
	Vector2 positionBottom = Vector2(WINDOWX + dimTop.x, holesize + 100.f + displacement);

	sf::RectangleShape rectTop;
	sf::RectangleShape rectBottom;

	Walls() {
		rectTop.setSize(dimTop.asSF());
		rectBottom.setSize(dimBottom.asSF());

	}

	Vector2 velocity = Vector2(-250.f, 0.f);
	void Update(float deltatime) {
		positionTop = positionTop + (velocity * deltatime);
		positionBottom = positionBottom + (velocity * deltatime);
	}
};


void updatePlayer(Player &player, float deltatime, sf::RenderWindow &window) {
	player.update(deltatime);
	player.rect.setPosition(player.position.asSF());
	window.draw(player.rect);
}


void updateWalls(WallArray &wallArray, float deltatime) {
	for (int i = 0; i < wallArray.size(); i++) {
		Walls &wall = wallArray[i];

		if (wall.positionTop.x < 0 - wall.dimTop.x) { // Refresh
			float holesize = wallArray[i].holesize;

			float randis = getrandom(100, 700);

			wall.dimTop = Vector2(20.f, randis);
			wall.positionTop = Vector2(WINDOWX + wall.dimTop.x, 0.f);
			
			wall.positionBottom = Vector2(WINDOWX + wall.dimTop.x, randis + holesize);
			wall.dimBottom = Vector2(20.f, WINDOWY - (randis + holesize));

			wall.rectTop.setFillColor(sf::Color::White);
			wall.rectBottom.setFillColor(sf::Color::White);

		}
		wallArray[i].Update(deltatime);
	}
}

void renderWalls(WallArray &wallArray, sf::RenderWindow &window) {
	for (int i = 0; i < wallArray.size(); i++) {
		Walls &wall = wallArray[i];

		wall.rectTop.setPosition(wall.positionTop.asSF());
		wall.rectBottom.setPosition(wall.positionBottom.asSF());

		wall.rectTop.setSize(wall.dimTop.asSF());
		wall.rectBottom.setSize(wall.dimBottom.asSF());

		window.draw(wall.rectTop);
		window.draw(wall.rectBottom);
	}
}

bool playerCollision(WallArray &w, Player p) {
	bool hit = false;
	for (int i = 0; i < w.size(); i++) {
		Walls &wall = w[i];

		float cx = p.position.x;
		float cy = p.position.y;
		float tX = cx;
		float tY = cy;

		// Top wall collision
		if (cx < wall.positionTop.x) {
			tX = wall.positionTop.x;
		}
		else if (cx > wall.positionTop.x + wall.dimTop.x) {
			tX = wall.positionTop.x + wall.dimTop.x;
		}
		if (cy < wall.positionTop.y) {
			tY = wall.positionTop.y;
		}
		else if (cy > wall.positionTop.y + wall.dimTop.y) {
			tY = wall.positionTop.y + wall.dimTop.y;
		}

		float dX = cx - tX;
		float dY = cy - tY;
		float dist = sqrt((dX * dX) + (dY * dY));
		if (dist <= p.radius)
			hit = true;

		// Bottom wall collision
		cx = p.position.x;
		cy = p.position.y;
		tX = cx;
		tY = cy;

		if (cx < wall.positionBottom.x) {
			tX = wall.positionBottom.x;
		}
		else if (cx > wall.positionBottom.x + wall.dimBottom.x) {
			tX = wall.positionBottom.x + wall.dimBottom.x;
		}
		if (cy < wall.positionBottom.y) {
			tY = wall.positionBottom.y;
		}
		else if (cy > wall.positionBottom.y + wall.dimBottom.y) {
			tY = wall.positionBottom.y + wall.dimBottom.y;
		}

		dX = cx - tX;
		dY = cy - tY;
		dist = sqrt((dX * dX) + (dY * dY));
		if (dist <= p.radius)
			hit = true;
	}
	return hit;
}

class Game {
public:
	void start(sf::RenderWindow &window, sf::Clock &clock) {
		float holesize = 45.f;
		WallArray wallArray(5);
		for (int i = 0; i < wallArray.size(); i++) {
			wallArray[i].positionTop.x = (float)WINDOWX + (i *(WINDOWX / wallArray.size()));
			wallArray[i].positionBottom.x = (float)WINDOWX + (i *(WINDOWX / wallArray.size()));
		}

		Player player;
		newPressMouse jump = newPressMouse(sf::Mouse::Left);

		sf::Event event;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			float deltatime = clock.restart().asSeconds();
			window.clear(sf::Color::Black);
			//

			if (jump.isPressed())
				player.velocity = player.velocity + Vector2(0.f, -400.f);

			updateWalls(wallArray, deltatime);
			renderWalls(wallArray, window);

			updatePlayer(player, deltatime, window);
			if (playerCollision(wallArray, player))
			{
				return;
			}
			if (player.position.x < 0)
				return;
			if (player.position.x > WINDOWX)
				return;
			if (player.position.y < 0)
				return;
			if (player.position.y > WINDOWY)
				return;
			//
			window.display();
		}
	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "FlappyBird", sf::Style::Close);
	sf::Clock clock;

	while (1) {
		Game game;
		game.start(window, clock);
	}

	return 0;
}