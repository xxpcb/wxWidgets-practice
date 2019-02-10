/*=========================================================
* Name: testApp.cpp
* Function: 用户控件测试(添加用户控件的cpp代码和wxFormBuilder的配置代码)
* Created: 2019-02-08
* Author: xxpcb(https://github.com/xxpcb)
* 说明：
    myImagePanel.cpp/myImagePanel.h:用户控件wxImagePanel源码，继承于wxScrolledWindow
	GUI.cpp/GUI.h:通过wxFormBuilder软件中的CustomControl控件调用wxImagePanel类
	testApp.cpp:(此文件)测试上述文件中的代码
* 存在问题：
    滚动窗口的最下和最右边缘部分显示不正常（窗口缩放时多出来3-5行/列像素）
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


//主窗口类(继承于设计的MyFrame1)
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
	picFrame *frame = new picFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

wxIMPLEMENT_APP(calcApp);//开始执行