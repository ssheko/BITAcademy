// ConnectDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// ConnectDlg 대화 상자

IMPLEMENT_DYNAMIC(ConnectDlg, CDialogEx)

ConnectDlg::ConnectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONNECT, pParent)
	, m_ipaddress(_T(""))
{

	m_ipaddress = _T("");
}

ConnectDlg::~ConnectDlg()
{
}

void ConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS, m_ipaddress);
}


BEGIN_MESSAGE_MAP(ConnectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONNECTS, &ConnectDlg::OnBnClickedButtonConnects)
END_MESSAGE_MAP()


// ConnectDlg 메시지 처리기


BOOL ConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_IPADDRESS, _T("127.0.0.1"));	// 루프백으로 초기화

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ConnectDlg::OnBnClickedButtonConnects()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS, m_ipaddress);
}
