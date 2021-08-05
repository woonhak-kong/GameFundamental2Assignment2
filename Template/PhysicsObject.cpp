#include "PhysicsObject.h"

#include <algorithm>

#include "Camera.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Game.h"
#include "TextureManager.h"

PhysicsObject::PhysicsObject() :
	m_isCollision(false),
	m_isGroundCollision(false),
	m_fallingRate(150.0f)
{
}

void PhysicsObject::draw()
{
	const SDL_Color greenColor = { 0, 255, 0, 255 };
	const SDL_Color redColor = { 255, 0, 0, 255 };

	if (Config::SHOWING_DEBUG)
	{
		const SDL_Rect collisionBox{ getRealCollisionRect().x, getRealCollisionRect().y, getRealCollisionRect().w, getRealCollisionRect().h };
		if (m_isCollision)
		{
			TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, redColor);
		}
		else
		{
			TextureManager::Instance().drawRect(collisionBox.x, collisionBox.y, collisionBox.w, collisionBox.h, greenColor);
		}
		if (m_isGroundCollision)
		{
			TextureManager::Instance().drawRect(m_groundCollisionRect.x, m_groundCollisionRect.y, m_groundCollisionRect.w, m_groundCollisionRect.h, redColor);
		}
		else
		{
			TextureManager::Instance().drawRect(m_groundCollisionRect.x, m_groundCollisionRect.y, m_groundCollisionRect.w, m_groundCollisionRect.h, greenColor);
		}
	}
}

void PhysicsObject::update()
{
	glm::vec2 previousPosition;
	glm::vec2 newPosition;
	// sync ground collision box position;
	m_groundCollisionRect.x = getRealCollisionRect().x;
	m_groundCollisionRect.y = getRealCollisionRect().y + getRealCollisionRect().h;
	m_groundCollisionRect.w = getRealCollisionRect().w;
	m_groundCollisionRect.h = 5;

	//// checking object is on ground
	if (getTransform().getPosition().y >= 400 && getRigidBody().getVelocity().y >= 0)
	{
		m_isGroundCollision = true;
	}
	else
	{
		m_isGroundCollision = false;
	}

	m_setGravity();

	previousPosition.x = getTransform().getPosition().x;
	newPosition.x = getTransform().getPosition().x + (getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	getTransform().getPosition().x = newPosition.x;
	if (!m_isGroundCollision)
	{
	previousPosition.y = getTransform().getPosition().y;
	newPosition.y = getTransform().getPosition().y + (getRigidBody().getVelocity().y * Game::Instance().getDeltaTime());
	getTransform().getPosition().y = newPosition.y;
	}
}

void PhysicsObject::clean()
{
}

void PhysicsObject::collision(DisplayObject* obj)
{
}

bool PhysicsObject::isOnGround()
{
	return m_isGroundCollision;
}

float PhysicsObject::getFallingRate()
{
	return m_fallingRate;
}

void PhysicsObject::m_setGravity()
{

		getRigidBody().getVelocity().y += Config::GRAVITY * getRigidBody().getMass();
		getRigidBody().getVelocity().y = std::clamp(getRigidBody().getVelocity().y, -(getRigidBody().getMass() * m_fallingRate), (getRigidBody().getMass() * m_fallingRate));
}
