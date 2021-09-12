#pragma once

#include "Mesh.h"

struct MeshRendererComponent
{
	Mesh* Messi;

	MeshRendererComponent() = default;
	MeshRendererComponent(Mesh* mesh)
		: Messi(mesh) {}
};