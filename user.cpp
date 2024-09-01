#include "user.h"

User::User(wxWindow* parent, sqlite3* db) :
	wxPanel(parent), m_db(db)
{
	grid = new wxGridSizer(4, 1, 0, 0);
	grid->SetVGap(20);
	wxBoxSizer* name_box = new wxBoxSizer(wxVERTICAL);
	name_txt = new wxStaticText(this, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize);
	name = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
	name_box->Add(name_txt, 0, wxALIGN_LEFT);
	name_box->AddSpacer(5);
	name_box->Add(name, 0, wxEXPAND);

	wxBoxSizer* psd_box = new wxBoxSizer(wxVERTICAL);
	psd_txt = new wxStaticText(this, wxID_ANY, "Password", wxDefaultPosition, wxDefaultSize);
	password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	psd_box->Add(psd_txt, 0, wxALIGN_LEFT);
	psd_box->AddSpacer(5);
	psd_box->Add(password, 0, wxEXPAND);

	wxBoxSizer* psd_ver_box = new wxBoxSizer(wxVERTICAL);
	psd_ver_txt = new wxStaticText(this, wxID_ANY, "Confirm password", wxDefaultPosition, wxDefaultSize);
	psd_ver = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	psd_ver_box->Add(psd_ver_txt, 0, wxALIGN_LEFT);
	psd_ver_box->AddSpacer(5);
	psd_ver_box->Add(psd_ver, 0, wxEXPAND);

	wxGridSizer* grid_btn = new wxGridSizer(1, 4, 0, 0);
	add_btn = new wxButton(this, wxID_ANY, "Submit", wxDefaultPosition);
	add_btn->Bind(wxEVT_BUTTON, &User::onAddClick, this);
	reset_btn = new wxButton(this, wxID_ANY, "Reset", wxDefaultPosition);
	reset_btn->Bind(wxEVT_BUTTON, &User::onResetClick, this);
	cancel_btn = new wxButton(this, wxID_ANY, "Cancel", wxDefaultPosition);
	cancel_btn->Bind(wxEVT_BUTTON, &User::onCancelClick, this);
	grid_btn->Add(cancel_btn, 0, wxALIGN_CENTER_VERTICAL);
	grid_btn->Add(new wxStaticText(this, wxID_ANY, ""), 1, wxEXPAND);
	grid_btn->Add(reset_btn, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	grid_btn->Add(add_btn, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);

	grid->Add(name_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(psd_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(psd_ver_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(grid_btn, 0, wxALIGN_LEFT | wxEXPAND);

	wxBoxSizer* grid_box = new wxBoxSizer(wxVERTICAL);
	grid_box->Add(grid, 0, wxEXPAND | wxALL, 30);
	this->SetSizer(grid_box);
}

void User::onAddClick(wxCommandEvent& event)
{
	wxString name_str = name->GetValue();
	wxString password_str = password->GetValue();
	wxString ver_psd_str = psd_ver->GetValue();
	if (ver_psd_str != password_str)
	{
		wxLogError("Your password is not identical");
		return;
	}
	const char* sql = "INSERT INTO Admins (name, password) VALUES (?, ?);";
	int exit = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (exit != SQLITE_OK)
	{
		wxLogError("Faile to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, name_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password_str.c_str(), -1, SQLITE_STATIC);
	int rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		wxLogError("SQL error %s", sqlite3_errmsg(m_db));
		return;
	}
	else
		wxLogMessage("Data has been successfuly saved!");
	sqlite3_finalize(stmt);
	clearData();
}

void User::onCancelClick(wxCommandEvent& event)
{
	wxWindow* parent = this->GetParent();
	wxFrame* frame = dynamic_cast<wxFrame*>(parent->GetParent());
	if (frame)
		frame->Close();
}

void User::onResetClick(wxCommandEvent& event)
{
	clearData();
}

void User::clearData()
{
	name->Clear();
	password->Clear();
	psd_ver->Clear();
}
