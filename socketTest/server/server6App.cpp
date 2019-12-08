/*=========================================================
* Name: server6App.cpp
* Function: wxSocket Test, Server-Side
* Created: 2019-12-6
* Author: xxpcb(https://github.com/xxpcb)
* Reference: wxWidgets official samples(sockets:server.cpp)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#  pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif
#include "wx/log.h"
#include "wx/busyinfo.h"
#include "wx/socket.h"

#include "gui_s.h"
#define BUFSIZE 4096

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public MyFrame1
{
public:
	MyFrame();
	~MyFrame();
	void OnSetPath(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnWaitForAccept(wxCommandEvent& event);
	void OnUDPTest(wxCommandEvent& event);

	void OnServerEvent(wxSocketEvent& event);
	void OnSocketEvent(wxSocketEvent& event);

	void Test1(wxSocketBase *sock);
	void Test2(wxSocketBase *sock);
	void Test3(wxSocketBase *sock);
	void Test4_rF(wxSocketBase *sock);
	void Test5_sF(wxSocketBase *sock);

	void UpdateStatusBar();
	
private:
	wxSocketServer *m_server;
	bool            m_busy;
	int             m_numClients;
	wxFile file1;
	wxFile file2;
	wxString dirpath = "./file";

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// simple helper class to log start and end of each test
class TestLogger
{
public:
	TestLogger(const wxString& name) : m_name(name)
	{
		wxLogMessage("=== %s begins ===", m_name);
	}

	~TestLogger()
	{
		wxLogMessage("=== %s ends ===", m_name);
	}

private:
	const wxString m_name;
};

// id for sockets
enum
{
	SERVER_ID = 100,
	SOCKET_ID
};

// event tables and other macros for wxWidgets
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_SOCKET(SERVER_ID, MyFrame::OnServerEvent) // [OnServerEvent]process the new connect request
EVT_SOCKET(SOCKET_ID, MyFrame::OnSocketEvent) // [OnSocketEvent]process the transport data
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : MyFrame1(NULL, wxID_ANY)
{
	wxLog::SetActiveTarget(new wxLogTextCtrl(m_text));

	//  [Create the address] - defaults to localhost:0 initially
	wxIPV4address addr;
	//addr.Hostname(wxGetFullHostName());
	addr.Service(3000);

	wxLogMessage("Creating server at %s:%u", addr.IPAddress(), addr.Service());

	//  [Create the socket]
	m_server = new wxSocketServer(addr);

	// We use IsOk() here to see if the server is really  [listening]
	if (!m_server->IsOk())
	{
		wxLogMessage("Could not listen at the specified port !");
		return;
	}

	// We use GetLocal() to get local IP and port
	wxIPV4address addrReal;
	if (!m_server->GetLocal(addrReal))
	{
		wxLogMessage("ERROR: couldn't get the address we bound to");
	}
	else
	{
		wxLogMessage("Server listening at %s:%u", addrReal.IPAddress(), addrReal.Service());
	}

	//  [Setup the event handler] and subscribe to connection events
	m_server->SetEventHandler(*this, SERVER_ID);
	m_server->SetNotify(wxSOCKET_CONNECTION_FLAG);
	m_server->Notify(true);

	// Set the dirpath
	if (!wxDirExists(dirpath))
	{
		wxMkDir(dirpath, 0);
		m_text->AppendText("mkdir: " + dirpath + "\n");
	}
	wxSetWorkingDirectory(dirpath);
	m_text->AppendText("[Current directoy path]: " + dirpath + "\n");

	m_busy = false;
	m_numClients = 0;
	UpdateStatusBar();
}

MyFrame::~MyFrame()
{
	// No delayed deletion here, as the frame is dying anyway
	delete m_server;
}

//=============================================================
void MyFrame::OnSetPath(wxCommandEvent& WXUNUSED(event))
{
	// --------- Select file path dialog test
	wxDirDialog selectDirDialog(this, "Select a directory for file");
	selectDirDialog.ShowModal();

	dirpath = (const char*)selectDirDialog.GetPath().mb_str();
	wxSetWorkingDirectory(dirpath);
	m_text->AppendText("[Current directoy path]: " + dirpath + "\n");
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("wxSocket demo: Server\n(c) 1999 Guillermo Rodriguez Garcia\nModify by xxpcb (Add File Transfer Function)",
		"About Server",
		wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnUDPTest(wxCommandEvent& WXUNUSED(event))
{
	TestLogger logtest("UDP test");

	wxIPV4address addr;
	addr.Service(3000);
	wxDatagramSocket sock(addr);

	char buf[BUFSIZE];
	size_t n = sock.RecvFrom(addr, buf, sizeof(buf)).LastCount();
	if (!n)
	{
		wxLogMessage("ERROR: failed to receive data");
		return;
	}

	wxLogMessage("Received \"%s\" from %s:%u.",
		wxString::From8BitData(buf, n),
		addr.IPAddress(), addr.Service());

	for (size_t i = 0; i < n; i++)
	{
		char& c = buf[i];
		if ((c >= 'A' && c <= 'M') || (c >= 'a' && c <= 'm'))
			c += 13;
		else if ((c >= 'N' && c <= 'Z') || (c >= 'n' && c <= 'z'))
			c -= 13;
	}

	if (sock.SendTo(addr, buf, n).LastCount() != n)
	{
		wxLogMessage("ERROR: failed to send data");
		return;
	}
}

void MyFrame::OnWaitForAccept(wxCommandEvent& WXUNUSED(event))
{
	TestLogger logtest("WaitForAccept() test");

	wxBusyInfo("Waiting for connection for 10 seconds...", this);
	if (m_server->WaitForAccept(10))
		wxLogMessage("Accepted client connection.");
	else
		wxLogMessage("Connection error or timeout expired.");
}

void MyFrame::Test1(wxSocketBase *sock)
{
	TestLogger logtest("Test 1");

	// Receive data from socket and send it back. We will first get a byte with the buffer size, 
	// so we can specify the exact size and use the wxSOCKET_WAITALL flag.
	// Also, we disabled input events so we won't have unwanted reentrance.
	// This way we can avoid the infamous wxSOCKET_BLOCK flag.

	sock->SetFlags(wxSOCKET_WAITALL);

	// Read the size
	unsigned char len;
	sock->Read(&len, 1);
	wxCharBuffer buf(len);

	// Read the data
	sock->Read(buf.data(), len);
	wxLogMessage("Got the data use [Read], sending it back");
	wxLogMessage("Sending the data back use [Write]");
	// Write it back
	sock->Write(buf, len);
}

void MyFrame::Test2(wxSocketBase *sock)
{
	char buf[4096];

	TestLogger logtest("Test 2");

	// We don't need to set flags because ReadMsg and WriteMsg are not affected by them anyway.

	// Read the message
	wxUint32 len = sock->ReadMsg(buf, sizeof(buf)).LastCount();
	if (!len)
	{
		wxLogError("Failed to read message.");
		return;
	}

	wxLogMessage("Got \"%s\" use [ReadMsg]from client.", wxString::FromUTF8(buf, len));
	wxLogMessage("Sending the data back use [WriteMsg]");

	// Write it back
	sock->WriteMsg(buf, len);
}

void MyFrame::Test3(wxSocketBase *sock)
{
	TestLogger logtest("Test 3");

	// This test is similar to the first one, but the len is expressed in kbytes
	// -- this tests large data transfers.

	sock->SetFlags(wxSOCKET_WAITALL);

	// Read the size
	unsigned char len;
	sock->Read(&len, 1);
	wxCharBuffer buf(len * BUFSIZE);

	// Read the data
	sock->Read(buf.data(), len * BUFSIZE);
	wxLogMessage("Got the data, sending it back");

	// Write it back
	sock->Write(buf, len * BUFSIZE);
}

void MyFrame::Test4_rF(wxSocketBase *sock)
{
	TestLogger logtest("Test 4 (client send File)");

	// This test is receive a File which come from Clinet

	// ----------- Read the file name
	char file2name[4096];
	wxUint32 len = 0;
	len = sock->ReadMsg(file2name, sizeof(file2name)).LastCount();
	if (!len)
	{
		wxLogError("Failed to read file name.");
		return;
	}
	wxString filename = wxString::FromUTF8(file2name, len);
	wxLogMessage("Got file name \"%s\" from client.", filename);

	// -------------------- Receive file
	//sock->SetFlags(wxSOCKET_WAITALL); // No wait !!!
	sock->SetFlags(wxSOCKET_NONE); // Must use wxSOCKET_NONE !!!

	file2.Create(filename, wxFile::write);
	if (file2.IsOpened())
		m_text->AppendText("Create file2 ok\n");

	wxUint8 *data = new wxUint8[BUFSIZE];
	len = 0;
	while ((len = sock->Read(data, BUFSIZE).LastCount()) && len > 0)
	{
		//wxLogMessage("%d", len);
		file2.Write(data, (size_t)len);

		if (len != BUFSIZE) break;
	}
	delete[] data;
	file2.Close();

	wxLogMessage("Receive the File ok");
}

void MyFrame::Test5_sF(wxSocketBase *sock)
{
	TestLogger logtest("Test 5 (client receive File)");

	// This test is send a File to client

	// ----------- Read the file name
	char file2name[4096];
	wxUint32 len = 0;
	len = sock->ReadMsg(file2name, sizeof(file2name)).LastCount();
	if (!len)
	{
		wxLogError("Failed to read file name.");
		return;
	}
	wxString filename = wxString::FromUTF8(file2name, len);
	wxLogMessage("Got file name \"%s\" from client.", filename);

	// ---------- Check the file information and send back
	wxString str;
	if (file1.Exists(filename))
	{
		file1.Open(filename);
		file1.Seek(0);
		wxFileOffset filesize = file1.Length();
		if (wxInvalidOffset == filesize) return;
		str = wxString::Format("File name : %s, File size : %lld byte (%lld KB)(%lld M)\n", filename, filesize, filesize >> 10, filesize >> 20);
		const wxScopedCharBuffer fileinfo(str.utf8_str());
		m_text->AppendText(str);

		m_text->AppendText("Sending back the file information ...");
		sock->WriteMsg(fileinfo, wxStrlen(fileinfo) + 1); // send file info
		m_text->AppendText(sock->Error() ? "failed !\n" : "done\n");
		sock->WaitForRead(2);

		// ----------------- Send file to client
		wxUint8 * data = new wxUint8[BUFSIZE];
		while (1)
		{
			if ((len = file1.Read(data, (size_t)BUFSIZE)) && len > 0)
			{
				//wxLogMessage("%d", len);
				sock->Write(data, len); // send data, len !!!(not BUFSIZE)
			}
			else
				break;
		}
		delete[] data;
		file1.Close();

		wxLogMessage("Send the File ok");
	}
	else // The request file not exist
	{
		str = wxString::Format("The request file \"%s\" not exist !\n", filename);
		const wxScopedCharBuffer fileinfo(str.utf8_str());
		sock->WriteMsg(fileinfo, wxStrlen(fileinfo) + 1); // send file info
		wxLogMessage("file \"%s\" not exist in current directory !", filename);
	}
}

// [OnServerEvent]process the new connect request
void MyFrame::OnServerEvent(wxSocketEvent& event)
{
	wxString s = " [OnServerEvent]: ";
	wxSocketBase *sock; // create a new serve socket ?

	switch (event.GetSocketEvent())
	{
		case wxSOCKET_CONNECTION: s.Append("wxSOCKET_CONNECTION\n"); break;
		default: s.Append("Unexpected event !\n"); break;
	}
	
	m_text->AppendText(s);

	// [Accept]new connection if there is one in the pending connections queue, else exit. 
	// We use Accept(false) for non-blocking accept 
	// (although if we got here, there should ALWAYS be a pending connection).

	sock = m_server->Accept(false);

	if (sock)
	{
		wxIPV4address addr;
		// we use GetPeer() to get the opposite info
		if (!sock->GetPeer(addr))
		{
			wxLogMessage("New connection from unknown client accepted.");
		}
		else
		{
			wxLogMessage("New client connection from %s:%u accepted",
				addr.IPAddress(), addr.Service());
		}
	}
	else
	{
		wxLogMessage("Error: couldn't accept a new connection");
		return;
	}

	//  [Setup the event handler] and subscribe to most events
	sock->SetEventHandler(*this, SOCKET_ID);
	sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
	sock->Notify(true);

	m_numClients++; // client count ++
	UpdateStatusBar();
}

//  [OnSocketEvent]process the transport data
void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
	wxString s = " [OnSocketEvent]: ";
	wxSocketBase *sock = event.GetSocket(); // get socket from ...

	// First, print a message
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT: s.Append("wxSOCKET_INPUT\n"); break;
	case wxSOCKET_LOST: s.Append("wxSOCKET_LOST\n"); break;
	default: s.Append("Unexpected event !\n"); break;
	}

	m_text->AppendText(s);

	// Now we process the event
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT:
	{
		// We disable input events, so that the test doesn't trigger wxSocketEvent again.
		sock->SetNotify(wxSOCKET_LOST_FLAG);

		// Which test are we going to run?
		unsigned char c;
		sock->Read(&c, 1);

		switch (c)
		{
			case 0xBE: Test1(sock); break;
			case 0xCE: Test2(sock); break;
			case 0xDE: Test3(sock); break;
			case 0xEE: Test4_rF(sock); break;
			case 0xFE: Test5_sF(sock); break;
			default:
				wxLogMessage("Unknown test id received from client");
		}

		// Enable input events again.
		sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
		break;
	}
	case wxSOCKET_LOST:
	{
		m_numClients--;

		// Destroy() should be used instead of delete wherever possible, due to the fact that wxSocket uses 
		// 'delayed events' (see the documentation for wxPostEvent) and we don't want an event to
		// arrive to the event handler (the frame, here) after the socket has been deleted.
		// Also, we might be doing some other thing with the socket at the same time; 
		// for example, we might be in the middle of a test or something.
		// Destroy() takes care of all this for us.

		wxLogMessage("Deleting socket.");
		sock->Destroy();
		break;
	}
	default:;
	}

	UpdateStatusBar();
}

void MyFrame::UpdateStatusBar()
{
	wxString s;
	s.Printf("%d clients connected", m_numClients);
	SetStatusText(s, 1);
}