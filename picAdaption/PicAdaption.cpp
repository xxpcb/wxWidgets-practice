///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PicAdaption.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_scrolledWindow1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480), wxHSCROLL | wxVSCROLL);
	m_scrolledWindow1->SetScrollRate(5, 5);
	m_scrolledWindow1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	bSizer2->Add(m_scrolledWindow1, 1, wxEXPAND | wxALL, 5);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(640, 100), wxTE_MULTILINE);
	bSizer2->Add(m_textCtrl1, 0, wxALL | wxEXPAND, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	m_button1 = new wxButton(this, wxID_OPEN, wxT("打开图片"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(m_button1, 0, wxALL, 5);

	m_button2 = new wxButton(this, wxID_ANY, wxT("原始图像"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(m_button2, 0, wxALL, 5);

	m_button3 = new wxButton(this, wxID_ANY, wxT("自适应窗口"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(m_button3, 0, wxALL, 5);

	m_button4 = new wxButton(this, wxID_ANY, wxT("铺满窗口"), wxPoint(-1, -1), wxDefaultSize, 0);
	bSizer3->Add(m_button4, 0, wxALL, 5);


	bSizer1->Add(bSizer3, 0, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	m_scrolledWindow1->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpen), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOriginal), NULL, this);
	m_button3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnAdaption), NULL, this);
	m_button4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOverspread), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_scrolledWindow1->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOpen), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOriginal), NULL, this);
	m_button3->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnAdaption), NULL, this);
	m_button4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnOverspread), NULL, this);

}
