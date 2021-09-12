#pragma once

#include "Core.h"

class Texture
{
public:
	Texture(const std::wstring& path);

	ComPtr<ID3D12DescriptorHeap> GetSrvHeap() { return m_SrvHeap; }

private:
	void CreateTexture(const std::wstring& path);
	void CreateView();

private:
	ScratchImage m_RawImage;
	ComPtr<ID3D12Resource> m_Texture;
	ComPtr<ID3D12Resource> m_TextureUploadBuffer;
	ComPtr<ID3D12DescriptorHeap> m_SrvHeap;
	D3D12_GPU_DESCRIPTOR_HANDLE m_SrvGpuHandle;
};