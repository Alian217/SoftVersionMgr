
// SoftVersionMgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SoftVersionMgr.h"
#include "SoftVersionMgrDlg.h"
#include "afxdialogex.h"
#include <io.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSoftVersionMgrDlg 对话框




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


// CSoftVersionMgrDlg 消息处理程序

BOOL CSoftVersionMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSoftVersionMgrDlg::OnPaint()
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
HCURSOR CSoftVersionMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSoftVersionMgrDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//获取机型和P# 内容
	int nLenType = GetDlgItemText(IDC_EDIT37,Type,20);
	int nLenPF = GetDlgItemText(IDC_EDIT38,PF,20);
	//过滤空白内容
	if (0==nLenType)
	{
		AfxMessageBox(_T("机芯不能为空！"));
		return;
	}
	else if (0==nLenPF)
	{
		AfxMessageBox(_T("P#不能为空！"));
		return;
	}
	//生成文件名
	memset( SoftVerFileName,'\0',sizeof(SoftVerFileName) );
	memcpy( SoftVerFileName+nPos,Type, nLenType );
	nPos +=nLenType;
	SoftVerFileName[nPos] = '_';
	nPos +=1;
	memcpy( SoftVerFileName+nPos,PF, nLenPF );
	nPos +=nLenPF;
	sprintf( SoftVerFileName+nPos,".txt" );

	memset( cWDataBuf, 0x20, LENTH_RWDATA );
	//获取所有版本信息，没有也留LENTH_ROWDATA字符给他
	for( nCnt=0;nCnt<SUM_EDIT;nCnt++)
	{
		memset( cRowBuf, 0x20, LENTH_ROWDATA );
		nRowBufLen = GetDlgItemText((IDC_EDIT1+nCnt),cRowBuf,LENTH_ROWDATA);
		memcpy( cWDataBuf+nWDataLen, cRowBuf, LENTH_ROWDATA );
		nWDataLen +=LENTH_ROWDATA;
		cWDataBuf[nWDataLen] ='\n';
		nWDataLen +=1;
	}
	//打开文件
	fp = fopen( SoftVerFileName, "a+" );
	if( fp == NULL ) 
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
	/*
	第一个参数stream为文件指针
	第二个参数offset为偏移量，整数表示正向偏移，负数表示负向偏移
	第三个参数origin设定从文件的哪里开始偏移,可能取值为：SEEK_CUR、 SEEK_END 或 SEEK_SET
	SEEK_SET： 文件开头
	SEEK_CUR： 当前位置
	SEEK_END： 文件结尾
	简言之：
	　　fseek(fp,100L,0);把fp指针移动到离文件开头100字节处；
	  　fseek(fp,100L,1);把fp指针移动到离文件当前位置100字节处；
		fseek(fp,100L,2);把fp指针退回到离文件结尾100字节处。
	*/
	//写文件
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_SET );
		fwrite( cWDataBuf, nWDataLen, 1, fp );
	}
	fclose(fp);

}


void CSoftVersionMgrDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	char SoftVerFileName[45] = {0};
	char Type[20] = {0};
	char PF[20] = {0};
	char cReadBuf[LENTH_READDATA] = {0};
	char cRowBuf[LENTH_ROWDATA] = {0};
	int nPos = 0;
	int nCnt = 0;
	FILE *fp = NULL;
	//获取机型和P# 内容
	int nLenType = GetDlgItemText(IDC_EDIT37,Type,20);
	int nLenPF = GetDlgItemText(IDC_EDIT38,PF,20);
	//过滤空白内容
	if (0==nLenType)
	{
		AfxMessageBox(_T("机芯不能为空！"));
		return;
	}
	else if (0==nLenPF)
	{
		AfxMessageBox(_T("P#不能为空！"));
		return;
	}
	//生成文件名
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
	amode参数为0时表示检查文件的存在性，如果文件存在，返回0，不存在，返回-1。 
	这个函数还可以检查其它文件属性： 
	06     检查读写权限 
	04     检查读权限 
	02     检查写权限 
	01     检查执行权限 
	00     检查文件的存在性
	*/
	if ( 0!=access(SoftVerFileName,0) )
	{
		AfxMessageBox(_T("文件不存在!请重新确认机芯和P#!"));
		return;
	}

	//打开文件
	fp = fopen( SoftVerFileName, "a+" );
	if( fp == NULL ) 
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}

	//读取一行数据显示到编辑框上，长度也是LENTH_ROWDATA字符
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
