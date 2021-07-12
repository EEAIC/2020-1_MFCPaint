#pragma once

#include "pch.h"
#include <vector>

using namespace std;

class Figure
{
public:
	virtual CPoint getP1() const = 0;
	virtual CPoint getP2() const = 0;
	virtual void setP1(CPoint& p) = 0;
	virtual void setP2(CPoint& p) = 0;
	virtual void draw(CPaintDC* dc) = 0;
	virtual bool onFigure(CPoint& p) = 0;	// 마우스 포인터가 도형 위에 있는지 확인
	virtual void move(CPoint& p) = 0;
	virtual void remove() = 0;
	virtual void resize(CPoint& s, CPoint& c, int seq) = 0;
	virtual void correctPoint() = 0;
	virtual bool getIsFliped() const = 0;
	virtual Figure* clone() = 0;
};

class FigureRectangle : public Figure
{
public:
	FigureRectangle() : p1(0, 0), p2(0, 0) {}
	FigureRectangle(CPoint& _p1, CPoint& _p2);
	CPoint getP1() const { return p1; }
	CPoint getP2() const { return p2; }
	void setP1(CPoint& _p) { p1 = _p; correctPoint(); }
	void setP2(CPoint& _p) { p2 = _p; correctPoint(); }
	void draw(CPaintDC* dc);
	bool onFigure(CPoint& p);
	void move(CPoint& p);
	void remove();
	void resize(CPoint& s, CPoint& c, int seq);
	void correctPoint();
	bool getIsFliped() const { return false; }
	Figure* clone();
private:
	CPoint p1, p2; /* khlee: 좌상단 및 우하단 꼭지점 */
};

class FigureEllipse : public Figure
{
public:
	FigureEllipse() : p1(0, 0), p2(0, 0) {}
	FigureEllipse(CPoint& _p1, CPoint& _p2);
	CPoint getP1() const { return p1; }
	CPoint getP2() const { return p2; }
	void setP1(CPoint& _p) { p1 = _p; }
	void setP2(CPoint& _p) { p2 = _p; }
	void draw(CPaintDC* dc);
	bool onFigure(CPoint& p);
	void move(CPoint& p);
	void remove();
	void resize(CPoint& s, CPoint& c, int seq);
	void correctPoint();
	bool getIsFliped() const { return false; }
	Figure* clone();
private:
	CPoint p1, p2; /* jklim: 좌상단 및 우하단 꼭지점 */
};

class FigureLine : public Figure
{
public:
	FigureLine() : p1(0, 0), p2(0, 0) {}
	FigureLine(CPoint& _p1, CPoint& _p2) : Figure(), p1(_p1), p2(_p2) {}
	FigureLine(CPoint& _p1, CPoint& _p2, bool _isFliped) : Figure(), p1(_p1), p2(_p2), isFliped(_isFliped) {}
	CPoint getP1() const { return p1; }
	CPoint getP2() const { return p2; }
	void setP1(CPoint& _p) { p1 = _p; }
	void setP2(CPoint& _p) { p2 = _p; }
	void draw(CPaintDC* dc);
	bool onFigure(CPoint& p);
	void move(CPoint& p);
	void remove();
	void resize(CPoint& s, CPoint& c, int seq);
	void correctPoint();
	bool getIsFliped() const { return isFliped; }
	Figure* clone();
private:
	CPoint p1, p2; /* jklim: 좌상단 및 우하단 꼭지점 */
	bool isFliped = false;	/* 우상단 및 좌하단 꼭지점 여부 */
};


class FigurePoint : public Figure
{
public:
	FigurePoint() : p1(0, 0), p2(0, 0), size(5), seq(0), parent(NULL) {}
	FigurePoint(CPoint& _p, int size, Figure* parent, int _seq);
	CPoint getP1() const { return p1; }
	CPoint getP2() const { return p2; }
	void setP1(CPoint& _p) { p1 = _p; }
	void setP2(CPoint& _p) { p2 = _p; }
	void draw(CPaintDC* dc);
	bool onFigure(CPoint& p);
	void move(CPoint& p);
	void remove();
	void resize(CPoint& s, CPoint& c, int seq);
	void correctPoint();
	int getSeq() { return seq; }
	bool getIsFliped() const { return false; }
	Figure* getParent();
	Figure* clone();
private:
	CPoint p1, p2; /* jklim: 좌상단 및 우하단 꼭지점 */
	Figure* parent;
	int size = 0;
	int seq;
};

class FigureGroup : public Figure
{
public:
	FigureGroup(CPoint& _p1, CPoint& _p2) : p1(_p1), p2(_p2){ };
	CPoint getP1() const { return p1; }
	CPoint getP2() const { return p2; }
	void setP1(CPoint& _p) { p1 = _p; }
	void setP2(CPoint& _p) { p2 = _p; }
	void draw(CPaintDC* dc);
	bool onFigure(CPoint& p);
	void move(CPoint& p);
	void remove();
	void resize(CPoint& s, CPoint& c, int seq);
	void correctPoint();
	bool getIsFliped() const { return false; }
	void clear();
	Figure* clone();
	vector<Figure*>& getChild();
	bool addChild(Figure* fig);
private:
	CPoint p1, p2; /* jklim: 좌상단 및 우하단 꼭지점 */
	vector<Figure*> child;
};
