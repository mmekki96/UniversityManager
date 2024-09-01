#include "form.h"
#include "teacher.h"
#include "student.h"
#include "user.h"
#include "subject.h"

Form::Form(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 600)), m_db(db)
{
	notebook = new wxNotebook(this, wxID_ANY);
	User* admin = new User(notebook, m_db);
	Teacher* teacher = new Teacher(notebook, m_db);
	Student* student = new Student(notebook, m_db);
	Subject* subject = new Subject(notebook, m_db);

	notebook->AddPage(admin, "Admin");
	notebook->AddPage(teacher, "Teacher");
	notebook->AddPage(student, "Student");
	notebook->AddPage(subject, "Subject");
}