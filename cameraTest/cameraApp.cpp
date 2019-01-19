/*=========================================================
* Name: cameraApp.cpp
* Function: USB摄像头测试
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h". 
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "camera1.h"//选用demo2.fbp
//#include <wx/wfstream.h>

#include "../common/util.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

wxBitmap imwx;
VideoCapture capture;
class camApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的MyFrame1)
class camFrame : public MyFrame1
{
public:
	camFrame();
private:
	void OnToggle(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	wxDECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(camFrame, wxFrame)
EVT_TIMER(myID_TIM, camFrame::OnTimer)
END_EVENT_TABLE()

wxIMPLEMENT_APP(camApp);//开始执行

bool camApp::OnInit()
{
	wxInitAllImageHandlers();//用于打开各种格式的图片？！
	imwx.LoadFile(wxT("camera.jpg"), wxBITMAP_TYPE_JPEG);//打开封面图
	camFrame *frame = new camFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

camFrame::camFrame(): MyFrame1(NULL, wxID_ANY)
{
	wxClientDC dc(m_panel1);
	dc.DrawBitmap(imwx, 0, 0);//此处无效？
};

void camFrame::OnToggle(wxCommandEvent& event)
{
	bool state = m_toggleBtn1->GetValue();
	if (state)
	{
		m_toggleBtn1->SetLabel("关闭摄像头");
		capture.open(0);//打开摄像头 ，从摄像头获取视频
		m_timer1.Start(30);//用一个定时器，每隔300毫秒取样一次 
	}
	else
	{
		m_toggleBtn1->SetLabel("打开摄像头");
		m_timer1.Stop();//停止定时器 
		capture.release();//关闭摄像头 
		wxClientDC dc(m_panel1);
		dc.Clear();//清除相机图像
		dc.DrawBitmap(imwx, 0, 0);//显示封面图
	}
}
void camFrame::OnTimer(wxTimerEvent& event)
{
	Mat imcv;//可以绘制的图片格式 
	capture>>imcv;// 抓取一帧画面 
	wxBitmap imwx = wx_from_mat(imcv);//Mat 转 wxBitmap

	wxClientDC dc(m_panel1);
	dc.DrawBitmap(imwx, 0, 0);
}
