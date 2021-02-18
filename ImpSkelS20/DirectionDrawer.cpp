#include "DirectionDrawer.h"
#include "Impressionist.h"
#include <math.h>

extern float rad2Deg(const float &);

DirectionDrawer::DirectionDrawer() {
	this->startPt = Point(0, 0);
	this->movePt = Point(0, 0);
	this->angle = 0;
	this->size = 0;
}

void DirectionDrawer::DrawBegin(const Point &source) {
	this->startPt = source;

	this->DrawMove(source);
}

void DirectionDrawer::DrawMove(const Point &source) {
	this->movePt = source;

	glColor3f(1, 0, 0);	// Set the color to red

	glBegin(GL_LINES);
	glVertex2i(this->startPt.x, this->startPt.y);
	glVertex2i(this->movePt.x, this->movePt.y);
	glEnd();
}

void DirectionDrawer::DrawEnd(const Point &source) {
	this->movePt = source;
	
	// Set the angle
	float theta = this->startPt.angleFrom(this->movePt);
	if (theta < 0) theta = 180 + theta;	// Fit the angle in range [0, 359]
	this->angle = static_cast<int>(theta);

	this->size = this->startPt.distFrom(this->movePt);	// Set the size
}

Point DirectionDrawer::getStartPt() {
	return this->startPt;
}

Point DirectionDrawer::getMovePt() {
	return this->movePt;
}

int DirectionDrawer::getAngle() {
	return this->angle;
}

int DirectionDrawer::getSize() {
	return this->size;
}
