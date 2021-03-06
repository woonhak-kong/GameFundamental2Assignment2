#include "UIControl.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MouseButtons.h"

UIControl::UIControl() :
	m_mouseOver(false),
	m_mouseOverActive(false),
	m_mouseOutActive(false),
	m_leftMouseButtonClicked(false)
{
}

bool UIControl::addEventListener(const Event event, const EventHandler & handler)
{
	if (m_eventExists(event))
	{
		return false;
	}

	m_events[event] = handler;
	return true;
}

UIControl::EventHandler UIControl::getEventHandler(Event event)
{
	return m_events[event];
}

void UIControl::onMouseOver()
{
	const auto mousePosition = EventManager::Instance().getMousePosition();

	if (CollisionManager::pointRectCheck(mousePosition, getTransform().getPosition(), getWidth(), getHeight()))
	{
		m_mouseOver = true;
	}
	else
	{
		m_mouseOver = false;
	}

	if ((m_events[Event::MOUSE_OVER]) && (!m_mouseOverActive))
	{
		if (m_mouseOver)
		{
			m_events[Event::MOUSE_OVER]();
			m_mouseOverActive = true;
		}
	}
	else if ((m_events[Event::MOUSE_OVER]) && (!m_mouseOver))
	{
		m_mouseOverActive = false;
	}
}

void UIControl::onMouseOut()
{
	if ((m_events[Event::MOUSE_OUT]) && (m_mouseOutActive) && (!m_mouseOver))
	{
		m_events[Event::MOUSE_OUT]();
		m_mouseOutActive = false;
	}
	else if ((m_events[Event::MOUSE_OUT]) && (m_mouseOver))
	{
		m_mouseOutActive = true;
	}
}

void UIControl::onLeftMouseButtonClick()
{
	if (EventManager::Instance().getMouseButton(static_cast<int>(MouseButtons::LEFT)))
	{
		if ((m_events[Event::CLICK]) && (m_mouseOver) && !m_leftMouseButtonClicked)
		{
			m_leftMouseButtonClicked = true;
			m_events[Event::CLICK](); // call click event
		}
	}
	else
	{
		m_leftMouseButtonClicked = false;
	}
}

bool UIControl::m_eventExists(Event id)
{
	return m_events.find(id) != m_events.end();
}
