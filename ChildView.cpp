
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Figure.h"
#include "2020-1_MFCPaint.h"
#include "ChildView.h"
#include <vector>
#include <string>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CChildView

/* khlee: window view 의 생성자 */
CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	drawings.clear();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_DRAWCIRCLE, &CChildView::OnDrawcircle)
	ON_UPDATE_COMMAND_UI(ID_DRAWCIRCLE, &CChildView::OnUpdateDrawcircle)
	ON_COMMAND(ID_DRAWLINE, &CChildView::OnDrawline)
	ON_UPDATE_COMMAND_UI(ID_DRAWLINE, &CChildView::OnUpdateDrawline)
	ON_COMMAND(ID_DRAWRECT, &CChildView::OnDrawrect)
	ON_UPDATE_COMMAND_UI(ID_DRAWRECT, &CChildView::OnUpdateDrawrect)
	ON_COMMAND(ID_EDITCOPY, &CChildView::OnEditcopy)
	ON_UPDATE_COMMAND_UI(ID_EDITCOPY, &CChildView::OnUpdateEditcopy)
	ON_COMMAND(ID_EDITCUT, &CChildView::OnEditcut)
	ON_UPDATE_COMMAND_UI(ID_EDITCUT, &CChildView::OnUpdateEditcut)
	ON_COMMAND(ID_EDITDEL, &CChildView::OnEditdel)
	ON_UPDATE_COMMAND_UI(ID_EDITDEL, &CChildView::OnUpdateEditdel)
	ON_COMMAND(ID_EDITDELALL, &CChildView::OnEditdelall)
	ON_UPDATE_COMMAND_UI(ID_EDITDELALL, &CChildView::OnUpdateEditdelall)
	ON_COMMAND(ID_EDITGROUP, &CChildView::OnEditgroup)
	ON_UPDATE_COMMAND_UI(ID_EDITGROUP, &CChildView::OnUpdateEditgroup)
	ON_COMMAND(ID_EDITPASTE, &CChildView::OnEditpaste)
	ON_UPDATE_COMMAND_UI(ID_EDITPASTE, &CChildView::OnUpdateEditpaste)
	ON_COMMAND(ID_EDITUNGROUP, &CChildView::OnEditungroup)
	ON_UPDATE_COMMAND_UI(ID_EDITUNGROUP, &CChildView::OnUpdateEditungroup)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CPen doFigureSelectPen(PS_ALL, 2, RGB(200, 200, 200));	// 도형을 선택하기 위한 드래그에 대한 펜
	CPen drawPen(PS_DASH, 1, RGB(0, 0, 200));	// 도형을 그리기 위한 드래그에 대한 펜
	CPen figurePointPen(PS_ALL, 3, RGB(200, 200, 200));	// 8방향의 점을 그리기 위한 펜

	/* khlee: 저장해둔 도형들을 모두 그려줌. */
	for (int i = 0; i < drawings.size(); i++)
		drawings[i]->draw(&dc);

	switch(mode)
	{
	case DO_FIGURE_SELECT:
		dc.SelectObject(&doFigureSelectPen);
		dc.SelectStockObject(HOLLOW_BRUSH);
		if (selecting_region != NULL)
			selecting_region->draw(&dc);
		break;
	case DRAW_RECT:
	case DRAW_ELLI:
	case DRAW_LINE:
		dc.SelectObject(&drawPen);
		dc.SelectStockObject(HOLLOW_BRUSH);
		if (selecting_region != NULL)
			selecting_region->draw(&dc);
		break;
	case FIGURE_SELECTED:
		dc.SelectObject(&figurePointPen);
		for (int i = 0; i < figure_point.size(); i++)	// 8방향의 점을 모두 그려줌
			figure_point[i]->draw(&dc);
		break;
	}

	/* khlee: 현재 마우스 포인터의 좌표값 출력 (좌표계에 익숙해지면 삭제하세요) */
	//string msg = "Mouse Pose x : " + to_string(current_point.x) + " y: " + to_string(current_point.y);
	//CString cmsg(msg.c_str());
	//dc.TextOut(0, 0, cmsg);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnDrawcircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/* jklim: 모드를 원 그리기 모드로 변경 */
	mode = DRAW_ELLI;
}


void CChildView::OnUpdateDrawcircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnDrawline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/* jklim: 모드를 원 그리기 모드로 변경 */
	mode = DRAW_LINE;
}


void CChildView::OnUpdateDrawline(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnDrawrect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/* khlee: 모드를 사각형 그리기 모드로 변경 */
	mode = DRAW_RECT;
}


void CChildView::OnUpdateDrawrect(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnEditcopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!selected_region.empty())
	{
		
		if (!clipboard.empty()) // 클립보드가 이미 차 있다면 들어있는 객체를 모두 삭제
		{
			for (vector<Figure*>::reverse_iterator cit = clipboard.rbegin(); cit != clipboard.rend(); cit++)
				(*cit)->remove();
			clipboard.clear();
		}

		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{
			clipboard.push_back((*vit)->clone());
		}
	}
	Invalidate(true);
}


void CChildView::OnUpdateEditcopy(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	/* Khlee: 버튼 활성화/비활성화 */
	if (!selected_region.empty())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditcut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!selected_region.empty())
	{
		if (!clipboard.empty()) // 클립보드가 이미 차 있다면 들어있는 객체를 모두 삭제
		{
			for (vector<Figure*>::reverse_iterator cit = clipboard.rbegin(); cit != clipboard.rend(); cit++)	
				(*cit)->remove();
			clipboard.clear();
		}

		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{
			clipboard.push_back(*vit);
			drawings.erase(remove(drawings.begin(), drawings.end(), *vit), drawings.end());
		}
		
		selected_region.clear();
		removeFigurePoint();
	}
	Invalidate(true);
}


void CChildView::OnUpdateEditcut(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	/* Khlee: 버튼 활성화/비활성화 */
	if (!selected_region.empty())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditdel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (drawings.size() > 0 && mode == FIGURE_SELECTED)
	{
		removeFigurePoint();
		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{
			drawings.erase(remove(drawings.begin(), drawings.end(), *vit), drawings.end());
			(*vit)->remove();
		}

		for (vector<Figure*>::reverse_iterator vit = figure_point.rbegin(); vit != figure_point.rend(); vit++)
			(*vit)->remove();
		
		selected_region.clear();
		mode = NORMAL;
		Invalidate(true);
	}
}


void CChildView::OnUpdateEditdel(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	/* Khlee: 버튼 활성화/비활성화 */
	if (!selected_region.empty())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditdelall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!drawings.empty())
	{
		removeFigurePoint();
		for (vector<Figure*>::iterator vit = drawings.begin(); vit != drawings.end(); vit++)
			(*vit)->remove();
		drawings.clear();
		clipboard.clear();
	}
	Invalidate(true);
}


void CChildView::OnUpdateEditdelall(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (!drawings.empty())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditgroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (selected_region.size() > 1)
	{
		FigureGroup* tmp_fig = new FigureGroup(selected_region.front()->getP1(), selected_region.front()->getP2());
		for (vector<Figure*>::iterator vit = selected_region.begin(); vit != selected_region.end(); vit++)
		{
			tmp_fig->addChild(*vit);
		}
		
		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{
			drawings.erase(remove(drawings.begin(), drawings.end(), *vit), drawings.end());
		}
		drawings.push_back(tmp_fig);
		selected_region.clear();
		selected_region.push_back(tmp_fig);
		setFigurePoint();
		mode = FIGURE_SELECTED;
	}
	Invalidate(true);
}


void CChildView::OnUpdateEditgroup(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (selected_region.size() > 1)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditpaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!clipboard.empty())
	{
		for (vector<Figure*>::iterator vit = clipboard.begin(); vit != clipboard.end(); vit++)
		{
			drawings.push_back((*vit)->clone());
		}
	}

	Invalidate(true);
}


void CChildView::OnUpdateEditpaste(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	/* Khlee: 버튼 활성화/비활성화 */
	if (!clipboard.empty())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnEditungroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!selected_region.empty())
	{
		vector<Figure*> tmp_vfig;	// 선택된 영역을 그대로 유지하기 위해 필요
		vector<Figure*>::iterator tmpit;

		for (vector<Figure*>::iterator vit = selected_region.begin(); vit != selected_region.end(); vit++)
		{
			tmpit = vit;
			if (nullptr != dynamic_cast<FigureGroup*>(*vit))	// Class Type이 FigureGroup인지 확인
			{
				vector<Figure*> tmp_fig2 = (dynamic_cast<FigureGroup*>(*vit))->getChild();
				for (vector<Figure*>::iterator fit = tmp_fig2.begin(); fit != tmp_fig2.end(); fit++)
				{
					drawings.push_back(*fit);
					tmp_vfig.push_back(*fit);
				}

				drawings.erase(remove(drawings.begin(), drawings.end(), *vit), drawings.end());
				

				dynamic_cast<FigureGroup*>(*vit)->clear();	// 그룹의 자식 노드를 비운 뒤 제거
			}
			else
			{
				/*assert(*vit != NULL);*/
				tmp_vfig.push_back(*vit);
			}
		}
		
		selected_region.clear();
		selected_region = tmp_vfig;
		setFigurePoint();
		mode = FIGURE_SELECTED;
	}
	Invalidate(true);
}


void CChildView::OnUpdateEditungroup(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
	{
		if (nullptr != dynamic_cast<FigureGroup*>(*vit))
		{
			pCmdUI->Enable(true);
			return;
		}
	}
	pCmdUI->Enable(false);

}


/* khlee: 마우스 왼쪽 버튼 누를 때 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/* khlee: 마우스 왼쪽 버튼이 눌렸을 때, cursor mode에 따른 여러가지 처리 */
	/* 두번째 parameter인 point에 클릭 당시의 좌표가 넘어옴 */
	/* CChildView 멤버 변수인 starting_point에 현재 point 좌표를 저장: 
	마우스 드래그를 지원하기 위하여 */
	starting_point = point;

	switch (mode)
	{
	case DRAW_RECT:
		selecting_region = new FigureRectangle(starting_point, point);
		break;
	case DRAW_ELLI:
		selecting_region = new FigureEllipse(starting_point, point);
		break;
	case DRAW_LINE:
		selecting_region = new FigureLine(starting_point, point);
		break;
	case FIGURE_SELECTED:
		if (isOnFigurePoint()) // 8방향의 작은 점위에 마우스 포인터가 있는 경우
		{
			selecting_point = getOnFigurePoint();
			mode = DO_POINT_SELECT;
			break;
		}
	case NORMAL:
		if (!isOnDrawnFigure())	// 도형이 없는 공간을 클릭한 경우
		{
			if (selecting_region != NULL)
				selecting_region->remove();
			selecting_region = new FigureRectangle(starting_point, point);
			selected_region.clear();
			mode = FIGURE_SELECTED;
		}
		else
		{
			if (!isOnSelectedFigure())	// 선택된 객체 이외의 객체를 클릭한 경우
			{
				selected_region.clear();
				for (vector<Figure*>::reverse_iterator vit = drawings.rbegin(); vit != drawings.rend(); vit++)	// 선택한 객체의 주소값 추출
				{
					if ((*vit)->onFigure(current_point))
					{
						selected_region.push_back(*vit);
						break;
					}
				}
			}
			mode = FIGURE_SELECTED;
		}
		break;
	default:
		break;
	}

	Invalidate(true);
	CWnd::OnLButtonDown(nFlags, point);
}

/* khlee: 마우스 왼쪽 버튼 뗄 때 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (mode)
	{
	case DRAW_RECT:
		/* 현재까지 그려진 모양 그대로 도형 (사각형) 을 생성해서, 내부 벡터에 저장해줌*/
		drawings.push_back(new FigureRectangle(selecting_region->getP1(), selecting_region->getP2()));
		mode = NORMAL;				/* 마우스 선택 모드를 일반 모드로 변경*/
		break;
	case DRAW_ELLI:
		/* 현재까지 그려진 모양 그대로 도형 (원) 을 생성해서, 내부 벡터에 저장해줌*/
		drawings.push_back(new FigureEllipse(selecting_region->getP1(), selecting_region->getP2()));
		mode = NORMAL;				/* 마우스 선택 모드를 일반 모드로 변경*/	
		break;
	case DRAW_LINE:
		/* 현재까지 그려진 모양 그대로 도형 (선) 을 생성해서, 내부 벡터에 저장해줌*/
		drawings.push_back(new FigureLine(selecting_region->getP1(), selecting_region->getP2()));
		drawings.back()->correctPoint();
		setFigurePoint();
		mode = NORMAL;				/* 마우스 선택 모드를 일반 모드로 변경*/
		break;

	case NORMAL:
	case FIGURE_SELECTED:
	case FIGURE_MOVE:
		removeFigurePoint();

		if (isOnDrawnFigure())
		{
			setFigurePoint();
			mode = FIGURE_SELECTED;
		}
		else
		{
			mode = NORMAL;
		}
		break;
	case DO_FIGURE_SELECT:
		for (vector<Figure*>::iterator vit = drawings.begin(); vit != drawings.end(); vit++)
		{
			CPoint tmpPoint1, tmpPoint2;
			// correctPoint()
			if (starting_point.x < current_point.x)
			{
				tmpPoint1.x = starting_point.x;
				tmpPoint2.x = current_point.x;
			}
			else
			{
				tmpPoint1.x = current_point.x;
				tmpPoint2.x = starting_point.x;
			}

			if (starting_point.y < current_point.y)
			{
				tmpPoint1.y = starting_point.y;
				tmpPoint2.y = current_point.y;
			}
			else
			{
				tmpPoint1.y = current_point.y;
				tmpPoint2.y = starting_point.y;
			}

			if (tmpPoint1.x <= (*vit)->getP1().x && (*vit)->getP2().x <= tmpPoint2.x && tmpPoint1.y <= (*vit)->getP1().y && (*vit)->getP2().y <= tmpPoint2.y)
			{
				selected_region.push_back(*vit);
			}
		}
		setFigurePoint();
		mode = FIGURE_SELECTED;
		
		break;
	case DO_POINT_SELECT:
		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{
			(*vit)->correctPoint();
		}

		setFigurePoint();
		
		mode = FIGURE_SELECTED;
		// cursor 모양 원위치 시켜야 함
		OnMouseMove(nFlags, current_point);
		break;
	default:
		mode = NORMAL;
		break;
	}

	if (selecting_region != NULL)	// 선택중인 영역이 있다면 삭제
	{
		selecting_region->remove();
		selecting_region = NULL;
	}

	Invalidate(true);	// OnPaint() 호출로 화면 업데이트
	CWnd::OnLButtonUp(nFlags, point);
}

/* khlee: 마우스 이동 중 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDC* dc = GetDC();
	int figurePointSeq;

	/* Khlee: 마우스 왼쪽 버튼이 눌린 상태로 움직이고 있을 때,
	point는 현재의 마우스 좌표 (이동된) 를 넘겨받음 */
	current_point = point;
	
	if (mode == NORMAL || mode == FIGURE_SELECTED)
	{
		figurePointSeq = isOnFigurePoint();

		if (figurePointSeq)
		{
			switch (figurePointSeq)
			{
			case 1:
			case 8:
				SetCursor(LoadCursor(0, IDC_SIZENWSE));
				break;
			case 2:
			case 7:
				SetCursor(LoadCursor(0, IDC_SIZENS));
				break;
			case 3:
			case 6:
				SetCursor(LoadCursor(0, IDC_SIZENESW));
				break;
			case 4:
			case 5:
				SetCursor(LoadCursor(0, IDC_SIZEWE));
				break;
			}
		}
		else if (isOnDrawnFigure())
			SetCursor(LoadCursor(0, IDC_HAND));
		else
			SetCursor(LoadCursor(0, IDC_ARROW));
	}

	if (nFlags & MK_LBUTTON)
	{
		switch (mode)
		{
		case DRAW_RECT:
		case DRAW_ELLI:
		case DRAW_LINE:
			/* jklim: 도형을 그리기 위한 임시 도형이 이미 생성되어 있다면,  */
			if (selecting_region)
			{
				selecting_region->setP1(starting_point);
				selecting_region->setP2(point);
				//selecting_region->correctPoint();
				Invalidate(true);
			}
			break;
		case FIGURE_SELECTED:
			// 선택된 도형 안에서 드래그 했을 경우 -> 도형을 움직이기 위한 드래그
			if (isOnSelectedFigure())
				mode = FIGURE_MOVE;
			// 선택된 도형 밖에서 드래그 했을 경우 -> 도형을 선택하기 위한 드래그
			else
				mode = DO_FIGURE_SELECT;
		case FIGURE_MOVE:
			for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
			{
				(*vit)->move(CPoint(current_point.x - starting_point.x, current_point.y - starting_point.y));
			}
			starting_point = current_point;
			
			Invalidate(true);
			break;
		case DO_FIGURE_SELECT:
			if (selecting_region != NULL)
			{
				
				selecting_region->setP1(starting_point);
				selecting_region->setP2(point);
				Invalidate(true);
			}
			break;
		case DO_POINT_SELECT:
			SetCursor(LoadCursor(0, IDC_CROSS)); // 사이즈 조정 중에는 마우스 포인터를 십자 모양으로 변경
			
			if (!selected_region.empty()) // 선택된 영역이 있는 경우에만 사이즈 조정
			{
				for (vector<Figure*>::iterator vit = selected_region.begin(); vit != selected_region.end(); vit++)
				{
					(*vit)->resize(starting_point, current_point, selecting_point->getSeq());
				}
				
				starting_point = current_point;
			}
			Invalidate(true);
			break;
		default:
			break;
		}
	} 

	
	CWnd::OnMouseMove(nFlags, point);
}

/* khlee: 커서 모양 설정 */
BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/* khlee: 모드에 따른 커서 모양 변경*/
	/* SetCursor(LoadCursor(0, IDC_CROSS)); 의 마지막 매개변수 조절 (IDC_XXXX)
	 * IDC_HAND 손모양
	 * IDC_SIZENS, IDC_SIZENS, IDC_SIZEWE, IDC_SIZENWSW, IDC_SIZENESW 크기조절화살표
	 * IDC_ARROW 화살표 
	 * IDC_CROSS 십자가 
	 */

	switch (mode)
	{
	case DRAW_RECT:
	case DRAW_ELLI:
	case DRAW_LINE:
		SetCursor(LoadCursor(0, IDC_CROSS));
		break;
	case FIGURE_SELECTED:
	case FIGURE_MOVE:
	case DO_POINT_SELECT:
	case NORMAL:
		break;
	default:
		SetCursor(LoadCursor(0, IDC_ARROW));
		break;
	}
	return true;

	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

bool CChildView::isOnSelectedFigure()	// 마우스 포인터가 선택된 영역 위에 있는지 확인하는 함수
{
	if (!selected_region.empty())
		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
			if ((*vit)->onFigure(current_point))
				return true;

	return false;
}

bool CChildView::isOnDrawnFigure()	// 마우스 포인터가 도형 위에 있는지 확인하는 함수
{
	if (!drawings.empty())
		for (vector<Figure*>::reverse_iterator vit = drawings.rbegin(); vit != drawings.rend(); vit++)
			if ((*vit)->onFigure(current_point))
				return true;

	return false;
}

int CChildView::isOnFigurePoint()	// 마우스 포인터가 8방향의 작은 점 중 어느 방향에 있는지 확인하는 함수
{
	if (!figure_point.empty())
		for (vector<Figure*>::reverse_iterator vit = figure_point.rbegin(); vit != figure_point.rend(); vit++)
			if (nullptr != dynamic_cast<FigurePoint*>(*vit) && (*vit)->onFigure(current_point))
				return dynamic_cast<FigurePoint*>(*vit)->getSeq();

	return 0;
}

void CChildView::setFigurePoint()	// 선택된 도형에 대한 8방향의 점을 만드는 함수
{
	int margin = 3;	// 도형과 떨어진 거리
	int pointSize = 10;	//  8방향의 점의 크기

	removeFigurePoint();	// 기존의 8방향의 점은 삭제(초기화 작업)

	if (!selected_region.empty())
	{
		for (vector<Figure*>::reverse_iterator vit = selected_region.rbegin(); vit != selected_region.rend(); vit++)
		{

			if (nullptr == dynamic_cast<FigureLine*>(*vit))	// Rectangle과 Ellipse에 대해서는 8방향의 점 모두 표시
			{
				figure_point.push_back(new FigureLine(CPoint((*vit)->getP1().x - margin, (*vit)->getP1().y - margin), CPoint((*vit)->getP1().x - margin, (*vit)->getP2().y + margin)));
				figure_point.push_back(new FigureLine(CPoint((*vit)->getP1().x - margin, (*vit)->getP1().y - margin), CPoint((*vit)->getP2().x + margin, (*vit)->getP1().y - margin)));
				figure_point.push_back(new FigureLine(CPoint((*vit)->getP1().x - margin, (*vit)->getP2().y - 1 + margin), CPoint((*vit)->getP2().x + margin, (*vit)->getP2().y - 1 + margin)));
				figure_point.push_back(new FigureLine(CPoint((*vit)->getP2().x - 1 + margin, (*vit)->getP1().y - margin), CPoint((*vit)->getP2().x - 1 + margin, (*vit)->getP2().y + margin)));

				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP1().x - margin, (*vit)->getP1().y - margin), pointSize, *vit, 1));
				figure_point.push_back(new FigurePoint(CPoint(((*vit)->getP1().x + (*vit)->getP2().x) / 2, (*vit)->getP1().y - margin), pointSize, *vit, 2));
				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP2().x + margin, (*vit)->getP1().y - margin), pointSize, *vit, 3));

				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP1().x - margin, ((*vit)->getP1().y + (*vit)->getP2().y) / 2), pointSize, *vit, 4));
				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP2().x + margin, ((*vit)->getP1().y + (*vit)->getP2().y) / 2), pointSize, *vit, 5));

				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP1().x - margin, (*vit)->getP2().y + margin), 10, *vit, 6));
				figure_point.push_back(new FigurePoint(CPoint(((*vit)->getP1().x + (*vit)->getP2().x) / 2, (*vit)->getP2().y + margin), pointSize, *vit, 7));
				figure_point.push_back(new FigurePoint(CPoint((*vit)->getP2().x + margin, (*vit)->getP2().y + margin), 10, *vit, 8));
			}
			else
			{
				if ((*vit)->getIsFliped())
				{
					figure_point.push_back(new FigurePoint(CPoint((*vit)->getP2().x, (*vit)->getP1().y), pointSize, *vit, 3));
					figure_point.push_back(new FigurePoint(CPoint((*vit)->getP1().x, (*vit)->getP2().y), pointSize, *vit, 6));
				}
				else
				{
					figure_point.push_back(new FigurePoint(CPoint((*vit)->getP1().x, (*vit)->getP1().y), pointSize, *vit, 1));
					figure_point.push_back(new FigurePoint(CPoint((*vit)->getP2().x, (*vit)->getP2().y), pointSize, *vit, 8));
				}
			}
		}
	}
}

void CChildView::removeFigurePoint()	// 8방향의 점을 삭제하는 함수
{
	if (!figure_point.empty())
	{
		for (vector<Figure*>::iterator vit = figure_point.begin(); vit != figure_point.end(); vit++)
			(*vit)->remove();

		figure_point.clear();
	}
}
