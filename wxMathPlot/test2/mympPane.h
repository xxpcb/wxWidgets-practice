#pragma once

#include "mathplot.h"
#include <wx/wxprec.h>
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>
#include <wx/print.h>
#include <wx/filename.h>
#include <math.h>

// Memory leak debugging
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class BasicMPPane : public wxPanel
{
public:
	BasicMPPane(wxWindow *parent=0);
	void Fit();
	void ToggleGrid();
	void ToggleScrollbars();

	mpFXYVector* vectorLayer;
	std::vector<double> vectorx, vectory;
	mpWindow* m_plot;
private:
	bool ticks,scrolls;
};


