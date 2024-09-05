#pragma once

#include "mainWindow.h"

class OperationButtionWindow
{
private:
	int x;					//整个按钮绘制区域的左上角x 
	int y;					//整个按钮绘制区域的左上角y 
	int height;
	int width;
	
	int buttonHeight;   	//按钮的高度 
	int buttonCount;		//保存当前按钮的数量 
	int buttonPaddingLeft;  //保存按钮离绘制区域的左侧边距 
	int buttonPaddingTop;	//保存按钮离绘制区域的顶部边距 
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
	
	//创建按钮，并返回按钮的边界区域 
	RECT createButton(const std::string& text)
	{
	    // 设置按钮背景颜色
	    setfillcolor(BLACK);
	    int buttonWidth = width - 2 * buttonPaddingLeft;
	    int buttonY = y + buttonPaddingTop + buttonCount * (buttonPaddingTop + buttonHeight);
	    
	    RECT buttonBorder = {x + buttonPaddingLeft, buttonY, x + buttonPaddingLeft + buttonWidth, buttonY + buttonHeight};
	    // 绘制按钮背景
	    fillrectangle(x + buttonPaddingLeft, buttonY, x + buttonPaddingLeft + buttonWidth, buttonY + buttonHeight);
	
	    // 设置文本颜色
	    settextcolor(WHITE);
	    setbkmode(TRANSPARENT);
	    setfillcolor(LIGHTGRAY);
	
	    // 定义按钮文本区域
	    RECT r = {x + buttonPaddingLeft, buttonY, width, buttonY + buttonHeight};
	    // 设置文本样式
	    settextstyle(16, 0, _T("Arial")); // 设置字体大小和字体名称
		
	    // 获取文本的宽度和高度
	    int textWidth = textwidth(_T(text.c_str()));
	    int textHeight = textheight(_T(text.c_str()));
	
	    // 计算文本位置，使其在按钮内居中
	    int textX = x + buttonPaddingLeft + (buttonWidth - textWidth) / 2;
	    int textY = buttonY + (buttonHeight - textHeight) / 2;
	
	    // 绘制文本
	    outtextxy(textX, textY, _T(text.c_str()));
	    buttonCount = buttonCount +1;
	    return buttonBorder;
	}	
	//创建语法分析器的按钮
	//绑定 MainWindow::parser函数 
	void createParserButton()
	{
	    RECT buttonBorder = createButton("语法分析");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::parser;
	    parent->addSubclassButton(buttonConfig);
	}
	
	//创建词法分析器的按钮 
	void createLexerButton()
	{
	    RECT buttonBorder = createButton("词法分析");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::lexer;
	    parent->addSubclassButton(buttonConfig);
	}
	
	//创建格式化文件的按钮 
	void createFormatButton()
	{
	    RECT buttonBorder = createButton("格式化");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::format;
	    parent->addSubclassButton(buttonConfig);
	}

	//重新选择文件 
	void createSelectFileButton()
	{
	    RECT buttonBorder = createButton("重选文件");
	    UiComponentConfig buttonConfig;
	    buttonConfig.rect = buttonBorder;
	    buttonConfig.handle = &MainWindow::selectFile;
	    parent->addSubclassButton(buttonConfig);
	}
};
