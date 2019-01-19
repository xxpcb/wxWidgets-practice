///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "openpic.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(850, 650), wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	bSizer2->SetMinSize(wxSize(-1, 40));
	m_button1 = new wxButton(this, wxID_ANY, wxT("打开1"), wxPoint(0, 0), wxSize(100, 30), 0);
	m_button1->SetMinSize(wxSize(100, 30));

	bSizer2->Add(m_button1, 1, wxALL | wxALIGN_BOTTOM | wxEXPAND, 5);

	m_button2 = new wxButton(this, wxID_ANY, wxT("打开2"), wxPoint(0, 0), wxSize(100, 30), 0);
	m_button2->SetMinSize(wxSize(100, 30));

	bSizer2->Add(m_button2, 1, wxALL, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(100, -1), 0);
	m_bitmap1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));

	bSizer3->Add(m_bitmap1, 1, wxALL | wxEXPAND, 5);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, -1), wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	bSizer3->Add(m_panel1, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpenPic1), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpenPic2), NULL, this);
	m_panel1->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaintPannel), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpenPic1), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpenPic2), NULL, this);
	m_panel1->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaintPannel), NULL, this);

}
