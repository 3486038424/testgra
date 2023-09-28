#include "tg_Frame.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//ͨ���ж���Ϣ������Ϣ��Ӧ
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ�����ǳ���û���˳�
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//����WM_QUIT��Ϣ��������Ϣѭ��
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//�Բ�����Ȥ����Ϣ����ȱʡ���������иô��룬�������������
	}
	return 0;
}
tg_Frame::tg_Frame(LPCWSTR name, int width, int height, LPCWSTR class_name, decltype(unload) WinSunProc)
{
		wndcls = { 0 };
		wndcls.lpfnWndProc = DefWindowProc;
		wndcls.hInstance = GetModuleHandle(NULL);
		wndcls.lpszClassName = class_name;
		RegisterClass(&wndcls);
		hwnd = CreateWindowEx(0, wndcls.lpszClassName, name, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height,
			NULL, NULL, wndcls.hInstance, NULL);
		ShowWindow(hwnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
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