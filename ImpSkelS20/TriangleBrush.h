/*
	Header file of Triangle Brush.

	The brush shape is triangle
*/
#ifndef TRIANGLEBRUSH_H
#define TRIANGLEBRUSH_H

#include "ImpBrush.h"

class TriangleBrush : public ImpBrush {
public:
	
	// Constructor
	TriangleBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);

	// Functions inherited from ImpBrush
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

private:

	int size;
};

#endif