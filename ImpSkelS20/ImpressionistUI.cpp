//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"
#include "ImpBrush.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//-------------------------------------------------------------
// Brings up the color dialog
// This is called by the UI when the color menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_color(Fl_Menu_ *o, void *v) {
	whoami(o)->m_ColorDialog->show();
}

void ImpressionistUI::cb_undo(Fl_Menu_ *o, void *v) {
	ImpressionistUI::whoami(o)->getDocument()->undo();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

void ImpressionistUI::cb_dissolveDialog(Fl_Menu_ *o, void *v) {
	ImpressionistUI::whoami(o)->m_DissolveDialog->show();
}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	pDoc->setBrushType(type);
	
	// Activate or deactivate Widget base on the brush chosen
	if(type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
		pUI->m_StrokeDirChoice->activate();
		pUI->m_BrushWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
	} else {
		pUI->m_StrokeDirChoice->deactivate();
		pUI->m_BrushWidthSlider->deactivate();
		pUI->m_LineAngleSlider->deactivate();
	}
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Sets the type of stroke direction to use to the one chosen in the brush 
// choice.  
// Called by the UI when a direction for the brush
//-----------------------------------------------------------
void ImpressionistUI::cb_strokeDir(Fl_Widget *o, void *v) {

	ImpressionistUI *pUI = ( (ImpressionistUI *) ( o->user_data() ) );
	ImpressionistDoc *pDoc = pUI->getDocument();
	
	int type = (int) v;

	pDoc->setStrokeDirType(type);
}

//-----------------------------------------------------------
// Updates the brush width to use from the value of the width
// slider
// Called by the UI when the width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_widthSlides(Fl_Widget *o, void *v) {
	( (ImpressionistUI *) ( o->user_data() ) )->m_nBrushWidth = int(( (Fl_Slider *) o )->value());
}

//-----------------------------------------------------------
// Updates the line rotation angle to use from the value 
// of the line angle slider
// Called by the UI when the lien angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_rotationAngle(Fl_Widget *o, void *v) {
	( (ImpressionistUI *) ( o->user_data() ) )->m_nRotationAngle = int(( (Fl_Slider *) o )->value());
}

//-----------------------------------------------------------
// Updates the opacity alpha to use from the value 
// of the opacity alpha slider
// Called by the UI when the alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alpha(Fl_Widget *o, void *v) {
	( (ImpressionistUI *) ( o->user_data() ) )->m_nAlpha = float(( (Fl_Slider *) o )->value());
}

//-----------------------------------------------------------
// Update the red color index
//-----------------------------------------------------------
void ImpressionistUI::cb_red(Fl_Widget *o, void *v) {
	((ImpressionistUI *) (o->user_data()))->m_nRedScale = float(((Fl_Slider *) o)->value());
}

//-----------------------------------------------------------
// Update the green color index
//-----------------------------------------------------------
void ImpressionistUI::cb_green(Fl_Widget *o, void *v) {
	((ImpressionistUI *) (o->user_data()))->m_nGreenScale = float(((Fl_Slider *) o)->value());
}

//-----------------------------------------------------------
// Update the blue color index
//-----------------------------------------------------------
void ImpressionistUI::cb_blue(Fl_Widget *o, void *v) {
	((ImpressionistUI *) (o->user_data()))->m_nBlueScale = float(((Fl_Slider *) o)->value());
}

void ImpressionistUI::cb_choseDissolveFile(Fl_Widget *o, void *v) {
	ImpressionistUI *pUI = (ImpressionistUI *) (o->user_data());

	char *newfile = fl_file_chooser("Open File?", "*.bmp", pUI->getDocument()->getImageName());
	if (newfile != NULL) {
		pUI->m_nDissolveFileName = newfile;
	}
}

void ImpressionistUI::cb_dissolveAlpha(Fl_Widget *o, void *v) {
	((ImpressionistUI *) (o->user_data()))->m_nDissolveAlpha = float(((Fl_Slider *) o)->value());
}

void ImpressionistUI::cb_dissolve(Fl_Widget *o, void *v) {
	ImpressionistDoc *pDoc = ((ImpressionistUI *) (o->user_data()))->getDocument();
	pDoc->dissolve();
}

//------------------------------------------------
// Swap the original view and the paint view
//------------------------------------------------
void ImpressionistUI::cb_swabView(Fl_Menu_ *o, void *v) {
	ImpressionistDoc *pDoc = ImpressionistUI::whoami(o)->getDocument();
	pDoc->swapView();
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	if (size > ImpressionistDoc::MAX_SIZE) {
		this->m_BrushSizeSlider->value(ImpressionistDoc::MAX_SIZE);
		this->m_nSize = ImpressionistDoc::MAX_SIZE;
	} else if (size < ImpressionistDoc::MIN_SIZE) {
		this->m_BrushSizeSlider->value(ImpressionistDoc::MIN_SIZE);
		this->m_nSize = ImpressionistDoc::MIN_SIZE;
	} else {
		this->m_BrushSizeSlider->value(size);
		this->m_nSize = size;
	}
}

//-------------------------------------------------
// Return the brush width
//-------------------------------------------------
int ImpressionistUI::getBrushWidth() {
	return this->m_nBrushWidth;
}

void ImpressionistUI::setBrushWidth(const int &width) {
	if (width > ImpressionistDoc::MAX_WIDTH) {
		this->m_BrushSizeSlider->value(ImpressionistDoc::MAX_WIDTH);
		this->m_nBrushWidth = ImpressionistDoc::MAX_WIDTH;
	} else if (width < ImpressionistDoc::MIN_WIDTH) {
		this->m_BrushSizeSlider->value(ImpressionistDoc::MIN_WIDTH);
		this->m_nBrushWidth = ImpressionistDoc::MIN_WIDTH;
	} else {
		this->m_BrushSizeSlider->value(width);
		this->m_nBrushWidth = width;
	}
}

//-------------------------------------------------
// Return the rotation angle of line
//-------------------------------------------------
int ImpressionistUI::getRotationAngle() {
	return this->m_nRotationAngle;
}

//-------------------------------------------------
// Set the rotation angle
//-------------------------------------------------
void ImpressionistUI::setRotationAngle(const int& angle) {
	if (angle > ImpressionistDoc::MAX_ANGLE) {
		this->m_LineAngleSlider->value(ImpressionistDoc::MAX_ALPHA);
		this->m_nRotationAngle = ImpressionistDoc::MAX_ANGLE;
	} else if (angle < ImpressionistDoc::MIN_ANGLE) {
		this->m_LineAngleSlider->value(ImpressionistDoc::MIN_ANGLE);
		this->m_nRotationAngle = ImpressionistDoc::MIN_ANGLE;
	} else {
		this->m_LineAngleSlider->value(this->m_nRotationAngle);
		this->m_nRotationAngle = angle;
	}
}

//-------------------------------------------------
// Return the opacity alpha
//-------------------------------------------------
float ImpressionistUI::getAlpha() {
	return this->m_nAlpha;
}

void ImpressionistUI::setAlpha(const float &alpha) {
	if (alpha > ImpressionistDoc::MAX_ALPHA) {
		this->m_AlphaSlider->value(ImpressionistDoc::MAX_ALPHA);
		this->m_nAlpha = ImpressionistDoc::MAX_ALPHA;
	} else if (alpha > ImpressionistDoc::MIN_ALPHA) {
		this->m_AlphaSlider->value(ImpressionistDoc::MIN_ALPHA);
		this->m_nAlpha = ImpressionistDoc::MIN_ALPHA;
	} else {
		this->m_AlphaSlider->value(alpha);
		this->m_nAlpha = alpha;
	}
}

float ImpressionistUI::getRedScale() const {
	return this->m_nRedScale;
}

float ImpressionistUI::getGreenScale() const {
	return this->m_nGreenScale;
}

float ImpressionistUI::getBlueScale() const {
	return this->m_nBlueScale;
}

char *ImpressionistUI::getDissolveFileName() const {
	return this->m_nDissolveFileName;
}

float ImpressionistUI::getDissolveAlpha() const {
	return this->m_nDissolveAlpha;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{"&Bonus",		0, 0, 0, FL_SUBMENU},
		{"&Swap Image",		FL_ALT+'s', (Fl_Callback*) ImpressionistUI::cb_swabView},
		{"&Color",			FL_ALT+'c', (Fl_Callback*) ImpressionistUI::cb_color},
		{"&Undo",			FL_ALT+'z', (Fl_Callback*) ImpressionistUI::cb_undo},
		{"&Dissolve",		FL_ALT+'d', (Fl_Callback*) ImpressionistUI::cb_dissolveDialog},
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Gray Scale",		FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_GRAY_SCALE},
  {"Triangle",			FL_ALT+'t', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_TRIANGLE},
  {"Scattered Triangle",FL_ALT+'w', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_TRIANGLE},
  {"Rings",				FL_ALT + 'r', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_RING},
  {"Scattered Rings",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_RING},
  {"Glass Mosaic",	FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_GLASS_MOSAIC},
  {"Basic Blur",	FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_BLUR},
  {"Basic Sharpen",	FL_ALT + 'h', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SHARPEN},
  {0}
};

//	Stroke direction menu definition
Fl_Menu_Item ImpressionistUI::strokeDirMenu[NUM_STROKE_TYPE + 1] = {
	{"Slider/Right Mouse",		FL_ALT+'s', (Fl_Callback *) ImpressionistUI::cb_strokeDir, (void *) STR_SLIDER_OR_MOUSE},
	{"Gradient",				FL_ALT+'g', (Fl_Callback *) ImpressionistUI::cb_strokeDir, (void *) STR_GRADIENT},
	{"Brush Direction",			FL_ALT+'b', (Fl_Callback *) ImpressionistUI::cb_strokeDir, (void *) STR_BRUSH_DIR},
	{0}
};

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
	m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
	// install menu bar
	m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
	m_menubar->menu(menuitems);

	// Create a group that will hold two sub windows inside the main
	// window
	Fl_Group* group = new Fl_Group(0, 25, 600, 275);

	// install paint view window
	m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
	m_paintView->box(FL_DOWN_FRAME);

	// install original view window
	m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
	m_origView->box(FL_DOWN_FRAME);
	m_origView->deactivate();

	group->end();
	Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// ----------------------------------------------------
	// Attributes initialization
	// ----------------------------------------------------
	this->m_nSize = 10;
	this->m_nBrushWidth = 1;
	this->m_nRotationAngle = 0;
	this->m_nAlpha = 1.0;
	this->m_nRedScale = 1.0;
	this->m_nGreenScale = 1.0;
	this->m_nBlueScale = 1.0;
	this->m_nDissolveFileName = NULL;
	this->m_nDissolveAlpha = 0.5;

	// ----------------------------------------------------
	// brush dialog definition
	// ----------------------------------------------------
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");

	// Add a brush type choice to the dialog
	m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
	m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushTypeChoice->menu(brushTypeMenu);
	m_BrushTypeChoice->callback(cb_brushChoice);

	// Add clear canvas button to the dialog
	m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
	m_ClearCanvasButton->user_data((void*)(this));
	m_ClearCanvasButton->callback(cb_clear_canvas_button);

	// Add stroke direction method to the dialog
	m_StrokeDirChoice = new Fl_Choice(114, 40, 150, 25, "&Stroke Direction");
	m_StrokeDirChoice->user_data((void *) ( this ));
	m_StrokeDirChoice->menu(strokeDirMenu);
	m_StrokeDirChoice->callback(cb_strokeDir);

	// Add brush size slider to the dialog 
	m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
	m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
    m_BrushSizeSlider->labelfont(FL_COURIER);
    m_BrushSizeSlider->labelsize(12);
	m_BrushSizeSlider->minimum(ImpressionistDoc::MIN_SIZE);
	m_BrushSizeSlider->maximum(ImpressionistDoc::MAX_SIZE);
	m_BrushSizeSlider->step(1);
	m_BrushSizeSlider->value(m_nSize);
	m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
	m_BrushSizeSlider->callback(cb_sizeSlides);

	// Add brush width slider to the dialog
	m_BrushWidthSlider = new Fl_Value_Slider(10, 105, 300, 20, "Line Width");
	m_BrushWidthSlider->user_data((void *) ( this ));	// record self to be used by static callback functions
	m_BrushWidthSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushWidthSlider->labelfont(FL_COURIER);
	m_BrushWidthSlider->labelsize(12);
	m_BrushWidthSlider->minimum(ImpressionistDoc::MIN_WIDTH);
	m_BrushWidthSlider->maximum(ImpressionistDoc::MAX_WIDTH);
	m_BrushWidthSlider->step(1);
	m_BrushWidthSlider->value(this->m_nBrushWidth);
	m_BrushWidthSlider->align(FL_ALIGN_RIGHT);
	m_BrushWidthSlider->callback(cb_widthSlides);
	m_BrushWidthSlider->deactivate();

	// Add rotation angle slider to the dialog
	m_LineAngleSlider = new Fl_Value_Slider(10, 130, 300, 20, "Line Angle");
	m_LineAngleSlider->user_data((void *) ( this ));	// record self to be used by static callback functions
	m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
	m_LineAngleSlider->labelfont(FL_COURIER);
	m_LineAngleSlider->labelsize(12);
	m_LineAngleSlider->minimum(ImpressionistDoc::MIN_ANGLE);
	m_LineAngleSlider->maximum(ImpressionistDoc::MAX_ANGLE);
	m_LineAngleSlider->step(1);
	m_LineAngleSlider->value(this->m_nRotationAngle);
	m_LineAngleSlider->align(FL_ALIGN_RIGHT);
	m_LineAngleSlider->callback(cb_rotationAngle);
	m_LineAngleSlider->deactivate();

	// Add alpha slider to the dialog
	m_AlphaSlider = new Fl_Value_Slider(10, 155, 300, 20, "Alpha");
	m_AlphaSlider->user_data((void *) ( this ));	// record self to be used by static callback functions
	m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
	m_AlphaSlider->labelfont(FL_COURIER);
	m_AlphaSlider->labelsize(12);
	m_AlphaSlider->minimum(ImpressionistDoc::MIN_ALPHA);
	m_AlphaSlider->maximum(ImpressionistDoc::MAX_ALPHA);
	m_AlphaSlider->step(0.01);
	m_AlphaSlider->value(this->m_nAlpha);
	m_AlphaSlider->align(FL_ALIGN_RIGHT);
	m_AlphaSlider->callback(cb_alpha);

    m_brushDialog->end();

	// ----------------------------------------------------
	// Color dialog definition
	// ----------------------------------------------------
	m_ColorDialog = new Fl_Window(400, 325, "Color Dialog");

	// Add red color index slider to the dialog
	m_RedSilder = new Fl_Value_Slider(10, 40, 300, 20, "&Red");
	m_RedSilder->user_data((void *) (this));	// record self to be used by static callback functions
	m_RedSilder->type(FL_HOR_NICE_SLIDER);
	m_RedSilder->labelfont(FL_COURIER);
	m_RedSilder->labelsize(12);
	m_RedSilder->minimum(ImpressionistDoc::MIN_COLOR_SCALE);
	m_RedSilder->maximum(ImpressionistDoc::MAX_COLOR_SCALE);
	m_RedSilder->step(0.01);
	m_RedSilder->value(this->m_nRedScale);
	m_RedSilder->align(FL_ALIGN_RIGHT);
	m_RedSilder->callback(cb_red);

	// Add green color index slider to the dialog
	m_GreenSilder = new Fl_Value_Slider(10, 65, 300, 20, "&Green");
	m_GreenSilder->user_data((void *) (this));	// record self to be used by static callback functions
	m_GreenSilder->type(FL_HOR_NICE_SLIDER);
	m_GreenSilder->labelfont(FL_COURIER);
	m_GreenSilder->labelsize(12);
	m_GreenSilder->minimum(ImpressionistDoc::MIN_COLOR_SCALE);
	m_GreenSilder->maximum(ImpressionistDoc::MAX_COLOR_SCALE);
	m_GreenSilder->step(0.01);
	m_GreenSilder->value(this->m_nGreenScale);
	m_GreenSilder->align(FL_ALIGN_RIGHT);
	m_GreenSilder->callback(cb_green);

	// Add blue color index slider to the dialog
	m_BlueSilder = new Fl_Value_Slider(10, 90, 300, 20, "&Blue");
	m_BlueSilder->user_data((void *) (this));	// record self to be used by static callback functions
	m_BlueSilder->type(FL_HOR_NICE_SLIDER);
	m_BlueSilder->labelfont(FL_COURIER);
	m_BlueSilder->labelsize(12);
	m_BlueSilder->minimum(ImpressionistDoc::MIN_COLOR_SCALE);
	m_BlueSilder->maximum(ImpressionistDoc::MAX_COLOR_SCALE);
	m_BlueSilder->step(0.01);
	m_BlueSilder->value(this->m_nBlueScale);
	m_BlueSilder->align(FL_ALIGN_RIGHT);
	m_BlueSilder->callback(cb_blue);

	m_ColorDialog->end();

	// ----------------------------------------------------
	// Dissolve dialog definition
	// ----------------------------------------------------
	m_DissolveDialog = new Fl_Window(400, 325, "Color Dialog");

	// Add choose file button into dialog
	m_FileChoseButton = new Fl_Button(10, 10, 150, 25, "&Choose FIle");
	m_FileChoseButton->user_data((void *) (this));
	m_FileChoseButton->callback(cb_choseDissolveFile);

	// Add dissolve alpha slider into dialog
	m_DissolveAlphaSilder = new Fl_Value_Slider(10, 45, 300, 20, "&Alpha");
	m_DissolveAlphaSilder->user_data((void *) (this));	// record self to be used by static callback functions
	m_DissolveAlphaSilder->type(FL_HOR_NICE_SLIDER);
	m_DissolveAlphaSilder->labelfont(FL_COURIER);
	m_DissolveAlphaSilder->labelsize(12);
	m_DissolveAlphaSilder->minimum(ImpressionistDoc::MIN_ALPHA);
	m_DissolveAlphaSilder->maximum(ImpressionistDoc::MAX_ALPHA);
	m_DissolveAlphaSilder->step(0.01);
	m_DissolveAlphaSilder->value(this->m_nDissolveAlpha);
	m_DissolveAlphaSilder->align(FL_ALIGN_RIGHT);
	m_DissolveAlphaSilder->callback(cb_dissolveAlpha);
	
	// Add dissolve button into dialog
	m_DissolveButton = new Fl_Button(10, 100, 150, 25, "&Dissolve");
	m_DissolveButton->user_data((void *) (this));
	m_DissolveButton->callback(cb_dissolve);

	//m_buff = new Fl_Text_Buffer();
	//m_disp = new Fl_Text_Display(10, 70, 300, 25);
	//m_disp->buffer(m_buff);
	//m_disp->resizable();

	m_DissolveDialog->end();
}
