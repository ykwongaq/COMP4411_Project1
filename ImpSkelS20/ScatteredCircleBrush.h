/*
	ScatteredCircleBrush.h
	The header file for Scattered Line Brush
*/

#ifndef SCATTEREDCIRCLEBRUSH_H
#define SCATTEREDCIRCLEBRUSH_H

#include "CircleBrush.h"

class ScatteredCircleBrush : public CircleBrush {
public:

	// Constructor
	ScatteredCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	// Functions inherited from LineBrush
	void BrushMove(const Point source, const Point target);
};
#endif