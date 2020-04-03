#pragma once
#include <wrl.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

using namespace Microsoft::WRL;

class CommandQueue
{
public:
	CommandQueue(ID3D12Device* device);
	~CommandQueue();

	bool Initialize();
	bool Destroy();

	ID3D12CommandQueue* GetCommandQueue();
	void Execute(ID3D12GraphicsCommandList* cmdlist);

private:
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12CommandQueue> cmdQueue;

};

