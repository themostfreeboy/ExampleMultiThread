
// ExampleMultiThreadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExampleMultiThread.h"
#include "ExampleMultiThreadDlg.h"
#include "afxdialogex.h"

#include "afxmt.h"//为了使用事件对象CEvent，所需的头文件
CEvent event1;//事件对象(程序中用到的CEvent对象是线程同步对象，用来在线程之间发送信息)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExampleMultiThreadDlg 对话框




CExampleMultiThreadDlg::CExampleMultiThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExampleMultiThreadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExampleMultiThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
}

BEGIN_MESSAGE_MAP(CExampleMultiThreadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CExampleMultiThreadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CExampleMultiThreadDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_Start, &CExampleMultiThreadDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CExampleMultiThreadDlg 消息处理程序

BOOL CExampleMultiThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExampleMultiThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExampleMultiThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExampleMultiThreadDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	exit(0);
}


void CExampleMultiThreadDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	exit(0);
}


void CExampleMultiThreadDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE thread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc1,&m_edit1,0,NULL);
    HANDLE thread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc2,&m_edit2,0,NULL);
}

UINT proc1(LPARAM lParam)
{
	CEdit* pEdit = (CEdit*)lParam;
    CString str;
    int i=1;
    while(1)
    {
		str.Format(_T("第%d次刷新"),i);
        pEdit->SetWindowText(str);
        if(i%5==0)
        {
			event1.SetEvent();
        }
        i++;
        Sleep(1000);
     }
}
 
 
UINT proc2(LPARAM lParam)
{
	CEdit* pEdit = (CEdit*)lParam;
    CString str;
    CTime time;
    while(1)
    {
		WaitForSingleObject(event1.m_hObject,INFINITE);
        time = CTime::GetCurrentTime();
        str = time.Format(_T("%H : %M : %S"));
        pEdit->SetWindowText(str);
    }
}
