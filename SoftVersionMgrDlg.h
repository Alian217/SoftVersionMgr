
// SoftVersionMgrDlg.h : ͷ�ļ�
//
#define LENTH_ROWDATA  100                        //100char
#define LENTH_READDATA (LENTH_ROWDATA+1)          //100char+'\n'
#define SUM_EDIT       36           //һ���༭��36��
#define LENTH_RWDATA   ((LENTH_ROWDATA+1)*SUM_EDIT)

#pragma once


// CSoftVersionMgrDlg �Ի���
class CSoftVersionMgrDlg : public CDialogEx
{
// ����
public:
	CSoftVersionMgrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOFTVERSIONMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
