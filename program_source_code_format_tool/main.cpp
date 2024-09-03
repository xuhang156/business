#include <iostream>
#include <conio.h>  // 包含getch函数
#include <windows.h>
#include <commdlg.h>  //
#include "easyx.h"
#include "graphics.h" 
#include "ui_files/mainWindow.h"

//int main()
//{
//    UiComponentConfig config;
//    config.handle = OpenFileDialog;
//
//    int data = 42;
//    config.handle(&data);  // 调用函数
//
//    return 0;
//}

//int main()
//{
//    MyList<int> myList;
//    myList.insert(10);
//    myList.insert(20);
//    myList.insert(30);
//
//    std::cout << "List after insertions: ";
//    myList.display();
//
//    myList.remove(20);
//    std::cout << "List after removal of 20: ";
//    myList.display();
//
//    return 0;
//}


//
using namespace std;
int main()
{
	MainWindow* window = new MainWindow("Test Window",1000,700);
	
    while (true)
    {
        MOUSEMSG msg = GetMouseMsg(); 
        window->runEvent(msg);
    }
    
	_getch();  // 等待用户按下任意键
    return 0;
}

//int main()
//{
// 	initgraph(640, 480);  // 初始化图形窗口，大小为640x480
//
//    // 设置按钮的位置和大小
//    int x = 100, y = 100, width = 200, height = 50;
//
//    // 绘制按钮的背景
//    setfillcolor(WHITE);
//    fillrectangle(x, y, x + width, y + height);
//
//    // 绘制按钮的边框
//    setlinecolor(BLACK);
//    rectangle(x, y, x + width, y + height);
//
//    // 绘制按钮的文本
//    settextcolor(BLACK);
//    settextstyle(20, 0, _T("Arial"));
//    outtextxy(x + 10, y + 10, _T("Click me"));
//
//    // 添加延迟
//    Sleep(1000);
//
//    // 等待用户点击按钮
//    MOUSEMSG msg;
//    while (true)
//    {
//        msg = GetMouseMsg();
//        if (msg.uMsg == WM_LBUTTONDOWN)
//        {
//            // 检查鼠标点击位置是否在按钮内
//            if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)
//            {
//                // 按钮被点击，退出循环
//                break;
//            }
//        }
//    }
//
//    closegraph();  // 关闭图形窗口
//
//    return 0;
//}
