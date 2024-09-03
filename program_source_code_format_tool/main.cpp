#include <iostream>
#include <conio.h>  // ����getch����
#include <windows.h>
#include <commdlg.h>  //
#include "easyx.h"
#include "graphics.h" 
#include "ui_files/mainWindow.h"
#include "data_structure/lexerInfo.h"

//int main()
//{
//	
//	initKeywords();
//	initOperators();
//	std::string test = "int main() { int a = 5; float b = 3.14; if (a == 5) return b; }";
//	Lexer er(test);
//	auto tokens = er.tokenize();
//	tokens.display();
//	
//	_getch();
//    return 0;
//}




using namespace std;
int main()
{
	initOperators();
	initKeywords();

	MainWindow* window = new MainWindow("Test Window",1920,1080);
	
    while (true)
    {
        MOUSEMSG msg = GetMouseMsg(); 
        window->runEvent(msg);
    }
    
	_getch();  // �ȴ��û����������
    return 0;
}

//int main()
//{
// 	initgraph(640, 480);  // ��ʼ��ͼ�δ��ڣ���СΪ640x480
//
//    // ���ð�ť��λ�úʹ�С
//    int x = 100, y = 100, width = 200, height = 50;
//
//    // ���ư�ť�ı���
//    setfillcolor(WHITE);
//    fillrectangle(x, y, x + width, y + height);
//
//    // ���ư�ť�ı߿�
//    setlinecolor(BLACK);
//    rectangle(x, y, x + width, y + height);
//
//    // ���ư�ť���ı�
//    settextcolor(BLACK);
//    settextstyle(20, 0, _T("Arial"));
//    outtextxy(x + 10, y + 10, _T("Click me"));
//
//    // ����ӳ�
//    Sleep(1000);
//
//    // �ȴ��û������ť
//    MOUSEMSG msg;
//    while (true)
//    {
//        msg = GetMouseMsg();
//        if (msg.uMsg == WM_LBUTTONDOWN)
//        {
//            // ��������λ���Ƿ��ڰ�ť��
//            if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)
//            {
//                // ��ť��������˳�ѭ��
//                break;
//            }
//        }
//    }
//
//    closegraph();  // �ر�ͼ�δ���
//
//    return 0;
//}
