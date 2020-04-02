#include<Windows.h>

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


const int window_width = 1024;
const int window_height = 768;


using namespace std;

void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list list;
	va_start(list, format);
	printf(format, list);
	va_end(list);
#endif // _DEBUG
}

// �E�B���h�E�v���[�W���[
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// �E�B���h�E���j�󎞌Ă΂��
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	// �E�B���h�E�N���X�̐���
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);				// �T�C�Y����Ɋm��
	w.lpfnWndProc = (WNDPROC)WindowProcedure;	// �E�B���h�E�v���V�[�W���[�̃R�[���o�b�N
	w.lpszClassName = TEXT("DirectX12");			// �A�v���P�[�V�����̖��O		 
	w.hInstance = GetModuleHandle(nullptr);		// �n���h���̎擾

	RegisterClassEx(&w); // �E�B���h�E�N���X��OS�ɓ`����

	RECT wrc = { 0, 0, window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false); // �E�B���h�E�T�C�Y�̕␳

	// �E�B���h�E�I�u�W�F�N�g�̐���
	HWND hwnd = CreateWindow(w.lpszClassName,
		TEXT("DirectX12"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

	ShowWindow(hwnd, SW_SHOW);


	MSG msg = {};
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
	}

	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}