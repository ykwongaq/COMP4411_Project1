#include "TriangleBrush.h"
#include "ImpressionistDoc.h"

TriangleBrush::TriangleBrush(ImpressionistDoc *pDoc, char *name) : ImpBrush(pDoc, name) {
	this->size = 0;
}

void TriangleBrush::BrushBegin(const Point source, const Point target) {
	this->size = this->GetDocument()->getSize();
	this->BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc *pDoc = this->GetDocument();

	if (pDoc == NULL) {
		printf("TriangleBrush::BrushMove document is NULL\N");
		return;
	}

	this->SetColor(source);

	glBegin(GL_TRIANGLES);
	glVertex2f(source.x, source.y + this->size);
	glVertex2f(source.x - this->size*sqrt(3), source.y - this->size / 2);
	glVertex2f(source.x + this->size*sqrt(3), source.y - this->size / 2);
	glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target) {}
