/*
	ScatteredLineBrush.cpp

	The implementation of Scattered Line Brush.
	It is a kind of ImpBrush.

	LineBrush contain the following variables:
	- Size (length of line)
	- Width (thickness of line)
	- Line Angle
	- Alpha (opacity)

	The stroke direction should be controlled by four different way:
	- Using a slider value
	- Using right mouse dragging
	- Using the direction of cursor movement
	- Using directions that are perpendicular to the gradient of the image
	- Randomly generate several number of lines (defined in scatteredFactor
	  defined in ImpressionistDoc) around the source point
*/

#include "ScatteredLineBrush.h"
#include "ImpressionistDoc.h"

extern int irand(int);
extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc *pDoc, char *name) : LineBrush(pDoc, name) {}

void ScatteredLineBrush::BrushMove(const Point source, const Point target) {
	
	// Get scattering parameter
	ImpressionistDoc *pDoc = this->GetDocument();
	int scatFactor = pDoc->getScatFactor();
	int scatRange = pDoc->getScatRange();

	// Define the location of each scattered line
	for (int i = 0; i < scatFactor; ++i) {
		
		// Define the offset, the offset have half change to be negative
		int x_offset = irand(scatRange);
		int y_offset = irand(scatRange);

		if (frand() < 0.5) x_offset *= -1;
		if (frand() < 0.5) y_offset *= -1;
		
		// Call the parent move function to draw scattered line
		LineBrush::BrushMove(Point(source.x + x_offset, source.y + y_offset),
							 Point(target.x + x_offset, source.y + y_offset));
	}
}
