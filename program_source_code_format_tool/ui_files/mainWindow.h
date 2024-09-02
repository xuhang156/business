#pragma once

#include <iostream>
#include "graphics.h" 

#include <graphics.h>
#include <easyx.h>
#include <windows.h>
#include "../data_structure/MyList.h"
using namespace std;

class IWindow;
typedef void (IWindow::*EventHandle)(void *);

//调用window底层的对话框来选择一个c++文件，目前主要过滤有.h、.cpp、.c三种类型文件 
std::string OpenFileDialog(void*); 

/*
定义ui组件（主要是按钮）配置结构体，包括:
Rect rect: 组件的位置信息，包括x,y,width,height，x,y表示左上角坐标值
*/
struct UiComponentConfig
{
	RECT rect;
	EventHandle handle;
}; 

class IWindow
{
public:
    IWindow(const std::string& title, int width, int height)
        : title(title), width(width), height(height)
    {
        initgraph(width, height);
        HWND hwnd = GetHWnd();  // 获取窗口句柄
        SetWindowText(hwnd, title.c_str());
        createSelectFileButton();
        createMsgText("点击按钮选择文件");
//        floodfill(0, 0, WHITE);
    }

	//鼠标时间处理函数 
	void runEvent(const MOUSEMSG& msg)
	{
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
        	MyList<UiComponentConfig>::Node* node = components.beginNode();  // 从头部节点开始
		    while (node != NULL) {
		    	cout<<"button msg: "<<node->data.rect.left;
				if (isPointInRect(msg.x,msg.y,node->data.rect))
            	{
            		cout<<"click button";
            		(this->*node->data.handle)(NULL);
            		return;
            	}
		        node = node->next;  // 移动到下一个节点
		    }
        }	
	}
	
	void createMsgText(const std::string& msg)
	{
		int y = height - 70;
		setfillcolor(LIGHTGRAY);
	    fillrectangle(0, height - 70, width, height);
	    
//	    setbkmode(TRANSPARENT);
	    setfillcolor(LIGHTGRAY);
	    RECT r = {0, height - 70, width, height};
	    drawtext(msg.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	void selectFile(void*)
	{
		std::string text = "当前选择的文件为："; 
		std::string filePath = OpenFileDialog(NULL);
		createMsgText(text + filePath);	
	}
	
	bool isPointInRect(int x, int y, RECT rect)
	{
	    return x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom;
	}
	
	void createSelectFileButton()
	{
		int buttonWidth = 150;
		int buttonHeight = 70;
		std::string text = "读取文件"; 
	    int x = (width - buttonWidth) / 2;
    	int y = (height - buttonHeight) / 2;
		// 绘制按钮的背景
	    setfillcolor(LIGHTGRAY);
	    fillrectangle(x, y, x + buttonWidth, y + buttonHeight);
	
	    // 绘制按钮的边框
	    setlinecolor(WHITE);
	    rectangle(x, y, x + buttonWidth, y + buttonHeight);
	
	    // 输出文本
	    
	    setfillcolor(LIGHTGRAY);
	    setbkmode(TRANSPARENT);
	    RECT r = { x, y, x + buttonWidth, y + buttonHeight };
	    drawtext(text.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = r;
	    buttonConfig.handle = &IWindow::selectFile;
	    components.insert(buttonConfig);
	}
	
    ~IWindow()
    {
        closegraph();  // 关闭窗口
    }

//    void move()
//    {
//        int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
//        int screenHeight = GetSystemMetrics(SM_CYSCREEN);  // 获取屏幕高度
//        int x = (screenWidth - width) / 2;  // 计算窗口的X坐标，使窗口居中
//        int y = (screenHeight - height) / 2;  // 计算窗口的Y坐标，使窗口居中
//        SetWindowPos(*hwnd, NULL, x, y, width, height, SWP_NOMOVE | SWP_NOZORDER);  // 设置窗口位置和大小
//    }

private:
    std::string title;
    int width;
    int height;
    MyList<UiComponentConfig> components;
};
