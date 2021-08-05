#pragma once
#include "Sprite.h"
class Concrete : public Sprite
{
public:
	Concrete();
	~Concrete();
	void draw() override;
	void update() override;
	void clean() override;


private:
	std::vector<int> m_listTile;
};

