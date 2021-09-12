#pragma once

#include "Core.h"

#include <entt/entt.hpp>

class Mesh;

class Scene
{
public:
	Scene();
	~Scene();

	void OnUpdate();
	void OnRender();
	void LoadAssets();

	void OnKeyDown(UINT8 keycode);
	void OnKeyUp(UINT8 keycode);

private:
	Mesh* CreateTestMesh();

private:
	entt::registry m_Registry;
};