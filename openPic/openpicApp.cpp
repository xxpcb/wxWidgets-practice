/*=========================================================
* Name: openpicApp.cpp
* Function: 打开图片及显示测试
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "openpic.h"//选用demo2.fbp
//#include <wx/wfstream.h>

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
	wxImage imwx2;
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnOpenPic1(wxCommandEvent& event);
	void OnOpenPic2(wxCommandEvent& event);
	void OnPaintPannel(wxPaintEvent& event);
};


wxIMPLEMENT_APP(calcApp);//开始执行

bool calcApp::OnInit()
{
	picFrame *frame = new picFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

void picFrame::OnOpenPic1(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxString s;
	openFileDialog.ShowModal();
	//wxFileInputStream input_stream(openFileDialog.GetPath());
	string imgfile = (const char*)openFileDialog.GetPath().mb_str();

	//From opencv to wx
	Mat imcv1 = imread(imgfile, IMREAD_UNCHANGED);//opencv读入图像
	string str = "Channels:" + to_string(imcv1.channels());
	putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//图像上面放字符串
	wxBitmap imwx1 = wx_from_mat(imcv1);//Mat 转 wxBitmap
	m_bitmap1->SetBitmap(imwx1);//显示wxBitmap
	Refresh(true);
}
void picFrame::OnOpenPic2(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxString s;
	openFileDialog.ShowModal();
	//wxFileInputStream input_stream(openFileDialog.GetPath());
	string imgfile = (const char*)openFileDialog.GetPath().mb_str();

	Mat imcv2 = imread(imgfile, IMREAD_UNCHANGED);//opencv读入图像
	string str = "Channels:" + to_string(imcv2.channels());
	putText(imcv2, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//图像上面放字符串
	this->imwx2 = wx_from_mat(imcv2);//Mat 转 wxBitmap
	wxClientDC dc(m_panel1);
	dc.Clear();//先清除上次打开的图
	dc.DrawBitmap(imwx2,0,0);//缩放窗口后，图片消失

	falg_OnPaintPannel = TRUE;    
}
void picFrame::OnPaintPannel(wxPaintEvent& event)
{
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_panel1);
		dc.DrawBitmap(imwx2, 0, 0);//添加这里，缩放窗口后，图片刷新
	}
}
