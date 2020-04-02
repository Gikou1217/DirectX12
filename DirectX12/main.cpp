#include<Windows.h>

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG

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
	w.lpszClassName = _T("DirectX12");			// �A�v���P�[�V�����̖��O		 
	w.hInstance = GetModuleHandle(nullptr);		// �n���h���̎擾



	DebugOutputFormatString("Hello World");
	getchar();
	return 0;
}