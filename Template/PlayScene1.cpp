#include "PlayScene1.h"

#include "AttackBox.h"
#include "Background.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyKnight.h"
#include "LevelParser.h"
#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "ScoreManager.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "Tile.h"
#include <iomanip>
#include <sstream>

PlayScene1::PlayScene1() :
	m_state(SceneState::PLAY_SCENE1),
	m_score(0),
	m_isHPushed(false),
	m_time(0),
	m_spawn(0),
	m_obstacleList(0)
{
}

PlayScene1::~PlayScene1()
{
}

void PlayScene1::draw()
{
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 0, 255, 255);
	Scene::drawDisplayList();


	m_pBackground->draw();

	for (auto& obstacle : m_obstacleList)
	{
		obstacle->draw();
	}

	m_pTile->draw();
	m_pConcrete->draw();
	m_pPlayer->draw();

	m_score->draw();
	//m_testPlayer->draw();
}

void PlayScene1::update()
{
	Scene::updateDisplayList();

	if (m_pPlayer->getCurrentState() != CharacterState::DEAD)
	{
		m_time += Game::Instance().getDeltaTime();
		m_pBackground->update();
		for (auto& obstacle : m_obstacleList)
		{
			obstacle->update();
		}
		m_pTile->update();
		m_pConcrete->update();
		m_pPlayer->update();
		//m_testPlayer->update();
	}

	std::stringstream time;
	time << std::fixed << std::setprecision(2) << m_time;

	if (m_score != nullptr)
	{
		m_score->setText("Time : " + time.str());
	}


	for (auto& obstacle : m_obstacleList)
	{
		if(obstacle->getTransform().getPosition().x < -300)
		{
			delete obstacle;
			obstacle = nullptr;
			m_obstacleList.erase(std::remove(m_obstacleList.begin(), m_obstacleList.end(), obstacle), m_obstacleList.end());
		}
	}


	m_spawn += Game::Instance().getDeltaTime();
	if(m_spawn > 1.5)
	{
		int num;
		do
		{
			num = (rand() % 3) + 1;
		} while (num == m_preObstacle);

		m_preObstacle = num;

		m_obstacleList.push_back(new Obstacle(num));
		m_spawn = 0;
	}

	for (auto& obstacle : m_obstacleList)
	{
		if (CollisionManager::AABBCheck(m_pPlayer->getRealCollisionRect(),obstacle))
		{
			std::cout << "collision!!" << std::endl;
			m_pPlayer->collision(obstacle);
		}
	}
}

void PlayScene1::clean()
{
}

bool PlayScene1::onExit()
{
	Scene::removeAllChildren();
	SoundManager::Instance().clear();
	return true;
}

void PlayScene1::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
	{
		if (!m_isHPushed)
		{
			if (Config::SHOWING_DEBUG)
			{
				Config::SHOWING_DEBUG = false;
			}
			else
			{
				Config::SHOWING_DEBUG = true;
			}
			m_isHPushed = true;
		}
	}
	else
	{
		m_isHPushed = false;
	}

}

bool PlayScene1::onEnter()
{
	SoundManager::Instance().load("assets/audio/rallyx_bgm.mp3", "bgm", SoundType::SOUND_MUSIC);
	SoundManager::Instance().load("assets/audio/sword1.wav", "attack", SoundType::SOUND_SFX);
	SoundManager::Instance().load("assets/audio/fire.wav", "fire", SoundType::SOUND_SFX);
	SoundManager::Instance().load("assets/audio/enemy_explosion1.wav", SoundID::ENEMY_EXPLOSION, SoundType::SOUND_SFX);
	SoundManager::Instance().setMusicVolume(1);
	SoundManager::Instance().setSoundVolume(1);
	// texture loading
	/*StateParser stateParser;
	stateParser.ParseState(Config::TEXTURE_LOCATION.c_str(), Config::PLAY_SCENE1);*/

	m_pBackground = new Background();
	m_pTile = new Tile();
	m_pPlayer = new Player();
	m_pConcrete = new Concrete();


	//m_obstacleList.push_back(new Obstacle(2));


	m_score = new Label("Score : ", "Consolas", 30, { 0, 255, 0, 255 }, glm::vec2(1000, 50.0f),0,false);
	addChild(m_score,5);





	//EnemyKnight* enemy = new EnemyKnight(glm::vec2(300, 0), 200, 10, level->getCollisionLayers());
	//addChild(enemy);


	//addChild(new AttackBox(SDL_Rect{ 100,100,100,100 }, glm::vec2(10, 0), 100));

	//setPlayer(player);

	//SoundManager::Instance().playMusic("bgm");
	return true;
}

SceneState PlayScene1::getState()
{
	return m_state;
}


