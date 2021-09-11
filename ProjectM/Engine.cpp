#include "pch.h"
#include "Engine.h"

Engine::Engine(UINT width, UINT height, std::wstring title)
	: m_Width(width)
	, m_Height(height)
	, m_Title(title)
{
	m_AspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

Engine::~Engine()
{

}

void Engine::OnInit()
{
	Log::Init();

	MK_INFO("Engine Initializing...");
}

void Engine::OnDestroy()
{

}

void Engine::OnUpdate()
{

}

void Engine::OnRender()
{

}

void Engine::OnKeyDown(UINT8 keycode)
{
	if (keycode == VK_ESCAPE)
	{
		::PostQuitMessage(0);
	}
}

void Engine::OnKeyUp(UINT8 keycode)
{

}
