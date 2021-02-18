#ifndef DIRECTIONDRAWER_H
#define DIRECTIONDRAWER_H

#include "ImpBrush.h"

class DirectionDrawer {
public:

	DirectionDrawer();

	void DrawBegin(const Point &source);
	void DrawMove(const Point &source);
	void DrawEnd(const Point &source);

	Point getStartPt();
	Point getMovePt();
	int	  getAngle();
	int	  getSize();

private:

	Point	startPt;
	Point	movePt;
	int		angle;
	int		size;
};

#endif