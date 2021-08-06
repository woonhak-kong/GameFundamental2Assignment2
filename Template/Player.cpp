#include "Player.h"

#include <iostream>

#include "Camera.h"
#include "Config.h"
#include "EventManager.h"
#include "Game.h"
#include "MouseButtons.h"
#include "Scene.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player() :
	Character(LoaderParams(200,200,100,100,50,100,10,10,"")),
	m_isSPushed(false)
{

	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "player";

	TextureManager::Instance().load("assets/characters/player/dead.png", "dead");
	TextureManager::Instance().load("assets/characters/player/fall.png", "fall");
	TextureManager::Instance().load("assets/characters/player/jump.png", "jump");
	TextureManager::Instance().load("assets/characters/player/slide.png", "slide");
	TextureManager::Instance().load("assets/characters/player/run.png", "run");

	size = glm::vec2(556, 504);
	animation.name = "dead";
	for (int i = 0; i < 10; ++i)
	{
		frame.name = "dead";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();


	size = glm::vec2(542, 474);
	animation.name = "fall";
	for (int i = 0; i < 8; ++i)
	{
		frame.name = "fall";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	size = glm::vec2(542, 474);
	animation.name = "jump";
	for (int i = 0; i < 8; ++i)
	{
		frame.name = "jump";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	size = glm::vec2(542, 474);
	animation.name = "slide";
	for (int i = 0; i < 10; ++i)
	{
		frame.name = "slide";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	size = glm::vec2(542, 474);
	animation.name = "run";
	for (int i = 0; i < 8; ++i)
	{
		frame.name = "run";
		frame.x = size.x * i;
		frame.y = 0;
		frame.w = size.x;
		frame.h = size.y;
		animation.frames.push_back(frame);
	}
	TextureManager::Instance().setAnimation(animationName, animation);
	animation.frames.clear();

	setAnimation(TextureManager::Instance().getAnimation("player"));


}

Player::~Player()
{

}

void Player::draw()
{
	Character::draw();
	/*TextureManager::Instance().draw("napkin", getTransform().getPosition().x - Camera::Instance().getPosition().x,
		getTransform().getPosition().y - Camera::Instance().getPosition().y , getWidth(), getHeight(),  0, 255);*/
	int alpha = 255;
	/*if (m_hitMotionNum > 0)
	{
		if (m_hitMotionNum % 2 == 0)
		{
			alpha = 20;
		}
		else
		{
			alpha = 255;
		}
		m_hitMotionNum--;
	}
	else
	{
		alpha = 255;
	}*/
	SDL_RendererFlip flip;
	//flip = isFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if (getCurrentDirection().x < 0)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}

	switch (getCurrentState())
	{


		case CharacterState::RUN:
			TextureManager::Instance().playAnimation(getAnimation("run"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 1.f, 0.0f, alpha, flip);

			break;
		case CharacterState::JUMP:
			TextureManager::Instance().playAnimation(getAnimation("jump"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 1.f, 0.0f, alpha, flip, false);

			break;
		case CharacterState::FALL:
			TextureManager::Instance().playAnimation(getAnimation("fall"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 1.f, 0.0f, alpha, flip, false);

			break;
		case CharacterState::SLIDE:
			TextureManager::Instance().playAnimation(getAnimation("slide"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 1.f, 0.0f, alpha, flip);

			break;

		case CharacterState::DEAD:
			TextureManager::Instance().playAnimation(getAnimation("dead"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 0.4f, 0.0f, alpha, flip, false, [&](CallbackType type) -> void
				{
					switch (type)
					{
						case CallbackType::ANIMATION_END:
							//m_gameOver = true;
							Game::Instance().changeSceneState(SceneState::END_SCENE);
							break;
						default:
							break;
					}
				}, -1, false, false);
			break;
	}


}

void Player::update()
{
	handleEvent();
	Character::update();

}

void Player::clean()
{

}

void Player::collision(DisplayObject* obj)
{
	takeDamage(100);
}

void Player::hit()
{
}

void Player::die()
{
	Character::die();
	SoundManager::Instance().playSound("die");
	Config::GAME_OVER = true;
}

void Player::handleEvent()
{

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
	//	if (!m_isSPushed)
	//	{
		slide();
	//}
	//m_isSPushed = true;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		moveToLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		moveToRight();
	}

	else
	{
		m_isSPushed = false;
		idle();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (!isJump())
		{
			SoundManager::Instance().playSound("jump");
		}
		jump();


	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		Game::Instance().pushSceneState(SceneState::PAUSE_SCENE);
		//jump();
		//if (!m_isQEPushed)
		//{
		//	changeSwordLeft();
		//}
		//m_isQEPushed = true;
	}
	else
	{
		//m_isQEPushed = false;
	}
}
