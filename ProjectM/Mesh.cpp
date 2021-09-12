#include "pch.h"
#include "Mesh.h"

#include "Engine.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<UINT>& indices)
{
	CreateVertexBuffer(vertices);
	CreateIndexBuffer(indices);
}

void Mesh::CreateVertexBuffer(const std::vector<Vertex>& vertices)
{
	m_VertexCount = static_cast<UINT>(vertices.size());
	UINT bufferSize = m_VertexCount * sizeof(Vertex);

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_VertexUploadBuffer));

	void* mappedData;
	m_VertexUploadBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, vertices.data(), bufferSize);
	m_VertexUploadBuffer->Unmap(0, nullptr);

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_VertexBuffer));

	CMD_LIST->CopyResource(m_VertexBuffer.Get(), m_VertexUploadBuffer.Get());
	CMD_LIST->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_VertexBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

	m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
	m_VertexBufferView.SizeInBytes = bufferSize;
	m_VertexBufferView.StrideInBytes = sizeof(Vertex);

	RELEASE_UPLOAD_BUFFER(m_VertexUploadBuffer);
}

void Mesh::CreateIndexBuffer(const std::vector<UINT>& indices)
{
	m_IndexCount = static_cast<UINT>(indices.size());
	UINT bufferSize = sizeof(UINT) * m_IndexCount;

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&m_IndexUploadBuffer));

	void* mappedData;
	m_IndexUploadBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, indices.data(), bufferSize);
	m_IndexUploadBuffer->Unmap(0, nullptr);

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_IndexBuffer));

	CMD_LIST->CopyResource(m_IndexBuffer.Get(), m_IndexUploadBuffer.Get());
	CMD_LIST->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_IndexBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

	m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
	m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_IndexBufferView.SizeInBytes = bufferSize;

	RELEASE_UPLOAD_BUFFER(m_IndexUploadBuffer);
}
