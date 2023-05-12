#include<Windows.h>
#include <time.h>
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASS wndcls; //����һ��������
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
	HWND hwnd = CreateWindow(L"test", L"�ҵĵ�һ������",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
	UpdateWindow(hwnd);//���´���
	HDC screenDC = GetDC(hwnd);  // ��ȡ��ĻDC

// ��������Ļ���ݵ��ڴ�DC��λͼ
	HDC memDC = CreateCompatibleDC(screenDC);
	RECT rc;
	GetClientRect(hwnd, &rc);                       // ��ȡ�ͻ�������

	int width = rc.right - rc.left;                 // ���
	int height = rc.bottom - rc.top;                // �߶�

	HBITMAP bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	BITMAPINFO info;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // ʹ��32λ���ظ�ʽ
	info.bmiHeader.biCompression = BI_RGB;

	void* ptr;
	GetDIBits(memDC, bitmap, 0, height, NULL, &info, DIB_RGB_COLORS);
	ptr = malloc(width * height * 4);  // 4�ֽ�per����
	// ����λͼ��������ɫ
	MSG msg;
	//��Ϣѭ��
	int delta_t = 0;
	while (GetMessage(&msg, NULL, 0, 0))//�����Ϣ����WM_QUIT,���ط���ֵ�������Ϣ��WM_QUIT��������
	{
		int t = clock();
		TranslateMessage(&msg);//������Ϣ�����WM_KEYDOWN��WM_KEYUP�����һ��WM_CHAR��Ϣ
		DispatchMessage(&msg);//�ɷ���Ϣ	
		int y = 0;
		for (; y < height && y < delta_t; y++) {
			int offset = y * width;
			for (int x = 0; x < width; x++) {
				((int*)ptr)[offset + x] = RGB(125, 0, 0);
			}
		}
		for (; y < height ; y++) {
			int offset = y * width;
			for (int x = 0; x < width; x++) {
				((int*)ptr)[offset + x] = RGB(0, 125, 0);
			}
		}

		// ��λͼ��������Ļ����ʾ
		SetDIBits(memDC, bitmap, 0, height, ptr, &info, DIB_RGB_COLORS);
		BitBlt(screenDC, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
		delta_t = clock() - t;
	}

	DeleteDC(memDC);
	DeleteObject(bitmap);
	ReleaseDC(NULL, screenDC);
}



	