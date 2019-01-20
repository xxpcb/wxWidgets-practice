///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "bigPic.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	m_scrolledWindow1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480), wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	m_scrolledWindow1->SetScrollRate(5, 5);
	m_scrolledWindow1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	bSizer1->Add(m_scrolledWindow1, 1, wxEXPAND | wxALL, 5);

	m_button1 = new wxButton(this, wxID_OPEN, wxT("´ò¿ªÍ¼Æ¬"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button1, 0, wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	m_scrolledWindow1->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpen), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_scrolledWindow1->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpen), NULL, this);

}

