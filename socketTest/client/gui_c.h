///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_C_H__
#define __GUI_C_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_Open 1000
#define wxID_Test1 1001
#define wxID_Test2 1002
#define wxID_Test3 1003
#define wxID_Test4 1004
#define wxID_Test5 1005
#define wxID_Close 1006

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxTextCtrl* m_text;
	wxMenuBar* m_menuBar;
	wxMenu* m_menuFile;
	wxMenu* m_menuTCP;
	wxMenu* m_menuUDP;
	wxMenu* m_menuProtocols;
	wxStatusBar* m_statusBar;

	// Virtual event handlers, overide them in your derived class
	virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
	virtual void OnQuit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnOpenConnection(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTest1(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTest2(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTest3(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTest4(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTest5(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCloseConnection(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDatagram(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTestURL(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxSocket: Client"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__GUI_C_H__
