/*=========================================================
* Name: openpicApp.cpp
* Function: ��ͼƬ����ʾ����
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "openpic.h"//ѡ��demo2.fbp
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

//��������(�̳�����Ƶ�MyFrame1)
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


wxIMPLEMENT_APP(calcApp);//��ʼִ��

bool calcApp::OnInit()
{
	picFrame *frame = new picFrame();//��������
	frame->Show(true);//��ʾ����
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
	Mat imcv1 = imread(imgfile, IMREAD_UNCHANGED);//opencv����ͼ��
	string str = "Channels:" + to_string(imcv1.channels());
	putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//ͼ��������ַ���
	wxBitmap imwx1 = wx_from_mat(imcv1);//Mat ת wxBitmap
	m_bitmap1->SetBitmap(imwx1);//��ʾwxBitmap
	Refresh(true);
}
void picFrame::OnOpenPic2(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open image file"), "", "", "image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	wxString s;
	openFileDialog.ShowModal();
	//wxFileInputStream input_stream(openFileDialog.GetPath());
	string imgfile = (const char*)openFileDialog.GetPath().mb_str();

	Mat imcv2 = imread(imgfile, IMREAD_UNCHANGED);//opencv����ͼ��
	string str = "Channels:" + to_string(imcv2.channels());
	putText(imcv2, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//ͼ��������ַ���
	this->imwx2 = wx_from_mat(imcv2);//Mat ת wxBitmap
	wxClientDC dc(m_panel1);
	dc.Clear();//������ϴδ򿪵�ͼ
	dc.DrawBitmap(imwx2,0,0);//���Ŵ��ں�ͼƬ��ʧ

	falg_OnPaintPannel = TRUE;    
}
void picFrame::OnPaintPannel(wxPaintEvent& event)
{
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_panel1);
		dc.DrawBitmap(imwx2, 0, 0);//���������Ŵ��ں�ͼƬˢ��
	}
}
