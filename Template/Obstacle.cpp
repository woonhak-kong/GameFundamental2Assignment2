#include "Obstacle.h"

#include "Config.h"
#include "Game.h"
#include "TextureManager.h"

Obstacle::Obstacle(int num) :
	m_num(num)
{

	Animation animation = Animation();
	Frame frame;
	glm::vec2 size;
	std::string animationName = "obstacle";
	getRigidBody().getVelocity().x = -250;
	switch (m_num)
	{
		case 1:
		{
			std::string animationName = "obstacle1";
			TextureManager::Instance().load("assets/objects/obstacle1.png", "obstacle1");
			size = glm::vec2(294, 512);
			animation.name = "obstacle1";
			for (int i = 0; i < 10; ++i)
			{
				frame.name = "obstacle1";
				frame.x = size.x * i;
				frame.y = 0;
				frame.w = size.x;
				frame.h = size.y;
				animation.frames.push_back(frame);
			}
			TextureManager::Instance().setAnimation(animationName, animation);
			animation.frames.clear();
			setWidth(180);
			setHeight(460);

			getTransform().getPosition() = { 1300, -20 };

			setRealCollisionRect(130, 450);
			setAnimation(TextureManager::Instance().getAnimation("obstacle1"));
			break;
		}

		case 2:
		{
			std::string animationName = "obstacle2";
			TextureManager::Instance().load("assets/objects/obstacle2.png", "obstacle2");
			size = glm::vec2(78, 116);
			animation.name = "obstacle2";
			for (int i = 0; i < 6; ++i)
			{
				frame.name = "obstacle2";
				frame.x = size.x * i;
				frame.y = 0;
				frame.w = size.x;
				frame.h = size.y;
				animation.frames.push_back(frame);
			}
			TextureManager::Instance().setAnimation(animationName, animation);
			animation.frames.clear();
			setWidth(78);
			setHeight(116);
			getTransform().getPosition() = { 1300, 505 - getHeight() };

			setRealCollisionRect(50, 100);
			setAnimation(TextureManager::Instance().getAnimation("obstacle2"));
			break;
		}
		case 3:
			TextureManager::Instance().load("assets/objects/obstacle3.png", "obstacle3");
			setWidth(100);
			setHeight(50);
			getTransform().getPosition() = { 1300, 500 - getHeight() };
			setRealCollisionRect(80, 50);
			break;
	}



}

Obstacle::~Obstacle()
{

}

void Obstacle::draw()
{
	const SDL_Color greenColor = { 0, 255, 0, 255 };
	const SDL_Color redColor = { 255, 0, 0, 255 };

	if (Config::SHOWING_DEBUG)
	{
		const SDL_Rect collisionBox{ getRealCollisionRect().x, getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h };
		TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, greenColor);
	}

	switch (m_num)
	{
		case 1:
			TextureManager::Instance().playAnimation(getAnimation("obstacle1"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 1.f, 0.0f);
			break;

		case 2:
			TextureManager::Instance().playAnimation(getAnimation("obstacle2"), getTransform().getPosition().x,
				getTransform().getPosition().y, getWidth(), getHeight(), 4.f, 0.0f);
			break;

		case 3:
			TextureManager::Instance().draw("obstacle3",getTransform().getPosition().x, getTransform().getPosition().y , getWidth(), getHeight());
			break;

	}
}

void Obstacle::update()
{
	int xSpeed = round(getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	getTransform().getPosition().x += xSpeed;

	if (m_num == 3)
	{
		if (getTransform().getPosition().y >= 500 - getHeight())
		{
			getRigidBody().getVelocity().y = -250;
		}
		else if (getTransform().getPosition().y <= 100)
		{
			getRigidBody().getVelocity().y = 250;
		}
		int xSpeed = round(getRigidBody().getVelocity().y * Game::Instance().getDeltaTime());
		getTransform().getPosition().y = getTransform().getPosition().y + xSpeed;
	}
}

void Obstacle::clean()
{
}
