/*=========================================================
* Name: cameraApp.cpp
* Function: USB����ͷ����
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h". 
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "camera1.h"//ѡ��demo2.fbp
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

//��������(�̳�����Ƶ�MyFrame1)
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

wxIMPLEMENT_APP(camApp);//��ʼִ��

bool camApp::OnInit()
{
	wxInitAllImageHandlers();//���ڴ򿪸��ָ�ʽ��ͼƬ����
	imwx.LoadFile(wxT("camera.jpg"), wxBITMAP_TYPE_JPEG);//�򿪷���ͼ
	camFrame *frame = new camFrame();//��������
	frame->Show(true);//��ʾ����
	return true;
}

camFrame::camFrame(): MyFrame1(NULL, wxID_ANY)
{
	wxClientDC dc(m_panel1);
	dc.DrawBitmap(imwx, 0, 0);//�˴���Ч��
};

void camFrame::OnToggle(wxCommandEvent& event)
{
	bool state = m_toggleBtn1->GetValue();
	if (state)
	{
		m_toggleBtn1->SetLabel("�ر�����ͷ");
		capture.open(0);//������ͷ ��������ͷ��ȡ��Ƶ
		m_timer1.Start(30);//��һ����ʱ����ÿ��300����ȡ��һ�� 
	}
	else
	{
		m_toggleBtn1->SetLabel("������ͷ");
		m_timer1.Stop();//ֹͣ��ʱ�� 
		capture.release();//�ر�����ͷ 
		wxClientDC dc(m_panel1);
		dc.Clear();//������ͼ��
		dc.DrawBitmap(imwx, 0, 0);//��ʾ����ͼ
	}
}
void camFrame::OnTimer(wxTimerEvent& event)
{
	Mat imcv;//���Ի��Ƶ�ͼƬ��ʽ 
	capture>>imcv;// ץȡһ֡���� 
	wxBitmap imwx = wx_from_mat(imcv);//Mat ת wxBitmap

	wxClientDC dc(m_panel1);
	dc.DrawBitmap(imwx, 0, 0);
}
