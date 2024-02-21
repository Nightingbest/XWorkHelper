#include <stdio.h>
#include <Windows.h>

// 定义任务栏托盘图标的ID
#define TRAY_ICON_ID 1

// 定义NOTIFYICONDATA结构体变量
NOTIFYICONDATA nid;

// 窗口消息处理函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        // 初始化托盘图标
        nid.cbSize = sizeof(NOTIFYICONDATA);           // 设置结构体大小
        nid.hWnd = hwnd;                               // 设置窗口句柄
        nid.uID = TRAY_ICON_ID;                        // 设置托盘图标ID
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; // 设置托盘图标属性
        nid.uCallbackMessage = WM_USER + 1;            // 设置回调消息
        nid.hIcon = LoadIcon(GetModuleHandle(NULL), "meme.ico"); // 加载图标
        lstrcpy(nid.szTip, "摸鱼小助手");              // 设置托盘图标提示文本
        Shell_NotifyIcon(NIM_ADD, &nid);               // 添加托盘图标到任务栏
        break;

    case WM_DESTROY:
        // 移除托盘图标
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0); // 退出消息循环
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam); // 默认消息处理
    }

    return 0;
}

int main()
{
    // 创建窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;              // 设置窗口消息处理函数
    wc.hInstance = GetModuleHandle(NULL);     // 获取当前实例句柄
    wc.lpszClassName = "TrayIconWindowClass"; // 设置窗口类名
    RegisterClass(&wc);                       // 注册窗口类

    // 创建窗口
    HWND hwnd = CreateWindow(wc.lpszClassName, "Tray Icon Example", 0, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // 翻译消息
        DispatchMessage(&msg);  // 分发消息
    }

    return 0;
}
