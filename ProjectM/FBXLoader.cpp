#include "pch.h"
#include "FBXLoader.h"

#include "Mesh.h"


FBXLoader* FBXLoader::s_Instance = nullptr;

FBXLoader* FBXLoader::Get()
{
	if (!s_Instance)
		s_Instance = new FBXLoader();

	return s_Instance;
}


FBXLoader::FBXLoader()
{
	m_Manager = FbxManager::Create();

	FbxIOSettings* ios = FbxIOSettings::Create(m_Manager, IOSROOT);
	m_Manager->SetIOSettings(ios);
}

void FBXLoader::Import(const std::wstring& path)
{
	FbxImporter* importer = FbxImporter::Create(m_Manager, "");

	std::string filepath = ws2s(path);
	bool status = importer->Initialize(filepath.c_str(), -1, m_Manager->GetIOSettings());
	MK_ASSERT(status, "Failed to Read FBX file");

	m_Scene = FbxScene::Create(m_Manager, "");
	importer->Import(m_Scene);

	m_Scene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::DirectX);

	FbxGeometryConverter geometryConverter(m_Manager);
	geometryConverter.Triangulate(m_Scene, true);

	importer->Destroy();
}

void FBXLoader::LoadNode(FbxNode* node)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();

	if (nodeAttribute)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			LoadMesh(node->GetMesh());
		}
	}

	const int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++)
	{
		LoadNode(node->GetChild(i));
	}
}

void FBXLoader::LoadMesh(FbxMesh* mesh)
{
	UINT vertexCount = mesh->GetControlPointsCount();
	m_Mesh.vertices.resize(vertexCount);

	FbxVector4* controlPoints = mesh->GetControlPoints();
	for (UINT i = 0; i < vertexCount; i++)
	{
		m_Mesh.vertices[i].Position.x = static_cast<float>(controlPoints[i].mData[0]);
		m_Mesh.vertices[i].Position.y = static_cast<float>(controlPoints[i].mData[1]);
		m_Mesh.vertices[i].Position.z = static_cast<float>(controlPoints[i].mData[2]);
	}

	UINT idx[3];
	UINT vertexCounter = 0;
	UINT triCount = mesh->GetPolygonCount();
	m_Mesh.indices.reserve(triCount * 3);
	for (UINT i = 0; i < triCount; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			UINT controlPointIndex = mesh->GetPolygonVertex(i, j);
			idx[j] = controlPointIndex;

			GetUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));

			vertexCounter++;
		}

		m_Mesh.indices.push_back(idx[0]);
		m_Mesh.indices.push_back(idx[1]);
		m_Mesh.indices.push_back(idx[2]);
	}
}

void FBXLoader::GetUV(FbxMesh* mesh, UINT idx, UINT uvIndex)
{
	FbxVector2 uv = mesh->GetElementUV()->GetDirectArray().GetAt(uvIndex);
	m_Mesh.vertices[idx].UV.x = static_cast<float>(uv.mData[0]);
	m_Mesh.vertices[idx].UV.y = 1.0f - static_cast<float>(uv.mData[1]);
}

Mesh* FBXLoader::LoadFBX(const std::wstring& path)
{
	Import(path);

	LoadNode(m_Scene->GetRootNode());

	auto loadedMesh = new Mesh(m_Mesh.vertices, m_Mesh.indices);

	return loadedMesh;
}