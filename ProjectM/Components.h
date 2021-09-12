#pragma once

#include "Mesh.h"
#include "d3dHelper.h"
#include "Engine.h"

struct MeshRendererComponent
{
	Mesh* Messi;

	MeshRendererComponent() = default;
	MeshRendererComponent(const MeshRendererComponent&) = default;
	MeshRendererComponent(Mesh* mesh)
		: Messi(mesh) {}
};

struct TransformComponent
{
	Vector3 Position;
	UploadBuffer<Vector3> CBuffer;

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const Vector3& position)
		: Position(position)
	, CBuffer(DEVICE.Get(), 1, true) {}

	operator Vector3& () { return Position; }
	operator const Vector3& () const { return Position; }
};