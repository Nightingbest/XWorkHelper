#include <stdio.h>
#include <Windows.h>
#define GET_win_() win = GetAsyncKeyState(VK_LWIN) & 0x8000
#define GET_cap_() cap = GetAsyncKeyState(VK_CAPITAL) & 0x0001
#define GET_esc_() esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000
#define GET_back_() back = GetAsyncKeyState(VK_BACK) & 0x8000
#define GET_oem_2_() oem_2 = GetAsyncKeyState(VK_OEM_2) & 0x8000
#define GET_period_() period = GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000
// #define GET_ctrl_() ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000//左\右切屏的备选按键
// #define GET_alt_() alt = GetAsyncKeyState(VK_MENU) & 0x8000//左\右切屏的备选按键

void window() // 获取生成的命令行窗口句柄并隐藏窗口
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    return;
}

int keyboard() // 检测按键,返回int值(1来回切屏;2暂停;3退出;4锁屏)
{
    // 循环获取按键状态,由宏命令替换完成
    SHORT GET_win_();
    SHORT GET_cap_();
    SHORT GET_esc_();
    SHORT GET_back_();
    SHORT GET_oem_2_();
    SHORT GET_period_();
    // 此处添加新按键

    if (win && cap) // 切屏判定,放弃触发后悔功能,可启用备选方案
    {
        // 普通按键一直按压会一直保持按压状态，但是大写锁定一直按压会一直处于切换状态，也就是会一直切换触发和不触发的状态,并不是这套判断逻辑的错误
        // Sleep(500);
        // GET_win_();
        // GET_cap_();
        // if (!(win && cap))
        //     return 1;
        // do
        // {
        //     GET_win_();
        //     GET_cap_();

        //     Sleep(10);

        // } while (win && cap);
        // return 0;
        return 1; // 最简单/无脑的切换
    }

    if (win && esc) // 暂停进入判定
    {
        Sleep(500);        // 容错时间
        GET_win_();        // 更新检测按键状态
        GET_esc_();        // 更新检测按键状态
        if (!(win && esc)) // 如果检测到存在按键在容错时间内被释放
        {
            return 2; // 执行操作
        }
        do // 按键容错时间后依旧被按压,进入循环,避免重新开始错误的按键判定,把一直按压的按键困在单次执行中
        {
            GET_win_();       // 更新检测按键状态
            GET_esc_();       // 更新检测按键状态
            Sleep(50);        // 避免过量消耗cpu
        } while (win && esc); // 检测是否有按键被释放
        return 0;             // 按键被释放,完成一次容错,开始下一次检测
    }

    if (win && back) // 退出判定
    {
        Sleep(500);
        GET_win_();
        GET_back_();
        if (!(win && back))
        {
            return 3;
        }
        do
        {
            GET_win_();
            GET_back_();
            Sleep(50);
        } while (win && back);
        return 0;
    }

    if (oem_2 && period) // 锁屏判定
    {
        Sleep(200);
        GET_oem_2_();
        GET_period_();
        if (!(oem_2 && period))
        {
            return 4;
        }
        do
        {
            GET_oem_2_();
            GET_period_();
            Sleep(50);
        } while (oem_2 && period);
        return 0;
    }
    /*
    此处添加新判断
    */
    Sleep(5);

    return 0;
}

void qie_huan_left() // 实现左切换
{
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_LEFT, 0, 0, 0);
    Sleep(5);
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    return;
}

void qie_huan_right() // 实现右切换
{
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_RIGHT, 0, 0, 0);
    Sleep(5);
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    return;
}

void qie_huan() // 实现切屏功能,目前仅支持2桌面
{
    static int i;
    if (i)
    {
        qie_huan_left();
        i = 0;
        Sleep(700); // 防鬼畜
        return;
    }
    qie_huan_right();
    i = 1;
    Sleep(700); // 防鬼畜
    return;
}

void quit() // 实现程序退出
{
    MessageBox(NULL, "摸鱼小助手下班啦！\n下次再一起摸鱼吧", "下班咯(￣▽￣)/", MB_OK);
    exit(0); // exit函数会直接停止整个程序的运行
    return;
}

void stop() // 实现暂停,暂停期间可退出
{
    MessageBox(NULL, "摸鱼小助手去打盹了！\n再次按下win+Esc叫醒它,或者win+Back退出小助手", "暂停提示>_<", MB_OK);
    SHORT i = 0;
    while (1)
    {
        i = keyboard();
        if (i == 2)
        {
            MessageBox(NULL, "小助手随叫随到呦！\n\n感蟹伟大的技术支持大人！", "小助手上线提示^_^", MB_OK);
            return;
        }
        else if (i == 3)
        {
            quit();
        }
        Sleep(5);
    }
}

void lock() // 实现锁定屏幕
{
    system("rundll32.exe user32.dll,LockWorkStation");
}

void function(int choice) // 接受功能代号,实现对应功能:已上线:0容错;1来回切屏;2暂停;3退出;4锁屏;未上线:5左切屏;6右切屏
{
    while (1)
    {
        switch (choice)
        {
        case 0:
            break;
        case 1:
            qie_huan(); // 执行没有容错的切换
            break;
        case 2:
            stop(); // 执行暂停
            break;
        case 3:
            quit(); // 执行退出
            break;
        case 4:
            lock(); // 执行锁定
            break;
        default: // 意料之外的异常,弹出提醒
            MessageBox(NULL, "参数错误,请立即反馈异常至邮箱3415592332@qq.com", "！:(", MB_OK);
        }
        return;
    }
}

int main()
{
    window();             // 隐藏命令窗口
    function(keyboard()); // 检测键盘按键,调用功能函数
    return 0;
}