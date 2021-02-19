/*
	ScatteredPointBrush.cpp

	The implementation of Scattered Point Brush
	It is a kind of ImpBrush

	Scattered Point Brush work exactly the same as the Point Brush
	except that the point is scattered in different location
*/

#include "ScatteredPointBrush.h"
#include "ImpressionistDoc.h"

extern int irand(int);
extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc *pDoc, char *name) : PointBrush(pDoc, name) {}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
	
	// Get the scattering parameter
	ImpressionistDoc *pDoc = this->GetDocument();
	int scatFactor	= pDoc->getScatFactor();
	int scatRange	= pDoc->getScatRange();

	// Define the location of each scattered point
	for (int i = 0; i < scatFactor; ++i) {
		
		// Define the offset, the offset have half change to be negative
		int x_offset = irand(scatRange);
		int y_offset = irand(scatRange);

		if (frand() < 0.5) x_offset *= -1;
		if (frand() < 0.5) y_offset *= -1;

		// Call the parent move function to draw the scattered point
		PointBrush::BrushMove(Point(source.x + x_offset, source.y + y_offset),
							  Point(target.x + x_offset, target.y + y_offset));
	}
}
