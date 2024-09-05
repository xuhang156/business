#pragma once

#include "mainWindow.h"

class OperationButtionWindow
{
private:
	int x;					//������ť������������Ͻ�x 
	int y;					//������ť������������Ͻ�y 
	int height;
	int width;
	
	int buttonHeight;   	//��ť�ĸ߶� 
	int buttonCount;		//���浱ǰ��ť������ 
	int buttonPaddingLeft;  //���水ť�������������߾� 
	int buttonPaddingTop;	//���水ť���������Ķ����߾� 
	MainWindow* parent = NULL;
	
public:
    OperationButtionWindow(MainWindow* parent):parent(parent)
    {
    	y = 0;
    	width = 100;			
    	buttonPaddingLeft = 10;
    	buttonPaddingTop = 30;
    	buttonCount = 0;
		buttonHeight = 40;
    }
    
    bool noParent()
    {
    	return parent == NULL;
	}
	
	int borderLeft()
	{
		return x;
	}
	
	void create()
	{
		setRegionalBackground();
		createLexerButton();
		createParserButton();
		createFormatButton();
		createSelectFileButton(); 
	}
	
    void setRegionalBackground ()
    {
    	if(noParent())
    		return;
    	
		setfillcolor(LIGHTGRAY);
		x = parent->getWidth() - 100;
		height = parent->getHeight() - 70;
	    fillrectangle(x, y, parent->getWidth(), height);
	}
	
	//������ť�������ذ�ť�ı߽����� 
	RECT createButton(const std::string& text)
	{
	    // ���ð�ť������ɫ
	    setfillcolor(BLACK);
	    int buttonWidth = width - 2 * buttonPaddingLeft;
	    int buttonY = y + buttonPaddingTop + buttonCount * (buttonPaddingTop + buttonHeight);
	    
	    RECT buttonBorder = {x + buttonPaddingLeft, buttonY, x + buttonPaddingLeft + buttonWidth, buttonY + buttonHeight};
	    // ���ư�ť����
	    fillrectangle(x + buttonPaddingLeft, buttonY, x + buttonPaddingLeft + buttonWidth, buttonY + buttonHeight);
	
	    // �����ı���ɫ
	    settextcolor(WHITE);
	    setbkmode(TRANSPARENT);
	    setfillcolor(LIGHTGRAY);
	
	    // ���尴ť�ı�����
	    RECT r = {x + buttonPaddingLeft, buttonY, width, buttonY + buttonHeight};
	    // �����ı���ʽ
	    settextstyle(16, 0, _T("Arial")); // ���������С����������
		
	    // ��ȡ�ı��Ŀ�Ⱥ͸߶�
	    int textWidth = textwidth(_T(text.c_str()));
	    int textHeight = textheight(_T(text.c_str()));
	
	    // �����ı�λ�ã�ʹ���ڰ�ť�ھ���
	    int textX = x + buttonPaddingLeft + (buttonWidth - textWidth) / 2;
	    int textY = buttonY + (buttonHeight - textHeight) / 2;
	
	    // �����ı�
	    outtextxy(textX, textY, _T(text.c_str()));
	    buttonCount = buttonCount +1;
	    return buttonBorder;
	}	
	//�����﷨�������İ�ť
	//�� MainWindow::parser���� 
	void createParserButton()
	{
	    RECT buttonBorder = createButton("�﷨����");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::parser;
	    parent->addSubclassButton(buttonConfig);
	}
	
	//�����ʷ��������İ�ť 
	void createLexerButton()
	{
	    RECT buttonBorder = createButton("�ʷ�����");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::lexer;
	    parent->addSubclassButton(buttonConfig);
	}
	
	//������ʽ���ļ��İ�ť 
	void createFormatButton()
	{
	    RECT buttonBorder = createButton("��ʽ��");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::format;
	    parent->addSubclassButton(buttonConfig);
	}

	//����ѡ���ļ� 
	void createSelectFileButton()
	{
	    RECT buttonBorder = createButton("��ѡ�ļ�");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::selectFile;
	    parent->addSubclassButton(buttonConfig);
	}
};
