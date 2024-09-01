#include "subject.h"

Subject::Subject(wxWindow* parent, sqlite3* db) :
	wxPanel(parent), m_db(db)
{
	grid = new wxGridSizer(2, 1, 0, 0);
	grid->SetVGap(30);

	wxBoxSizer* box_txt = new wxBoxSizer(wxVERTICAL);
	txt = new wxStaticText(this, wxID_ANY, "Subject", wxDefaultPosition, wxDefaultSize);
	txt_ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
	box_txt->Add(txt, 0, wxALIGN_LEFT);
	box_txt->AddSpacer(5);
	box_txt->Add(txt_ctrl, 0, wxEXPAND);

	wxGridSizer* grid_btn = new wxGridSizer(1, 2, 0, 0);
	submit_btn = new wxButton(this, wxID_ANY, "Submit", wxDefaultPosition, wxDefaultSize);
	submit_btn->Bind(wxEVT_BUTTON, &Subject::onClickSubmit, this);
	close_btn = new wxButton(this, wxID_ANY, "Close", wxDefaultPosition, wxDefaultSize);
	grid_btn->Add(close_btn, 0, wxALIGN_LEFT);
	grid_btn->Add(submit_btn, 0, wxALIGN_RIGHT);

	grid->Add(box_txt, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(grid_btn, 0, wxALIGN_BOTTOM | wxEXPAND);
	
	wxBoxSizer* grid_box = new wxBoxSizer(wxVERTICAL);
	grid_box->Add(grid, 0, wxALL | wxEXPAND, 30);
	this->SetSizer(grid_box);
}

void Subject::onClickSubmit(wxCommandEvent& event)
{
	wxString sub_str = txt_ctrl->GetValue();
	const char* sql = "INSERT INTO Subjects (name) VALUES (?)";
	int exit = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (exit != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, sub_str.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		wxLogError("SQL error %s", sqlite3_errmsg(m_db));
		return;
	}
	else
		wxLogMessage("Data has been saved successfuly!");
	sqlite3_finalize(stmt);
	txt_ctrl->Clear();
}