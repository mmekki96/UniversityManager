#include "initFrame.h"
#include "frame.h"
#include "sqlite/sqlite3.h"

InitFrame::InitFrame(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200)), db(db)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	initTxt = new wxStaticText(panel, wxID_ANY, "Insert password", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	initPsd = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);
	connect_btn = new wxButton(panel, wxID_ANY, "Connect");
	connect_btn->Bind(wxEVT_BUTTON, &InitFrame::onConnectClick, this);
	
	wxGridSizer* grid = new wxGridSizer(4, 1, 10, 0);
	grid->Add(initTxt, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
	grid->Add(initPsd, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
	grid->AddSpacer(0);
	grid->Add(connect_btn, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);

	wxBoxSizer* boxsizer = new wxBoxSizer(wxVERTICAL);
	boxsizer->Add(grid, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
	panel->SetSizer(boxsizer);
}

void InitFrame::onConnectClick(wxCommandEvent& event)
{
	m_psd = initPsd->GetValue().ToStdString();
	if (m_psd == "0000")
	{
		this->Hide();
		myFrame* frame = new myFrame(wxT("Authentification"), db);
		frame->Show(true);
	}
	else
		wxLogError("Wrong password, please try again");
}
