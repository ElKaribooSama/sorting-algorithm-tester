//builtin
#include <iostream>
//src
#include "./src/geometry.h"
#include "./src/primitive.h"
#include "./src/text.h"
//bbgl
#include "./bbgl/bbgl.h"


#define rgb(r,g,b) ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))

BBGL *bbgl;
void update();

Vec2f tri[3] = {
    Vec2f(50,50),
    Vec2f(300,50),
    Vec2f(175,300)
};

Vec2f quad[4] = {
    Vec2f(50 ,300),
    Vec2f(50 , 50),
    Vec2f(300, 50),
    Vec2f(300,300),
};

Vec2f linepts[2] = {
    Vec2f(50,50),
    Vec2f(70,50)
};

COLORREF white = rgb(255,255,255);
COLORREF red   = rgb(255,  0,  0);
COLORREF blue  = rgb(  0,  0,255);
COLORREF green = rgb(  0,255,  0);

int FONTSIZE = 16;
int stringTest[12] = {
    8,5,12,12,15,32,23,15,18,12,4,33
};

TEXTDRAWER textdrawer("textfont.bmp",16);

void update() {
    if (bbgl->inputs.mouse.leftClick) {
        circle(Vec2f(bbgl->inputs.mouse.positionX,bbgl->inputs.mouse.positionY),2,bbgl->buffs,rgb(255,0,0));
    }
    textdrawer.drawStringAt(stringTest,11,Vec2f(50,50),bbgl->buffs,red);
}

int main() {
    BBGLOPTIONS bbglOptions;
    bbglOptions.windowOptions.maxHeight = 712;
    bbglOptions.windowOptions.maxWidth = 712;
    bbglOptions.windowOptions.allowResize = true;
    bbglOptions.windowOptions.allowMaximised = true;
    bbglOptions.bufferOptions.clearBufferOnDraw = false;

    bbgl = new BBGL(bbglOptions);
    bbgl->update = update;
    bbgl->start();
    std::cout << "GoodBye World!" << std::endl;
    return 0;
}

