#include "managestd.h"
#include "action.h"


ManageStd::ManageStd(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	menu = new wxMenuBar();
	file_menu = new wxMenu();
	file_menu->Append(wxID_EDIT, "&Edit");
	file_menu->Append(wxID_DELETE, "&Delete");
	menu->Append(file_menu, "&File");
	SetMenuBar(menu);
	file_menu->Bind(wxEVT_MENU, &ManageStd::onClickDelete, this, wxID_DELETE);

	wxGridSizer* grid_box = new wxGridSizer(2, 1, 0, 0);
	close_btn = new wxButton(this, wxID_ANY, "Close");
	close_btn->Bind(wxEVT_BUTTON, &ManageStd::onClickClose, this);
	grid = new wxGrid(this, wxID_ANY);
	grid->CreateGrid(0, 0);
	const char* sql = "SELECT name, lastname, cin, email, gender, birthdate, phone FROM Students;";
	int rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Faile to execute querry %s", sqlite3_errmsg(m_db));
		return;
	}
	int numCols = sqlite3_column_count(stmt);
	grid->AppendCols(numCols);

	for (int col = 0; col < numCols; col++)
	{
		grid->SetColLabelValue(col, wxString::FromUTF8(sqlite3_column_name(stmt, col)));
	}

	int row = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		grid->AppendRows(1);
		for (int col = 0; col < numCols; col++)
		{
			wxString value = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
			grid->SetCellValue(row, col, value);
		}
		row++;
	}

	sqlite3_finalize(stmt);
	grid_box->Add(grid, 0, wxALL, 20);
	grid_box->Add(close_btn, 0, wxALIGN_BOTTOM | wxALL, 20);

	Bind(EVT_TABLE_UPDATE, &ManageStd::onTableUpdate, this);
	
	this->SetSizerAndFit(grid_box);
	loadData();
}

void ManageStd::onClickClose(wxCommandEvent& event)
{
	this->Close();
}

void ManageStd::onClickDelete(wxCommandEvent& event)
{
	DeleteStd* delete_std = new DeleteStd("Delete student", m_db, this);
	delete_std->Show(true);
}

void ManageStd::loadData()
{
	grid->ClearGrid();
	if (grid->GetNumberRows() > 0)
		grid->DeleteRows(0, grid->GetNumberRows());

	const char* sql = "SELECT name, lastname, cin, email, gender, birthdate, phone FROM Students;";
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

void ManageStd::onTableUpdate(wxCommandEvent& event)
{
	ManageStd::loadData();
}