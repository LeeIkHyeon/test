// SocketDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "YouAreBusted.h"
#include "SocketDialog.h"
#include "afxdialogex.h"
#include "YouAreBusted.h"
#include "usb3_dio01_frm_import.h"


// SocketDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SocketDialog, CDialogEx)

SocketDialog::SocketDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Socket, pParent)
{
}

SocketDialog::~SocketDialog()
{
}

void SocketDialog::DoDataExchange(CDataExchange* pDX)
{
	//MessageBox("ddd");
	SetTimer(0, 500, NULL);
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STATE_BLAND, pState_Img);
}


BEGIN_MESSAGE_MAP(SocketDialog, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SocketDialog �޽��� ó�����Դϴ�.


void SocketDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Sokect_Result  = Sokect_Check();
	if (!Sokect_Result) {
		KillTimer(0);
		::PostMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		//Sleep(10);
	}

	if (STATE) {
		setBitmap(IDB_BITMAP_Socket_Bl);
		STATE = 0;
	}
	else {
		setBitmap(IDB_BITMAP_Socket_Open);
		STATE = 1;
	}
	CDialogEx::OnTimer(nIDEvent);
}
void SocketDialog::Sokect_ISP(CString strISPFilePath,int num)
{
	RECT rect;
	int width;
	int height;

	// ǥ����ġ ����
	//SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);
	m_strISPFilePath = strISPFilePath;
	m_nDeviceNum = num;
	Sokect_Result = FALSE;
	WritePrivateProfileStringA("ISP", "Socket", "1", m_strISPFilePath);
}
BOOL SocketDialog::Sokect_Check()
{
	char temp[20];
	GetPrivateProfileStringA("ISP", "Socket", "0", temp, sizeof(temp), m_strISPFilePath);
	int result = strtol(temp, NULL, 10);
	return result;

}
BOOL SocketDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_NUMPAD1 || pMsg->wParam == VK_NUMPAD2){
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		//DestroyWindow();
		Sleep(10);
	}

	return FALSE;
}
void SocketDialog::setBitmap(int BITMAP)
{
	// ���ҽ��� �ִ� ��Ʈ�� �̹����� �б� ���ؼ� CBitmap Ŭ���� ��ü�� �����Ѵ�.
	CBitmap lamp_image;
	// ���ҽ����� IDB_BITMAP2 �̹����� �д´�.
	lamp_image.LoadBitmap(BITMAP);

	// Picture ��Ʈ�ѿ� ���� �о���� �̹����� �����ϰ� ������ ����ϴ� �̹��� �ڵ���
	// p_old_ bitmap ������ �����Ѵ�.
	HBITMAP h_old_bitmap = pState_Img.SetBitmap(lamp_image);

	// Picture ��Ʈ���� ������ ����ϴ� �̹����� �־��ٸ� �����Ѵ�.
	if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

	// Picture ��Ʈ�ѿ� �̹����� �����ϱ� ���ؼ� �����ߴ� �̹����� Picture ��Ʈ���� ����ϱ�
	// ������ lamp_image ��ü�� ����Ǹ鼭 �������� �ʵ��� ������ �����Ѵ�.
	// �� �ڵ带 ������� �ʾƵ� �Ǵ� ��ó�� �������� �ش� Picture ��Ʈ���� �������ٰ�
	// �ٽ� ���̰� �Ǵ� ��� �׸��� �׷����� �ʴ´�. ���� �� ����ؾ� �մϴ�.
	lamp_image.Detach();
}
//
//LRESULT SocketDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
//
//	if (message == this->g_nRegMsg && (HWND)wParam != this->GetSafeHwnd())
//	{
//		switch (lParam)
//		{
//		}
//	}
//	return TRUE;
//}