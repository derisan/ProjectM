#include "pch.h"
#include "Mesh.h"

#include "Engine.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<UINT>& indices)
{
	m_VertexCount = static_cast<UINT>(vertices.size());
	UINT bufferSize = m_VertexCount * sizeof(Vertex);

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_VertexBuffer));

	void* mappedData;
	m_VertexBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, vertices.data(), bufferSize);
	m_VertexBuffer->Unmap(0, nullptr);

	m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
	m_VertexBufferView.SizeInBytes = bufferSize;
	m_VertexBufferView.StrideInBytes = sizeof(Vertex);

	m_IndexCount = static_cast<UINT>(indices.size());
	bufferSize = sizeof(UINT) * m_IndexCount;

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&m_IndexBuffer));

	m_IndexBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, indices.data(), bufferSize);
	m_IndexBuffer->Unmap(0, nullptr);

	m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
	m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_IndexBufferView.SizeInBytes = bufferSize;
}
