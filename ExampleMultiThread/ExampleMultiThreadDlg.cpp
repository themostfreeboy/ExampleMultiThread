
// ExampleMultiThreadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExampleMultiThread.h"
#include "ExampleMultiThreadDlg.h"
#include "afxdialogex.h"

#include "afxmt.h"//Ϊ��ʹ���¼�����CEvent�������ͷ�ļ�
CEvent event1;//�¼�����(�������õ���CEvent�������߳�ͬ�������������߳�֮�䷢����Ϣ)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExampleMultiThreadDlg �Ի���




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


// CExampleMultiThreadDlg ��Ϣ�������

BOOL CExampleMultiThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExampleMultiThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExampleMultiThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExampleMultiThreadDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	exit(0);
}


void CExampleMultiThreadDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	exit(0);
}


void CExampleMultiThreadDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		str.Format(_T("��%d��ˢ��"),i);
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
