#pragma once
#include "Button.h"
#include "Scene.h"
class PauseScene : public Scene
{
public:
	PauseScene();
	~PauseScene();
	void draw() override;
	void clean() override;
	void update() override;
	bool onExit() override;
	void handleEvents() override;
	bool onEnter() override;
	SceneState getState() override;


private:
	SceneState m_state;
	Button* m_pSartButton;
};

