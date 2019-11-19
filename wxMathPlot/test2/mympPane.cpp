#include "mympPane.h"

BasicMPPane::BasicMPPane(wxWindow *parent)
	: wxPanel(parent)
{

	// Create a 【mpFXYVector layer】
	vectorLayer = new mpFXYVector(_("Vector"));
	//// Create two vectors for x,y and fill them with data
	//std::vector<double> vectorx, vectory;

	double xcoord;
	for (unsigned int p = 0; p < 100; p++)
	{
		xcoord = ((double)p - 50.0)*5.0;//x:-250~250
		vectorx.push_back(xcoord);
		vectory.push_back(0.0001*pow(xcoord, 3));//y=0.001*x^3
	}

	vectorLayer->SetData(vectorx, vectory);//导入数据
	vectorLayer->SetContinuity(true);//连续线
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);//蓝色线
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);


	 //【mathPlot窗口】
	m_plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
	mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);//底部x轴
	mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true);//左侧y轴
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	xaxis->SetFont(graphFont);//图标轴字体
	yaxis->SetFont(graphFont);
	xaxis->SetDrawOutsideMargins(false);
	yaxis->SetDrawOutsideMargins(false);

	m_plot->SetMargins(30, 30, 50, 100);//边缘 top, right, bottom, left
	m_plot->AddLayer(xaxis);//将轴添加到窗口中
	m_plot->AddLayer(yaxis);
	m_plot->AddLayer(vectorLayer);//将自定义的vector函数添加到窗口中
	m_plot->AddLayer(new mpText(wxT("mpText sample"), 20, 10));//添加文字

	//BoxSizer
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	topsizer->Add(m_plot, 1, wxEXPAND);//添加mathPlot窗口
	SetAutoLayout(TRUE);
	SetSizer(topsizer);
	ticks = true;

	m_plot->EnableDoubleBuffer(true);
	m_plot->SetMPScrollbars(false);
	m_plot->Fit();
}

void BasicMPPane::Fit()
{
	m_plot->Fit();
}

void BasicMPPane::ToggleGrid()
{
	ticks = !ticks;
	((mpScaleX*)(m_plot->GetLayer(0)))->SetTicks(ticks);
	((mpScaleY*)(m_plot->GetLayer(1)))->SetTicks(ticks);
	m_plot->UpdateAll();
}

void BasicMPPane::ToggleScrollbars()
{
	scrolls = !scrolls;
	m_plot->SetMPScrollbars(scrolls);

}


