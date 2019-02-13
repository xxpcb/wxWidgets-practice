///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PICADAPTION_H__
#define __PICADAPTION_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxScrolledWindow* m_scrolledWindow1;
	wxTextCtrl* m_textCtrl1;
	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;
	wxButton* m_button4;

	// Virtual event handlers, overide them in your derived class
	virtual void OnPaint(wxPaintEvent& event) { event.Skip(); }
	virtual void OnOpen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnOriginal(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAdaption(wxCommandEvent& event) { event.Skip(); }
	virtual void OnOverspread(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("图像铺满窗口与自适应窗口"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__PICADAPTION_H__
