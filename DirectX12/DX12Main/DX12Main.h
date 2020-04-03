#pragma once
#include <d3d12.h>
#include<wrl.h>
#include<memory>

#pragma comment(lib, "d3d12.lib")

class CommandList;
class CommandQueue;
class SwapChain;
class Descriptor;

using namespace Microsoft::WRL;

class DX12Main
{
public:

	static DX12Main& GetInstance()
	{
		static DX12Main ins;
		return ins;
	}
	~DX12Main();

	HRESULT Intialize(HWND& hwnd);
	HRESULT Run();
	HRESULT Termianl();

	void SetWindowSize(RECT& size);

private:
	HRESULT CreateDevice();

private:
	ComPtr<ID3D12Device> device;
	std::shared_ptr<CommandList> cmdList;
	std::shared_ptr<CommandQueue> cmdQueue;
	std::shared_ptr<SwapChain> swapChain;
	std::shared_ptr<Descriptor> descriptor;

	RECT windowSize;

private:
	DX12Main();
	DX12Main(const DX12Main&);
	DX12Main& operator=(const DX12Main&);
};

