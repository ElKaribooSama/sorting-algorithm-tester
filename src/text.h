#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_

#include "../bbgl/graphic_buffers.h"
#include "geometry.h"
#include "bmp.h"

class TEXTDRAWER {
public:
    TEXTDRAWER(const char *bmp_path, int size);
    ~TEXTDRAWER();
    void setTextSize(int size);
    void drawCharAt(char character, Vec2f pos, graphic_buffers *buffs, COLORREF color, bool negative = false);
    void drawStringAt(char *text, int length, Vec2f pos, graphic_buffers *buffs, COLORREF color, bool negative = false);
private:
    int FONTSIZE;
    BMP *textFont;
    Vec2i ch_pos;
    uint8_t *ch;
    void getCharAt(int x,int y);
};

#endif