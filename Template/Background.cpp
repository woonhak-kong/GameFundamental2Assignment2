#include "Background.h"

#include "Config.h"
#include "Game.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance().load("assets/maps/background/bg1.png", "background1");
	TextureManager::Instance().load("assets/maps/background/bg2.png", "background2");
	TextureManager::Instance().load("assets/maps/background/bg3.png", "background3");
	TextureManager::Instance().load("assets/maps/background/bg4.png", "background4");

	for (int i = 0; i < 6; i++)
	{
		m_speed[i] = (i + 1) * -1;
	}
	/*m_speed[0] = 3;
	m_speed[1] = 0;
	m_speed[2] = 5;
	m_speed[3] = 5;
	m_speed[4] = 5;
	m_speed[6] = 5;*/
	for (int& i : m_backgroudX1)
	{
		i = 0;
	}

	for (int& i : m_backgroudX2)
	{
		i = Config::SCREEN_WIDTH;
	}

}

void Background::draw()
{
	TextureManager::Instance().draw("background1", m_backgroudX1[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background1", m_backgroudX2[0], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background2", m_backgroudX1[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background2", m_backgroudX2[1], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background3", m_backgroudX1[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background3", m_backgroudX2[2], 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	TextureManager::Instance().draw("background4", m_backgroudX1[3], 50, Config::SCREEN_WIDTH, 500);
	TextureManager::Instance().draw("background4", m_backgroudX2[3], 50, Config::SCREEN_WIDTH, 500);

}

void Background::update()
{

	//std::cout << (Game::Instance().getDeltaTime() * 100 / 4) << std::endl;
	for (int i = 0; i < 6; i++)
	{
		int speed = round(float((m_speed[i]) * (Game::Instance().getDeltaTime()*50)));
		m_backgroudX1[i] = m_backgroudX1[i] + speed;
	}
	for (int i = 0; i < 6; i++)
	{
		int speed = round(float((m_speed[i]) * (Game::Instance().getDeltaTime()*50)));
		m_backgroudX2[i] = m_backgroudX2[i] + speed;
	}

	for (int i = 0; i < 6; i++)
	{
		if (m_backgroudX1[i] <= (-Config::SCREEN_WIDTH))
		{
			m_backgroudX1[i] = m_backgroudX2[i] + Config::SCREEN_WIDTH;
		}
		if (m_backgroudX2[i] <= (-Config::SCREEN_WIDTH))
		{
			m_backgroudX2[i] = m_backgroudX1[i] + Config::SCREEN_WIDTH;
		}
	}

	//for (int& obj : m_backgroudX1)
	//{
	//	if (obj <= (-Config::SCREEN_WIDTH))
	//	{
	//		obj = Config::SCREEN_WIDTH;
	//	}

	//}
	//for (int& obj : m_backgroudX2)
	//{
	//	if (obj < (-Config::SCREEN_WIDTH))
	//	{
	//		obj = Config::SCREEN_WIDTH;
	//	}

	//}

	//for (int i = 0; i < 6; i++)
	//{
	//	if (abs(m_backgroudX1[i]) + abs(m_backgroudX2[i]) != Config::SCREEN_WIDTH)
	//	{
	//		if (m_backgroudX1[i] - m_backgroudX2[i] > 0)
	//		{
	//			m_backgroudX2[i] = m_backgroudX1[i] - Config::SCREEN_WIDTH;
	//		}
	//		else if (m_backgroudX1[i] - m_backgroudX2[i] < 0)
	//		{
	//			m_backgroudX1[i] = m_backgroudX2[i] - Config::SCREEN_WIDTH;
	//		}
	//	}
	//}
}

void Background::clean()
{
}
