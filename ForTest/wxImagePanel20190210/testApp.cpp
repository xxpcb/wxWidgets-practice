/*=========================================================
* Name: testApp.cpp
* Function: �û��ؼ�����(����û��ؼ���cpp�����wxFormBuilder�����ô���)
* Created: 2019-02-08
* Author: xxpcb(https://github.com/xxpcb)
* ˵����
    myImagePanel.cpp/myImagePanel.h:�û��ؼ�wxImagePanelԴ�룬�̳���wxScrolledWindow
	GUI.cpp/GUI.h:ͨ��wxFormBuilder����е�CustomControl�ؼ�����wxImagePanel��
	testApp.cpp:(���ļ�)���������ļ��еĴ���
* �������⣺
    �������ڵ����º����ұ�Ե������ʾ����������������ʱ�����3-5��/�����أ�
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "GUI.h"     

//#include "../common/util.h"
//#include <opencv2/opencv.hpp>
//#include <string>
//using namespace cv;
//using namespace std;


//��������(�̳�����Ƶ�MyFrame1)
class picFrame : public MyFrame1
{
public:
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnPaint(wxPaintEvent& event);
};


void picFrame::OnPaint(wxPaintEvent& event)
{
	drawPane->OnPaint();
}

class calcApp : public wxApp
{
public:
	virtual bool OnInit();
};

bool calcApp::OnInit()
{
	picFrame *frame = new picFrame();//��������
	frame->Show(true);//��ʾ����
	return true;
}

wxIMPLEMENT_APP(calcApp);//��ʼִ��