#include <iostream>
#include <memory>
#include <vector>
#include <conio.h>  // ����getch����
#include <windows.h>
#include <commdlg.h>  //
#include "easyx.h"
#include "graphics.h" 
#include "ui_files/mainWindow.h"
#include "data_structure/lexerInfo.h"
#include "data_structure/parserInfo.h"

//int main()
//{
//    std::vector<Token> tokenVector = {
//        Token("add", IDENT), Token("(", LP), Token("x", IDENT), Token(",", COMMA), Token("y", IDENT), Token(")", RP), Token(";", SEMI),
//        Token("int", IDENT), Token("x", IDENT), Token("=", ASSIGN), Token("2", INT_CONST), Token(";", SEMI),
//        Token("", END_OF_FILE)
//    };
//
//    // �� std::vector ת��Ϊ MyList
//    MyList<Token> tokens;
//    for (const auto& token : tokenVector) {
//        tokens.insert(token);
//    }
//    
//    Parser parser(tokens);
//    try {
//        std::shared_ptr<ASTNode> ast = parser.parse();
//        std::cout << "Parsing completed successfully!" << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Parsing failed: " << e.what() << std::endl;
//    }
//    
//	_getch();
//    return 0;
//}
//
using namespace std;
int main()
{
    std::unique_ptr<int> values[10];
    for (int i = 0; i < 10; ++i) {
        values[i] = std::unique_ptr<int>(new int(i));  // ����һ��ָ�������� unique_ptr
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << *values[i] << " ";  // ��ӡÿ�� unique_ptr ָ���ֵ
    }
		
				
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
