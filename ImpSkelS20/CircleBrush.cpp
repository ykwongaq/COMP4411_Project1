//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include <cmath>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);
	int radius = size / 2;
	
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//int size = pDoc->getSize();

	//int radius = size / 2;

	//float i = 0.0f;

	glBegin(GL_POINTS);
	//glBegin(GL_POLYGON);
	SetColor(source);
	glVertex2d(target.x, target.y);
	//glVertex2f(target.x, target.y);
	//for (i = 0.0f; i <= 360; i++)
	//	glVertex2f(target.x + cos(M_PI*i/180.0)*radius, target.y + sin(M_PI * i / 180.0) * radius);

	glEnd();

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

