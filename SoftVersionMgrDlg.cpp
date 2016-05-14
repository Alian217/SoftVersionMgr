
// SoftVersionMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SoftVersionMgr.h"
#include "SoftVersionMgrDlg.h"
#include "afxdialogex.h"
#include <io.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSoftVersionMgrDlg �Ի���




CSoftVersionMgrDlg::CSoftVersionMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoftVersionMgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoftVersionMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSoftVersionMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSoftVersionMgrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSoftVersionMgrDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSoftVersionMgrDlg ��Ϣ�������

BOOL CSoftVersionMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSoftVersionMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSoftVersionMgrDlg::OnPaint()
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
HCURSOR CSoftVersionMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSoftVersionMgrDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//DD1C_JP87312.txt
	char SoftVerFileName[45] = {0};
	char Type[20] = {0};
	char PF[20] = {0};
	char cRowBuf[LENTH_ROWDATA] = {0};
	char cWDataBuf[LENTH_RWDATA] = {0};
	int  nRowBufLen = 0;
	int  nWDataLen = 0;
	int nPos = 0;
	int nCnt = 0;
	FILE *fp = NULL;
	//��ȡ���ͺ�P# ����
	int nLenType = GetDlgItemText(IDC_EDIT37,Type,20);
	int nLenPF = GetDlgItemText(IDC_EDIT38,PF,20);
	//���˿հ�����
	if (0==nLenType)
	{
		AfxMessageBox(_T("��о����Ϊ�գ�"));
		return;
	}
	else if (0==nLenPF)
	{
		AfxMessageBox(_T("P#����Ϊ�գ�"));
		return;
	}
	//�����ļ���
	memset( SoftVerFileName,'\0',sizeof(SoftVerFileName) );
	memcpy( SoftVerFileName+nPos,Type, nLenType );
	nPos +=nLenType;
	SoftVerFileName[nPos] = '_';
	nPos +=1;
	memcpy( SoftVerFileName+nPos,PF, nLenPF );
	nPos +=nLenPF;
	sprintf( SoftVerFileName+nPos,".txt" );

	memset( cWDataBuf, 0x20, LENTH_RWDATA );
	//��ȡ���а汾��Ϣ��û��Ҳ��LENTH_ROWDATA�ַ�����
	for( nCnt=0;nCnt<SUM_EDIT;nCnt++)
	{
		memset( cRowBuf, 0x20, LENTH_ROWDATA );
		nRowBufLen = GetDlgItemText((IDC_EDIT1+nCnt),cRowBuf,LENTH_ROWDATA);
		memcpy( cWDataBuf+nWDataLen, cRowBuf, LENTH_ROWDATA );
		nWDataLen +=LENTH_ROWDATA;
		cWDataBuf[nWDataLen] ='\n';
		nWDataLen +=1;
	}
	//���ļ�
	fp = fopen( SoftVerFileName, "a+" );
	if( fp == NULL ) 
	{
		AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
		return;
	}
	/*
	��һ������streamΪ�ļ�ָ��
	�ڶ�������offsetΪƫ������������ʾ����ƫ�ƣ�������ʾ����ƫ��
	����������origin�趨���ļ������￪ʼƫ��,����ȡֵΪ��SEEK_CUR�� SEEK_END �� SEEK_SET
	SEEK_SET�� �ļ���ͷ
	SEEK_CUR�� ��ǰλ��
	SEEK_END�� �ļ���β
	����֮��
	����fseek(fp,100L,0);��fpָ���ƶ������ļ���ͷ100�ֽڴ���
	  ��fseek(fp,100L,1);��fpָ���ƶ������ļ���ǰλ��100�ֽڴ���
		fseek(fp,100L,2);��fpָ���˻ص����ļ���β100�ֽڴ���
	*/
	//д�ļ�
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_SET );
		fwrite( cWDataBuf, nWDataLen, 1, fp );
	}
	fclose(fp);

}


void CSoftVersionMgrDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char SoftVerFileName[45] = {0};
	char Type[20] = {0};
	char PF[20] = {0};
	char cReadBuf[LENTH_READDATA] = {0};
	char cRowBuf[LENTH_ROWDATA] = {0};
	int nPos = 0;
	int nCnt = 0;
	FILE *fp = NULL;
	//��ȡ���ͺ�P# ����
	int nLenType = GetDlgItemText(IDC_EDIT37,Type,20);
	int nLenPF = GetDlgItemText(IDC_EDIT38,PF,20);
	//���˿հ�����
	if (0==nLenType)
	{
		AfxMessageBox(_T("��о����Ϊ�գ�"));
		return;
	}
	else if (0==nLenPF)
	{
		AfxMessageBox(_T("P#����Ϊ�գ�"));
		return;
	}
	//�����ļ���
	memset( SoftVerFileName,'\0',sizeof(SoftVerFileName) );
	memcpy( SoftVerFileName+nPos,Type, nLenType );
	nPos +=nLenType;
	SoftVerFileName[nPos] = '_';
	nPos +=1;
	memcpy( SoftVerFileName+nPos,PF, nLenPF );
	nPos +=nLenPF;
	sprintf( SoftVerFileName+nPos,".txt" );

	/*
	int   access(const   char   *filename,   int   amode); 
	amode����Ϊ0ʱ��ʾ����ļ��Ĵ����ԣ�����ļ����ڣ�����0�������ڣ�����-1�� 
	������������Լ�������ļ����ԣ� 
	06     ����дȨ�� 
	04     ����Ȩ�� 
	02     ���дȨ�� 
	01     ���ִ��Ȩ�� 
	00     ����ļ��Ĵ�����
	*/
	if ( 0!=access(SoftVerFileName,0) )
	{
		AfxMessageBox(_T("�ļ�������!������ȷ�ϻ�о��P#!"));
		return;
	}

	//���ļ�
	fp = fopen( SoftVerFileName, "a+" );
	if( fp == NULL ) 
	{
		AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
		return;
	}

	//��ȡһ��������ʾ���༭���ϣ�����Ҳ��LENTH_ROWDATA�ַ�
	for( nCnt=0;nCnt<SUM_EDIT;nCnt++)
	{
		memset( cReadBuf, 0x00, LENTH_READDATA );
		memset( cRowBuf, 0x00, LENTH_ROWDATA );
		fread( cReadBuf, LENTH_READDATA, 1, fp );
		memcpy( cRowBuf, cReadBuf, LENTH_ROWDATA );
		SetDlgItemText(IDC_EDIT1+nCnt,cRowBuf);
	}

	fclose(fp);
	
}
