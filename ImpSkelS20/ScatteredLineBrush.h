/*
	ScatteredLineBrush.h

	The header file for Scattered Line Brush
*/

#ifndef SCATTEREDLINEBRUSH_H
#define SCATTEREDLINEBRUSH_H

#include "LineBrush.h"

class ScatteredLineBrush : public LineBrush {
public:

	// Constructor
	ScatteredLineBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);

	// Functions inherited from LineBrush
	void BrushMove(const Point source, const Point target);
};
#endif
