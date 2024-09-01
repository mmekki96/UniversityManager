#include "teacher.h"

Teacher::Teacher(wxWindow* parent, sqlite3* db) :
	wxPanel(parent), m_db(db)
{
	grid = new wxGridSizer(8, 1, 0, 0);
	grid->SetVGap(20);
	wxGridSizer* grid_btn = new wxGridSizer(1, 4, 0, 0);

	wxBoxSizer* name_box = new wxBoxSizer(wxVERTICAL);
	name_txt = new wxStaticText(this, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxGridSizer* name_grid = new wxGridSizer(1, 2, 0, 10);
	name = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	lastname = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	name_grid->Add(name, 0, wxALIGN_LEFT);
	name_grid->Add(lastname, 0, wxALIGN_LEFT);
	name_box->Add(name_txt, 0, wxALIGN_LEFT);
	name_box->AddSpacer(5);
	name_box->Add(name_grid, 0, wxALIGN_LEFT);

	wxBoxSizer* cin_box = new wxBoxSizer(wxVERTICAL);
	cin_txt = new wxStaticText(this, wxID_ANY, "CIN Number", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	cin = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	cin_box->Add(cin_txt, 0, wxALIGN_LEFT);
	cin_box->AddSpacer(5);
	cin_box->Add(cin, 0, wxEXPAND);

	wxBoxSizer* mail_box = new wxBoxSizer(wxVERTICAL);
	email_txt = new wxStaticText(this, wxID_ANY, "E-mail", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	email = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	mail_box->Add(email_txt, 0, wxALIGN_LEFT);
	mail_box->AddSpacer(5);
	mail_box->Add(email, 0, wxEXPAND);

	wxBoxSizer* gender_box = new wxBoxSizer(wxVERTICAL);
	gender_txt = new wxStaticText(this, wxID_ANY, "Gender", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxGridSizer* gender_grid = new wxGridSizer(1, 2, 0, 20);
	m_gender = new wxRadioButton(this, wxID_ANY, "Male");
	f_gender = new wxRadioButton(this, wxID_ANY, "Female");
	gender_grid->Add(m_gender, 0, wxALIGN_LEFT);
	gender_grid->Add(f_gender, 0, wxALIGN_LEFT);
	gender_box->Add(gender_txt, 0, wxALIGN_LEFT);
	gender_box->AddSpacer(5);
	gender_box->Add(gender_grid, 0, wxALIGN_LEFT);

	wxBoxSizer* birth_box = new wxBoxSizer(wxVERTICAL);
	birthdate_txt = new wxStaticText(this, wxID_ANY, "Date of birth", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxDatePickerCtrl* datepicker = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition,
		wxDefaultSize, wxDP_DROPDOWN | wxDP_SHOWCENTURY);
	datepicker->ClearBackground();
	datepicker->Bind(wxEVT_DATE_CHANGED, &Teacher::onCalendarClick, this);
	birth_box->Add(birthdate_txt, 0, wxALIGN_LEFT);
	birth_box->AddSpacer(5);
	birth_box->Add(datepicker, 0, wxEXPAND);

	wxBoxSizer* phone_box = new wxBoxSizer(wxVERTICAL);
	phone_txt = new wxStaticText(this, wxID_ANY, "Phone number", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	phone = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	phone_box->Add(phone_txt, 0, wxALIGN_LEFT);
	phone_box->AddSpacer(5);
	phone_box->Add(phone, 0, wxEXPAND);

	add_btn = new wxButton(this, wxID_ANY, "Submit", wxDefaultPosition);
	add_btn->Bind(wxEVT_BUTTON, &Teacher::onAddClick, this);
	reset_btn = new wxButton(this, wxID_ANY, "Reset", wxDefaultPosition);
	reset_btn->Bind(wxEVT_BUTTON, &Teacher::onResetClick, this);
	cancel_btn = new wxButton(this, wxID_ANY, "Cancel", wxDefaultPosition);
	cancel_btn->Bind(wxEVT_BUTTON, &Teacher::onCancelClick, this);

	grid_btn->Add(cancel_btn, 0, wxALIGN_CENTER_VERTICAL);
	grid_btn->Add(new wxStaticText(this, wxID_ANY, ""), 1, wxEXPAND);
	grid_btn->Add(reset_btn, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
	grid_btn->Add(add_btn, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);

	wxBoxSizer* subject_box = new wxBoxSizer(wxVERTICAL);
	subject_txt = new wxStaticText(this, wxID_ANY, "Subject", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	const char* sql_select = "SELECT * FROM Subjects;";
	int qc = sqlite3_prepare_v2(m_db, sql_select, -1, &stmt, NULL);
	if (qc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	choices.Add("(Select otpion...)");
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		wxString val = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		choices.Add(val);
	}
	subject = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	subject->SetSelection(0);
	subject_box->Add(subject_txt, 0, wxALIGN_LEFT);
	subject_box->AddSpacer(5);
	subject_box->Add(subject, 0, wxEXPAND);

	grid->Add(name_box, 0, wxALIGN_LEFT);
	grid->Add(cin_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(subject_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(mail_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(gender_box, 0, wxALIGN_LEFT);
	grid->Add(birth_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(phone_box, 0, wxALIGN_LEFT | wxEXPAND);
	grid->Add(grid_btn, 0, wxALIGN_LEFT | wxEXPAND);

	wxBoxSizer* gridsizer = new wxBoxSizer(wxVERTICAL);
	gridsizer->Add(grid, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	this->SetSizer(gridsizer);
}

void Teacher::onAddClick(wxCommandEvent& event)
{
	wxString name_str = name->GetValue();
	wxString lastname_str = lastname->GetValue();
	wxString cin_str = cin->GetValue();
	wxString subject_str = subject->GetStringSelection();
	wxString mail_str = email->GetValue();
	std::string gender_str;
	if (m_gender->GetValue())
		gender_str = m_gender->GetLabel().ToStdString();
	else if (f_gender->GetValue())
		gender_str = f_gender->GetLabel().ToStdString();
	else
		gender_str = "";
	wxString phone_str = phone->GetValue();

	const char* sql_select = "INSERT INTO Teachers (name, lastname, subject, cin, email, gender, birthdate, phone) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
	int rc = sqlite3_prepare_v2(m_db, sql_select, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, name_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, lastname_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, subject_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, cin_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, mail_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, gender_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, date_str.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 8, phone_str.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		wxLogError("SQL error %s", sqlite3_errmsg(m_db));
		return;
	}
	else
		wxLogMessage("Data saved to database successfuly!");
	sqlite3_finalize(stmt);
	clearData();
}

void Teacher::onCalendarClick(wxDateEvent& event)
{
	wxDateTime date = event.GetDate();
	date_str = date.Format("%d-%m-%Y");
}

void Teacher::onCancelClick(wxCommandEvent& event)
{
	wxWindow* parent = this->GetParent(); 
	wxFrame* frame = dynamic_cast<wxFrame*>(parent->GetParent());
	if (frame)
		frame->Close();
}

void Teacher::onResetClick(wxCommandEvent& event)
{
	clearData();
}

void Teacher::clearData()
{
	name->Clear();
	lastname->Clear();
	cin->Clear();
	subject->SetSelection(0);
	email->Clear();
	phone->Clear();
}