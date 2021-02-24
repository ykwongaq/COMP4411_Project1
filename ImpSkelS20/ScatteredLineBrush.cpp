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

void ScatteredLineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc *pDoc = this->GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;

	// Line settings
	glLineWidth(pDoc->getLineWidth());		// Set line width
	this->prevSource = target;

	this->BrushMove(source, target);
}

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
		//LineBrush::BrushMove(Point(source.x + x_offset, source.y + y_offset),
		//					 Point(target.x + x_offset, source.y + y_offset));

		Point newSource = Point(source.x + x_offset, source.y + y_offset);
		Point newTarget = Point(target.x + x_offset, target.y + y_offset);

		ImpressionistDoc *pDoc = this->GetDocument();
		ImpressionistUI *dlg = pDoc->m_pUI;

		if (pDoc == NULL) {
			printf("PointBrush::BrushMove document is NULL\n");
			return;
		}

		// Load parameter from UI
		GLint length = pDoc->getSize();
		GLfloat alpha = pDoc->getAlpha();

		// Set the rotation angle based on stroke direction selection
		GLfloat rotateAngle = 0.0;
		switch (pDoc->getStrokeDirType()) {
			case STROKE_DIR::STR_SLIDER_OR_MOUSE:
				rotateAngle = pDoc->getLineAngle();
				break;
			case STROKE_DIR::STR_BRUSH_DIR:	// Use the direction of cursor movement
				rotateAngle = this->prevSource.angleFrom(target);
				break;
			case STROKE_DIR::STR_GRADIENT:	// Use the direction that perpendicular to the gradient of image
			{
				// Get the 3-by-3 gray scale grid
				vector<int> grid = this->getGrayPixelGrid(newSource);

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
		glTranslated(newTarget.x, newTarget.y, 0);
		glRotatef(rotateAngle, 0, 0, 1);
		glTranslated(-newTarget.x, -newTarget.y, 0);

		glBegin(GL_LINES);			// Start drawing

		/// Set the color of line
		SetColor(source);

		// Draw horizontal line
		glVertex2f(newTarget.x - length / 2, newTarget.y);
		glVertex2f(newTarget.x + length / 2, newTarget.y);

		glEnd();					// Stop drawing
		glPopMatrix();	
	}
	
	this->prevSource = target;
}
