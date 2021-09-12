#include "pch.h"
#include "Scene.h"

#include "Engine.h"
#include "Components.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::OnUpdate()
{

}

void Scene::OnRender()
{
	auto view = m_Registry.view<MeshRendererComponent>();
	for (auto entity : view)
	{
		auto& meshRenderer = view.get<MeshRendererComponent>(entity);
		SUBMIT(meshRenderer.Messi);
	}
}

void Scene::LoadAssets()
{
	auto entt = m_Registry.create();
	auto& meshRenderer = m_Registry.emplace<MeshRendererComponent>(entt);
	meshRenderer = CreateTestMesh();
}

Mesh* Scene::CreateTestMesh()
{
	float aspectRatio = ENGINE->GetAspectRatio();

	std::vector<Vertex> vertices(4);
	vertices[0].Position = Vector3(-0.5f, 0.5f * aspectRatio, 0.5f);
	vertices[0].Color = Vector4(1.f, 0.f, 0.f, 1.f);
	vertices[1].Position = Vector3(0.5f, 0.5f * aspectRatio, 0.5f);
	vertices[1].Color = Vector4(0.f, 1.f, 0.f, 1.f);
	vertices[2].Position = Vector3(0.5f, -0.5f * aspectRatio, 0.5f);
	vertices[2].Color = Vector4(0.f, 0.f, 1.f, 1.f);
	vertices[3].Position = Vector3(-0.5f, -0.5f * aspectRatio, 0.5f);
	vertices[3].Color = Vector4(0.f, 1.f, 0.f, 1.f);

	std::vector<UINT> indices;
	{
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}
	{
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
	}

	Mesh* rect = new Mesh(vertices, indices);
	return rect;
}
