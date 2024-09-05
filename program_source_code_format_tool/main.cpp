#include <iostream>
#include <memory>
#include <conio.h>  // 包含getch函数
#include <windows.h>
#include <commdlg.h> 

#include "ui_files/mainWindow.h"
#include "data_structure/lexerInfo.h"
#include "data_structure/parserInfo.h"

using namespace std;
int main()
{	
	initOperators();
	initKeywords();

	MainWindow* window = new MainWindow("Test Window",1000,880);
	
    while (true)
    {
        MOUSEMSG msg = GetMouseMsg(); 
        window->runEvent(msg);
    }
    
	_getch();  // 等待用户按下任意键
    return 0;
}
