// GraphicsDoc.cpp : CGraphicsDoc 类的实现
//

#include "stdafx.h"
#include "Graphics.h"

#include "GraphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicsDoc

IMPLEMENT_DYNCREATE(CGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicsDoc 构造/析构

CGraphicsDoc::CGraphicsDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGraphicsDoc::~CGraphicsDoc()
{
}

BOOL CGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle(L"蚁群算法");	
	return TRUE;
}

// CGraphicsDoc 序列化

void CGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGraphicsDoc 诊断

#ifdef _DEBUG
void CGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CGraphicsDoc 命令
