#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"
#include "SceneState.h"

class Background : public DisplayObject
{
public:
	Background();
	~Background() = default;
	void draw() override;
	void update() override;
	void clean() override;

private:

	// temporary

	int m_speed[6];

	int m_backgroudX1[6];
	int m_backgroudX2[6];
};

#endif // __BACKGROUND__