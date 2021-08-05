#pragma once
#ifndef __PLAY__SCENE1__
#define __PLAY__SCENE1__
#include "Background.h"
#include "Concrete.h"
#include "Level.h"
#include "Napkin.h"
#include "Node.h"
#include "Obstacle.h"
#include "Player.h"
#include "Scene.h"
#include "Tile.h"
class Label;

class PlayScene1 : public Scene
{
public:
	PlayScene1();
	~PlayScene1();

	// Inherited via Scene
	void draw() override;
    void update() override;
    void clean() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;

	SceneState getState() override;


private:

	bool m_isHPushed;



	Background* m_pBackground;
	Tile* m_pTile;
	Concrete* m_pConcrete;
	Player* m_pPlayer;

	std::vector<Obstacle*> m_obstacleList;

	Label* m_score;
	float m_time;
	float m_spawn;
	int m_preObstacle;

	SceneState m_state;
};

#endif // __PLAY__SCENE1__
