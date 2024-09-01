#include "managetchr.h"
#include "action.h"

ManageTeacher::ManageTeacher(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	menu = new wxMenuBar();
	file_menu = new wxMenu();
	file_menu->Append(wxID_EDIT, "&Edit");
	file_menu->Append(wxID_DELETE, "&Delete");
	menu->Append(file_menu, "&File");
	SetMenuBar(menu);
	Bind(wxEVT_MENU, &ManageTeacher::onClickDelete, this, wxID_DELETE);

	wxGridSizer* gridsizer = new wxGridSizer(2, 1, 0, 0);
	close_btn = new wxButton(this, wxID_ANY, "Close", wxDefaultPosition, wxDefaultSize);
	close_btn->Bind(wxEVT_BUTTON, &ManageTeacher::onClickClose, this);
	grid = new wxGrid(this, wxID_ANY);
	grid->CreateGrid(0, 0);
	const char* sql_select = "SELECT name, lastname, subject, cin, email, gender, birthdate, phone FROM Teachers;";
	int rc = sqlite3_prepare_v2(m_db, sql_select, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Faile to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	int numCols = sqlite3_column_count(stmt);
	grid->AppendCols(numCols);
	for (int col = 0; col < numCols; col++)
		grid->SetColLabelValue(col, wxString::FromUTF8(sqlite3_column_name(stmt, col)));

	int row = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		grid->AppendRows(1);
		for (int col = 0; col < numCols; col++)
		{
			wxString val = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
			grid->SetCellValue(row, col, val);
		}
		row++;
	}
	sqlite3_finalize(stmt);
	gridsizer->Add(grid, 0, wxALL, 20);
	gridsizer->Add(close_btn, 0, wxALL | wxALIGN_BOTTOM, 20);
	Bind(EVT_TABLE_UPDATE, &ManageTeacher::onTableUpdate, this);
	this->SetSizerAndFit(gridsizer);
	loadData();
}

void ManageTeacher::onClickClose(wxCommandEvent& event)
{
	this->Close();
}

void ManageTeacher::onClickDelete(wxCommandEvent& event)
{
	DeleteTeacher* del_teacher = new DeleteTeacher("Teacher manager", m_db, this);
	del_teacher->Show(true);
}

void ManageTeacher::loadData()
{
	grid->ClearGrid();
	if (grid->GetNumberRows() > 0)
		grid->DeleteRows(0, grid->GetNumberRows());

	const char* sql = "SELECT name, lastname, subject, cin, email, gender, birthdate, phone FROM Teachers;";
	int exit = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (exit != SQLITE_OK)
	{
		wxLogError("Faile to execute querry %s", sqlite3_errmsg(m_db));
		return;
	}
	int rows = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		grid->AppendRows(1);
		for (int col = 0; col < sqlite3_column_count(stmt); col++)
		{
			wxString val = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
			grid->SetCellValue(rows, col, val);
		}
		rows++;
	}
}

void ManageTeacher::onTableUpdate(wxCommandEvent& event)
{
	loadData();
}