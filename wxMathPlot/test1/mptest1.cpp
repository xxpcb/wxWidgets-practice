/*=========================================================
* Name: mptest1.cpp
* Function: MathPlot二维图形显示测试1
* Created: 2019-11-19
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/
#include <wx/wxprec.h>
#include "mathplot.h"
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>
#include <wx/print.h>
#include <wx/filename.h>
#include <math.h>

// Memory leak debugging
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// derived classes

class MySIN;
class MyFrame;
class MyApp;

// MySIN

class MySIN : public mpFX
{
	double m_freq, m_amp;
public:
	MySIN(double freq, double amp) : mpFX(wxT("f(x) = SIN(x)"), mpALIGN_LEFT) { m_freq = freq; m_amp = amp; m_drawOutsideMargins = false; }
	virtual double GetY(double x) { return m_amp * sin(x / 6.283185 / m_freq); }
	virtual double GetMinY() { return -m_amp; }
	virtual double GetMaxY() { return  m_amp; }
};


// MyFrame

class MyFrame : public wxFrame
{
public:
	MyFrame();

	void OnQuit(wxCommandEvent &event);
	void OnFit(wxCommandEvent &event);
	void OnToggleGrid(wxCommandEvent &event);
	void OnToggleScrollbars(wxCommandEvent& event);
	void OnToggleInfoLayer(wxCommandEvent& event);

	mpWindow        *m_plot;
	wxTextCtrl      *m_log;

private:
	bool ticks;
	mpInfoCoords *nfo; // mpInfoLayer* nfo;
	DECLARE_DYNAMIC_CLASS(MyFrame)
	DECLARE_EVENT_TABLE()
};

// MyApp

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

// main program

IMPLEMENT_APP(MyApp)

// MyFrame

enum {
	ID_QUIT = 108,
	ID_TOGGLE_GRID,
	ID_TOGGLE_SCROLLBARS,
	ID_TOGGLE_INFO,
	ID_BLACK_THEME
};

IMPLEMENT_DYNAMIC_CLASS(MyFrame, wxFrame)

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_QUIT, MyFrame::OnQuit)
EVT_MENU(mpID_FIT, MyFrame::OnFit)
EVT_MENU(ID_TOGGLE_GRID, MyFrame::OnToggleGrid)
EVT_MENU(ID_TOGGLE_SCROLLBARS, MyFrame::OnToggleScrollbars)
EVT_MENU(ID_TOGGLE_INFO, MyFrame::OnToggleInfoLayer)
END_EVENT_TABLE()

MyFrame::MyFrame()
	: wxFrame((wxFrame *)NULL, -1, wxT("wxWindows mathplot sample"), wxDefaultPosition, wxSize(500, 500))
{
	wxMenu *file_menu = new wxMenu();
	wxMenu *view_menu = new wxMenu();

	file_menu->Append(ID_QUIT, wxT("E&xit\tAlt-X"));

	view_menu->Append(mpID_FIT, wxT("&Fit bounding box"), wxT("Set plot view to show all items"));
	view_menu->Append(ID_TOGGLE_GRID, wxT("Toggle grid/ticks"));
	view_menu->AppendCheckItem(ID_TOGGLE_SCROLLBARS, wxT("Show Scroll Bars"));
	view_menu->AppendCheckItem(ID_TOGGLE_INFO, wxT("Show overlay info box"));

	wxMenuBar *menu_bar = new wxMenuBar();
	menu_bar->Append(file_menu, wxT("&File"));
	menu_bar->Append(view_menu, wxT("&View"));

	SetMenuBar(menu_bar);
	CreateStatusBar(1);

	// Create a 【mpFXYVector layer】
	mpFXYVector* vectorLayer = new mpFXYVector(_("Vector"));
	// Create two vectors for x,y and fill them with data
	std::vector<double> vectorx, vectory;
	double xcoord;
	for (unsigned int p = 0; p < 100; p++) 
	{
		xcoord = ((double)p - 50.0)*5.0;//x:-250~250
		vectorx.push_back(xcoord);
		vectory.push_back(0.0001*pow(xcoord, 3));//y=0.001*x^3
	}
	vectorLayer->SetData(vectorx, vectory);//导入数据
	vectorLayer->SetContinuity(true);//连续线
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);//蓝色线
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);//开始画？

	
	//【mathPlot窗口】
	m_plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
	mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);//底部x轴
	mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true);//左侧y轴
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	xaxis->SetFont(graphFont);//图标轴字体
	yaxis->SetFont(graphFont);
	xaxis->SetDrawOutsideMargins(false);
	yaxis->SetDrawOutsideMargins(false);

	m_plot->SetMargins(30, 30, 50, 100);//边缘 top, right, bottom, left
	m_plot->AddLayer(xaxis);//将轴添加到窗口中
	m_plot->AddLayer(yaxis);
	m_plot->AddLayer(new MySIN(10.0, 520.0));//将sin函数添加到窗口中
	m_plot->AddLayer(vectorLayer);//将自定义的vector函数添加到窗口中
	m_plot->AddLayer(new mpText(wxT("mpText sample"), 10, 10));//添加文字

	//log窗口
	m_log = new wxTextCtrl(this, -1, wxT("This is the log window.\n"), wxPoint(0, 0), wxSize(100, 100), wxTE_MULTILINE);
	wxLog *old_log = wxLog::SetActiveTarget(new wxLogTextCtrl(m_log));
	delete old_log;

	//BoxSizer
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	topsizer->Add(m_plot, 1, wxEXPAND);//添加mathPlot窗口
	topsizer->Add(m_log, 0, wxEXPAND);//添加log窗口

	SetAutoLayout(TRUE);
	SetSizer(topsizer);
	ticks = true;

	m_plot->EnableDoubleBuffer(true);
	m_plot->SetMPScrollbars(false);
	m_plot->Fit();

}

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
	Close(TRUE);
}

void MyFrame::OnFit(wxCommandEvent &WXUNUSED(event))
{
	m_plot->Fit();
}


void MyFrame::OnToggleGrid(wxCommandEvent &WXUNUSED(event))
{
	ticks = !ticks;
	((mpScaleX*)(m_plot->GetLayer(0)))->SetTicks(ticks);
	((mpScaleY*)(m_plot->GetLayer(1)))->SetTicks(ticks);
	m_plot->UpdateAll();
}

void MyFrame::OnToggleScrollbars(wxCommandEvent& event)
{
	if (event.IsChecked())
		m_plot->SetMPScrollbars(true);
	else
		m_plot->SetMPScrollbars(false);
	event.Skip();
}

void MyFrame::OnToggleInfoLayer(wxCommandEvent& event)
{
	if (event.IsChecked())
		nfo->SetVisible(true);
	else
		nfo->SetVisible(false);
	m_plot->UpdateAll();
	event.Skip();
}


//-----------------------------------------------------------------------------
// MyApp
//-----------------------------------------------------------------------------

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	wxFrame *frame = new MyFrame();
	frame->Show(TRUE);

	return TRUE;
}

