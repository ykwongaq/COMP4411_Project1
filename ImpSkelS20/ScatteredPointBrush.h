/*
	ScatteredPointBrush.h

	The header file for Scattered Point Brush
*/

#ifndef SCATTEREDPOINTBRUSH_H
#define SCATTEREDPOINTBRUSH_H

#include "PointBrush.h"

class ScatteredPointBrush : public PointBrush {
public:

	// Constructor
	ScatteredPointBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);

	// Function inherited from PointBrush
	void BrushMove(const Point source, const Point target);
};
#endif