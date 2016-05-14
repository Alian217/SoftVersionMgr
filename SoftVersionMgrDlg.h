
// SoftVersionMgrDlg.h : 头文件
//
#define LENTH_ROWDATA  100                        //100char
#define LENTH_READDATA (LENTH_ROWDATA+1)          //100char+'\n'
#define SUM_EDIT       36           //一共编辑框36个
#define LENTH_RWDATA   ((LENTH_ROWDATA+1)*SUM_EDIT)

#pragma once


// CSoftVersionMgrDlg 对话框
class CSoftVersionMgrDlg : public CDialogEx
{
// 构造
public:
	CSoftVersionMgrDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOFTVERSIONMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
