//
// RingBrush.h
//
// The header file for Ring Brush. 
//

#ifndef RINGBRUSH_H
#define RINGBRUSH_H

#include "ImpBrush.h"

class RingBrush : public ImpBrush
{
public:
	RingBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif