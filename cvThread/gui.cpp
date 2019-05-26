///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(480, 360), wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	fgSizer1->Add(m_panel1, 1, wxALL | wxEXPAND, 5);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(480, 360), wxTAB_TRAVERSAL);
	m_panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	fgSizer1->Add(m_panel2, 1, wxEXPAND | wxALL, 5);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("原图"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	fgSizer1->Add(m_staticText1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("灰度图"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	fgSizer1->Add(m_staticText2, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(480, 360), wxTAB_TRAVERSAL);
	m_panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	fgSizer1->Add(m_panel3, 1, wxEXPAND | wxALL, 5);

	m_panel4 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(480, 360), wxTAB_TRAVERSAL);
	m_panel4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	fgSizer1->Add(m_panel4, 1, wxEXPAND | wxALL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("轮廓图"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	fgSizer1->Add(m_staticText3, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("SURF特征点"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	fgSizer1->Add(m_staticText4, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_toggleBtn = new wxToggleButton(this, wxID_ANY, wxT("打开摄像头"), wxPoint(-1, -1), wxSize(100, 80), 0);
	bSizer2->Add(m_toggleBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxRIGHT | wxLEFT, 5);


	bSizer1->Add(bSizer2, 0, wxALIGN_CENTER_VERTICAL, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	m_toggleBtn->Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnButton), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_toggleBtn->Disconnect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnButton), NULL, this);

}
