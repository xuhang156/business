
#include <fstream>
#include "mainWindow.h"
#include <sstream>
#include "operationButtonWindow.h"
#include "../data_structure/parserInfo.h" 

void showTree(bool clear,const std::string& text,int leftAdd = 10)
{
	static int index = 0;
	if(clear)
		index = 0;
	int lineHeight = 15;
    outtextxy(leftAdd, index * lineHeight,text.c_str());
    index++; 
}


MainWindow::MainWindow(const std::string& title, int width, int height): title(title), width(width), height(height)
{
    initgraph(width, height);
    msgAreaTop = height - 70; 
    HWND hwnd = GetHWnd();  // 获取窗口句柄
    SetWindowText(hwnd, title.c_str());
    createSelectFileButton();
    createMsgText("点击按钮选择文件");
    
    operationButtons = new OperationButtionWindow(this);
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
		outtextxy(200, i * lineHeight, node->data.value.c_str());
		i++;
		node = node->next;  // 移动到下一个节点
	}
	cout<<"分析结束:"<<i <<endl; 
	Parser parser(tokens);
	
}

void MainWindow::parser(void *)
{
	cout<<"语法分析程序"; 
	if(fileStringData == "")
		return;
	showTree(true,""); 
	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	Token token = {"结束",END_OF_FILE};
	tokens.insert(token);
	Parser parser(tokens);
	
	try {
        std::shared_ptr<ASTNode> ast = parser.parse();
        clearMainPlotArea();
        
        printAST(ast.get());
        createMsgText("语法分析成功。 "); 
    }
    catch (const std::exception& e) {
        createMsgText("语法分析失败。"); 
    }
	cout<<"分析结束:"<<endl; 	
}

//easyX绘制文字函数，主要用于格式化功能，
//easyX遇到换行符、空格不会绘制，因此重写绘制逻辑，能够支持换行符和空格 
void drawTextWithNewlines(const std::ostringstream& oss, int x, int y, int lineHeight = 20) {
    std::string text = oss.str();  // 获取 ostringstream 中的字符串
    std::string line;
    int currentY = y;

    for (char ch : text) {
        if (ch == '\n') {
            outtextxy(x, currentY, line.c_str());  // 绘制当前行
            currentY += lineHeight;  // 移动到下一行
            line.clear();  // 清空当前行的内容
        } else {
            line += ch;  // 添加字符到当前行
        }
    }

    if (!line.empty()) {
        outtextxy(x, currentY, line.c_str());  // 绘制最后一行（如果有的话）
    }
}

void MainWindow::format(void *)
{
	if(fileStringData == "")
		return;

	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	Token token = {"结束",END_OF_FILE};
	tokens.insert(token);
	Parser parser(tokens);

	try {
        std::shared_ptr<ASTNode> ast = parser.parse();
        clearMainPlotArea();
        std::ostringstream oss;
        
        ast-> format(oss);
        drawTextWithNewlines(oss,20,20);
    }
    catch (const std::exception& e) {
    	createMsgText("格式化错误。"); 
        std::cerr << "Parsing failed: " << e.what() << std::endl;
    }
	cout<<"分析结束:"<<endl; 
}

//用于打印语法树 
void printAST(ASTNode* node, int indent){
	int margin = 30;
    if (!node) return;
	string text = "";
    // 用于打印缩进
    auto printIndent = [indent]() {
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";  // 每个缩进单位为两个空格
        }
    };
    
    std::string str = node->description();
    std::string token;
    for (char ch : str) {
        if (ch == '\n') {
            if (!token.empty()) 
			{
            	showTree(false,token,0);
                token.clear();
            }
        } 
		else 
            token += ch;
    }
    if (!token.empty())
        showTree(false,token,0);
    return;
    // 判断节点类型并输出对应的信息
    if (auto constantNode = dynamic_cast<ConstantNode*>(node)) {
        printIndent();
        std::string text = "常量节点: " + std::to_string(constantNode->value);
        showTree(false,text,indent*margin);
        std::cout << "常量节点: " << constantNode->value << std::endl;
    }
    else if (auto variableNode = dynamic_cast<VariableNode*>(node)) {
        printIndent();
        std::string text = "变量节点: " + variableNode->name;
        showTree(false,text,indent*margin);
        std::cout << "变量节点: " << variableNode->name << std::endl;
    }
    else if (auto operatorNode = dynamic_cast<OperatorNode*>(node)) {
        printIndent();
    	string text = "操作符节点:  ";
        for (auto* node = operators.beginNode(); node != nullptr; node = node->next) {
            if(node->data.type == operatorNode->op)
            	text += node->data.value;
        }
        printIndent();
        showTree(false,text,indent*margin);
        showTree(false,"左操作数:",indent*margin);
        printAST(operatorNode->left.get(), indent + 1);
        printIndent();
        showTree(false,"右操作数:",indent*margin);
        std::cout << "右操作数:" << std::endl;
        printAST(operatorNode->right.get(), indent + 1);
    }
    else if (auto functionCallNode = dynamic_cast<FunctionCallNode*>(node)) {
        printIndent();
        string text = "函数调用节点: " + functionCallNode->functionName;
        std::cout << "函数调用节点: " << functionCallNode->functionName << std::endl;
        showTree(false,text,indent*margin);
        for (auto* argNode = functionCallNode->arguments.beginNode(); argNode != nullptr; argNode = argNode->next) {
            printAST(argNode->data.get(), indent + 1);
        }
    }
    else if (auto assignmentNode = dynamic_cast<AssignmentNode*>(node)) {
        printIndent();
        std::cout << "赋值节点: " << assignmentNode->varName << std::endl;
        text = "赋值节点: " + assignmentNode->varName;
        showTree(false,text,indent*margin);
        printIndent();
        std::cout << "值:" << std::endl;
        showTree(false,"值:" ,indent*margin);
        printAST(assignmentNode->value.get(), indent + 1);
    }
    else if (auto returnNode = dynamic_cast<ReturnStatementNode*>(node)) {
        printIndent();
        std::cout << "返回语句节点:" << std::endl;
        showTree(false,"返回语句节点:",indent*margin);
        printAST(returnNode->returnValue.get(), indent + 1);
    }
    else if (auto compoundStmtNode = dynamic_cast<CompoundStatementNode*>(node)) {
        printIndent();
        std::cout << "复合语句节点:" << std::endl;
        showTree(false,"复合语句节点:",indent*margin);
        for (auto* stmtNode = compoundStmtNode->statements.beginNode(); stmtNode != nullptr; stmtNode = stmtNode->next) {
            printAST(stmtNode->data.get(), indent + 1);
        }
    }
    else if (auto functionDefNode = dynamic_cast<FunctionDefinitionNode*>(node)) {
        printIndent();
        text = "函数定义节点:" + functionDefNode->functionName + "返回类型: " + functionDefNode->returnType;
        showTree(false,text,indent * 10);
        std::cout << "函数定义节点: " << functionDefNode->functionName << " 返回类型: " << functionDefNode->returnType << std::endl;
        printIndent();
        std::cout << "参数: ";
        showTree(false,"参数: ",indent * 10);
        for (auto* paramNode = functionDefNode->parameters.beginNode(); paramNode != nullptr; paramNode = paramNode->next) {
            std::cout << paramNode->data << " ";
            showTree(false,paramNode->data,indent * 10);
        }
        std::cout << std::endl;
        printIndent();
        std::cout << "函数体:" << std::endl;
        showTree(false,"函数体:",indent * 10);
        printAST(functionDefNode->body.get(), indent + 1);
    }
    else if (auto ifNode = dynamic_cast<IfNode*>(node)) {
        printIndent();
        std::cout << "条件语句节点:" << std::endl;
        showTree(false,"条件语句节点:",indent * 10);
        printIndent();
        showTree(false,"条件:",indent * 10);
        std::cout << "条件:" << std::endl;
        printAST(ifNode->condition.get(), indent + 1);
        printIndent();
        showTree(false,"执行分支:",indent * 10);
        std::cout << "执行分支:" << std::endl;
        printAST(ifNode->thenBranch.get(), indent + 1);
        if (ifNode->elseBranch) {
            printIndent();
            showTree(false,"否则分支:",indent * 10);
            std::cout << "否则分支:" << std::endl;
            printAST(ifNode->elseBranch.get(), indent + 1);
        }
    }
    else if (auto exprStmtNode = dynamic_cast<ExpressionStatementNode*>(node)) {
        printIndent();
        showTree(false,"达式语句节点:",indent * 10);
        std::cout << "表达式语句节点:" << std::endl;
        printAST(exprStmtNode->expression.get(), indent + 1);
    }
    else {
        printIndent();
        showTree(false,"未知的AST节点",indent * 10);
        std::cout << "未知的AST节点" << std::endl;
    }
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

//调用window的对话框功能，支持选择文件 
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
