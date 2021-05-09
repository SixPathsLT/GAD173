#include "GameScene.h"
#include <kage2dutil/texture_manager.h>
#include <iostream>
#include "ResourceManager.h"
#include "GameManager.h"
#include "Entities/ChocoboNPC.h"
#include "Utils.h"
#include "Entities/Ball.h"

Entity* chocoboNPC;


GameScene::GameScene(sf::RenderWindow* m_window) : Scene()
{
	this->m_window = m_window;

	m_backgroundSprite = kage::TextureManager::getSprite("data/GameData/game_background.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);
}

GameScene::~GameScene()
{
	/*delete animatedCoins;
	delete balls;
	delete scoreText;
	delete chocoboNPC;*/
}


bool GameScene::start()
{
	return Scene::start();
}

void GameScene::load() {
	clock.restart();

	sf::Color color = sf::Color::White;
	text->setString("");
	text->setFillColor(sf::Color(color.r, color.g, color.b, 220));
	text->setPosition(800, 200);
	text->setCharacterSize(450);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(8);

	scoreText->setPosition(1650, 100);
	scoreText->setFillColor(sf::Color::Yellow);
	scoreText->setCharacterSize(50);
	scoreText->setOutlineColor(sf::Color::Black);
	scoreText->setOutlineThickness(2);
	scoreText->setFont(ResourceManager::FONT_BLUE_HIGH);
		
	Button::START_BUTTON.setPosition(670, 500);

	int startX = 1670;
	int startY = 300;
	Button::PAUSE_BUTTON.setPosition(startX, startY);
	Button::MENU_BUTTON.setPosition(startX, startY + 100);
	Button::QUIT_BUTTON.setPosition(startX, startY + 200);

	balls = new Ball[TOTAL_COINS];
	animatedCoins = new AnimatedSprite[TOTAL_COINS];

	for (int i = 0; i < TOTAL_COINS; i++) {
		balls[i].setDirection(0, 0);
		balls[i].setPosition(0, 1200);

		animatedCoins[i].setAnimation(AnimatedSprite::COIN, 90);
		animatedCoins[i].spriteSheet.setPosition(250 * (1 + i), 550);
		animatedCoins[i].spriteSheet.setScale(0.4, 0.4);
		animatedCoins[i].play(true);
	}
	float health = 100;
	float multiplier = 1.f + ((GameManager::currentLevel / 10.f) * 2);
	chocoboNPC = new ChocoboNPC(health * multiplier, 3);
	chocoboNPC->setPosition(30, 300);

	Scene::load();

	isRunning = false;
}
void GameScene::end() {
	clock.restart();

	Scene::end();
}

void GameScene::update()
{

	scoreText->setString("Score: " + std::to_string(GameManager::points));

	sf::Time time = clock.getElapsedTime();

	bool won = chocoboNPC->isDead() && gameOver();
	if (won && time.asSeconds() > 10) {
		clock.restart();
	}

	
	switch ((int) time.asSeconds()) {
	case 1:
		text->setString("3");
		break;
	case 2:
		text->setString("2");
		break;
	case 3:
		text->setString("1");
		break;
	case 4:
		if (won) {
			GameManager::endGame();
			GameManager::openLevels();
		} else {
			isRunning = true;
		}
		text->setString("");
		break;
	}


	if (!isRunning) {
		if (chocoboNPC->getClock().getElapsedTime().asSeconds() >= 1)
			chocoboNPC->getClock().restart();
	}

	Button::MENU_BUTTON.update(*m_window);
	Button::QUIT_BUTTON.update(*m_window);

	if (gameOver()) {
		text->setPosition(400, won ? 300 : 100);
		text->setCharacterSize(250);
		
		sf::Color color = won ? sf::Color::Green : sf::Color::Red;
		text->setFillColor(sf::Color(color.r, color.g, color.b, 100));
		text->setString(won ? "YOU WON!" : "YOU LOST!");

		Button::START_BUTTON.update(*m_window);
		return;
	} else if (time.asSeconds() > 4) {
		Button::PAUSE_BUTTON.update(*m_window);
	}

	Scene::update();

	if (!isRunning)
		return;

	for (int i = 0; i < TOTAL_COINS; i++) {
		AnimatedSprite &animatedCoin = animatedCoins[i];
		animatedCoin.update();

		Ball *extraBall = nullptr;

		for (int i2 = 0; i2 < TOTAL_COINS; i2++) {
			Ball &ball = balls[i2];
			if (ball.getDirection().x == 0 && ball.getDirection().y == 0)
				continue;

			extraBall = &ball;
			break;
		}

		if ((extraBall != nullptr && Utils::collides(extraBall->getBallShape().getGlobalBounds(), animatedCoin.spriteSheet.getGlobalBounds()))
			|| Utils::collides(GameManager::ball->getBallShape().getGlobalBounds(), animatedCoin.spriteSheet.getGlobalBounds())) {
			balls[i].setPosition(animatedCoin.spriteSheet.getPosition().x, animatedCoin.spriteSheet.getPosition().y);
			balls[i].setDirection(-1, -1);
			balls[i].getBallShape().setFillColor(sf::Color::White);
			animatedCoin.spriteSheet.setPosition(0, 1500);
			animatedCoin.play(false);
		}
	}

	for (int i = 0; i < TOTAL_COINS; i++) {
		Ball &ball = balls[i];
		if (ball.getDirection().x == 0 && ball.getDirection().y == 0)
			continue;

		ball.update(*m_window);
		if (Utils::collides(ball.getBallShape().getGlobalBounds(), chocoboNPC->getAnimatedSprite().spriteSheet.getGlobalBounds())) {
			chocoboNPC->doDamage(2.f);
		}
	}


	GameManager::grid.update(*m_window);
	GameManager::ball->update(*m_window);
	GameManager::player->update(*m_window);
	chocoboNPC->update(*m_window);
}

void GameScene::render()
{
	//if (!isRunning)
	//	return;

	m_window->draw(*m_backgroundSprite);


	m_window->draw(GameManager::grid.rectShape);

	GameManager::grid.draw(*m_window);

	for (int i = 0; i < TOTAL_COINS; i++) {
		animatedCoins[i].render(*m_window);
	}

	for (int i = 0; i < TOTAL_COINS; i++) {
		Ball &ball = balls[i];
		if (ball.getDirection().x == 0 && ball.getDirection().y == 0)
			continue;

		balls[i].render(*m_window);
	}

	GameManager::ball->render(*m_window);
	GameManager::player->render(*m_window);
	chocoboNPC->render(*m_window);

	Button::PAUSE_BUTTON.color = isRunning ? sf::Color::Cyan : sf::Color::Yellow;
	sf::Time time = clock.getElapsedTime();

	if (gameOver()) {
		if (!chocoboNPC->isDead())
			Button::START_BUTTON.render(*m_window);
	} else if(time.asSeconds() > 4) {
		Button::PAUSE_BUTTON.render(*m_window);
	}
	Button::MENU_BUTTON.render(*m_window);
	Button::QUIT_BUTTON.render(*m_window);


	if (time.asSeconds() < 4 || gameOver()) {
		m_window->draw(*text);
	}

	m_window->draw(*scoreText);

}

bool GameScene::gameOver()
{
	if (GameManager::player->isDead() || (chocoboNPC->isDead() && (chocoboNPC->getPosition().y > GameManager::player->getPosition().y + 200)))
		return true;

	int playerY = (GameManager::player->getPosition().y + (GameManager::player->getPlayerShape().getSize().y * 2));
	bool ballExists = false;

	if (GameManager::ball->getPosition().y < playerY) {
		ballExists = true;
	}

	if (!ballExists) {
		for (int i = 0; i < TOTAL_COINS; i++) {
			Ball &ball = balls[i];
			if (ball.getDirection().x == 0 && ball.getDirection().y == 0)
				continue;

			if (ball.getPosition().y < playerY) {
				ballExists = true;
			}
		}
	}

	if (ballExists)
		return false;

	return true;
}
