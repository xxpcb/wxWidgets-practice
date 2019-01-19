/*=========================================================
* Name: contoursApp.cpp
* Function: 计算平方数测试
* Created: 2019-01-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "calc.h"//选用demo2.fbp

class calcApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的demoFrame)
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

wxIMPLEMENT_APP(calcApp);//开始执行

bool calcApp::OnInit()
{
	calcFrame *frame = new calcFrame();//窗口名称
	frame->Show(true);//显示窗口
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
	Close(true);//关闭整个窗口
}
//About子窗口
void calcFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is my wxWidgets' test demo",//输出信息（弹出信息框）
		"About This demo", wxOK | wxICON_INFORMATION);//（信息框）标题
}