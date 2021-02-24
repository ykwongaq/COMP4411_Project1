/*
	ScatteredCircleBrush.h
	The header file for Scattered Line Brush
*/

#ifndef SCATTEREDRINGBRUSH_H
#define SCATTEREDRINGBRUSH_H

#include "RingBrush.h"

class ScatteredRingBrush : public RingBrush {
public:

	// Constructor
	ScatteredRingBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	// Functions inherited from LineBrush
	void BrushMove(const Point source, const Point target);
};
#endif