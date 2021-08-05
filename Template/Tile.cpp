#include "Tile.h"

#include "Game.h"
#include "TextureManager.h"

Tile::Tile()
{
	//getTransform().getPosition() = { x, y };
	setWidth(50);
	setHeight(50);
	getRigidBody().getVelocity().x = -250;
	TextureManager::Instance().load("assets/maps/tile.png", "tile");
	m_listTile.reserve(30);
	for (int i = 0; i < 29; i++)
	{
		m_listTile.push_back(50 * i);
	}
}

Tile::~Tile()
{
}

void Tile::draw()
{
	int tileSize = 32;
	for (auto& tileX : m_listTile)
	{
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 0, tileSize, tileSize }),tileX ,500, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 1, tileSize, tileSize }), tileX, 550, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 1, tileSize, tileSize }), tileX, 600, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 1, tileSize, tileSize }), tileX, 650, getWidth(), getHeight());
		TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 1, tileSize, tileSize }), tileX, 700, getWidth(), getHeight());
	}

	//TextureManager::Instance().draw("tile",SDL_Rect({tileSize*1,tileSize*0, tileSize, tileSize}) ,  getTransform().getPosition().x, getTransform().getPosition().y, getWidth(), getHeight());
	//TextureManager::Instance().draw("tile", SDL_Rect({ tileSize * 1,tileSize * 1, tileSize, tileSize }), getTransform().getPosition().x, getTransform().getPosition().y + 50, getWidth(), getHeight());
}

void Tile::update()
{
	for (auto& tileX : m_listTile)
	{

		if (tileX <= -50)
		{
			tileX = m_listTile.back() + 50;
			m_listTile.push_back(tileX);
			m_listTile.erase(m_listTile.begin());
		}
		int xSpeed = round(getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
		tileX = tileX + xSpeed;
		//std::cout << tileX << std::endl;
	}
	/*int xSpeed = round(getRigidBody().getVelocity().x * Game::Instance().getDeltaTime());
	getTransform().getPosition().x = getTransform().getPosition().x + xSpeed;*/
	/*if (getTransform().getPosition().x <= -50)
	{
		getTransform().getPosition().x = getWidth() * 26;
	}*/
}

void Tile::clean()
{
}
