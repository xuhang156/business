
#include <fstream>

#include "mainWindow.h"
#include "operationButtonWindow.h"
#include "../data_structure/lexerInfo.h"

MainWindow::MainWindow(const std::string& title, int width, int height): title(title), width(width), height(height)
{
    initgraph(width, height);
    msgAreaTop = height - 70; 
    HWND hwnd = GetHWnd();  // ��ȡ���ھ��
    SetWindowText(hwnd, title.c_str());
    createSelectFileButton();
    createMsgText("�����ťѡ���ļ�");
    
    operationButtons = new OperationButtionWindow(this);
    
//        floodfill(0, 0, WHITE);
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
		i++;
		node = node->next;  // �ƶ�����һ���ڵ�
	}
	cout<<"��������:"<<i <<endl; 
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

//MainWindow::~MainWindow()
//{
//	
//}

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
