#include "AnimatedSprite.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <filesystem>
#include <random>
#include <thread>


const std::filesystem::path textures_dir = R"(G:\Uczelnia\psio_2022\textures)";

const std::size_t monsterCount = 5;
const std::size_t mudCount = 2;
const float Epsilon = 1.0f;
const float scale = 1.0f;

float VectorLength(const sf::Vector2f& vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Texture LoadTextureFromFile(const std::string& name) {
	const auto filename = textures_dir / name;

	if (exists(filename))
	{
		sf::Texture texture;
		texture.loadFromFile(filename.string());
		return texture;
	}
	else
	{
		std::cout << "Couldn't open file: " << filename << "\n";
		throw;
	}

}

bool EqualWithEpsilon(
	const float f1,
	const float f2,
	const float epsilon
) {
	return std::abs(f2 - f1) < epsilon;
}

bool EqualWithEpsilon(
	const sf::Vector2f& v1,
	const sf::Vector2f& v2,
	const float epsilon
) {
	return EqualWithEpsilon(v1.x, v2.x, epsilon)
		&& EqualWithEpsilon(v1.y, v2.y, epsilon);

}

struct ResourceManager
{
	sf::Texture hero;
	sf::Texture monster;
	sf::Texture mud;
};

class Hero : public AnimatedSprite
{
	const std::vector<sf::IntRect> standingFrames_{
		sf::IntRect{0, 0, 50, 37},
		sf::IntRect{50, 0, 50, 37},
		sf::IntRect{100, 0, 50, 37},
	};
	const std::vector<sf::IntRect> runningFrames_{
		sf::IntRect{150, 0, 50, 37},
		sf::IntRect{200, 0, 50, 37},
		sf::IntRect{250, 0, 50, 37},
		sf::IntRect{300, 0, 50, 37},
		sf::IntRect{350, 0, 50, 37},
		sf::IntRect{400, 0, 50, 37},
	};


	sf::Vector2f goal_;
	float maxSpeed_ = 10.0f;
	bool isRunning = false;
	int health_ = 3;
public:
	Hero(ResourceManager& resources, float fps) :
		AnimatedSprite(
			resources.hero,
			fps) {

		setFrames(runningFrames_);
	}

	void SetGoal(const sf::Vector2f& goal) {
		goal_ = goal;
	}

	void GoTowardsTheGoal() {
		const bool isRunningBefore = isRunning;
		if (EqualWithEpsilon(goal_, getPosition(), Epsilon))
		{
			setSpeed({0, 0});
			isRunning = false;
		}
		else
		{
			const auto distance = goal_ - getPosition();
			const auto speed = maxSpeed_ * distance / VectorLength(distance);
			setSpeed(speed);
			isRunning = true;
		}

		if (isRunning != isRunningBefore)
		{
			if (isRunning)
			{
				setFrames(runningFrames_);
			}
			else
			{
				setFrames(standingFrames_);
			}
		}
	}

	void DecreaseHealth() {
		health_--;
	}

	bool IsAlive() {
		return health_ != 0;
	}
};

class Monster : public AnimatedSprite
{
public:
	Monster(ResourceManager& resources, float fps) :
		AnimatedSprite(
			resources.monster,
			fps) {
	}

	bool inactive = false;
};

class Mud : public AnimatedSprite
{
public:
	Mud(ResourceManager& resources, float fps) :
		AnimatedSprite(
			resources.mud,
			fps) {

		setFrames({
			sf::IntRect{
				190, 180, 47, 45
			}
		});
	}

	bool inactive = false;
};

struct GameState
{
	Hero hero;
	std::vector<Monster> monsters;
	std::vector<Mud> MudTiles;
};


sf::Vector2f GetRandomPosition(std::mt19937& random_generator,
                               const sf::Vector2f& windowSize,
                               const sf::Vector2f& assetSize) {

	const std::uniform_real_distribution<float> disX(0,
	                                                 windowSize.x - assetSize.x);
	const std::uniform_real_distribution<float> disY(0,
	                                                 windowSize.y - assetSize.y);
	const sf::Vector2f position = {
		disX(random_generator),
		disY(random_generator),
	};
	return position;
}


float GetRandomNumber(std::mt19937& random_generator, float from, float to) {
	const std::uniform_real_distribution<float> dis(from, to);
	return dis(random_generator);
}


void Update(GameState& gameState, const sf::Time& elapsedTime, sf::Vector2f boundaries) {

	gameState.hero.GoTowardsTheGoal();
	gameState.hero.Step(elapsedTime.asMilliseconds(), boundaries);

	for (auto& monster : gameState.monsters)
	{
		if (!monster.inactive)
		{
			monster.Step(elapsedTime.asMilliseconds(), boundaries);
		}
	}
	for (auto& mud : gameState.MudTiles)
	{
		if (!mud.inactive)
		{
			mud.Step(elapsedTime.asMilliseconds(), boundaries);
		}
	}

}

void Draw(GameState& gameState, sf::RenderWindow& window) {

	// draw
	window.draw(gameState.hero);
	for (auto& monster : gameState.monsters)
	{
		if (!monster.inactive)
		{
			window.draw(monster);
		}
	}
	for (auto& mud : gameState.MudTiles)
	{
		if (!mud.inactive)
		{
			window.draw(mud);
		}
	}

}

int main() {
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	const float fps = 5;

	const sf::Vector2f windowSize(window.getSize());

	const sf::Vector2f heroSpeed = {10, -10};
	const sf::Vector2f initialHeroGoal = windowSize / 2.0f;


	ResourceManager resources{
		LoadTextureFromFile("Character\\character.png"),
		LoadTextureFromFile("guy.png"),
		LoadTextureFromFile("Map\\tileset.png"),
	};

	GameState gameState{
		.hero = Hero{resources, fps}
	};
	std::mt19937 random_generator(1337); // Standard mersenne_twister_engine seeded with rd()

	{
		// Initialize gameState
		gameState.hero.scale(scale, scale);
		gameState.hero.setPosition(0,
		                           window.getSize().y - gameState.hero.getGlobalBounds().height);
		gameState.hero.setSpeed(heroSpeed);
		gameState.hero.SetGoal(initialHeroGoal);

		for (auto index = 0; index < monsterCount; ++index)
		{
			gameState.monsters.emplace_back(
				Monster{resources, fps}
			);

			auto& monster = gameState.monsters.back();
			monster.scale(scale, scale);

			// w losowych miejscach (poza lewym dolnym narożnikiem ekranu,
			// wylosuj takie wartości, aby obiekty nie wystawały poza krawędź ekranu), 

			monster.setPosition(
				GetRandomPosition(random_generator,
				                  sf::Vector2f{
					                  window.getSize()
				                  },
				                  {
					                  monster.getGlobalBounds().width,
					                  monster.getGlobalBounds().height
				                  }));
			monster.setSpeed({
				0,
				GetRandomNumber(random_generator, -200, 200)
			});
		}
		for (auto index = 0; index < mudCount; ++index)
		{
			gameState.MudTiles.emplace_back(
				Mud{resources, fps}
			);
			auto& mud = gameState.MudTiles.back();
			mud.scale(scale, scale);


			mud.setPosition(
				GetRandomPosition(random_generator,
				                  sf::Vector2f{window.getSize()},
				                  {
					                  static_cast<float>(mud.getGlobalBounds().width),
					                  static_cast<float>(mud.getGlobalBounds().height)
				                  }));
			mud.setSpeed({
				GetRandomNumber(random_generator, -50, 50),
				0,
			});
		}
	}

	sf::Clock clock;

	sf::Time elapsedTime;

	// run the program as long as the window is open
	while (window.isOpen() && gameState.hero.IsAlive())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					gameState.hero.SetGoal(mouse_position);
				}
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		const sf::Vector2f boundaries(window.getSize());
		Update(gameState, elapsedTime, boundaries);
		Draw(gameState, window);

		// end the current frame
		window.display();

		elapsedTime = clock.restart();
		std::this_thread::sleep_for(std::chrono::milliseconds{1});
	}

	return 0;
}
