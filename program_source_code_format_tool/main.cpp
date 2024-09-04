#include <iostream>
#include <memory>
#include <vector>
#include <conio.h>  // 包含getch函数
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
//    // 将 std::vector 转换为 MyList
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
        values[i] = std::unique_ptr<int>(new int(i));  // 创建一个指向整数的 unique_ptr
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << *values[i] << " ";  // 打印每个 unique_ptr 指向的值
    }
		
				
	initOperators();
	initKeywords();

	MainWindow* window = new MainWindow("Test Window",1920,1080);
	
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
