// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "RingBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredRingBrush.h"
#include "GlassMosaicBrush.h"
#include "BlurBrush.h"
#include "SharpenBrush.h"



#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

const float ImpressionistDoc::MIN_ALPHA = 0.0;
const float ImpressionistDoc::MAX_ALPHA = 1.0;

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new PointBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new PointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new PointBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_RING]
		= new RingBrush(this, "Rings");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_RING]
		= new ScatteredRingBrush(this, "Scattered Rings");
	ImpBrush::c_pBrushes[BRUSH_GLASS_MOSAIC]
		= new GlassMosaicBrush(this, "Glass mosaic");
	ImpBrush::c_pBrushes[BRUSH_BLUR]
		= new BlurBrush(this, "Blur");
	ImpBrush::c_pBrushes[BRUSH_SHARPEN]
		= new SharpenBrush(this, "Sharpen");



	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

	// Initialize scattering parameter
	this->scatRange = 20;
	this->scatFactor = 4;
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

int ImpressionistDoc::getScatRange() const {
	return this->scatRange;
}

void ImpressionistDoc::setScatRange(const int &scatRange) {
	this->scatRange = scatRange;
}

int ImpressionistDoc::getScatFactor() const {
	return this->scatFactor;
}

void ImpressionistDoc::setScatFactor(const int &scatFactor) {
	this->scatFactor = scatFactor;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Called by the UI when the user changes the definition of 
// stroke direction.
// type: one of the defined stroke method types.
//---------------------------------------------------------
void ImpressionistDoc::setStrokeDirType(int type) {
	this->m_pCurrentDirMethod = (STROKE_DIR) type;
}

//---------------------------------------------------------
// Return the stroke direction method
//---------------------------------------------------------
STROKE_DIR ImpressionistDoc::getStrokeDirType() {
	return this->m_pCurrentDirMethod;
}

//---------------------------------------------------------
// Return the width of brush
//---------------------------------------------------------
int ImpressionistDoc::getLineWidth() {
	return this->m_pUI->getBrushWidth();
}

void ImpressionistDoc::setLineWidth(const int &width) {
	this->m_pUI->setBrushWidth(width);
}

//---------------------------------------------------------
// Return the rotation angle of line
//---------------------------------------------------------
int ImpressionistDoc::getLineAngle() {
	return this->m_pUI->getRotationAngle();
}

void ImpressionistDoc::setLineAngle(const int &angle) {
	this->m_pUI->setRotationAngle(angle);
}

//---------------------------------------------------------
// Return the opacity alpha
//---------------------------------------------------------
float ImpressionistDoc::getAlpha() {
	return this->m_pUI->getAlpha();
}

void ImpressionistDoc::setAlpha(const float &alpha) {
	this->m_pUI->setAlpha(alpha);
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

void ImpressionistDoc::setSize(const int &size) {
	if (size < ImpressionistDoc::MIN_SIZE)
		this->m_nSize = ImpressionistDoc::MIN_SIZE;
	else if (size > ImpressionistDoc::MAX_SIZE)
		this->m_nSize = ImpressionistDoc::MAX_SIZE;
	else
		this->m_nSize = size;

	this->m_pUI->setSize(size);
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}



