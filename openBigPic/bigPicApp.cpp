/*=========================================================
* Name: openpicApp.cpp
* Function: �򿪴�ͼƬ����ʾ���ԣ��������ڲ��ԣ�
* Created: 2019-01-20
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "bigpic.h"//ѡ��demo2.fbp

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

//��������(�̳�����Ƶ�MyFrame1)
class picFrame : public MyFrame1
{
public:
	wxImage imwx;
	picFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnOpen(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
};


wxIMPLEMENT_APP(calcApp);//��ʼִ��

bool calcApp::OnInit()
{
	picFrame *frame = new picFrame();//��������
	frame->Show(true);//��ʾ����
	return true;
}

void picFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxString s;
	openFileDialog.ShowModal();
	string imgfile = (const char*)openFileDialog.GetPath().mb_str();

	//From opencv to wx
	Mat imcv1 = imread(imgfile, IMREAD_UNCHANGED);//opencv����ͼ��
	string str = "Channels:" + to_string(imcv1.channels());
	putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//ͼ��������ַ���
	imwx = wx_from_mat(imcv1);//Mat ת wxBitmap

	m_scrolledWindow1->SetVirtualSize(imcv1.cols, imcv1.rows);//���û����С
	wxClientDC dc(m_scrolledWindow1);
	dc.Clear();//������ϴδ򿪵�ͼ
	//m_scrolledWindow1->PrepareDC(dc);
	//m_scrolledWindow1->DoPrepareDC(dc);
	dc.DrawBitmap(imwx, 0, 0);//���Ŵ��ں�ͼƬ��ʧ

	falg_OnPaintPannel = TRUE;
}

void picFrame::OnPaint(wxPaintEvent& event)
{
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_scrolledWindow1);
		//m_scrolledWindow1->DoPrepareDC(dc);//�˾����¾�������ͬ��
		m_scrolledWindow1->PrepareDC(dc);
		dc.DrawBitmap(imwx, 0, 0);
	}
}
