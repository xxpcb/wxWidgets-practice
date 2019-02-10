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

	/*construction*/
	wxInitAllImageHandlers();
	drawPane = new wxImagePanel(this, wxT("../2.jpg"), wxBITMAP_TYPE_JPEG);
	//drawPane = new wxImagePanel(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480), wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL);
	//drawPane->LoadFile(wxT("../2.jpg"), wxBITMAP_TYPE_JPEG);
	drawPane->SetVirtualSize(1920, 1080);//设置画面大小
	/*construction*/

	/*settings*/
	drawPane->SetScrollRate(5, 5);//设置滚动间距
	/*settings*/

	drawPane->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	drawPane->SetMinSize(wxSize(640, 480));

	bSizer1->Add(drawPane, 1, wxALL | wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	drawPane->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	drawPane->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::OnPaint), NULL, this);

}
