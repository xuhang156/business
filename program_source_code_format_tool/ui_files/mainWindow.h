#pragma once

#include <iostream>
#include "graphics.h" 

#include <graphics.h>
#include <easyx.h>
#include <windows.h>
#include "../data_structure/MyList.h"
using namespace std;

typedef void (*EventHandle)(void *);

//����window�ײ�ĶԻ�����ѡ��һ��c++�ļ���Ŀǰ��Ҫ������.h��.cpp��.c���������ļ� 
void OpenFileDialog(void*); 

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
            		node->data.handle(NULL);
            		return;
            	}
		        node = node->next;  // �ƶ�����һ���ڵ�
		    }
        }	
	}
	
	bool isPointInRect(int x, int y, RECT rect)
	{
	    return x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom;
	}
	
	void createButton(int x,int y,int width, int height,std::string text)
	{
		// ���ư�ť�ı���
	    setfillcolor(LIGHTGRAY);
	    fillrectangle(x, y, x + width, y + height);
	
	    // ���ư�ť�ı߿�
	    setlinecolor(WHITE);
	    rectangle(x, y, x + width, y + height);
	
	    // ����ı�
	    setfillcolor(LIGHTGRAY);
	    RECT r = { x, y, x + width, y + height };
	    drawtext(text.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = r;
	    buttonConfig.handle = OpenFileDialog;
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
