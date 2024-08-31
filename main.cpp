#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(700, 500), "cat doge");
	window.setFramerateLimit(60);

	//hpBar
	int hp = 10;
	sf::RectangleShape hpBar;
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f((float)hp * 20.f, 20.f));
	hpBar.setPosition(330.f, 30.f);

	//ala
	sf::Texture alaTex;
	sf::Sprite ala;

	if (!alaTex.loadFromFile("ala.png"))
	{
		throw "Could not load ala.png!";
	}

	ala.setTexture(alaTex);
	ala.setScale(0.6f, 0.6f);
	ala.setPosition(sf::Vector2f(100.f, 100.f));

	//enemies
	sf::Texture enemyTex;
	sf::Sprite enemy;

	if (!enemyTex.loadFromFile("enemy.png"))
	{
		throw "Could not load enemy.png!";
	}

	enemy.setTexture(enemyTex);
	enemy.setScale(0.5f, 0.5f);

	std::vector<sf::Sprite> enemies;
	enemies.push_back(sf::Sprite(enemy));

	int enemySpawnTimer = 30;


	while (window.isOpen() && hp > 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}

		//UPDATE

		//enemies

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-10.f, 0.f);

			if (enemies[i].getPosition().x < 0 - enemy.getGlobalBounds().width)
			{
				enemies.erase(enemies.begin() + i);
			}
		}

		if (enemySpawnTimer < 32)
		{
			enemySpawnTimer++;
		}
		else if (enemySpawnTimer >= 32)
		{
			enemy.setPosition(window.getSize().x, rand() % int(window.getSize().y - enemy.getGlobalBounds().height));
			enemies.push_back(sf::Sprite(enemy));
			enemySpawnTimer = 0;
		}

		//ala

		ala.setPosition(ala.getPosition().x, sf::Mouse::getPosition(window).y);

		//Intersection

		if (ala.getPosition().y > window.getSize().y - ala.getGlobalBounds().height)
		{
			ala.setPosition(ala.getPosition().x, window.getSize().y - ala.getGlobalBounds().height);
		}

		if (ala.getPosition().y < 0)
		{
			ala.setPosition(ala.getPosition().x, 0.f);
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].getGlobalBounds().intersects(ala.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				hp--;
			}
		}

		//hpBar

		hpBar.setSize(sf::Vector2f((float)hp * 20.f, 20.f));

		//DRAW

		window.clear();

		for (int i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

		window.draw(ala);
		window.draw(hpBar);

		window.display();
	}

	return 0;
}