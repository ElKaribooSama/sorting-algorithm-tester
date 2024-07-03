#pragma once
#ifndef _GEOMETRY_PRIMITIVE_H_
#define _GEOMETRY_PRIMITIVE_H_

#include "geometry.h"
#include "../bbgl/graphic_buffers.h"

void line(Vec2f *pts, graphic_buffers *buffs, COLORREF color);
void line(Vec2f *pts, int width, graphic_buffers *buffs, COLORREF color);
void box(Vec2f *pts, graphic_buffers *buffs, COLORREF color);
void box(Vec2f c, float w, float h, graphic_buffers *buffs, COLORREF color);
void circle(Vec2f c, float r, graphic_buffers *buffs, COLORREF color);
void elipse(Vec2f *pts, float r, graphic_buffers *buffs, COLORREF color);
void triangle(Vec2f *pts, graphic_buffers *buffs, COLORREF color);

#endif