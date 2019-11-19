///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "mympPane.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	BasicMPPane* mpPane;
	wxTimer m_timer1;

	// Virtual event handlers, overide them in your derived class
	virtual void OnFit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnToggleGrid(wxCommandEvent& event) { event.Skip(); }
	virtual void OnToggleScrollbars(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTimer(wxTimerEvent& event) { event.Skip(); }


public:
	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(900, 700), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__GUI_H__
