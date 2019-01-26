/*=========================================================
* Name: test1.1.cpp
* Function: 打开大图片及显示测试（wxImagePanel继承于滚动窗口）
* Created: 2019-01-25
* Author: xxpcb(https://github.com/xxpcb)
* 参考自：https://wiki.wxwidgets.org/An_image_panel ，将wxPanel换为wxScrolledWindow
==========================================================*/

//====================================================================
//没有调整尺寸功能的代码

#include <wx/wx.h>
#include <wx/sizer.h>

// 自定义的wxImagePanel类，公有继承于【wxPanel】
class wxImagePanel : public wxScrolledWindow//wxPanel
{
	wxBitmap image;
public:
	wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);//构造函数
	void paintEvent(wxPaintEvent & evt);//显示图像（需重画时系统触发）
	void render(wxDC& dc);//图像渲染执行函数
	DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(wxImagePanel, wxScrolledWindow)//wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)// catch paint events
END_EVENT_TABLE()

//自定义的wxImagePanel类的构造函数，继承于【wxPanel】，参数用于加载图片
wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) 
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL)//wxPanel(parent)
{
	// load the file... ideally add a check to see if loading was successful
	image.LoadFile(file, format);
}

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::render(wxDC&  dc)
{
	this->PrepareDC(dc);
	dc.DrawBitmap(image, 0, 0, false);
}


// ----------------------------------------
// how-to-use example

class MyApp : public wxApp
{
	wxFrame *frame;
	wxImagePanel * drawPane;
public:
	bool OnInit()
	{
		// make sure to call this first
		wxInitAllImageHandlers();

		// 新建一个【布局器】
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		// 新建一个【框架】
		frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

		// then simply create like this
		// 新建一个【图像面板】并添加到布局器中
		drawPane = new wxImagePanel(frame, wxT("../2.jpg"), wxBITMAP_TYPE_JPEG);//此处需修改图片路径！
		drawPane->SetScrollRate(5, 5);//设置滚动间距
		drawPane->SetVirtualSize(1920, 1080);//设置画面大小
		sizer->Add(drawPane, 1, wxEXPAND);

		frame->SetSizer(sizer);//再将布局器放入框架中
		frame->Show();

		return true;
	}

};

IMPLEMENT_APP(MyApp)