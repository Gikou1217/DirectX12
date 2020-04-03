#include "CommandList.h"


CommandList::CommandList(ID3D12Device* device):
	dev(device),
	cmdAllocator(nullptr),
	cmdList(nullptr)
{
}


CommandList::~CommandList()
{
}

bool CommandList::Initialize()
{
	// アロケーターの生成
	if(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator))!=S_OK) return false;
	// リストの生成
	if(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&cmdList)) != S_OK) return false;

	return true;
}

void CommandList::Update()
{
	float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

	cmdList->Close();

}

bool CommandList::Destroy()
{
	return false;
}

bool CommandList::Reset()
{
	cmdAllocator->Reset();
	if(cmdList->Reset(cmdAllocator.Get(), nullptr)!=S_OK) return false;
	
	return true;
}

ID3D12CommandAllocator * CommandList::GetCommandAllocator()
{
	return cmdAllocator.Get();
}

ID3D12GraphicsCommandList * CommandList::GetCommandList()
{
	return cmdList.Get();
}

void CommandList::SetRenderTarget(unsigned int targetNum, D3D12_CPU_DESCRIPTOR_HANDLE& startRTVHeap)
{
	cmdList->OMSetRenderTargets(targetNum, &startRTVHeap, true, nullptr);
	rtvH = startRTVHeap;
}
