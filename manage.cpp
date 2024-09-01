#include "manage.h"
#include "managestd.h"
#include "manageusr.h"
#include "managetchr.h"

Manage::Manage(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 250)), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxStaticText* txt = new wxStaticText(panel, wxID_ANY, "Please choose one of options bellow to manage: ", wxDefaultPosition);
	wxBoxSizer* box_panel = new wxBoxSizer(wxVERTICAL);
	close_btn = new wxButton(panel, wxID_ANY, "Close");
	close_btn->Bind(wxEVT_BUTTON, &Manage::onClickClose, this);
	user_link = new wxHyperlinkCtrl(panel, wxID_ANY, "User management", "", wxDefaultPosition);
	teacher_link = new wxHyperlinkCtrl(panel, wxID_ANY, "Teacher management", "", wxDefaultPosition);
	student_link = new wxHyperlinkCtrl(panel, wxID_ANY, "Student management", "", wxDefaultPosition);
	user_link->Bind(wxEVT_HYPERLINK, &Manage::onUserClick, this);
	student_link->Bind(wxEVT_HYPERLINK, &Manage::onStudentClick, this);
	teacher_link->Bind(wxEVT_HYPERLINK, &Manage::onTeacherClick, this);
	wxBoxSizer* box_manage = new wxBoxSizer(wxVERTICAL);
	box_manage->Add(user_link, 0, wxALIGN_LEFT);
	box_manage->AddSpacer(5);
	box_manage->Add(teacher_link, 0, wxALIGN_LEFT);
	box_manage->AddSpacer(5);
	box_manage->Add(student_link, 0, wxALIGN_LEFT);
	
	box_panel->Add(txt, 0, wxALIGN_LEFT | wxALL, 20);
	box_panel->Add(box_manage, 0, wxALIGN_LEFT | wxALL, 20);
	box_panel->Add(close_btn, 0, wxALIGN_LEFT | wxALL, 20);
	panel->SetSizer(box_panel);
}

void Manage::onClickClose(wxCommandEvent& event)
{
	this->Close();
}

void Manage::onStudentClick(wxHyperlinkEvent& event)
{
	ManageStd* manage_std = new ManageStd("Student manager", m_db);
	manage_std->Show(true);
}

void Manage::onUserClick(wxHyperlinkEvent& event)
{
	ManageUsr* manage_usr = new ManageUsr("User manager", m_db);
	manage_usr->Show(true);
}

void Manage::onTeacherClick(wxHyperlinkEvent& event)
{
	ManageTeacher* manage_teacher = new ManageTeacher("Teacher manager", m_db);
	manage_teacher->Show(true);
}