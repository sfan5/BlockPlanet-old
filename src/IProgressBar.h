#ifndef IPROGRESSBAR_HEADER
#define IPROGRESSBAR_HEADER
#include "common_irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
class IProgressBar : public IGUIElement
{
public:
    
    IProgressBar(IGUIEnvironment * guienv,const core::rect<s32>& rectangle,s32 id=-1,IGUIElement * parent=0, IGUIFont * font=0);
    

    /*Set percentage in positive percentual (0~100). Please note that a call to this function with others values, will set the progress bar to 0.*/
    void setProgress(irr::u32 progress);

    /*Set bar Colors*/
    void setColors(irr::video::SColor progress= irr::video::SColor(255,255,255,255),irr::video::SColor filling= irr::video::SColor(255,0,0,0));

    /*Allow you to add a "border" into your bar. You MUST specify the size (of course in pixel) of the border. You can also pass a color parameter (Black by default)*/
    void addBorder(irr::s32 size,irr::video::SColor color = irr::video::SColor(255,0,0,0));
    
    /*Set the Text of the Progress Bar*/
    void setText(std::string s);

    
    virtual void draw();
private:
    
    IGUIEnvironment * gui; //GUI ENV. pointer
    irr::s32 total; //Dimension (X) of the bar, to calculate relative percentage.
    rect<s32> bar; //Dimension of the bar
    rect<s32> position; //Bar
    rect<s32> border; //Border 
    rect<s32> tofill; //Percentage indicator
    rect<s32> empty; //"Empty" indicator
    std::string text; // Text in the Progress Bar

    irr::video::SColor fillcolor;
    irr::video::SColor emptycolor;
    irr::video::SColor bordercolor;
    irr::video::IVideoDriver * vdriver;
    irr::gui::IGUIFont * textfont;
    
};
#endif
