// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "DirectionDrawer.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int			clearCanvas();							// called by the UI to clear the drawing canvas
	void		setBrushType(int type);					// called by the UI to set the brushType
	void		setStrokeDirType(int type);				// called by the UI to set the stroke direction
	STROKE_DIR	getStrokeDirType();						// get the stroke direction method
	int			getLineWidth();							// get the brush width from UI
	void		setLineWidth(const int &width);			// set the line width
	int			getLineAngle();							// get the line angle from UI
	void		setLineAngle(const int &angle);			// set the line angle
	float		getAlpha();								// get the alpha from UI
	void		setAlpha(const float &alpha);			// set the alpha
	int			getSize();								// get the UI size
	void		setSize(const int &size);				// set the UI size
	char*		getImageName();							// get the current image name
	int			getScatRange() const;					// get the scatteredRange
	void		setScatRange(const int &scatRange);		// set the scatteredRange
	int			getScatFactor() const;					// get the scatteredFactor
	void		setScatFactor(const int &scatFactor);	// set the scatteredFactor
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	

	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	// Scattering parameter
	int				scatRange;		// Define the distance range of scattered from the source
	int				scatFactor;	// Define the number of scattered primitives generated


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;

	// The current methods for defining stoke direction
	STROKE_DIR			m_pCurrentDirMethod;

	// Size of the brush.
	int m_nSize;

	ImpressionistUI*	m_pUI;

	// Used to draw the direction angle for line
	DirectionDrawer		*m_pDirDrawer;

	// Parameter Boundary Setting
	static const int MIN_SIZE = 1;
	static const int MAX_SIZE = 40;
	static const int MIN_WIDTH = 1;
	static const int MAX_WIDTH = 40;
	static const int MIN_ANGLE = 0;
	static const int MAX_ANGLE = 359;
	static const float MIN_ALPHA;	// 0.0
	static const float MAX_ALPHA;	// 1.0

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
