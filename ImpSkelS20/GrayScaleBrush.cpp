/*
	GrayScaleBrush.cpp

	The implementation of Gray Scale Brush
	It is a kind of ImpBrush

	Gray Scale Brush is the brush that draw the gray scale
	image of the original image

	The brush shape is the same as the Scattered Point Brush
*/

#include "GrayScaleBrush.h"
#include "ImpressionistDoc.h"

extern GLubyte RGBtoGray(GLubyte *rgb);

GrayScaleBrush::GrayScaleBrush(ImpressionistDoc *pDoc, char *name) : ScatteredLineBrush(pDoc, name) {}

void GrayScaleBrush::SetColor(const Point source) {

	ImpressionistDoc *pDoc = GetDocument();

	GLubyte color[3];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);	// Copy the color from original source


	GLubyte grayColor = RGBtoGray(color);

	glColor3ub(grayColor, grayColor, grayColor);
}	
