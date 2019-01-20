/*=========================================================
* Name: openpicApp.cpp
* Function: 打开大图片及显示测试（滚动窗口测试）
* Created: 2019-01-20
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "bigpic.h"//选用demo2.fbp

#include "../common/util.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

bool falg_OnPaintPannel = FALSE;

class calcApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的MyFrame1)
class picFrame : public MyFrame1
{
public:
	wxImage imwx;
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnOpen(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
};


wxIMPLEMENT_APP(calcApp);//开始执行

bool calcApp::OnInit()
{
	picFrame *frame = new picFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

void picFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxString s;
	openFileDialog.ShowModal();
	string imgfile = (const char*)openFileDialog.GetPath().mb_str();

	//From opencv to wx
	Mat imcv1 = imread(imgfile, IMREAD_UNCHANGED);//opencv读入图像
	string str = "Channels:" + to_string(imcv1.channels());
	putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//图像上面放字符串
	imwx = wx_from_mat(imcv1);//Mat 转 wxBitmap

	m_scrolledWindow1->SetVirtualSize(imcv1.cols, imcv1.rows);//设置画面大小
	wxClientDC dc(m_scrolledWindow1);
	dc.Clear();//先清除上次打开的图
	//m_scrolledWindow1->PrepareDC(dc);
	//m_scrolledWindow1->DoPrepareDC(dc);
	dc.DrawBitmap(imwx, 0, 0);//缩放窗口后，图片消失

	falg_OnPaintPannel = TRUE;
}

void picFrame::OnPaint(wxPaintEvent& event)
{
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_scrolledWindow1);
		//m_scrolledWindow1->DoPrepareDC(dc);//此句与下句作用相同？
		m_scrolledWindow1->PrepareDC(dc);
		dc.DrawBitmap(imwx, 0, 0);
	}
}
