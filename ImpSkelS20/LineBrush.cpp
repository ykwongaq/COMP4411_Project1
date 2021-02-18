/*
	LineBrush.cpp

	The implementation of Line Brush. It is a kind of ImpBrush.

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
*/

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <vector>
#include <math.h>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc *pDoc, char *name) : ImpBrush(pDoc, name) {
	this->prevSource = Point(0, 0);
}

void LineBrush::BrushBegin(const Point source, const Point target) {

	ImpressionistDoc *pDoc = this->GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;

	// Line settings
	glLineWidth(pDoc->getLineWidth());		// Set line width
	this->prevSource = target;

	this->BrushMove(source, target);
}	

void LineBrush::BrushMove(const Point source, const Point target) {

	ImpressionistDoc *pDoc = this->GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;

	if(pDoc == NULL) {
		printf("PointBrush::BrushMove document is NULL\n");
		return;
	}
	
	// Load parameter from UI
	GLint length = pDoc->getSize();
	GLfloat alpha = pDoc->getAlpha();

	// Set the rotation angle
	GLfloat rotateAngle = 0.0;
	switch(pDoc->getStrokeDirType()) {
		case STROKE_DIR::STR_SLIDER_OR_MOUSE:
			rotateAngle = pDoc->getLineAngle();
			break;
		case STROKE_DIR::STR_BRUSH_DIR:	// Use the direction of cursor movement
			rotateAngle = this->prevSource.angleFrom(target);
			break;
		case STROKE_DIR::STR_GRADIENT:	// Use the direction that perpendicular to the gradient of image
		{
			// Get the 3-by-3 gray scale grid
			vector<int> grid = this->getGrayPixelGrid(source);

			// Calculate the gradient in x and y direction
			int dx = 0, dy = 0;
			for (int i = 0; i < 9; ++i) {
				dx += grid[i] * this->sobelXOperator[i];
				dy += grid[i] * this->sobelYoperator[i];
			}

			if (dx == 0)
				rotateAngle = 90.0;
			else if (dy == 0)
				rotateAngle = 0.0;
			else
				rotateAngle = static_cast<GLfloat>(atan2(dy, dx) * 180 / M_PI);
		} break;
		default:
			break;
	}

	// Rotate the line 
	glPushMatrix();
	glTranslated(target.x, target.y, 0);
	glRotatef(rotateAngle, 0, 0, 1);
	glTranslated(-target.x, -target.y, 0);

	glBegin(GL_LINES);			// Start drawing

	/// Set the color of line
	SetColor(source);	

	// Draw horizontal line
	glVertex2f(target.x - length / 2, target.y);
	glVertex2f(target.x + length / 2, target.y);

	glEnd();					// Stop drawing
	glPopMatrix();

	this->prevSource = target;
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// Do nothing
}

// -------------------------------------------------------
//	Get the 3-by-3 gray scale matrix around the source
// -------------------------------------------------------
vector<int> LineBrush::getGrayPixelGrid(const Point source) {
	
	ImpressionistDoc *pDoc = this->GetDocument();	// Get the document

	vector<int> grid;
	GLubyte colorRGB[3];

	int index = 0;
	for(int i = -1; i < 2; ++i) {
		for(int j = -1; j < 2; ++j) {

			memcpy(colorRGB, pDoc->GetOriginalPixel(source.x + i, source.y + j), 3);
			grid.push_back(static_cast<int>(0.299 * colorRGB[0] + 0.587 * colorRGB[1] + 0.114 * colorRGB[2]));	// Convert RGB to gray scale

		}
	}

	return grid;
}
