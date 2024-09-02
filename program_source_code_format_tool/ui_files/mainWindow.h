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

//����window�ײ�ĶԻ�����ѡ��һ��c++�ļ���Ŀǰ��Ҫ������.h��.cpp��.c���������ļ� 
std::string OpenFileDialog(void*); 

/*
����ui�������Ҫ�ǰ�ť�����ýṹ�壬����:
Rect rect: �����λ����Ϣ������x,y,width,height��x,y��ʾ���Ͻ�����ֵ
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
        HWND hwnd = GetHWnd();  // ��ȡ���ھ��
        SetWindowText(hwnd, title.c_str());
        createSelectFileButton();
        createMsgText("�����ťѡ���ļ�");
//        floodfill(0, 0, WHITE);
    }

	//���ʱ�䴦���� 
	void runEvent(const MOUSEMSG& msg)
	{
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
        	MyList<UiComponentConfig>::Node* node = components.beginNode();  // ��ͷ���ڵ㿪ʼ
		    while (node != NULL) {
		    	cout<<"button msg: "<<node->data.rect.left;
				if (isPointInRect(msg.x,msg.y,node->data.rect))
            	{
            		cout<<"click button";
            		(this->*node->data.handle)(NULL);
            		return;
            	}
		        node = node->next;  // �ƶ�����һ���ڵ�
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
		std::string text = "��ǰѡ����ļ�Ϊ��"; 
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
		std::string text = "��ȡ�ļ�"; 
	    int x = (width - buttonWidth) / 2;
    	int y = (height - buttonHeight) / 2;
		// ���ư�ť�ı���
	    setfillcolor(LIGHTGRAY);
	    fillrectangle(x, y, x + buttonWidth, y + buttonHeight);
	
	    // ���ư�ť�ı߿�
	    setlinecolor(WHITE);
	    rectangle(x, y, x + buttonWidth, y + buttonHeight);
	
	    // ����ı�
	    
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
        closegraph();  // �رմ���
    }

//    void move()
//    {
//        int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // ��ȡ��Ļ���
//        int screenHeight = GetSystemMetrics(SM_CYSCREEN);  // ��ȡ��Ļ�߶�
//        int x = (screenWidth - width) / 2;  // ���㴰�ڵ�X���꣬ʹ���ھ���
//        int y = (screenHeight - height) / 2;  // ���㴰�ڵ�Y���꣬ʹ���ھ���
//        SetWindowPos(*hwnd, NULL, x, y, width, height, SWP_NOMOVE | SWP_NOZORDER);  // ���ô���λ�úʹ�С
//    }

private:
    std::string title;
    int width;
    int height;
    MyList<UiComponentConfig> components;
};
