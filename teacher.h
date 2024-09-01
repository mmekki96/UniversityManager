#ifndef TEACHER_H
#define TEACHER_H

#include <wx/wx.h>
#include <wx/choice.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>
#include "sqlite/sqlite3.h"

class Teacher : public wxPanel
{
public:
	Teacher(wxWindow* parent, sqlite3* db);
private:
	void onAddClick(wxCommandEvent& event);
	void onCalendarClick(wxDateEvent& event);
	void onResetClick(wxCommandEvent& event);
	void onCancelClick(wxCommandEvent& event);
	void clearData();

	wxGridSizer* grid;
	wxButton* add_btn, * reset_btn, * cancel_btn;
	wxStaticText* name_txt, * cin_txt, * birthdate_txt, * gender_txt, * email_txt, * phone_txt, * subject_txt;
	wxTextCtrl* name, * lastname, * cin, * email, * phone;
	wxRadioButton* m_gender, * f_gender;
	wxString date_str;
	wxChoice* subject;
	wxArrayString choices;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
};


#endif // !TEACHER_H
