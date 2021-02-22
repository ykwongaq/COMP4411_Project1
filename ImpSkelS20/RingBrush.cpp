//
// RingBrush.cpp
//
// The implementation of Ring Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ringbrush.h"
#include <cmath>

extern float frand();

RingBrush::RingBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void RingBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);

	BrushMove(source, target);
}

void RingBrush::BrushMove(const Point source, const Point target)
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
	int radius = (pDoc->getSize())/2;

	GLfloat i ;

	//glBegin(GL_POINTS);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	SetColor(source);
	//glVertex2d(target.x, target.y);
	//glVertex3f(target.x, target.y, 0.0f);
	for (i = 0.0f; i <= 2.0f * (M_PI); i += 0.1f) {
		//glVertex2f(target.x + cos(M_PI*i/180.0)*radius, target.y + sin(M_PI * i / 180.0) * radius);
		float x = target.x + cos(i) * radius;
		float y = target.y + sin(i) * radius;
		glVertex3f(x,y, 0.0f);
	}
	glEnd();

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);
}

void RingBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

