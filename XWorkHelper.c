#include <stdio.h>
#include <Windows.h>
#define GET_win_() win = GetAsyncKeyState(VK_LWIN) & 0x8000
#define GET_cap_() cap = GetAsyncKeyState(VK_CAPITAL) & 0x0001
#define GET_esc_() esc = GetAsyncKeyState(VK_ESCAPE) & 0x8000
#define GET_back_() back = GetAsyncKeyState(VK_BACK) & 0x8000
#define GET_oem_2_() oem_2 = GetAsyncKeyState(VK_OEM_2) & 0x8000
#define GET_period_() period = GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000
// #define GET_ctrl_() ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000//��\�������ı�ѡ����
// #define GET_alt_() alt = GetAsyncKeyState(VK_MENU) & 0x8000//��\�������ı�ѡ����

void window() // ��ȡ���ɵ������д��ھ�������ش���
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    return;
}

int keyboard() // ��ⰴ��,����intֵ(1��������;2��ͣ;3�˳�;4����)
{
    // ѭ����ȡ����״̬,�ɺ������滻���
    SHORT GET_win_();
    SHORT GET_cap_();
    SHORT GET_esc_();
    SHORT GET_back_();
    SHORT GET_oem_2_();
    SHORT GET_period_();
    // �˴�����°���

    if (win && cap) // �����ж�,����������ڹ���,�����ñ�ѡ����
    {
        // ��ͨ����һֱ��ѹ��һֱ���ְ�ѹ״̬�����Ǵ�д����һֱ��ѹ��һֱ�����л�״̬��Ҳ���ǻ�һֱ�л������Ͳ�������״̬,�����������ж��߼��Ĵ���
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
        return 1; // ���/���Ե��л�
    }

    if (win && esc) // ��ͣ�����ж�
    {
        Sleep(500);        // �ݴ�ʱ��
        GET_win_();        // ���¼�ⰴ��״̬
        GET_esc_();        // ���¼�ⰴ��״̬
        if (!(win && esc)) // �����⵽���ڰ������ݴ�ʱ���ڱ��ͷ�
        {
            return 2; // ִ�в���
        }
        do // �����ݴ�ʱ������ɱ���ѹ,����ѭ��,�������¿�ʼ����İ����ж�,��һֱ��ѹ�İ������ڵ���ִ����
        {
            GET_win_();       // ���¼�ⰴ��״̬
            GET_esc_();       // ���¼�ⰴ��״̬
            Sleep(50);        // �����������cpu
        } while (win && esc); // ����Ƿ��а������ͷ�
        return 0;             // �������ͷ�,���һ���ݴ�,��ʼ��һ�μ��
    }

    if (win && back) // �˳��ж�
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

    if (oem_2 && period) // �����ж�
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
    �˴�������ж�
    */
    Sleep(5);

    return 0;
}

void qie_huan_left() // ʵ�����л�
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

void qie_huan_right() // ʵ�����л�
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

void qie_huan() // ʵ����������,Ŀǰ��֧��2����
{
    static int i;
    if (i)
    {
        qie_huan_left();
        i = 0;
        Sleep(700); // ������
        return;
    }
    qie_huan_right();
    i = 1;
    Sleep(700); // ������
    return;
}

void quit() // ʵ�ֳ����˳�
{
    MessageBox(NULL, "����С�����°�����\n�´���һ�������", "�°࿩(������)/", MB_OK);
    exit(0); // exit������ֱ��ֹͣ�������������
    return;
}

void stop() // ʵ����ͣ,��ͣ�ڼ���˳�
{
    MessageBox(NULL, "����С����ȥ�����ˣ�\n�ٴΰ���win+Esc������,����win+Back�˳�С����", "��ͣ��ʾ>_<", MB_OK);
    SHORT i = 0;
    while (1)
    {
        i = keyboard();
        if (i == 2)
        {
            MessageBox(NULL, "С��������浽�ϣ�\n\n��зΰ��ļ���֧�ִ��ˣ�", "С����������ʾ^_^", MB_OK);
            return;
        }
        else if (i == 3)
        {
            quit();
        }
        Sleep(5);
    }
}

void lock() // ʵ��������Ļ
{
    system("rundll32.exe user32.dll,LockWorkStation");
}

void function(int choice) // ���ܹ��ܴ���,ʵ�ֶ�Ӧ����:������:0�ݴ�;1��������;2��ͣ;3�˳�;4����;δ����:5������;6������
{
    while (1)
    {
        switch (choice)
        {
        case 0:
            break;
        case 1:
            qie_huan(); // ִ��û���ݴ���л�
            break;
        case 2:
            stop(); // ִ����ͣ
            break;
        case 3:
            quit(); // ִ���˳�
            break;
        case 4:
            lock(); // ִ������
            break;
        default: // ����֮����쳣,��������
            MessageBox(NULL, "��������,�����������쳣������3415592332@qq.com", "��:(", MB_OK);
        }
        return;
    }
}

int main()
{
    window();             // ���������
    function(keyboard()); // �����̰���,���ù��ܺ���
    return 0;
}