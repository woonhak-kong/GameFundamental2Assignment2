#include "PauseScene.h"

#include "EventManager.h"
#include "Game.h"
#include "Label.h"
#include "SoundID.h"
#include "SoundManager.h"
#include "TextureManager.h"

PauseScene::PauseScene() :
	m_state(SceneState::END_SCENE)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::draw()
{

	SDL_Rect m_rect = { Config::SCREEN_WIDTH / 10 , Config::SCREEN_HEIGHT / 10 , Config::SCREEN_WIDTH / 10 * 8 , Config::SCREEN_HEIGHT/ 10 * 8 };
	SDL_SetRenderDrawColor(TextureManager::Instance().getRenderer(), 0, 255, 0, 100);
	SDL_SetRenderDrawBlendMode(TextureManager::Instance().getRenderer(), SDL_BLENDMODE_BLEND);

	SDL_RenderFillRect(TextureManager::Instance().getRenderer(), &m_rect);
	Scene::drawDisplayList();
}

void PauseScene::clean()
{
}

void PauseScene::update()
{
	Scene::updateDisplayList();
}

bool PauseScene::onExit()
{
	Scene::removeAllChildren();
	Config::GAME_OVER = false;
	SoundManager::Instance().resumeMusic();
	return true;
}

void PauseScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

bool PauseScene::onEnter()
{
	SoundManager::Instance().pauseMusic();

	Config::GAME_OVER = true;

	const SDL_Color blue = { 0, 255, 255, 255 };
	Label* m_pSubLabel = new Label("Pause!", "Consolas", 150, blue, glm::vec2(Config::SCREEN_WIDTH/2, 150), 0, true);
	m_pSubLabel->setParent(this);
	addChild(m_pSubLabel);



	m_pSartButton = new Button("assets/UI/PlayButton.png", "Resume", GameObjectType::START_BUTTON,
		glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2), true);

	m_pSartButton->addEventListener(Event::CLICK, [&]()-> void
		{
			SoundManager::Instance().playSound(SoundID::BTN_CLICK);
			Game::Instance().popSceneState();

		});
	m_pSartButton->addEventListener(Event::MOUSE_OVER, [&]() -> void
		{
			m_pSartButton->setAlpha(150);
			SoundManager::Instance().playSound(SoundID::BTN_HOVER);
		});

	m_pSartButton->addEventListener(Event::MOUSE_OUT, [&]() -> void
		{
			m_pSartButton->setAlpha(255);
		});

	addChild(m_pSartButton);


	return true;
}

SceneState PauseScene::getState()
{
	return m_state;
}
