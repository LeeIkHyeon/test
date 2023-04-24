// SocketDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YouAreBusted.h"
#include "SocketDialog.h"
#include "afxdialogex.h"
#include "YouAreBusted.h"
#include "usb3_dio01_frm_import.h"


// SocketDialog 대화 상자입니다.

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


// SocketDialog 메시지 처리기입니다.


void SocketDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// 표시위치 지정
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_NUMPAD1 || pMsg->wParam == VK_NUMPAD2){
		//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		//DestroyWindow();
		Sleep(10);
	}

	return FALSE;
}
void SocketDialog::setBitmap(int BITMAP)
{
	// 리소스에 있는 비트맵 이미지를 읽기 위해서 CBitmap 클래스 객체를 선언한다.
	CBitmap lamp_image;
	// 리소스에서 IDB_BITMAP2 이미지를 읽는다.
	lamp_image.LoadBitmap(BITMAP);

	// Picture 컨트롤에 새로 읽어들인 이미지를 설정하고 이전에 사용하던 이미지 핸들을
	// p_old_ bitmap 변수에 저장한다.
	HBITMAP h_old_bitmap = pState_Img.SetBitmap(lamp_image);

	// Picture 컨트롤이 이전에 사용하던 이미지가 있었다면 제거한다.
	if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

	// Picture 컨트롤에 이미지를 설정하기 위해서 생성했던 이미지는 Picture 컨트롤이 사용하기
	// 때문에 lamp_image 객체가 종료되면서 삭제되지 않도록 연결을 해제한다.
	// 이 코드를 사용하지 않아도 되는 것처럼 보이지만 해당 Picture 컨트롤이 가려졌다가
	// 다시 보이게 되는 경우 그림이 그려지지 않는다. 따라서 꼭 사용해야 합니다.
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