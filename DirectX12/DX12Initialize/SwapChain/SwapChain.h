#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Initialize(RECT& rect, ID3D12CommandQueue* cmdQueue, HWND& hwnd);
	bool Destroy();

	IDXGISwapChain3* GetSwapChain();
	unsigned int GetBufferIndex();
	void Swap();

private:
	ComPtr<IDXGISwapChain3> swapchain;
	ComPtr<IDXGIFactory4> dxgifactory;
};

