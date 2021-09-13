#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             
#endif

#include <windows.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include "d3dx12.h"
#include <DirectXTK12/SimpleMath.h>
#include <DirectXTex.h>
#include <DirectXTex.inl>

#include <string>
#include <wrl.h>
#include <shellapi.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <array>
#include <filesystem>
#include <unordered_map>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace DirectX::PackedVector;
using namespace DirectX::SimpleMath;


#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "debug\\libfbxsdk-md.lib")
#pragma comment(lib, "debug\\libxml2-md.lib")
#pragma comment(lib, "debug\\zlib-md.lib")
#else
#pragma comment(lib, "release\\libfbxsdk-md.lib")
#pragma comment(lib, "release\\libxml2-md.lib")
#pragma comment(lib, "release\\zlib-md.lib")
#endif

#include "fbxsdk.h"

#include "d3dHelper.h"
#include "Log.h"


std::wstring s2ws(const std::string& s);
std::string ws2s(const std::wstring& s);