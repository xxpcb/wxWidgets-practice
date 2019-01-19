///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "calc.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(330, 250), wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	bSizer1->SetMinSize(wxSize(300, 200));
	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("输入数字"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	m_staticText1->Wrap(-1);
	bSizer1->Add(m_staticText1, 1, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_textCtrl1, 1, wxALL | wxEXPAND, 5);

	m_button1 = new wxButton(this, wxID_ANY, wxT("计算平方"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button1, 1, wxALL | wxEXPAND, 5);

	m_textCtrl2 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_textCtrl2, 1, wxALL | wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_menubar1 = new wxMenuBar(0);
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem(m_menu1, wxID_EXIT, wxString(wxT("退出")), wxEmptyString, wxITEM_NORMAL);
	m_menu1->Append(m_menuItem1);

	m_menubar1->Append(m_menu1, wxT("文件"));

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem(m_menu2, wxID_ABOUT, wxString(wxT("关于")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem2);

	m_menubar1->Append(m_menu2, wxT("帮助"));

	this->SetMenuBar(m_menubar1);

	m_statusBar1 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnCalcSquare), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnCalcSquare), NULL, this);

}
