#pragma once

#include <iostream>
#include "graphics.h" 

#include <graphics.h>
#include <easyx.h>
#include <windows.h>
#include "../data_structure/MyList.h"

using namespace std;

class MainWindow;
class OperationButtionWindow;
typedef void (MainWindow::*EventHandle)(void *);

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
	
   // 重载 == 运算符
    bool operator==(const UiComponentConfig& other) const
    {
        return (rect.left == other.rect.left && rect.bottom == other.rect.bottom && rect.right == other.rect.right && rect.top == other.rect.top); 
    }
	// 重载 != 运算符
    bool operator!=(const UiComponentConfig& other) const
    {
        return (rect.left != other.rect.left || rect.bottom != other.rect.bottom || rect.right != other.rect.right || rect.top != other.rect.top); 
    }
}; 

class MainWindow
{
public:
	MainWindow(const std::string& title, int width, int height);
	~MainWindow();
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
	 
	void doBack(void*)
	{
		cout<<" Need back"<<endl;
	}
	
	int getWidth() const
	{
		return width;
	}
	
	int getHeight() const
	{
		return height;
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
	
	void selectFile(void*);
	
	bool isPointInRect(int x, int y, RECT rect)
	{
	    return x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom;
	}
	
	//添加子类中的按钮配置，所有按钮处理函数目前都是在这个类中实现的 
	void addSubclassButton(UiComponentConfig& config)
	{
		components.insert(config);
	}
	
	void hideSelectFileButton()
	{
		components.remove(selectFileButton);
		setfillcolor(BLACK);
	    fillrectangle(selectFileButton.rect.left, selectFileButton.rect.top, selectFileButton.rect.right, selectFileButton.rect.bottom);
	    // 设置边框颜色
    	setlinecolor(BLACK);
    	rectangle(selectFileButton.rect.left, selectFileButton.rect.top, selectFileButton.rect.right, selectFileButton.rect.bottom);
	    cout<<"隐藏主界面上的选择文件按钮"<<endl;
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
	    selectFileButton.rect = r;
	    selectFileButton.handle = &MainWindow::selectFile;
	    components.insert(selectFileButton);
	}


private:
    std::string title;
    int width;
    int height;
    MyList<UiComponentConfig> components;
    UiComponentConfig selectFileButton;
    OperationButtionWindow* operationButtons;
};
