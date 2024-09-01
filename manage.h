#ifndef MANAGE_H
#define MANAGE_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/hyperlink.h>
#include "sqlite/sqlite3.h"

class Manage : public wxFrame
{
public:
	Manage(const wxString& title, sqlite3 *db);
private:
	void onClickClose(wxCommandEvent& event);
	void onUserClick(wxHyperlinkEvent& event);
	void onTeacherClick(wxHyperlinkEvent& event);
	void onStudentClick(wxHyperlinkEvent& event);
	sqlite3* m_db;
	wxButton * close_btn;
	wxHyperlinkCtrl* user_link, * teacher_link, * student_link;
};



#endif // !MANAGE_H
