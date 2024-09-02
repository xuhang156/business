#include "mainWindow.h"


//MainWindow::MainWindow(const std::string& titles):IWindow(titles)
//{
//	
//}
//
//MainWindow::~MainWindow()
//{
//	
//}

void OpenFileDialog(void*) {
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
    } else {
        std::cout << "No file selected or operation canceled." << std::endl;
    }
}
