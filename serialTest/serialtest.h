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
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_SELPORT 1000
#define ID_BAUDRATE 1001
#define ID_TXTRX 1002
#define ID_BTNSEND 1003
#define ID_TXTSEND 1004
#define ID_TIMER 1005

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;
	wxButton* m_button4;
	wxTimer m_timer;

	// Virtual event handlers, overide them in your derived class
	virtual void OnSelPort(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSetBaud(wxCommandEvent& event) { event.Skip(); }
	virtual void OnToggle(wxCommandEvent& event) { event.Skip(); }
	virtual void OnClearText(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSend(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTimer(wxTimerEvent& event) { event.Skip(); }


public:
	wxToggleButton* m_toggleBtn;
	wxTextCtrl* m_txtRx;
	wxTextCtrl* m_txtSend;

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("´®¿Ú²âÊÔ"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__NONAME_H__
