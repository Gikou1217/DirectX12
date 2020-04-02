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

// ウィンドウプロージャー
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ウィンドウが破壊時呼ばれる
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
	// ウィンドウクラスの生成
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);				// サイズ分先に確保
	w.lpfnWndProc = (WNDPROC)WindowProcedure;	// ウィンドウプロシージャーのコールバック
	w.lpszClassName = _T("DirectX12");			// アプリケーションの名前		 
	w.hInstance = GetModuleHandle(nullptr);		// ハンドルの取得



	DebugOutputFormatString("Hello World");
	getchar();
	return 0;
}