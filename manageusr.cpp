#include "manageusr.h"
#include "action.h"

ManageUsr::ManageUsr(const wxString& title, sqlite3* db) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	wxGridSizer* gridsizer = new wxGridSizer(2, 1, 0, 0);
	close_btn = new wxButton(this, wxID_ANY, "Close", wxDefaultPosition, wxDefaultSize);
	close_btn->Bind(wxEVT_BUTTON, &ManageUsr::onClickClose, this);
	menu = new wxMenuBar();
	file_menu = new wxMenu();
	file_menu->Append(wxID_EDIT, "&Edit");
	file_menu->Append(wxID_DELETE, "&Delete");
	menu->Append(file_menu, "&File");
	SetMenuBar(menu);
	Bind(wxEVT_MENU, &ManageUsr::onClickDelete, this, wxID_DELETE);

	grid = new wxGrid(this, wxID_ANY);
	grid->CreateGrid(0, 0);
	const char* sql_select = "SELECT * FROM Admins;";
	int exit = sqlite3_prepare_v2(m_db, sql_select, -1, &stmt, NULL);
	if (exit != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
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
			wxString val = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
			grid->SetCellValue(row, col, val);
		}
		row++;
	}
	sqlite3_finalize(stmt);
	gridsizer->Add(grid, 0, wxALL, 20);
	gridsizer->Add(close_btn, 0, wxALL | wxALIGN_BOTTOM, 20);
	this->SetSizer(gridsizer);
	Bind(EVT_TABLE_UPDATE, &ManageUsr::onTableUpdate, this);
	loadData();

}

void ManageUsr::onClickDelete(wxCommandEvent& event)
{
	DeleteUsr* delete_usr = new DeleteUsr("User manager", m_db, this);
	delete_usr->Show(true);
}

void ManageUsr::onClickClose(wxCommandEvent& event)
{
	this->Close();
}

void ManageUsr::onTableUpdate(wxCommandEvent& event)
{
	loadData();
}

void ManageUsr::loadData()
{
	grid->ClearGrid();
	if (grid->GetNumberRows() > 0)
		grid->DeleteRows(0, grid->GetNumberRows());

	const char* sql = "SELECT * FROM Admins;";
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