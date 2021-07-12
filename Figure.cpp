#include "pch.h"
#include "Figure.h"
#include <cmath>

FigureRectangle::FigureRectangle(CPoint& _p1, CPoint& _p2)
{
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
		p1.x = _p2.x;
	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
		p1.y = _p2.y;

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;
}

void FigureRectangle::draw(CPaintDC* dc)
{
	dc->Rectangle(p1.x, p1.y, p2.x, p2.y);
}

bool FigureRectangle::onFigure(CPoint& p)
{
	if (p1.x <= p.x && p.x <= p2.x && p1.y <= p.y && p.y <= p2.y)
		return true;
	else
		return false;
}

void FigureRectangle::move(CPoint& p)
{
	p1.x += p.x, p2.x += p.x, p1.y += p.y, p2.y += p.y;
}

void FigureRectangle::remove()
{
	delete this;
}

void FigureRectangle::resize(CPoint& s, CPoint& c, int seq)
{
	CPoint p(c.x - s.x, c.y - s.y);

	switch (seq)
	{
	case 1:
		p1 += p;
		break;
	case 2:
		p1.y += p.y;
		break;
	case 3:
		p1.y += p.y;
		p2.x += p.x;
		break;
	case 4:
		p1.x += p.x;
		break;
	case 5:
		p2.x += p.x;
		break;
	case 6:
		p1.x += p.x;
		p2.y += p.y;
		break;
	case 7:
		p2.y += p.y;
		break;
	case 8:
		p2 += p;
		break;
	default:
		break;
	}
}

Figure* FigureRectangle::clone()
{
	return new FigureRectangle(CPoint(this->getP1().x + 10, this->getP1().y + 10), CPoint(this->getP2().x + 10, this->getP2().y + 10));
}

void FigureRectangle::correctPoint()
{
	CPoint _p1(p1);
	CPoint _p2(p2);
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
		p1.x = _p2.x;
	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
		p1.y = _p2.y;

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;
}

FigureEllipse::FigureEllipse(CPoint& _p1, CPoint& _p2)
{
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
		p1.x = _p2.x;
	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
		p1.y = _p2.y;

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;
}

void FigureEllipse::draw(CPaintDC* dc)
{
	dc->Ellipse(p1.x, p1.y, p2.x, p2.y);
}

bool FigureEllipse::onFigure(CPoint& p)
{

	CPoint m(p1.x + (p2.x - p1.x) / 2, p1.y + (p2.y - p1.y) / 2);
	if (pow((p.x - m.x), 2) / pow((p2.x - p1.x) / 2, 2) + pow((p.y - m.y), 2) / pow((p2.y - p1.y) / 2, 2) <= 1)
		return true;
	else
		return false;
}

void FigureEllipse::move(CPoint& p)
{
	p1.x += p.x, p2.x += p.x, p1.y += p.y, p2.y += p.y;
}

void FigureEllipse::remove()
{
	delete this;
}

void FigureEllipse::resize(CPoint& s, CPoint& c, int seq)
{
	CPoint p(c.x - s.x, c.y - s.y);

	switch (seq)
	{
	case 1:
		p1 += p;
		break;
	case 2:
		p1.y += p.y;
		break;
	case 3:
		p1.y += p.y;
		p2.x += p.x;
		break;
	case 4:
		p1.x += p.x;
		break;
	case 5:
		p2.x += p.x;
		break;
	case 6:
		p1.x += p.x;
		p2.y += p.y;
		break;
	case 7:
		p2.y += p.y;
		break;
	case 8:
		p2 += p;
		break;
	default:
		break;
	}
}

void FigureEllipse::correctPoint()
{
	CPoint _p1(p1);
	CPoint _p2(p2);
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
		p1.x = _p2.x;
	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
		p1.y = _p2.y;

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;
}

Figure* FigureEllipse::clone()
{
	return new FigureEllipse(CPoint(this->getP1().x + 10, this->getP1().y + 10), CPoint(this->getP2().x + 10, this->getP2().y + 10));
}

void FigureLine::draw(CPaintDC* dc)
{
	if (isFliped)
	{
		dc->MoveTo(p2.x, p1.y);
		dc->LineTo(p1.x, p2.y);
	}
	else {
		dc->MoveTo(p1.x, p1.y);
		dc->LineTo(p2.x, p2.y);
	}
}

bool FigureLine::onFigure(CPoint& p)
{
	int lineMargin = 20;	// 선이 너무 얇아 선택하기 어려우므로 선택영역에 대한 Margin 값
	pair<double, double> tmpP1;	// 값의 정확도 향상을 위해 double 형태의 pair 객체를 사용
	pair<double, double> tmpP2;
	if (isFliped)
	{
		tmpP1 = pair<double, double>(p2.x, p1.y);
		tmpP2 = pair<double, double>(p1.x, p2.y);
	}
	else
	{
		tmpP1 = pair<double, double>(p1.x, p1.y);
		tmpP2 = pair<double, double>(p2.x, p2.y);
	}

	if (min(tmpP1.first, tmpP2.first) <= p.x && p.x <= max(tmpP1.first, tmpP2.first) && min(tmpP1.second, tmpP2.second) <= p.y && p.y <= max(tmpP1.second, tmpP2.second))
	{
		if (tmpP1.first != tmpP2.first)
		{
			double m = (tmpP2.second - tmpP1.second) / (tmpP2.first - tmpP1.first);
			double n = tmpP1.second - (m * tmpP1.first);
			if (abs(m * p.x - p.y + n) / sqrt(m * m + 1) <= lineMargin)
				return true;
			else
				return false;
		}
		else {
			if (abs(p.x - p1.x) <= lineMargin)
				return true;
			else
				return false;
		}
	}
	else
		return false;
}

void FigureLine::move(CPoint& p)
{
	p1.x += p.x, p2.x += p.x, p1.y += p.y, p2.y += p.y;
}

void FigureLine::remove()
{
	delete this;
}

void FigureLine::resize(CPoint& s, CPoint& c, int seq)
{
	CPoint p(c.x - s.x, c.y - s.y);
	if (isFliped)
	{
		switch (seq)
		{
		case 1:
			p1 += p;
			break;
		case 2:
			p1.y += p.y;
			break;
		case 3:
			p1.y += p.y;
			p2.x += p.x;
			break;
		case 4:
			p1.x += p.x;
			break;
		case 5:
			p2.x += p.x;
			break;
		case 6:
			p1.x += p.x;
			p2.y += p.y;
			break;
		case 7:
			p2.y += p.y;
			break;
		case 8:
			p2 += p;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (seq)
		{
		case 1:
			p1 += p;
			break;
		case 2:
			p1.y += p.y;
			break;
		case 3:
			p1.y += p.y;
			p2.x += p.x;
			break;
		case 4:
			p1.x += p.x;
			break;
		case 5:
			p2.x += p.x;
			break;
		case 6:
			p1.x += p.x;
			p2.y += p.y;
			break;
		case 7:
			p2.y += p.y;
			break;
		case 8:
			p2 += p;
			break;
		default:
			break;
		}
	}

}

void FigureLine::correctPoint()
{	
	CPoint _p1(p1);
	CPoint _p2(p2);
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
	{
		p1.x = _p2.x;
	}

	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
	{
		p1.y = _p2.y;
	}

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;

	if (isFliped == false)
	{
		if ((p1 == _p1 && p2 == _p2) || (p1 == _p2 && p2 == _p1))
		{
			isFliped = false;
		}
		else
		{
			isFliped = true;
		}
	}
	else
	{
		if ((p1 == _p1 && p2 == _p2) || (p1 == _p2 && p2 == _p1))
		{
			isFliped = true;
		}
		else
		{
			isFliped = false;
		}
	}
}


Figure* FigureLine::clone()
{
	return new FigureLine(CPoint(this->getP1().x + 10, this->getP1().y + 10), CPoint(this->getP2().x + 10, this->getP2().y + 10), this->isFliped);
}

FigurePoint::FigurePoint(CPoint& _p, int size, Figure* _parent, int _seq)
{
	p1.x = _p.x - size;
	p1.y = _p.y - size;
	p2.x = _p.x + size;
	p2.y = _p.y + size;
	parent = _parent;
	seq = _seq;
}

void FigurePoint::draw(CPaintDC* dc)
{
	dc->Ellipse(p1.x, p1.y, p2.x, p2.y);
}

bool FigurePoint::onFigure(CPoint& p)
{
	CPoint m(p1.x + (p2.x - p1.x) / 2, p1.y + (p2.y - p1.y) / 2);
	if (pow((p.x - m.x), 2) / pow((p2.x - p1.x) / 2, 2) + pow((p.y - m.y), 2) / pow((p2.y - p1.y) / 2, 2) <= 1)
		return true;
	else
		return false;
}

void FigurePoint::move(CPoint& p)
{
}

Figure* FigurePoint::getParent()
{
	return parent;
}

void FigurePoint::remove()
{
	delete this;
}

void FigurePoint::resize(CPoint& s, CPoint& c, int seq)
{
}

void FigurePoint::correctPoint()
{
	CPoint _p1(p1);
	CPoint _p2(p2);
	if (_p1.x < _p2.x)
		p1.x = _p1.x;
	else
		p1.x = _p2.x;
	if (_p1.y < _p2.y)
		p1.y = _p1.y;
	else
		p1.y = _p2.y;

	if (_p1.x < _p2.x)
		p2.x = _p2.x;
	else
		p2.x = _p1.x;
	if (_p1.y < _p2.y)
		p2.y = _p2.y;
	else
		p2.y = _p1.y;
}

Figure* FigurePoint::clone()
{
	return new FigurePoint(this->getP1(), this->size, this->parent, this->seq);
}

void FigureGroup::draw(CPaintDC* dc)
{
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		(*vit)->draw(dc);
	}
}

bool FigureGroup::onFigure(CPoint& p)
{
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		if ((*vit)->onFigure(p)) return true;
	}

	return false;
}

void FigureGroup::move(CPoint& p)
{
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		(*vit)->move(p);
	}
	p1.x += p.x, p2.x += p.x, p1.y += p.y, p2.y += p.y;

}

void FigureGroup::remove()
{
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		(*vit)->remove();
	}
	delete this;
}

void FigureGroup::resize(CPoint& s, CPoint& c, int seq)
{
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		(*vit)->resize(s, c, seq);
	}
	
}

void FigureGroup::correctPoint()
{

	p1 = child.front()->getP1();
	p2 = child.front()->getP2();
	CPoint tmpP1(p1);
	CPoint tmpP2(p2);
	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		(*vit)->correctPoint();
	}

	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		if (!(*vit)->getIsFliped())
		{
			tmpP1 = (*vit)->getP1();
			tmpP2 = (*vit)->getP2();
		}
		else
		{
			tmpP1 = CPoint((*vit)->getP1().x, (*vit)->getP2().y);
			tmpP2 = CPoint((*vit)->getP2().x, (*vit)->getP1().y);
		}

		if (p1.x > tmpP1.x)
			p1.x = tmpP1.x;
		if (p1.x > tmpP2.x)
			p1.x = tmpP2.x;

		if (p1.y > tmpP1.y)
			p1.y = tmpP1.y;
		if (p1.y > tmpP2.y)
			p1.y = tmpP2.y;

		if (p2.x < tmpP2.x)
			p2.x = tmpP2.x;
		if (p2.x < tmpP1.x)
			p2.x = tmpP1.x;

		if (p2.y < tmpP2.y)
			p2.y = tmpP2.y;
		if (p2.y < tmpP1.y)
			p2.y = tmpP1.y;

	
	}
}

void FigureGroup::clear()
{
	child.clear();
	delete this;
}

Figure* FigureGroup::clone()
{
	FigureGroup* tmpFig = new FigureGroup(child.front()->getP1(), child.front()->getP2());

	for (vector<Figure*>::iterator vit = child.begin(); vit != child.end(); vit++)
	{
		tmpFig->addChild((*vit)->clone());
	}
	return tmpFig;
}

vector<Figure*>& FigureGroup::getChild()
{
	// TODO: insert return statement here
	return child;
}

bool FigureGroup::addChild(Figure* fig)
{
	child.push_back(fig);
	correctPoint();

	return true;
}
