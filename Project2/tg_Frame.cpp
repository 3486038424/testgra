#include "tg_Frame.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//通过判断消息进行消息响应
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}
tg_Frame::tg_Frame(LPCWSTR name, int width, int height, LPCWSTR class_name, decltype(unload) WinSunProc)
{
		wndcls = { 0 };
		wndcls.lpfnWndProc = WinSunProc;
		wndcls.hInstance = GetModuleHandle(NULL);
		wndcls.lpszClassName = class_name;
		RegisterClass(&wndcls);
		hwnd = CreateWindowEx(0, wndcls.lpszClassName, name, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, ((int)0x80000000), width, height,
			NULL, NULL, wndcls.hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);//把窗体显示出来
	UpdateWindow(hwnd);//更新窗体
	screen.init(hwnd);
}

int tg_Frame::before_work()
{
	screen.clear();
	return 0;
}

int tg_Frame::after_work()
{
	screen.draw();
	return 0;
}