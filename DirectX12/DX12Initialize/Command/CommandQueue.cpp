#include "CommandQueue.h"


CommandQueue::CommandQueue(ID3D12Device* device):
	dev(device),
	cmdQueue(nullptr)
{
}


CommandQueue::~CommandQueue()
{
}

bool CommandQueue::Initialize()
{
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cmdQueueDesc.NodeMask = 0;

	if(dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue))!=S_OK) return false;

	return true;
}

bool CommandQueue::Destroy()
{
	return false;
}

ID3D12CommandQueue * CommandQueue::GetCommandQueue()
{
	return cmdQueue.Get();
}

void CommandQueue::Execute(ID3D12GraphicsCommandList * cmdlist)
{
	ID3D12CommandList* cmdlists[] = { cmdlist };
	cmdQueue->ExecuteCommandLists(1, cmdlists);
}
