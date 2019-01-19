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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_QUIT 1000

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxMenuBar* m_menubar1;
	wxMenu* m_menu1;
	wxMenu* m_menu2;
	wxStaticText* m_staticText1;
	wxStaticLine* m_staticline2;
	wxPanel* m_panel1;
	wxPanel* m_panel2;
	wxStatusBar* m_statusBar1;

	// Virtual event handlers, overide them in your derived class
	virtual void OnScroll_Th(wxScrollEvent& event) { event.Skip(); }
	virtual void OnPaint1(wxPaintEvent& event) { event.Skip(); }
	virtual void OnPaint2(wxPaintEvent& event) { event.Skip(); }


public:
	wxSlider* m_slider1;

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("»æÖÆÂÖÀª"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(850, 700), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

#endif //__NONAME_H__
