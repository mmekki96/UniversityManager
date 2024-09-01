#include "frame.h"
#include "adminFrame.h"

myFrame::myFrame(const wxString& title, sqlite3 *db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 200)), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	wxGridSizer* grid = new wxGridSizer(3, 2, 0, 0);
	grid->SetVGap(15);

	user_id_label = new wxStaticText(this, wxID_ANY, "User id", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	user_id = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));
	user_psd_label = new wxStaticText(this, wxID_ANY, "User password", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	user_psd = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);
	sign_btn = new wxButton(this, wxID_ANY, "Connect");
	sign_btn->Bind(wxEVT_BUTTON, &myFrame::onSignClick, this);
	grid->Add(user_id_label, 0, wxALIGN_CENTER );
	grid->Add(user_id, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	grid->Add(user_psd_label, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
	grid->Add(user_psd, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	grid->Add(new wxStaticText(this, wxID_ANY, ""), 0, wxALL);
	grid->Add(sign_btn, 0, wxALIGN_RIGHT);

	wxBoxSizer* boxsizer = new wxBoxSizer(wxVERTICAL);
	boxsizer->Add(grid, 0,  wxALIGN_CENTER_HORIZONTAL | wxALL, 30);
	this->SetSizer(boxsizer);
}


void myFrame::onSignClick(wxCommandEvent& event)
{
	std::string querry = "SELECT * FROM Admins;";
	bool valid = false;
	int rc = sqlite3_prepare_v2(m_db, querry.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	
	while (rc = sqlite3_step(stmt) == SQLITE_ROW)
	{
		const unsigned char* name = sqlite3_column_text(stmt, 1);
		const unsigned char* password = sqlite3_column_text(stmt, 2);
		wxString name_str = wxString::FromUTF8(reinterpret_cast<const char*>(name));
		wxString password_str = wxString::FromUTF8(reinterpret_cast<const char*>(password));
		if (user_id->GetValue() == name_str && user_psd->GetValue() == password_str)
		{
			AdminFrame* adminframe = new AdminFrame("Admin Control", m_db, &name_str);
			adminframe->Show(true);
			valid = true;
			this->Hide();
			break;
		}		
	}

	if (!valid)
		wxLogError("Name or password incorrect, please try again!");

	sqlite3_finalize(stmt);
}

BEGIN_EVENT_TABLE(myFrame, wxFrame)
	EVT_BUTTON(wxID_ANY, myFrame::onSignClick)
END_EVENT_TABLE()