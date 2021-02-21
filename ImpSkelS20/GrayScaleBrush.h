/*
	GrayScaleBrush.h

	The header file for Gray Scale Brush

	Gray Scale Brush is the brush that draw the gray scale
	image of the original image

	The brush shape is the same as the Scattered Point Brush
*/

#ifndef GRAYSCALEBRUSH_H
#define GRAYSCALEBRUSH_H

#include "ScatteredPointBrush.h"

class GrayScaleBrush : public ScatteredPointBrush {
public:
	
	// Constructor
	GrayScaleBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);
	
	// Function inherited from ImpBrush
	void SetColor(const Point source) override;
};
#endif