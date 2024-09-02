#include <iostream>
#include "easyx.h"
#include "graphics.h" 

using namespace std;

int main()
{
 initgraph(640, 480);  // 初始化图形窗口，大小为640x480

    // 设置按钮的位置和大小
    int x = 100, y = 100, width = 200, height = 50;

    // 绘制按钮的背景
    setfillcolor(WHITE);
    fillrectangle(x, y, x + width, y + height);

    // 绘制按钮的边框
    setlinecolor(BLACK);
    rectangle(x, y, x + width, y + height);

    // 绘制按钮的文本
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Arial"));
    outtextxy(x + 10, y + 10, _T("Click me"));

    // 添加延迟
    Sleep(1000);

    // 等待用户点击按钮
    MOUSEMSG msg;
    while (true)
    {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            // 检查鼠标点击位置是否在按钮内
            if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)
            {
                // 按钮被点击，退出循环
                break;
            }
        }
    }

    closegraph();  // 关闭图形窗口

    return 0;
}
