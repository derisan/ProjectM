#include "pch.h"
#include "ResourceManager.h"

#include "Mesh.h"
#include "Texture.h"

std::unordered_map<std::wstring, Mesh*> ResourceManager::m_Meshes;
std::unordered_map<std::wstring, Texture*> ResourceManager::m_Textures;

Mesh* ResourceManager::LoadMesh(const std::wstring& path)
{
	auto iter = m_Meshes.find(path);
	if (iter != m_Meshes.end())
	{
		return iter->second;
	}
	else
	{
		auto mesh = Mesh::CreateMesh(path);
		if (!mesh)
		{
			m_Meshes[path] = mesh;
		}
		return mesh;
	}
}

Mesh* ResourceManager::LoadCubeMesh()
{
	return nullptr;
}

Texture* ResourceManager::LoadTexture(const std::wstring& path)
{
	auto iter = m_Textures.find(path);
	if (iter != m_Textures.end())
	{
		return iter->second;
	}
	else
	{
		auto tex = Texture::CreateTexture(path);
		if (!tex)
		{
			m_Textures[path] = tex;
		}
		return tex;
	}
}
