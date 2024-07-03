#include "text.h"



TEXTDRAWER::TEXTDRAWER(const char *bmp_path, int size) {
    textFont = new BMP(bmp_path);
    setTextSize(size);
}

TEXTDRAWER::~TEXTDRAWER() {
    free(ch);
}

void TEXTDRAWER::setTextSize(int size) {
    FONTSIZE = size;
    ch = (uint8_t *)malloc(sizeof(uint8_t) * (textFont->bmp_info_header.bit_count / 8) * size * size);
}

int charToBmpPos(char character) {
    if(character >= 'a' && character <= 'z') {
        return character - 'a' + 1;
    }

    if(character >= 'A' && character <= 'Z') {
        return character - 'A' + 1;
    }

    if(character >= ' ' && character <= '?') {
        return character; //weirdly i can just do that
    }

    return 0;
}

void TEXTDRAWER::drawStringAt(char *text, int length, Vec2f pos, graphic_buffers *buffs, COLORREF color, bool negative) {
    for(int i=0;i<=length;i++) {
        int character = charToBmpPos(text[i]);

        if (!negative) character = charToBmpPos(text[i]) + (textFont->bmp_info_header.width / FONTSIZE) * 4;
        Vec2i bmp_pos(character % (textFont->bmp_info_header.width / FONTSIZE),character / (textFont->bmp_info_header.width / FONTSIZE));
        
        this->getCharAt(bmp_pos.x,bmp_pos.y);
        
        int channels = textFont->bmp_info_header.bit_count / 8;

        for (int y = 0; y < FONTSIZE; y++) {
            for (int x = 0; x < FONTSIZE; x++) {
                int index = (y * FONTSIZE + x) * channels;
                if(ch[index] == 255 && ch[index + 1] == 255 && ch[index + 2] == 255 ) {
                    buffs->safe_set_pixel(pos.x + x, pos.y + y, color);
                }
            }
        }
        pos.x += FONTSIZE;
    }
}

void TEXTDRAWER::drawCharAt(char character, Vec2f pos, graphic_buffers *buffs, COLORREF color, bool negative) {
    if (!negative) character += (textFont->bmp_info_header.width / FONTSIZE) * 4;
    Vec2i bmp_pos(character % (textFont->bmp_info_header.width / FONTSIZE),character / (textFont->bmp_info_header.width / FONTSIZE));
    
    if (ch_pos.x != bmp_pos.x || ch_pos.y != bmp_pos.y) {
        this->getCharAt(bmp_pos.x,bmp_pos.y);
    }
    int channels = textFont->bmp_info_header.bit_count / 8;

    for (int y = 0; y < FONTSIZE; y++) {
        for (int x = 0; x < FONTSIZE; x++) {
            int index = (y * FONTSIZE + x) * channels;
            if(ch[index] == 255 && ch[index + 1] == 255 && ch[index + 2] == 255 ) {
                buffs->set_pixel(pos.x + x, pos.y + y, color);
            }
        }
    }
}

void TEXTDRAWER::getCharAt(int x,int y) {
    textFont->get_region(x*FONTSIZE,y*FONTSIZE,x*FONTSIZE + FONTSIZE,y*FONTSIZE + FONTSIZE,ch);
}