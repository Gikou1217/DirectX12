#include "SwapChain.h"


SwapChain::SwapChain()
{
}


SwapChain::~SwapChain()
{
}

bool SwapChain::Initialize(RECT& rect, ID3D12CommandQueue* cmdQueue, HWND& hwnd)
{
	if (cmdQueue == nullptr) return false;

	if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgifactory)) != S_OK) return false;



	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = rect.left;
	swapchainDesc.Height = rect.bottom;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2;

	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if(dxgifactory->CreateSwapChainForHwnd(cmdQueue, hwnd, &swapchainDesc, nullptr, nullptr, (IDXGISwapChain1**)(swapchain.GetAddressOf()))!=S_OK) return false;
	
	return true;
}

bool SwapChain::Destroy()
{
	return false;
}

IDXGISwapChain3 * SwapChain::GetSwapChain()
{
	return swapchain.Get();
}

unsigned int SwapChain::GetBufferIndex()
{
	return swapchain->GetCurrentBackBufferIndex();
}

void SwapChain::Swap()
{
	swapchain->Present(1, 0);
}
