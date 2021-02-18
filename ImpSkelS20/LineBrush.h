//
// LineBrush.h
//
// The header file for Line Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"
#include <vector>

using namespace std;

class LineBrush : public ImpBrush {
public:

	// Constructor
	LineBrush(ImpressionistDoc *pDoc = NULL, char *name = NULL);

	// Functions inherited from ImpBrush
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
private:

	// Sobel operator for gradient calculation
	const int sobelXOperator[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	const int sobelYoperator[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
	
	// Get the 3-by-3 gray scale matrix around the source
	vector<int> getGrayPixelGrid(const Point source);

	Point prevSource;	// Previous location of source. Used to track bursh movement
};

#endif