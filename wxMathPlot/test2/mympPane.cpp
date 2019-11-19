#include "mympPane.h"

BasicMPPane::BasicMPPane(wxWindow *parent)
	: wxPanel(parent)
{

	// Create a ��mpFXYVector layer��
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

	vectorLayer->SetData(vectorx, vectory);//��������
	vectorLayer->SetContinuity(true);//������
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);//��ɫ��
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);


	 //��mathPlot���ڡ�
	m_plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER);
	mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, true, mpX_NORMAL);//�ײ�x��
	mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, true);//���y��
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	xaxis->SetFont(graphFont);//ͼ��������
	yaxis->SetFont(graphFont);
	xaxis->SetDrawOutsideMargins(false);
	yaxis->SetDrawOutsideMargins(false);

	m_plot->SetMargins(30, 30, 50, 100);//��Ե top, right, bottom, left
	m_plot->AddLayer(xaxis);//������ӵ�������
	m_plot->AddLayer(yaxis);
	m_plot->AddLayer(vectorLayer);//���Զ����vector������ӵ�������
	m_plot->AddLayer(new mpText(wxT("mpText sample"), 20, 10));//�������

	//BoxSizer
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	topsizer->Add(m_plot, 1, wxEXPAND);//���mathPlot����
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


