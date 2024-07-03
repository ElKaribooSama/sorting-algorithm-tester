#include "primitive.h"
#include <iostream>

void line(Vec2f *pts, graphic_buffers *buffs, COLORREF color) {
    size_t length = std::max(std::abs(pts[0].x - pts[1].x),std::abs(pts[0].y - pts[1].y));
    float step = 1. / (length + 1);

    for (float t=0;t<1;t+=step) {
        int x = pts[0].x + (pts[1].x - pts[0].x)*t;
        int y = pts[0].y + (pts[1].y - pts[0].y)*t;
        buffs->set_pixel(x, y, color);
    }
}

void line(Vec2f *pts, int width, graphic_buffers *buffs, COLORREF color) {
    size_t length = std::max(std::abs(pts[0].x - pts[1].x),std::abs(pts[0].y - pts[1].y));
    Vec2f thickness_dir = Vec2f((pts[0].y - pts[1].y),-(pts[0].x - pts[1].x));
    Vec2f normal = thickness_dir * (1. / sqrt(thickness_dir.x * thickness_dir.x + thickness_dir.y * thickness_dir.y));
    float step = 1. / (length + 1);

    for (float t=0;t<1;t+=step) {
        int x = pts[0].x + (pts[1].x - pts[0].x)*t;
        int y = pts[0].y + (pts[1].y - pts[0].y)*t;
        buffs->set_pixel(x, y, color);
        for (int w=0;w<width;w++) {
            buffs->set_pixel(x - (normal.x * w), y - (normal.y * w), color);
            buffs->set_pixel(x + (normal.x * w), y + (normal.y * w), color);
        }
    }
}


void box(Vec2f *pts, graphic_buffers *buffs, COLORREF color, COLORREF) {
    for (int x = pts[0].x; x < pts[1].x; x++) {
        for (int y = pts[0].y; y < pts[1].y; y++) {
            buffs->set_pixel(x, y, color);
        }
    }
};

void box(Vec2f c, float w, float h, graphic_buffers *buffs, COLORREF color) {
    Vec2f b0,b1;
    b0 = Vec2f(c.x - w,c.y - h);
    b1 = Vec2f(c.x + w,c.y + h);

    for (int x = b0.x; x < b1.x; x++) {
        for (int y = b0.y; y < b1.y; y++) {
            buffs->set_pixel(x, y, color);
        }
    }
};

void circle(Vec2f c, float r, graphic_buffers *buffs, COLORREF color) {
    Vec2f b0,b1;
    b0 = Vec2f(c.x - r,c.y - r);
    b1 = Vec2f(c.x + r,c.y + r);

    for (int x = b0.x; x < b1.x; x++) {
        for (int y = b0.y; y < b1.y; y++) {
            Vec2f p = c - Vec2f(x,y);
            if (sqrt(p.x*p.x + p.y*p.y) < r) {
                buffs->safe_set_pixel(x, y, color);
            }
        }
    }
};

void elipse(Vec2f *pts, float r, graphic_buffers *buffs, COLORREF color) {

};

Vec3f cross(Vec3f v1, Vec3f v2) {
    return Vec3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

Vec3f baricentric(Vec2f v1, Vec2f v2, Vec2f v3, Vec2f p) {
    Vec3f u = cross(Vec3f(v3.x-v1.x,v2.x-v1.x,v1.x-p.x), Vec3f(v3.y-v1.y,v2.y-v1.y,v1.y-p.y));
    if (std::abs(u.z)>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void triangle(Vec2f *pts, graphic_buffers *buffs, COLORREF color) {
    Vec2f b0,b1;
    b0 = Vec2f(std::min(std::min(pts[0].x,pts[1].x),pts[2].x),std::min(std::min(pts[0].y,pts[1].y),pts[2].y));
    b1 = Vec2f(std::max(std::max(pts[0].x,pts[1].x),pts[2].x),std::max(std::max(pts[0].y,pts[1].y),pts[2].y));

    for (int x = b0.x; x < b1.x; x++) {
        for (int y = b0.y; y < b1.y; y++) {
            Vec3f bar = baricentric(pts[0],pts[1],pts[2],Vec2f(x,y));

            if (bar.x >= 0 && bar.y >= 0 && bar.x + bar.y <= 1) {
                buffs->set_pixel(x, y, color);
            }
        }
    }
};