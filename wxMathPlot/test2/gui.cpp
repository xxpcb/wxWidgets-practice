///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	mpPane = new BasicMPPane(this);
	mpPane->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));

	bSizer1->Add(mpPane, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_button1 = new wxButton(this, wxID_ANY, wxT("Fit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button1, 0, wxALL, 5);

	m_button2 = new wxButton(this, wxID_ANY, wxT("ToggleGrid"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button2, 0, wxALL, 5);

	m_button3 = new wxButton(this, wxID_ANY, wxT("Toggle\nScrollbars"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button3, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 0, 0, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_timer1.SetOwner(this, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnFit), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggleGrid), NULL, this);
	m_button3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggleScrollbars), NULL, this);
	this->Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer));
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnFit), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggleGrid), NULL, this);
	m_button3->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggleScrollbars), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(MyFrame1::OnTimer));

}
