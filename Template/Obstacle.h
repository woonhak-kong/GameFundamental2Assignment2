#pragma once
#include "Sprite.h"
class Obstacle : public Sprite
{
public:
	Obstacle(int num);
	~Obstacle();
	void draw() override;
	void update() override;
	void clean() override;

private:
	int m_num;
};

