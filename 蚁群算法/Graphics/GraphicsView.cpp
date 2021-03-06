// GraphicsView.cpp : CGraphicsView 类的实现
//

#include "stdafx.h"
#include "Graphics.h"

#include "GraphicsDoc.h"
#include "GraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int result[6];
extern double city[6][2];
extern doubleMatrix D;
extern double c[6][6];
// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DRAWITEM()
	ON_WM_DRAWCLIPBOARD()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGraphicsView 构造/析构

CGraphicsView::CGraphicsView()
{
	// TODO: 在此处添加构造代码
	this->flag=true;
}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphicsView 绘制
//记得在此函数加上pDc参数
void CGraphicsView::OnDraw(CDC* pDC/*pDC*/)
{	
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
		//标记城市序号-----------------------------------------------------------------------------
		CFont font;
		CFont *pOldFont=pDC->SelectObject(&font);
		CString str;		
		for(int i=0;i<6;i++){
			str.Format(_T("%d"),i+1);
			pDC->TextOutW(city[i][0]+10,city[i][1]+10,str,1);
		}
		pDC->SelectObject(pOldFont);
		//用虚线画出城市连线----------------------------------------------------------------------
		CBrush brush(RGB(0,0,0));
		CBrush* pOldBrush=pDC->SelectObject(&brush);
		for(int i=0;i<6;i++)
			pDC->Ellipse(CRect(city[i][0]+10,city[i][1]+10,city[i][0]-10,city[i][1]-10));
		pDC->SelectObject(pOldBrush);
		CPen pen(PS_DASH,1,RGB(0,0,255));//构造一个虚线，1像素宽，绿色的画笔
		CPen* pOldPen=pDC->SelectObject(&pen);//将新画笔选入描述表，并得到原先设备描述表中的画笔地址	
		for(int i=0;i<6;i++)
			for(int j=i;j<6;j++)
				if(c[i][j]==1){
					pDC->MoveTo(CPoint(city[i][0],city[i][1]));
					pDC->LineTo(CPoint(city[j][0],city[j][1]));		
				}
		pDC->SelectObject(pOldPen);//恢复设备描述表中原先的画笔类型
		this->flag=true;
}

// CGraphicsView 打印

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGraphicsView 诊断

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

void CGraphicsView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);
	OnDraw(&dc);
}
//点击鼠标画出最优回路
void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point){
	if(flag){
		::MessageBox(NULL,_T("完成求解"),_T("提示"),MB_OK);
		CDC* pDC=GetDC();
		CPen pen(PS_SOLID,2,RGB(0,0,0));//构造一个实线，2像素宽，黑的画笔
		CPen* pOldPen=pDC->SelectObject(&pen);
		for(int i=0;i<6;i++)
			if(i!=5){
				pDC->MoveTo(CPoint(city[result[i]-1][0],city[result[i]-1][1]));
				pDC->LineTo(CPoint(city[result[i+1]-1][0],city[result[i+1]-1][1]));
			}
			else{
				pDC->MoveTo(CPoint(city[result[i]-1][0],city[result[i]-1][1]));
				pDC->LineTo(CPoint(city[0][0],city[0][1]));
			}
		pDC->SelectObject(pOldPen);
		flag=false;
	}
}