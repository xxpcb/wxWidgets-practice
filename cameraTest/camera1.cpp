///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "camera1.h"


///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480), wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	m_panel1->SetMinSize(wxSize(640, 480));

	bSizer1->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_toggleBtn1 = new wxToggleButton(this, wxID_ANY, wxT("´ò¿ªÉãÏñÍ·"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_toggleBtn1, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);
	m_timer1.SetOwner(this, myID_TIM);

	this->Centre(wxBOTH);

	// Connect Events
	m_toggleBtn1->Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggle), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_toggleBtn1->Disconnect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnToggle), NULL, this);

}
