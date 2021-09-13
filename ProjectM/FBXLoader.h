
#include "Core.h"


class Mesh;

struct MeshInfo
{
	std::vector<Vertex> vertices;
	std::vector<UINT> indices;
};


class FBXLoader
{
public:

	static FBXLoader* Get();
	Mesh* LoadFBX(const std::wstring& path);

private:
	FBXLoader();

	void Import(const std::wstring& path);
	void LoadNode(FbxNode* node);
	void LoadMesh(FbxMesh* mesh);
	void GetUV(FbxMesh* mesh, UINT idx, UINT uvIndex);

private:
	static FBXLoader* s_Instance;

	FbxManager* m_Manager;
	FbxScene* m_Scene;

	MeshInfo m_Mesh;
};