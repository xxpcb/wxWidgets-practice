///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_s.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_text = new wxTextCtrl(this, wxID_ANY, wxT("Welcome to wxSocket demo: Server\n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	bSizer1->Add(m_text, 1, wxALL | wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_menuBar = new wxMenuBar(0);
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem(m_menuFile, wxID_ANY, wxString(wxT("Set file path")), wxEmptyString, wxITEM_NORMAL);
	m_menuFile->Append(m_menuItem5);

	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem(m_menuFile, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menuFile->Append(m_menuItem1);

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem(m_menuFile, wxID_ANY, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	m_menuFile->Append(m_menuItem2);

	m_menuBar->Append(m_menuFile, wxT("File"));

	m_menuTest = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem(m_menuTest, wxID_ANY, wxString(wxT("Wait connect")), wxEmptyString, wxITEM_NORMAL);
	m_menuTest->Append(m_menuItem3);

	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem(m_menuTest, wxID_ANY, wxString(wxT("UDP Test")), wxEmptyString, wxITEM_NORMAL);
	m_menuTest->Append(m_menuItem4);

	m_menuBar->Append(m_menuTest, wxT("Test"));

	this->SetMenuBar(m_menuBar);

	m_statusBar = this->CreateStatusBar(2, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnSetPath));
	this->Connect(m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnAbout));
	this->Connect(m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
	this->Connect(m_menuItem3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnWaitForAccept));
	this->Connect(m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnUDPTest));
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnSetPath));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnAbout));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnWaitForAccept));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnUDPTest));

}
