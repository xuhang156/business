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
	
   // ���� == �����
    bool operator==(const UiComponentConfig& other) const
    {
        return (rect.left == other.rect.left && rect.bottom == other.rect.bottom && rect.right == other.rect.right && rect.top == other.rect.top); 
    }
	// ���� != �����
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
	
	//��������еİ�ť���ã����а�ť������Ŀǰ�������������ʵ�ֵ� 
	void addSubclassButton(UiComponentConfig& config)
	{
		components.insert(config);
	}
	
	void hideSelectFileButton()
	{
		components.remove(selectFileButton);
		setfillcolor(BLACK);
	    fillrectangle(selectFileButton.rect.left, selectFileButton.rect.top, selectFileButton.rect.right, selectFileButton.rect.bottom);
	    // ���ñ߿���ɫ
    	setlinecolor(BLACK);
    	rectangle(selectFileButton.rect.left, selectFileButton.rect.top, selectFileButton.rect.right, selectFileButton.rect.bottom);
	    cout<<"�����������ϵ�ѡ���ļ���ť"<<endl;
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
