#pragma once
#ifndef __PLAYER__
#define __PLAYER__
#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();
	void draw() override;
	void update() override;
	void clean() override;
	void collision(DisplayObject* obj) override;
	void hit() override;
	void die() override;

	void handleEvent();

private:

	bool m_isSPushed;

};

#endif // __PLAYER__