
// ExampleMultiThreadDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CExampleMultiThreadDlg 对话框
class CExampleMultiThreadDlg : public CDialogEx
{
// 构造
public:
	CExampleMultiThreadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXAMPLEMULTITHREAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
