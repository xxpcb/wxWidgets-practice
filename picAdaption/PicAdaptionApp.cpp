/*=========================================================
* Name: PicAdaptionApp.cpp
* Function: ͼ����������������Ӧ����
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

//��������(�̳�����Ƶ�MyFrame1)
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

	if (!imgfile.empty())//�ַ����ǿ�
	{
		//From opencv to wx
		imcv0 = imread(imgfile, IMREAD_UNCHANGED);//opencv����ͼ��
		m_textCtrl1->AppendText(wxString::Format(wxT("��ͼ�� %s ok.\n--------------------------------\n"), imgfile));

		Mat imcv1 = imcv0.clone();
		string str = "Channels:" + to_string(imcv1.channels());
		putText(imcv1, str, Point(10, 50), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(128, 0, 128), 1.0);//ͼ��������ַ���
		imwx = wx_from_mat(imcv1);//Mat ת wxBitmap

		m_scrolledWindow1->SetVirtualSize(imcv1.cols, imcv1.rows);//���û����С
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//������ϴδ򿪵�ͼ
		dc.DrawBitmap(imwx, 0, 0);

		falg_OnPaintPannel = TRUE;
	}
}

void picFrame::OnPaint(wxPaintEvent& event)
{
	//m_textCtrl1->AppendText(wxString::Format(wxT("����OnPaint����...\n")));
	if (falg_OnPaintPannel)
	{
		wxPaintDC dc(m_scrolledWindow1);
		m_scrolledWindow1->PrepareDC(dc);
		dc.DrawBitmap(imwx, 0, 0);
	}
}

//ԭʼͼ��
void picFrame::OnOriginal(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("���ȴ�һ��ͼƬ������\n")));
	else
	{
		Mat imcv2 = imcv0.clone();
		imwx = wx_from_mat(imcv2);//Mat ת wxBitmap
		m_scrolledWindow1->SetVirtualSize(imcv2.cols, imcv2.rows);//���û����С
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//������ϴδ򿪵�ͼ
		dc.DrawBitmap(imwx, 0, 0);
		m_textCtrl1->AppendText(wxString::Format(wxT("��ʾԭʼͼ��ok.\n--------------------------------\n")));
	}
}

//����Ӧ����
void picFrame::OnAdaption(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("���ȴ�һ��ͼƬ������\n")));
	else
	{
		Mat imcv3 = imcv0.clone();
		m_scrolledWindow1->SetVirtualSize(m_scrolledWindow1->GetSize());//���ô��ڻ����С
		Size size(m_scrolledWindow1->GetSize().x, m_scrolledWindow1->GetSize().y);//��ǰ���ڴ�С

		double ImgRatio = 1.0 * imcv3.cols / imcv3.rows; // ͼ���߱�
		double WinRatio = 1.0 * size.width / size.height; // ���ڿ�߱�
		m_textCtrl1->AppendText(wxString::Format(wxT("ͼ��ߴ磺(%d,%d)\t"), imcv3.cols, imcv3.rows));
		m_textCtrl1->AppendText(wxString::Format(wxT("���ڳߴ磺(%d,%d)\n"), size.width, size.height));
		m_textCtrl1->AppendText(wxString::Format(wxT("ͼ���߱ȣ�%f\t"), ImgRatio));
		m_textCtrl1->AppendText(wxString::Format(wxT("���ڿ�߱ȣ�%f\n"), WinRatio));
		if (ImgRatio >= WinRatio)
		{
			m_textCtrl1->AppendText(wxString::Format(wxT("ͼ���߱�>���ڿ�߱�\t")));
			double scale1 = 1.0 *size.width / imcv3.cols;//����<1
			m_textCtrl1->AppendText(wxString::Format(wxT("�������űȣ�%d/%d=%f\t"), size.width, imcv3.cols, scale1));
			resize(imcv3, imcv3, Size(size.width, int(imcv3.rows * scale1)));
		}
		else
		{
			m_textCtrl1->AppendText(wxString::Format(wxT("ͼ���߱�<���ڿ�߱�\t")));
			double scale2 = 1.0 *size.height / imcv3.rows;//����<1
			m_textCtrl1->AppendText(wxString::Format(wxT("�������űȣ�%d/%d=%f\t"), size.height, imcv3.rows, scale2));
			resize(imcv3, imcv3, Size(int(imcv3.cols * scale2), size.height));
		}
		m_textCtrl1->AppendText(wxString::Format(wxT("�������ͼ��ߴ磺(%d,%d)\n"), imcv3.cols, imcv3.rows));

		imwx = wx_from_mat(imcv3);//Mat ת wxBitmap
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//������ϴδ򿪵�ͼ
		dc.DrawBitmap(imwx, 0, 0);

		m_textCtrl1->AppendText(wxString::Format(wxT("ͼ������Ӧ����ok.\n--------------------------------\n")));
	}
}

//��������
void picFrame::OnOverspread(wxCommandEvent& event)
{
	if (!falg_OnPaintPannel)
		m_textCtrl1->AppendText(wxString::Format(wxT("���ȴ�һ��ͼƬ������\n")));
	else
	{
		Mat imcv4 = imcv0.clone();

		m_scrolledWindow1->SetVirtualSize(m_scrolledWindow1->GetSize());//���û����С
		Size size(m_scrolledWindow1->GetSize().x, m_scrolledWindow1->GetSize().y);
		resize(imcv4, imcv4, size);

		imwx = wx_from_mat(imcv4);//Mat ת wxBitmap
		wxClientDC dc(m_scrolledWindow1);
		dc.Clear();//������ϴδ򿪵�ͼ
		dc.DrawBitmap(imwx, 0, 0);

		m_textCtrl1->AppendText(wxString::Format(wxT("ͼ����������ok.\n--------------------------------\n")));
	}
}