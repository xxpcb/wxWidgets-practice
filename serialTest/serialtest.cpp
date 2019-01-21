///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "serialtest.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(450, 300), wxDefaultSize);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_button1 = new wxButton(this, ID_SELPORT, wxT("串口号"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button1, 0, wxALL, 5);

	m_button2 = new wxButton(this, ID_BAUDRATE, wxT("波特率"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button2, 0, wxALL, 5);

	m_toggleBtn = new wxToggleButton(this, wxID_ANY, wxT("打开串口"), wxDefaultPosition, wxSize(-1, 50), 0);
	bSizer1->Add(m_toggleBtn, 0, wxALL, 5);

	m_button3 = new wxButton(this, wxID_CLEAR, wxT("清除接收框"), wxPoint(-1, -1), wxDefaultSize, 0);
	bSizer1->Add(m_button3, 0, wxALL, 5);


	fgSizer1->Add(bSizer1, 1, wxEXPAND, 5);

	m_txtRx = new wxTextCtrl(this, ID_TXTRX, wxEmptyString, wxDefaultPosition, wxSize(300, 200), wxTE_MULTILINE | wxALWAYS_SHOW_SB | wxVSCROLL);
	fgSizer1->Add(m_txtRx, 0, wxALL, 5);

	m_button4 = new wxButton(this, ID_BTNSEND, wxT("发送"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(m_button4, 0, wxALL, 5);

	m_txtSend = new wxTextCtrl(this, ID_TXTSEND, wxT("Hello!"), wxDefaultPosition, wxSize(300, 30), 0);
	fgSizer1->Add(m_txtSend, 0, wxALL, 5);


	this->SetSizer(fgSizer1);
	this->Layout();
	m_timer.SetOwner(this, ID_TIMER);

	this->Centre(wxBOTH);

	// Connect Events
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSelPort), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSetBaud), NULL, this);
	m_toggleBtn->Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggle), NULL, this);
	m_button3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnClearText), NULL, this);
	m_button4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSend), NULL, this);
	this->Connect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer));
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSelPort), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSetBaud), NULL, this);
	m_toggleBtn->Disconnect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggle), NULL, this);
	m_button3->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnClearText), NULL, this);
	m_button4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnSend), NULL, this);
	this->Disconnect(ID_TIMER, wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer));

}

