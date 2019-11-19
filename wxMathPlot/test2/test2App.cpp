/*=========================================================
* Name: test2App.cpp
* Function: MathPlot二维图形显示测试2
* Created: 2019-11-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include <string>
#include "gui.h"


class myApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的MyFrame1)
class myFrame : public MyFrame1
{
public:
	myFrame() : MyFrame1(NULL, wxID_ANY) {};
	void OnFit(wxCommandEvent &event);
	void OnToggleGrid(wxCommandEvent &event);
	void OnToggleScrollbars(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);//定时器
};

wxIMPLEMENT_APP(myApp);//开始执行

bool myApp::OnInit()
{
	myFrame *frame = new myFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

void myFrame::OnFit(wxCommandEvent &event)
{
	m_timer1.Start(100);
	mpPane->Fit();
}


//void BasicMPPane::OnToggleGrid(wxCommandEvent &WXUNUSED(event))
void myFrame::OnToggleGrid(wxCommandEvent &event)
{
	mpPane->ToggleGrid();
}

void myFrame::OnToggleScrollbars(wxCommandEvent& event)
{
	mpPane->ToggleScrollbars();
}


double A = 0.0002;
//定时器
void myFrame::OnTimer(wxTimerEvent& event)
{
	A += 0.0002;
	if (A > 0.01) A = 0.002;
	double xcoord;
	mpPane->vectorx.clear();
	mpPane->vectory.clear();
	for (unsigned int p = 0; p < 100; p++)
	{
		xcoord = ((double)p - 50.0)*5.0;//x:-250~250
		mpPane->vectorx.push_back(xcoord);
		mpPane->vectory.push_back(A*pow(xcoord, 2));//y=0.001*x^3
	}
	mpPane->vectorLayer->SetData(mpPane->vectorx, mpPane->vectory);//导入数据
	mpPane->m_plot->UpdateAll();//更新
}

