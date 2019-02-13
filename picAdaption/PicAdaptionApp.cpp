/*=========================================================
* Name: PicAdaptionApp.cpp
* Function: 图像铺满窗口与自适应窗口
* Created: 2019-02-13
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "PicAdaption.h"

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
	Mat imcv0;
	wxImage imwx;
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnOpen(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnOriginal(wxCommandEvent& event);
	void OnAdaption(wxCommandEvent& event);
	void OnOverspread(wxCommandEvent& event);
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

	if (!imgfile.empty())//字符串非空
	{
		//From opencv to wx
		imcv0 = imread(imgfile, IMREAD_UNCHANGED);//opencv读入图像
		m_textCtrl1->AppendText(wxString::Format(wxT("打开图像 %s ok.\n--------------------------------\n"), imgfile));

		Mat imcv1 = imcv0.clone();
		string str = "Channels:" + to_string(imcv1.channels());
		putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//图像上面放字符串
		imwx = wx_from_mat(imcv1);//Mat 转 wxBitmap

		m_scrolledWindow1->SetVirtualSize(imcv1.cols, imcv1.rows);//设置画面大小
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//先清除上次打开的图
		dc.DrawBitmap(imwx, 0, 0);

		falg_OnPaintPannel = TRUE;
	}
}

void picFrame::OnPaint(wxPaintEvent& event)
{
	//m_textCtrl1->AppendText(wxString::Format(wxT("调用OnPaint函数...\n")));
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_scrolledWindow1);
		m_scrolledWindow1->PrepareDC(dc);
		dc.DrawBitmap(imwx, 0, 0);
	}
}

//原始图像
void picFrame::OnOriginal(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("请先打开一张图片！！！\n")));
	else
	{
		Mat imcv2 = imcv0.clone();
		imwx = wx_from_mat(imcv2);//Mat 转 wxBitmap
		m_scrolledWindow1->SetVirtualSize(imcv2.cols, imcv2.rows);//设置画面大小
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//先清除上次打开的图
		dc.DrawBitmap(imwx, 0, 0);
		m_textCtrl1->AppendText(wxString::Format(wxT("显示原始图像ok.\n--------------------------------\n")));
	}
}

//自适应窗口
void picFrame::OnAdaption(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("请先打开一张图片！！！\n")));
	else
	{
		Mat imcv3 = imcv0.clone();
		m_scrolledWindow1->SetVirtualSize(m_scrolledWindow1->GetSize());//设置窗口画面大小
		Size size(m_scrolledWindow1->GetSize().x, m_scrolledWindow1->GetSize().y);//当前窗口大小

		double ImgRatio = 1.0 * imcv3.cols / imcv3.rows; // 图像宽高比
		double WinRatio = 1.0 * size.width / size.height; // 窗口宽高比
		m_textCtrl1->AppendText(wxString::Format(wxT("图像尺寸：(%d,%d)\t"), imcv3.cols, imcv3.rows));
		m_textCtrl1->AppendText(wxString::Format(wxT("窗口尺寸：(%d,%d)\n"), size.width, size.height));
		m_textCtrl1->AppendText(wxString::Format(wxT("图像宽高比：%f\t"), ImgRatio));
		m_textCtrl1->AppendText(wxString::Format(wxT("窗口宽高比：%f\n"), WinRatio));
		if (ImgRatio >= WinRatio)
		{
			m_textCtrl1->AppendText(wxString::Format(wxT("图像宽高比>窗口宽高比\t")));
			double scale1 = 1.0 *size.width / imcv3.cols;//假设<1
			m_textCtrl1->AppendText(wxString::Format(wxT("整体缩放比：%d/%d=%f\t"), size.width, imcv3.cols, scale1));
			resize(imcv3, imcv3, Size(size.width, int(imcv3.rows * scale1)));
		}
		else
		{
			m_textCtrl1->AppendText(wxString::Format(wxT("图像宽高比<窗口宽高比\t")));
			double scale2 = 1.0 *size.height / imcv3.rows;//假设<1
			m_textCtrl1->AppendText(wxString::Format(wxT("整体缩放比：%d/%d=%f\t"), size.height, imcv3.rows, scale2));
			resize(imcv3, imcv3, Size(int(imcv3.cols * scale2), size.height));
		}
		m_textCtrl1->AppendText(wxString::Format(wxT("调整后的图像尺寸：(%d,%d)\n"), imcv3.cols, imcv3.rows));

		imwx = wx_from_mat(imcv3);//Mat 转 wxBitmap
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//先清除上次打开的图
		dc.DrawBitmap(imwx, 0, 0);

		m_textCtrl1->AppendText(wxString::Format(wxT("图像自适应窗口ok.\n--------------------------------\n")));
	}
}

//铺满窗口
void picFrame::OnOverspread(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("请先打开一张图片！！！\n")));
	else
	{
		Mat imcv4 = imcv0.clone();

		m_scrolledWindow1->SetVirtualSize(m_scrolledWindow1->GetSize());//设置画面大小
		Size size(m_scrolledWindow1->GetSize().x, m_scrolledWindow1->GetSize().y);
		resize(imcv4, imcv4, size);

		imwx = wx_from_mat(imcv4);//Mat 转 wxBitmap
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//先清除上次打开的图
		dc.DrawBitmap(imwx, 0, 0);

		m_textCtrl1->AppendText(wxString::Format(wxT("图像铺满窗口ok.\n--------------------------------\n")));
	}
}