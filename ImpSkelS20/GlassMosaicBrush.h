#ifndef GLASSMOSAICBRUSH_H
#define GLASSMOSAICBRUSH_H

#include "GlassMosaicBrush.h"

class GlassMosaicBrush : public ImpBrush
{
public:
	GlassMosaicBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif