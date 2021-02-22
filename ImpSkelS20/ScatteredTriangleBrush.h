#ifndef SCATTEREDTRIANGLEBRUSH_H
#define SCATTEREDTRIANGLEBRUSH_H

#include "TriangleBrush.h"

class ScatteredTriangleBrush : public TriangleBrush {
public:
	ScatteredTriangleBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);

	void BrushMove(const Point source, const Point target);
};

#endif
