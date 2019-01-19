/*=========================================================
* Name: contoursApp.cpp
* Function: 查找图像轮廓测试
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "contours.h"//选用demo2.fbp
//#include <wx/wfstream.h>

#include "../common/util.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

bool falg_OnPaint = FALSE;
bool falg_OnScroll = FALSE;
Mat g_srcImage;//原图
Mat g_grayImage;//灰度图
int g_nThresh = 80;//阈值
int g_nThresh_max = 255;//最大阈值
RNG g_rng(12345);
Mat g_cannyMat_output;//输出图
vector<vector<Point>> g_vContours;//【轮廓】
vector<Vec4i> g_vHierarchy;//层次

class contoursApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的demoFrame)
class picFrame : public MyFrame1
{
public:
	wxImage imwx1, imwx2;
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnPaint1(wxPaintEvent& event);
	void OnPaint2(wxPaintEvent& event);
	void OnScroll_Th(wxScrollEvent& event);
	void ImgProcess_Thresh(void);

	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};
wxBEGIN_EVENT_TABLE(picFrame, wxFrame)
EVT_MENU(wxID_OPEN, picFrame::OnOpen)//File->Quit
EVT_MENU(wxID_EXIT, picFrame::OnExit)//File->Quit
EVT_MENU(wxID_ABOUT, picFrame::OnAbout)//Help-About
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(contoursApp);//开始执行

bool contoursApp::OnInit()
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

	// 【加载源图像】
	g_srcImage = imread(imgfile, IMREAD_UNCHANGED);//opencv读入图像
	// 【转成灰度并模糊化降噪】
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转成灰度图
	blur(g_grayImage, g_grayImage, Size(3, 3));//滤波
    //  【Mat 转 wxBitmap】
	imwx1 = wx_from_mat(g_srcImage);

	wxClientDC dc(m_panel1);
	dc.Clear();//先清除上次打开的图
	dc.DrawBitmap(imwx1, 0, 0);//缩放窗口后，图片消失

	ImgProcess_Thresh();

	falg_OnPaint = TRUE;
	falg_OnScroll = TRUE;
}

void picFrame::OnPaint1(wxPaintEvent& event)
{
	if (falg_OnPaint)
	{
		wxPaintDC dc(m_panel1);
		dc.DrawBitmap(imwx1, 0, 0);//添加这里，缩放窗口后，图片刷新
	}
}
void picFrame::OnPaint2(wxPaintEvent& event)
{
	if (falg_OnPaint)
	{
		wxPaintDC dc(m_panel2);
		dc.DrawBitmap(imwx2, 0, 0);//添加这里，缩放窗口后，图片刷新
	}
}

void picFrame::OnScroll_Th(wxScrollEvent& event)
{
	if (falg_OnScroll)
	{
		g_nThresh = m_slider1->GetValue();
		ImgProcess_Thresh();
	}
}

void picFrame::OnExit(wxCommandEvent& event)
{
	Close(true);//关闭整个窗口
}
void picFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a findContours(OpenCV) test demo",//输出信息（弹出信息框）
		"About This demo", wxOK | wxICON_INFORMATION);//（信息框）标题
}

void picFrame::ImgProcess_Thresh()
{
	// 用【Canny算子】检测边缘
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);
	// 【寻找轮廓】
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 【绘出轮廓】
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);//全0，黑
	for (int i = 0; i < g_vContours.size(); i++)//轮廓循环
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}
	wxClientDC dc(m_panel2);
	imwx2 = wx_from_mat(drawing);
	dc.DrawBitmap(imwx2, 0, 0);//缩放窗口后，图片消失
}
