///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define myID_TIM 1000

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxPanel* m_panel1;
	wxTimer m_timer1;

	// Virtual event handlers, overide them in your derived class
	virtual void OnPaint(wxPaintEvent& event) { event.Skip(); }
	virtual void OnToggle(wxCommandEvent& event) { event.Skip(); }


public:
	wxToggleButton* m_toggleBtn1;

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("œ‡ª˙≤‚ ‘1"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__NONAME_H__
