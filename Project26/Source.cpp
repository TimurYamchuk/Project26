#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <string>
#include <map>

class CMainModalDialog
{
public:
	CMainModalDialog(void);
public:
	~CMainModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hEdit1, hStatic1, hList1;

};

class CModelessDialog
{
public:
	CModelessDialog(void);
public:
	~CModelessDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CModelessDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hStatic, hList;
	static HWND hAddDialog; 
	void SetText(LPCTSTR str);

};


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	CMainModalDialog dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, CMainModalDialog::DlgProc);
}


CModelessDialog* CModelessDialog::ptr = NULL;
HWND CModelessDialog::hAddDialog = NULL;

CModelessDialog::CModelessDialog(void)
{
	ptr = this;
}

CModelessDialog::~CModelessDialog(void)
{

}

void CModelessDialog::Cls_OnClose(HWND hwnd)
{
	
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

void CModelessDialog::SetText(LPCTSTR str)
{
	TCHAR text[100];
	_tcscpy(text, str);
	SetWindowText(hStatic, text);

}

BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("Дополнительный немодальный диалог"));
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("Передача данных главному диалогу!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		TCHAR buffer[200];
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), buffer, 200);
		HWND hParent = GetParent(hwnd);
		HWND hList = GetDlgItem(hParent, IDC_LIST1);
	
		SendMessage(hList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(buffer));
		return;
	}
	else if (id == IDCANCEL)
	{
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CModelessDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	hList1 = GetDlgItem(hwnd, IDC_LIST1);
	SendMessage(hList1, LB_SETCOLUMNWIDTH, 200, 0);
	SendMessage(hList1, LB_SETHORIZONTALEXTENT, 400, 0);
	SendMessage(hList1, LB_SETTABSTOPS, 0, NULL);
	SendMessage(hList1, LB_SETSEL, TRUE, -1);
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static CModelessDialog dlg;
	if (id == IDC_BUTTON1 || id == IDC_BUTTON2 || id == IDC_BUTTON3)
	{
		CModelessDialog::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CModelessDialog::DlgProc);
		ShowWindow(CModelessDialog::hAddDialog, SW_RESTORE);
		TCHAR buffer[200];
		GetWindowText(hEdit1, buffer, 200);
		dlg.SetText(buffer);
		return;
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
