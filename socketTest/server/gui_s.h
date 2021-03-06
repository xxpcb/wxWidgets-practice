///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_S_H__
#define __GUI_S_H__

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
	wxMenu* m_menuTest;
	wxStatusBar* m_statusBar;

	// Virtual event handlers, overide them in your derived class
	virtual void OnSetPath(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
	virtual void OnQuit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWaitForAccept(wxCommandEvent& event) { event.Skip(); }
	virtual void OnUDPTest(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxSocket: Server"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__GUI_S_H__
