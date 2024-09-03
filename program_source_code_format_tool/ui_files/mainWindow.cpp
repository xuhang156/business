#include "mainWindow.h"
#include "operationButtonWindow.h"

MainWindow::MainWindow(const std::string& title, int width, int height): title(title), width(width), height(height)
{
    initgraph(width, height);
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
	if(filePath != "" && !hadCreateButton)
	{
		operationButtons->create();
		hadCreateButton = true;
		hideSelectFileButton();
	}
}

//MainWindow::~MainWindow()
//{
//	
//}

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
