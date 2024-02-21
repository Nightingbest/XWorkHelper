#include <stdio.h>
#include <Windows.h>

// ��������������ͼ���ID
#define TRAY_ICON_ID 1

// ����NOTIFYICONDATA�ṹ�����
NOTIFYICONDATA nid;

// ������Ϣ������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        // ��ʼ������ͼ��
        nid.cbSize = sizeof(NOTIFYICONDATA);           // ���ýṹ���С
        nid.hWnd = hwnd;                               // ���ô��ھ��
        nid.uID = TRAY_ICON_ID;                        // ��������ͼ��ID
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; // ��������ͼ������
        nid.uCallbackMessage = WM_USER + 1;            // ���ûص���Ϣ
        nid.hIcon = LoadIcon(GetModuleHandle(NULL), "meme.ico"); // ����ͼ��
        lstrcpy(nid.szTip, "����С����");              // ��������ͼ����ʾ�ı�
        Shell_NotifyIcon(NIM_ADD, &nid);               // �������ͼ�굽������
        break;

    case WM_DESTROY:
        // �Ƴ�����ͼ��
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0); // �˳���Ϣѭ��
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam); // Ĭ����Ϣ����
    }

    return 0;
}

int main()
{
    // ����������
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;              // ���ô�����Ϣ������
    wc.hInstance = GetModuleHandle(NULL);     // ��ȡ��ǰʵ�����
    wc.lpszClassName = "TrayIconWindowClass"; // ���ô�������
    RegisterClass(&wc);                       // ע�ᴰ����

    // ��������
    HWND hwnd = CreateWindow(wc.lpszClassName, "Tray Icon Example", 0, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // ������Ϣ
        DispatchMessage(&msg);  // �ַ���Ϣ
    }

    return 0;
}
