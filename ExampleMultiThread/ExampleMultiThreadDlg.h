
// ExampleMultiThreadDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CExampleMultiThreadDlg �Ի���
class CExampleMultiThreadDlg : public CDialogEx
{
// ����
public:
	CExampleMultiThreadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXAMPLEMULTITHREAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_edit1;
	CEdit m_edit2;
	afx_msg void OnBnClickedStart();
};

UINT proc1(LPARAM lParam);
UINT proc2(LPARAM lParam);
