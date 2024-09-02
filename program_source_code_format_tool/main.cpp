#include <iostream>
#include "easyx.h"
#include "graphics.h" 

using namespace std;

int main()
{
 initgraph(640, 480);  // ��ʼ��ͼ�δ��ڣ���СΪ640x480

    // ���ð�ť��λ�úʹ�С
    int x = 100, y = 100, width = 200, height = 50;

    // ���ư�ť�ı���
    setfillcolor(WHITE);
    fillrectangle(x, y, x + width, y + height);

    // ���ư�ť�ı߿�
    setlinecolor(BLACK);
    rectangle(x, y, x + width, y + height);

    // ���ư�ť���ı�
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Arial"));
    outtextxy(x + 10, y + 10, _T("Click me"));

    // ����ӳ�
    Sleep(1000);

    // �ȴ��û������ť
    MOUSEMSG msg;
    while (true)
    {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            // ��������λ���Ƿ��ڰ�ť��
            if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)
            {
                // ��ť��������˳�ѭ��
                break;
            }
        }
    }

    closegraph();  // �ر�ͼ�δ���

    return 0;
}
