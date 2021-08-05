#include "Concrete.h"

#include "Game.h"
#include "TextureManager.h"

Concrete::Concrete()
{
	setWidth(50);
	setHeight(50);
	getRigidBody().getVelocity().x = -350;
	TextureManager::Instance().load("assets/maps/tile.png", "tile");
	m_listTile.reserve(30);
	for (int i = 0; i < 10; i++)
	{
		m_listTile.push_back(200 * i);
	}
}

Concrete::~Concrete()
{
}

void Concrete::draw()
{
	int tileSize = 16;
	for (auto& tileX : m_listTile)
	{
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 20,tileSize * 0, tileSize, tileSize }), tileX, 520, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 21,tileSize * 0, tileSize, tileSize }), tileX+getWidth(), 520, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 22,tileSize * 0, tileSize, tileSize }), tileX + getWidth()*2, 520, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 25,tileSize * 0, tileSize, tileSize }), tileX + getWidth()*3, 520, getWidth(), getHeight());

		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 20,tileSize * 2, tileSize, tileSize }), tileX, 570, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 20,tileSize * 2, tileSize, tileSize }), tileX + getWidth() * 3, 570, getWidth(), getHeight());

		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 20,tileSize * 3, tileSize*4, tileSize*4 }), tileX, 620, getWidth()*4, getHeight()*4);

	}
}

void Concrete::update()
{
	for (auto& tileX : m_listTile)
	{

		//std::cout << tileX << std::endl;
		if (tileX <= -200)
		{
			tileX = m_listTile.back() + 200;
			m_listTile.push_back(tileX);
			m_listTile.erase(m_listTile.begin());
		}
		int xSpeed = round(getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
		tileX = tileX + xSpeed;
	}
}

void Concrete::clean()
{
}
