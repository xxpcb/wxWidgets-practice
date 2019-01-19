///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "contours.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(850, 700), wxDefaultSize);

	m_menubar1 = new wxMenuBar(0);
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem(m_menu1, wxID_OPEN, wxString(wxT("Open")), wxEmptyString, wxITEM_NORMAL);
	m_menu1->Append(m_menuItem1);

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem(m_menu1, wxID_EXIT, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	m_menu1->Append(m_menuItem2);

	m_menubar1->Append(m_menu1, wxT("File"));

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem(m_menu2, wxID_ABOUT, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem3);

	m_menubar1->Append(m_menu2, wxT("Help"));

	this->SetMenuBar(m_menubar1);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	bSizer2->SetMinSize(wxSize(800, 50));
	m_slider1 = new wxSlider(this, wxID_ANY, 150, 0, 255, wxDefaultPosition, wxSize(700, 50), wxSL_BOTTOM | wxSL_HORIZONTAL | wxSL_LABELS | wxSL_TOP);
	bSizer2->Add(m_slider1, 0, wxALL, 5);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("ãÐÖµ"), wxPoint(-1, -1), wxSize(80, 30), wxALIGN_CENTRE);
	m_staticText1->Wrap(-1);
	m_staticText1->SetFont(wxFont(18, 70, 90, 90, false, wxEmptyString));

	bSizer2->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer1->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	bSizer3->SetMinSize(wxSize(800, 600));
	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, -1), wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	bSizer3->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, -1), wxTAB_TRAVERSAL);
	m_panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	bSizer3->Add(m_panel2, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_statusBar1 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	m_slider1->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_panel1->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint1), NULL, this);
	m_panel2->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint2), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_slider1->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_slider1->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::OnScroll_Th), NULL, this);
	m_panel1->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint1), NULL, this);
	m_panel2->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint2), NULL, this);

}


