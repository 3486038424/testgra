#include "tgra_win.h"
LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
tgra_win::tgra_win(LPSTR name, int width, int height, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	wndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
	wndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//���ù��
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);//���ô������Ͻǵ�ͼ��
	wndcls.hInstance = hInstance;//���ô���������Ӧ�ó���ʵ��
	wndcls.lpfnWndProc = WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	wndcls.lpszClassName = L"test";//���ô��������
	wndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&wndcls);//�����ϵͳע�ᴰ��


	//����һ�����壬�����ظô���ľ������һ����������ΪҪ�����Ĵ�����������ڶ�������Ϊ���������
	hwnd = CreateWindow(L"test", L"�ҵĵ�һ������",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
	UpdateWindow(hwnd);//���´���
	screenDC = GetDC(hwnd);  // ��ȡ��ĻDC

// ��������Ļ���ݵ��ڴ�DC��λͼ
	memDC = CreateCompatibleDC(screenDC);
	GetClientRect(hwnd, &rc);                       // ��ȡ�ͻ�������

	w = width;                 // ���
	h = height;                // �߶�

	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // ʹ��32λ���ظ�ʽ
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, 0, height, NULL, &info, DIB_RGB_COLORS);
	ptr = malloc(width * height * 4);  // 4�ֽ�per����
}



int tgra_win::loop()
{

	// ����λͼ��������ɫ
	MSG msg;
	//��Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))//�����Ϣ����WM_QUIT,���ط���ֵ�������Ϣ��WM_QUIT��������
	{
		TranslateMessage(&msg);//������Ϣ�����WM_KEYDOWN��WM_KEYUP�����һ��WM_CHAR��Ϣ
		DispatchMessage(&msg);//�ɷ���Ϣ	
		int y = 0;
		for (; y < h; y++) {
			int offset = y * w;
			for (int x = 0; x < w; x++) {
				((int*)ptr)[offset + x] = RGB(125, 0, 0);
			}
		}
		for (; y < h; y++) {
			int offset = y * w;
			for (int x = 0; x < w; x++) {
				((int*)ptr)[offset + x] = RGB(0, 125, 0);
			}
		}

		// ��λͼ��������Ļ����ʾ
		SetDIBits(memDC, bitmap, 0, h, ptr, &info, DIB_RGB_COLORS);
		BitBlt(screenDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
	}

	DeleteDC(memDC);
	DeleteObject(bitmap);
	ReleaseDC(NULL, screenDC);
	return 0;
}