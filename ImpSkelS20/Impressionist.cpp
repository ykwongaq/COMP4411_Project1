//
// impressionist.cpp
//
// The main driver program for the other parts. We have two major components,
// UI and Doc.
// They do have a link to each other as their member such that they can 
// communicate.
//

#include <stdio.h>

#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "impressionistUI.h"
#include "impressionistDoc.h"

ImpressionistUI *impUI;
ImpressionistDoc *impDoc;

GLubyte RGBtoGray(GLubyte, GLubyte, GLubyte);

int main(int	argc, 
		 char**	argv) 
{
	impDoc = new ImpressionistDoc();

	// Create the UI
	impUI = new ImpressionistUI();

	// Set the impDoc which is used as the bridge between UI and brushes
	impUI->setDocument(impDoc);
	impDoc->setUI(impUI);

	Fl::visual(FL_DOUBLE|FL_INDEX);

	impUI->show();

	return Fl::run();
}

// global functions
float frand()
{
	return (float)rand()/RAND_MAX;
}

int irand(int max)
{
	return rand()%max;
}

// -----------------------------------
// Convert degree to radian
// -----------------------------------
float deg2Rad(const float &degree) {
	return degree * M_PI / 180;
}

// -----------------------------------
// Convert radian to degree
// -----------------------------------
float rad2Deg(const float &radian) {
	return radian * 180 / M_PI;
}

GLubyte RGBtoGray(GLubyte red, GLubyte green, GLubyte blue) {
	return static_cast<GLubyte>(0.299 * red + 0.587 * green + 0.114 * blue);
}

GLubyte RGBtoGray(GLubyte *rgb) {
	return RGBtoGray(rgb[0], rgb[1], rgb[2]);
}
