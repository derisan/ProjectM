#pragma once

#include "Core.h"


class Engine
{
public:
	Engine(UINT width, UINT height, std::wstring title);
	~Engine();

	void OnInit();
	void OnDestroy();
	void OnUpdate();
	void OnRender();

	void OnKeyDown(UINT8 keycode);
	void OnKeyUp(UINT8 keycode);

	UINT GetWidth() const { return m_Width; }
	UINT GetHeight() const { return m_Height; }
	float GetAspectRatio() const { return m_AspectRatio; }
	const std::wstring& GetTitle() const { return m_Title; }

private:
	UINT m_Width;
	UINT m_Height;
	float m_AspectRatio;
	std::wstring m_Title;
};

