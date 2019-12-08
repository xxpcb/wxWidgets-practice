///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_c.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_text = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	bSizer1->Add(m_text, 1, wxALL | wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_menuBar = new wxMenuBar(0);
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem(m_menuFile, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menuFile->Append(m_menuItem1);

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem(m_menuFile, wxID_ANY, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	m_menuFile->Append(m_menuItem2);

	m_menuBar->Append(m_menuFile, wxT("File"));

	m_menuTCP = new wxMenu();
	wxMenuItem* m_menuItem_Open;
	m_menuItem_Open = new wxMenuItem(m_menuTCP, wxID_Open, wxString(wxT("Open session")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Open);

	m_menuTCP->AppendSeparator();

	wxMenuItem* m_menuItem_Test1;
	m_menuItem_Test1 = new wxMenuItem(m_menuTCP, wxID_Test1, wxString(wxT("Test1 (short text)")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Test1);

	wxMenuItem* m_menuItem_Test2;
	m_menuItem_Test2 = new wxMenuItem(m_menuTCP, wxID_Test2, wxString(wxT("Test2 (arbitrary text)")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Test2);

	wxMenuItem* m_menuItem_Test3;
	m_menuItem_Test3 = new wxMenuItem(m_menuTCP, wxID_Test3, wxString(wxT("Test3 (large text)")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Test3);

	m_menuTCP->AppendSeparator();

	wxMenuItem* m_menuItem_Test4;
	m_menuItem_Test4 = new wxMenuItem(m_menuTCP, wxID_Test4, wxString(wxT("Test4 (Send File)")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Test4);

	wxMenuItem* m_menuItem_Test5;
	m_menuItem_Test5 = new wxMenuItem(m_menuTCP, wxID_Test5, wxString(wxT("Test5 (Receive File)")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Test5);

	m_menuTCP->AppendSeparator();

	wxMenuItem* m_menuItem_Close;
	m_menuItem_Close = new wxMenuItem(m_menuTCP, wxID_Close, wxString(wxT("Close session")), wxEmptyString, wxITEM_NORMAL);
	m_menuTCP->Append(m_menuItem_Close);

	m_menuBar->Append(m_menuTCP, wxT("TCP"));

	m_menuUDP = new wxMenu();
	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem(m_menuUDP, wxID_ANY, wxString(wxT("Datagram test")), wxEmptyString, wxITEM_NORMAL);
	m_menuUDP->Append(m_menuItem8);

	m_menuBar->Append(m_menuUDP, wxT("UDP"));

	m_menuProtocols = new wxMenu();
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem(m_menuProtocols, wxID_ANY, wxString(wxT("Test URL")), wxEmptyString, wxITEM_NORMAL);
	m_menuProtocols->Append(m_menuItem9);

	m_menuBar->Append(m_menuProtocols, wxT("Protocols"));

	this->SetMenuBar(m_menuBar);

	m_statusBar = this->CreateStatusBar(2, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnAbout));
	this->Connect(m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
	this->Connect(m_menuItem_Open->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnOpenConnection));
	this->Connect(m_menuItem_Test1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest1));
	this->Connect(m_menuItem_Test2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest2));
	this->Connect(m_menuItem_Test3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest3));
	this->Connect(m_menuItem_Test4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest4));
	this->Connect(m_menuItem_Test5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest5));
	this->Connect(m_menuItem_Close->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnCloseConnection));
	this->Connect(m_menuItem8->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnDatagram));
	this->Connect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTestURL));
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnAbout));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
	this->Disconnect(wxID_Open, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnOpenConnection));
	this->Disconnect(wxID_Test1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest1));
	this->Disconnect(wxID_Test2, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest2));
	this->Disconnect(wxID_Test3, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest3));
	this->Disconnect(wxID_Test4, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest4));
	this->Disconnect(wxID_Test5, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTest5));
	this->Disconnect(wxID_Close, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnCloseConnection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnDatagram));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnTestURL));

}
