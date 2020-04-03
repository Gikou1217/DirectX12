#pragma once
#include <wrl.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

using namespace Microsoft::WRL;

class CommandList
{
public:
	CommandList(ID3D12Device* device);
	~CommandList();

	bool Initialize();
	void Update();
	bool Destroy();

	bool Reset();
	ID3D12CommandAllocator* GetCommandAllocator();
	ID3D12GraphicsCommandList* GetCommandList();
	void SetRenderTarget(unsigned int targetNum, D3D12_CPU_DESCRIPTOR_HANDLE& startRTVHeap);

private:
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH;
};

