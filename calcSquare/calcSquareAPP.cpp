/*=========================================================
* Name: contoursApp.cpp
* Function: ����ƽ��������
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "calc.h"//ѡ��demo2.fbp

class calcApp : public wxApp
{
public:
	virtual bool OnInit();
};

//��������(�̳�����Ƶ�demoFrame)
class calcFrame : public MyFrame1
{
public:
	calcFrame() : MyFrame1(NULL, wxID_ANY) {};
private:
	void OnCalcSquare(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(calcFrame, wxFrame)
EVT_MENU(wxID_EXIT, calcFrame::OnExit)//File->Quit
EVT_MENU(wxID_ABOUT, calcFrame::OnAbout)//Help-About
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(calcApp);//��ʼִ��

bool calcApp::OnInit()
{
	calcFrame *frame = new calcFrame();//��������
	frame->Show(true);//��ʾ����
	return true;
}

void calcFrame::OnCalcSquare(wxCommandEvent& event)
{
	wxString num_str = this->m_textCtrl1->GetValue();
	int num = wxAtoi(num_str);
	wxString mystring = wxString::Format(wxT("%i"), num*num);
	this->m_textCtrl2->SetValue(mystring);
}
//Quit
void calcFrame::OnExit(wxCommandEvent& event)
{
	Close(true);//�ر���������
}
//About�Ӵ���
void calcFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is my wxWidgets' test demo",//�����Ϣ��������Ϣ��
		"About This demo", wxOK | wxICON_INFORMATION);//����Ϣ�򣩱���
}