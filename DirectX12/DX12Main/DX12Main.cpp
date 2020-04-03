#include "DX12Main.h"
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include "../DX12Initialize/Command/CommandList.h"
#include "../DX12Initialize/Command/CommandQueue.h"
#include "../DX12Initialize/SwapChain/SwapChain.h"
#include "../DX12Initialize/Descriptor/Descriptor.h"


DX12Main::DX12Main()
{
}


DX12Main::~DX12Main()
{
}

HRESULT DX12Main::Intialize(HWND& hwnd)
{
	if (CreateDevice() != S_OK) return E_FAIL;

	cmdList = std::make_shared<CommandList>(device.Get());
	cmdQueue = std::make_shared<CommandQueue>(device.Get());
	swapChain = std::make_shared<SwapChain>();
	descriptor = std::make_shared<Descriptor>(device.Get());

	if (!cmdList->Initialize()) return E_FAIL;
	if (!cmdQueue->Initialize()) return E_FAIL;
	if (!swapChain->Initialize(windowSize, cmdQueue->GetCommandQueue(), hwnd)) return E_FAIL;
	if (!descriptor->Initialize()) return E_FAIL;

	if (descriptor->CreateRTV(swapChain->GetSwapChain())) return E_FAIL;

	return S_OK;
}

HRESULT DX12Main::Run()
{
	HRESULT result = S_FALSE;

	if (cmdList->Reset() != S_OK) return E_FAIL;

	unsigned int bbindex = swapChain->GetBufferIndex();
	cmdList->SetRenderTarget(1, descriptor->GetDescriptorHandle(bbindex));

	cmdList->Update();

	cmdQueue->Execute(cmdList->GetCommandList());

	cmdList->Reset();

	swapChain->Swap();

	return S_OK;
}

HRESULT DX12Main::Termianl()
{
	HRESULT result = S_FALSE;

	return result;
}

void DX12Main::SetWindowSize(RECT& size)
{
	windowSize = size;
}

HRESULT DX12Main::CreateDevice()
{
	HRESULT result = S_FALSE;

	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL featureLevel;

	for (auto lv : levels) {
		if (D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&device)) == S_OK) {
			featureLevel = lv;
			result = S_OK;
			break;
		}
	}

	return result;
}
