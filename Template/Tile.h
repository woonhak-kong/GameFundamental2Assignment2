#pragma once
#include "Sprite.h"
class Tile : public Sprite
{
public:
	Tile();
	~Tile();
	void draw() override;
	void update() override;
	void clean() override;

private:

	std::vector<int> m_listTile;
};

