#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

class Descriptor
{
public:
	Descriptor(ID3D12Device* device);
	~Descriptor();

	bool Initialize();
	bool Destroy();

	D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandle(unsigned int bbIdx);
	
	bool CreateRTV(IDXGISwapChain3* swapchain);
	

private:
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
};

