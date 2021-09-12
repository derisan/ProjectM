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

	Mesh* CreateTestMesh();

private:
	entt::registry m_Registry;
};