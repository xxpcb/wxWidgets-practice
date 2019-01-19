/*=========================================================
* Name: contoursApp.cpp
* Function: ����ͼ����������
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "contours.h"//ѡ��demo2.fbp
//#include <wx/wfstream.h>

#include "../common/util.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

bool falg_OnPaint = FALSE;
bool falg_OnScroll = FALSE;
Mat g_srcImage;//ԭͼ
Mat g_grayImage;//�Ҷ�ͼ
int g_nThresh = 80;//��ֵ
int g_nThresh_max = 255;//�����ֵ
RNG g_rng(12345);
Mat g_cannyMat_output;//���ͼ
vector<vector<Point>> g_vContours;//��������
vector<Vec4i> g_vHierarchy;//���

class contoursApp : public wxApp
{
public:
	virtual bool OnInit();
};

//��������(�̳�����Ƶ�demoFrame)
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

wxIMPLEMENT_APP(contoursApp);//��ʼִ��

bool contoursApp::OnInit()
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

	// ������Դͼ��
	g_srcImage = imread(imgfile, IMREAD_UNCHANGED);//opencv����ͼ��
	// ��ת�ɻҶȲ�ģ�������롿
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//ת�ɻҶ�ͼ
	blur(g_grayImage, g_grayImage, Size(3, 3));//�˲�
    //  ��Mat ת wxBitmap��
	imwx1 = wx_from_mat(g_srcImage);

	wxClientDC dc(m_panel1);
	dc.Clear();//������ϴδ򿪵�ͼ
	dc.DrawBitmap(imwx1, 0, 0);//���Ŵ��ں�ͼƬ��ʧ

	ImgProcess_Thresh();

	falg_OnPaint = TRUE;
	falg_OnScroll = TRUE;
}

void picFrame::OnPaint1(wxPaintEvent& event)
{
	if (falg_OnPaint)
	{
		wxPaintDC dc(m_panel1);
		dc.DrawBitmap(imwx1, 0, 0);//���������Ŵ��ں�ͼƬˢ��
	}
}
void picFrame::OnPaint2(wxPaintEvent& event)
{
	if (falg_OnPaint)
	{
		wxPaintDC dc(m_panel2);
		dc.DrawBitmap(imwx2, 0, 0);//���������Ŵ��ں�ͼƬˢ��
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
	Close(true);//�ر���������
}
void picFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a findContours(OpenCV) test demo",//�����Ϣ��������Ϣ��
		"About This demo", wxOK | wxICON_INFORMATION);//����Ϣ�򣩱���
}

void picFrame::ImgProcess_Thresh()
{
	// �á�Canny���ӡ�����Ե
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);
	// ��Ѱ��������
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// �����������
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);//ȫ0����
	for (int i = 0; i < g_vContours.size(); i++)//����ѭ��
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//����ֵ
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}
	wxClientDC dc(m_panel2);
	imwx2 = wx_from_mat(drawing);
	dc.DrawBitmap(imwx2, 0, 0);//���Ŵ��ں�ͼƬ��ʧ
}
