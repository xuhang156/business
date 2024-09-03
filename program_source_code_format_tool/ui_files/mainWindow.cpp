
#include <fstream>

#include "mainWindow.h"
#include "operationButtonWindow.h"
#include "../data_structure/lexerInfo.h"

MainWindow::MainWindow(const std::string& title, int width, int height): title(title), width(width), height(height)
{
    initgraph(width, height);
    msgAreaTop = height - 70; 
    HWND hwnd = GetHWnd();  // 获取窗口句柄
    SetWindowText(hwnd, title.c_str());
    createSelectFileButton();
    createMsgText("点击按钮选择文件");
    
    operationButtons = new OperationButtionWindow(this);
    
//        floodfill(0, 0, WHITE);
}

MainWindow::~MainWindow()
{
    closegraph();  // 关闭窗口
    delete operationButtons;
}

void MainWindow::selectFile(void*)
{
	static bool hadCreateButton = false;
	std::string text = "当前选择的文件为："; 
	std::string filePath = OpenFileDialog(NULL);
	createMsgText(text + filePath);	
	
	if(filePath != "")
	{
		if(!hadCreateButton) 
		{
			operationButtons->create();
			hadCreateButton = true;
			hideSelectFileButton();
		}
		showCode(filePath);
		return;
	}
	createMsgText("未选择文件，请重新选择文件。");
	
}

//清除代码主要显示区域 
void MainWindow::clearMainPlotArea()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, operationButtons->borderLeft(), msgAreaTop);
}

void MainWindow::lexer(void *)
{
	cout<<"词法分析程序"; 
	if(fileStringData == "")
		return;
	cout<<"kaishi词法分析程序";
	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	tokens.display();
	
	MyList<Token>::Node* node = tokens.beginNode();  // 从头部节点开始
	int i = 0;
	clearMainPlotArea();
	while (node != NULL) {
		int lineHeight = 15;
		cout<<"获取此分析："<<node->data.description();
		outtextxy(10, i * lineHeight, node->data.description().c_str());
		i++;
		node = node->next;  // 移动到下一个节点
	}
	cout<<"分析结束:"<<i <<endl; 
}

void MainWindow::showCode(const std::string& filePath)
{
	fileStringData = "";
	// 读取文件内容
	MyList<std::string> fileDatas = readFile(filePath);
	fileDatas.display();
	
	int i = 0;
	MyList<std::string>::Node* node = fileDatas.beginNode();  // 从头部节点开始
	clearMainPlotArea();
	while (node != NULL) {
		int lineHeight = 15;
		outtextxy(10, i * lineHeight, node->data.c_str());
		i++;
		fileStringData += node->data;
		fileStringData += '\n';
		node = node->next;  // 移动到下一个节点
	}
}

//MainWindow::~MainWindow()
//{
//	
//}

MyList<std::string> readFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    MyList<std::string> lines;
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            lines.insert(line);
        }
        file.close();
    } else {
        MessageBox(NULL, "Unable to open file!", "Error", MB_OK);
    }

    return lines;
}

std::string OpenFileDialog(void*) {
    // 创建一个结构体来保存文件选择对话框的信息
    OPENFILENAME ofn;       		// 文件选择对话框结构体
    char szFile[260] = { 0 };  		// 保存选择的文件名
    ZeroMemory(&ofn, sizeof(ofn)); 	// 将结构体置零

    // 设置结构体的参数
    ofn.lStructSize = sizeof(ofn); 	// 结构体大小
    ofn.hwndOwner = NULL;       	// 所属窗口的句柄，NULL表示无父窗口
    ofn.lpstrFile = szFile;        	// 存储选中的文件名的缓冲区
    ofn.nMaxFile = sizeof(szFile); 	// 缓冲区大小
    ofn.lpstrFilter = "C++ Files\0*.cpp;*.c;*.h;\0All Files\0*.*\0"; // 文件类型过滤
    ofn.nFilterIndex = 1;         	// 默认过滤类型索引
    ofn.lpstrFileTitle = NULL;  	// 如果不需要文件名和路径分开，可以为空
    ofn.nMaxFileTitle = 0;         	// 如果不需要文件名和路径分开，可以为0
    ofn.lpstrInitialDir = NULL; 	// 初始目录（若为nullptr则为当前目录）
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 确保路径和文件都必须存在

    // 显示文件选择对话框
    if (GetOpenFileName(&ofn)) {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    } else {
    	return "";
        std::cout << "No file selected or operation canceled." << std::endl;
    }
}
