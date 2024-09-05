
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
    HWND hwnd = GetHWnd();  // ��ȡ���ھ��
    SetWindowText(hwnd, title.c_str());
    createSelectFileButton();
    createMsgText("�����ťѡ���ļ�");
    
    operationButtons = new OperationButtionWindow(this);
}

MainWindow::~MainWindow()
{
    closegraph();  // �رմ���
    delete operationButtons;
}

void MainWindow::selectFile(void*)
{
	static bool hadCreateButton = false;
	std::string text = "��ǰѡ����ļ�Ϊ��"; 
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
	createMsgText("δѡ���ļ���������ѡ���ļ���");
	
}

//���������Ҫ��ʾ���� 
void MainWindow::clearMainPlotArea()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, operationButtons->borderLeft(), msgAreaTop);
}

void MainWindow::lexer(void *)
{
	cout<<"�ʷ���������"; 
	if(fileStringData == "")
		return;
	cout<<"kaishi�ʷ���������";
	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	tokens.display();
	
	MyList<Token>::Node* node = tokens.beginNode();  // ��ͷ���ڵ㿪ʼ
	int i = 0;
	clearMainPlotArea();
	while (node != NULL) {
		int lineHeight = 15;
		cout<<"��ȡ�˷�����"<<node->data.description();
		outtextxy(10, i * lineHeight, node->data.description().c_str());
		outtextxy(200, i * lineHeight, node->data.value.c_str());
		i++;
		node = node->next;  // �ƶ�����һ���ڵ�
	}
	cout<<"��������:"<<i <<endl; 
	Parser parser(tokens);
	
}

void MainWindow::parser(void *)
{
	cout<<"�﷨��������"; 
	if(fileStringData == "")
		return;
	showTree(true,""); 
	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	Token token = {"����",END_OF_FILE};
	tokens.insert(token);
	Parser parser(tokens);
	
	try {
        std::shared_ptr<ASTNode> ast = parser.parse();
        clearMainPlotArea();
        
        printAST(ast.get());
        createMsgText("�﷨�����ɹ��� "); 
    }
    catch (const std::exception& e) {
        createMsgText("�﷨����ʧ�ܡ�"); 
    }
	cout<<"��������:"<<endl; 	
}

//easyX�������ֺ�������Ҫ���ڸ�ʽ�����ܣ�
//easyX�������з����ո񲻻���ƣ������д�����߼����ܹ�֧�ֻ��з��Ϳո� 
void drawTextWithNewlines(const std::ostringstream& oss, int x, int y, int lineHeight = 20) {
    std::string text = oss.str();  // ��ȡ ostringstream �е��ַ���
    std::string line;
    int currentY = y;

    for (char ch : text) {
        if (ch == '\n') {
            outtextxy(x, currentY, line.c_str());  // ���Ƶ�ǰ��
            currentY += lineHeight;  // �ƶ�����һ��
            line.clear();  // ��յ�ǰ�е�����
        } else {
            line += ch;  // ����ַ�����ǰ��
        }
    }

    if (!line.empty()) {
        outtextxy(x, currentY, line.c_str());  // �������һ�У�����еĻ���
    }
}

void MainWindow::format(void *)
{
	if(fileStringData == "")
		return;

	Lexer er(fileStringData);
	auto tokens = er.tokenize();
	Token token = {"����",END_OF_FILE};
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
    	createMsgText("��ʽ������"); 
        std::cerr << "Parsing failed: " << e.what() << std::endl;
    }
	cout<<"��������:"<<endl; 
}

//���ڴ�ӡ�﷨�� 
void printAST(ASTNode* node, int indent){
	int margin = 30;
    if (!node) return;
	string text = "";
    // ���ڴ�ӡ����
    auto printIndent = [indent]() {
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";  // ÿ��������λΪ�����ո�
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
    // �жϽڵ����Ͳ������Ӧ����Ϣ
    if (auto constantNode = dynamic_cast<ConstantNode*>(node)) {
        printIndent();
        std::string text = "�����ڵ�: " + std::to_string(constantNode->value);
        showTree(false,text,indent*margin);
        std::cout << "�����ڵ�: " << constantNode->value << std::endl;
    }
    else if (auto variableNode = dynamic_cast<VariableNode*>(node)) {
        printIndent();
        std::string text = "�����ڵ�: " + variableNode->name;
        showTree(false,text,indent*margin);
        std::cout << "�����ڵ�: " << variableNode->name << std::endl;
    }
    else if (auto operatorNode = dynamic_cast<OperatorNode*>(node)) {
        printIndent();
    	string text = "�������ڵ�:  ";
        for (auto* node = operators.beginNode(); node != nullptr; node = node->next) {
            if(node->data.type == operatorNode->op)
            	text += node->data.value;
        }
        printIndent();
        showTree(false,text,indent*margin);
        showTree(false,"�������:",indent*margin);
        printAST(operatorNode->left.get(), indent + 1);
        printIndent();
        showTree(false,"�Ҳ�����:",indent*margin);
        std::cout << "�Ҳ�����:" << std::endl;
        printAST(operatorNode->right.get(), indent + 1);
    }
    else if (auto functionCallNode = dynamic_cast<FunctionCallNode*>(node)) {
        printIndent();
        string text = "�������ýڵ�: " + functionCallNode->functionName;
        std::cout << "�������ýڵ�: " << functionCallNode->functionName << std::endl;
        showTree(false,text,indent*margin);
        for (auto* argNode = functionCallNode->arguments.beginNode(); argNode != nullptr; argNode = argNode->next) {
            printAST(argNode->data.get(), indent + 1);
        }
    }
    else if (auto assignmentNode = dynamic_cast<AssignmentNode*>(node)) {
        printIndent();
        std::cout << "��ֵ�ڵ�: " << assignmentNode->varName << std::endl;
        text = "��ֵ�ڵ�: " + assignmentNode->varName;
        showTree(false,text,indent*margin);
        printIndent();
        std::cout << "ֵ:" << std::endl;
        showTree(false,"ֵ:" ,indent*margin);
        printAST(assignmentNode->value.get(), indent + 1);
    }
    else if (auto returnNode = dynamic_cast<ReturnStatementNode*>(node)) {
        printIndent();
        std::cout << "�������ڵ�:" << std::endl;
        showTree(false,"�������ڵ�:",indent*margin);
        printAST(returnNode->returnValue.get(), indent + 1);
    }
    else if (auto compoundStmtNode = dynamic_cast<CompoundStatementNode*>(node)) {
        printIndent();
        std::cout << "�������ڵ�:" << std::endl;
        showTree(false,"�������ڵ�:",indent*margin);
        for (auto* stmtNode = compoundStmtNode->statements.beginNode(); stmtNode != nullptr; stmtNode = stmtNode->next) {
            printAST(stmtNode->data.get(), indent + 1);
        }
    }
    else if (auto functionDefNode = dynamic_cast<FunctionDefinitionNode*>(node)) {
        printIndent();
        text = "��������ڵ�:" + functionDefNode->functionName + "��������: " + functionDefNode->returnType;
        showTree(false,text,indent * 10);
        std::cout << "��������ڵ�: " << functionDefNode->functionName << " ��������: " << functionDefNode->returnType << std::endl;
        printIndent();
        std::cout << "����: ";
        showTree(false,"����: ",indent * 10);
        for (auto* paramNode = functionDefNode->parameters.beginNode(); paramNode != nullptr; paramNode = paramNode->next) {
            std::cout << paramNode->data << " ";
            showTree(false,paramNode->data,indent * 10);
        }
        std::cout << std::endl;
        printIndent();
        std::cout << "������:" << std::endl;
        showTree(false,"������:",indent * 10);
        printAST(functionDefNode->body.get(), indent + 1);
    }
    else if (auto ifNode = dynamic_cast<IfNode*>(node)) {
        printIndent();
        std::cout << "�������ڵ�:" << std::endl;
        showTree(false,"�������ڵ�:",indent * 10);
        printIndent();
        showTree(false,"����:",indent * 10);
        std::cout << "����:" << std::endl;
        printAST(ifNode->condition.get(), indent + 1);
        printIndent();
        showTree(false,"ִ�з�֧:",indent * 10);
        std::cout << "ִ�з�֧:" << std::endl;
        printAST(ifNode->thenBranch.get(), indent + 1);
        if (ifNode->elseBranch) {
            printIndent();
            showTree(false,"�����֧:",indent * 10);
            std::cout << "�����֧:" << std::endl;
            printAST(ifNode->elseBranch.get(), indent + 1);
        }
    }
    else if (auto exprStmtNode = dynamic_cast<ExpressionStatementNode*>(node)) {
        printIndent();
        showTree(false,"��ʽ���ڵ�:",indent * 10);
        std::cout << "���ʽ���ڵ�:" << std::endl;
        printAST(exprStmtNode->expression.get(), indent + 1);
    }
    else {
        printIndent();
        showTree(false,"δ֪��AST�ڵ�",indent * 10);
        std::cout << "δ֪��AST�ڵ�" << std::endl;
    }
}

void MainWindow::showCode(const std::string& filePath)
{
	fileStringData = "";
	// ��ȡ�ļ�����
	MyList<std::string> fileDatas = readFile(filePath);
	fileDatas.display();
	
	int i = 0;
	MyList<std::string>::Node* node = fileDatas.beginNode();  // ��ͷ���ڵ㿪ʼ
	clearMainPlotArea();
	while (node != NULL) {
		int lineHeight = 15;
		outtextxy(10, i * lineHeight, node->data.c_str());
		i++;
		fileStringData += node->data;
		fileStringData += '\n';
		node = node->next;  // �ƶ�����һ���ڵ�
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

//����window�ĶԻ����ܣ�֧��ѡ���ļ� 
std::string OpenFileDialog(void*) {
    // ����һ���ṹ���������ļ�ѡ��Ի������Ϣ
    OPENFILENAME ofn;       		// �ļ�ѡ��Ի���ṹ��
    char szFile[260] = { 0 };  		// ����ѡ����ļ���
    ZeroMemory(&ofn, sizeof(ofn)); 	// ���ṹ������

    // ���ýṹ��Ĳ���
    ofn.lStructSize = sizeof(ofn); 	// �ṹ���С
    ofn.hwndOwner = NULL;       	// �������ڵľ����NULL��ʾ�޸�����
    ofn.lpstrFile = szFile;        	// �洢ѡ�е��ļ����Ļ�����
    ofn.nMaxFile = sizeof(szFile); 	// ��������С
    ofn.lpstrFilter = "C++ Files\0*.cpp;*.c;*.h;\0All Files\0*.*\0"; // �ļ����͹���
    ofn.nFilterIndex = 1;         	// Ĭ�Ϲ�����������
    ofn.lpstrFileTitle = NULL;  	// �������Ҫ�ļ�����·���ֿ�������Ϊ��
    ofn.nMaxFileTitle = 0;         	// �������Ҫ�ļ�����·���ֿ�������Ϊ0
    ofn.lpstrInitialDir = NULL; 	// ��ʼĿ¼����Ϊnullptr��Ϊ��ǰĿ¼��
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ȷ��·�����ļ����������

    // ��ʾ�ļ�ѡ��Ի���
    if (GetOpenFileName(&ofn)) {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        return ofn.lpstrFile;
    } else {
    	return "";
        std::cout << "No file selected or operation canceled." << std::endl;
    }
}
