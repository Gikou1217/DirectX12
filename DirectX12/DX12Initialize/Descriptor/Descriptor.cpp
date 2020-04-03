#include "Descriptor.h"
#include <vector>

Descriptor::Descriptor(ID3D12Device* device):
	dev(device)
{
}


Descriptor::~Descriptor()
{
}

bool Descriptor::Initialize()
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	if(dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps))!=S_OK) return false;
	
	return true;
}

bool Descriptor::Destroy()
{
	return false;
}

D3D12_CPU_DESCRIPTOR_HANDLE Descriptor::GetDescriptorHandle(unsigned int bbIdx)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeap = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
	rtvHeap.ptr += bbIdx*dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);


	return rtvHeap;
}

bool Descriptor::CreateRTV(IDXGISwapChain3* swapchain)
{
	DXGI_SWAP_CHAIN_DESC swcdesc = {};
	if(swapchain->GetDesc(&swcdesc)!=S_OK) return false;


	std::vector<ID3D12Resource*> backBuffers(swcdesc.BufferCount);
	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
	for (unsigned int idx = 0; idx < swcdesc.BufferCount; ++idx)
	{
		if(swapchain->GetBuffer(idx, IID_PPV_ARGS(&backBuffers[idx]))!=S_OK)return false;
		
		dev->CreateRenderTargetView(backBuffers[idx], nullptr, handle);

		handle.ptr += dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	}

	return true;
}
