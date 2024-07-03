//builtin
#include <iostream>
#include <fstream> // To use ifstream
#include <stdlib.h>     /* atoi */
#include <vector>
#include <chrono>
//src
#include "./src/geometry.h"
#include "./src/primitive.h"
#include "./src/text.h"
//bbgl
#include "./bbgl/bbgl.h"


#define rgb(r,g,b) ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))

BBGL *bbgl;
void update();
void sorting();

TEXTDRAWER textdrawer("textfont.bmp",16);
COLORREF white = rgb(255,255,255);
COLORREF red   = rgb(255,  0,  0);
COLORREF blue  = rgb(  0,  0,255);
COLORREF green = rgb(  0,255,  0);

char *HelloWorld = "hello world!";
char *TimeSpent = "time spent:";

int *baseArray;
int *sortingArray;

void loadArray() {
    baseArray = new int[256];
    sortingArray = new int[256];
    int count = 0;

    FILE *pFile;
    std::vector<char> buffer;
    
    char ch = 'x';

    pFile = fopen ("input.txt" , "r");
    if (pFile == NULL) {
        perror ("Error opening file");
    } else {
        while (!feof(pFile)) {
            ch = fgetc(pFile);
            while(ch != ' ' && !feof(pFile)) {
                buffer.push_back(ch);
                ch = fgetc(pFile);
            }
            buffer.push_back('\0');
            char *bufferArr = &buffer[0];
            baseArray[count] = atoi(bufferArr);
            sortingArray[count] = atoi(bufferArr);
            count++;
            buffer.erase(buffer.begin(),buffer.end());
        }
        fclose(pFile);
    }
}

bool sortingFinished = false;
int sort_i, sort_l, sort_o;
bool swapped = false;
std::chrono::duration<double> sort_duration;
std::chrono::_V2::steady_clock::time_point start;

void back_sorting() {
    int i, j;
    bool swapped;
    for (i = 0; i < 256 - 1; i++) {
        swapped = false;
        for (j = 0; j < 256 - i - 1; j++) {
            if (sortingArray[j] > sortingArray[j + 1]) {
                std::swap(sortingArray[j], sortingArray[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false) {
            sort_duration = std::chrono::steady_clock::now() - start; 
            break;
        };
    }
}

void visual_sorting() {
    if (sortingFinished) return;

    for (int k = 0;k<sort_o;k++) {
        if(sort_i == sort_l) {
            sort_i=0;
            sort_l--;
            if (sort_l < 2 || !swapped) {
                sortingFinished = true;
                return;
            } else {
                swapped = false;
            }
        } else {
            sort_i++;
        }

        if (sortingArray[sort_i] > sortingArray[sort_i + 1]) {
            std::swap(sortingArray[sort_i], sortingArray[sort_i + 1]);
            swapped = true;
        }
    }
}

void drawBars(int sx, int sy, COLORREF color) {
    Vec2f linepoints[2];
    for (int x=0;x<256;x++) {
        linepoints[0] = Vec2f(x+sx,sy);
        linepoints[1] = Vec2f(x+sx,sy-sortingArray[x]);

        line(linepoints,bbgl->buffs,color);
    }
}

void setup() {
    loadArray();
    sort_l = 256;
    sort_o = 100;
    start = std::chrono::steady_clock::now();
    back_sorting();
    for(int k=0;k<256;k++) sortingArray[k] = baseArray[k];
}

void update() {
    if (!sortingFinished) {
        visual_sorting();
    } else {
        char array[10];
        sprintf(array, "%f", sort_duration);
        textdrawer.drawStringAt("time spent:",10,Vec2f(8,32),bbgl->buffs,red,false);
        textdrawer.drawStringAt(array,7,Vec2f(16*11 + 8,32),bbgl->buffs,white,false);
    }
    textdrawer.drawStringAt("hello world!",11,Vec2f(8,16),bbgl->buffs,red,false);
    // textdrawer.drawStringAt("start",11,Vec2f(8,16),bbgl->buffs,red,false);
    drawBars(32,332,red);
    // if (bbgl->inputs.mouse.leftClick) {
    //     circle(Vec2f(bbgl->inputs.mouse.positionX,bbgl->inputs.mouse.positionY),2,bbgl->buffs,rgb(255,0,0));
    // }
}

int main() {
    BBGLOPTIONS bbglOptions;
    bbglOptions.windowOptions.minWidth = 345;
    bbglOptions.windowOptions.minHeight = 425;
    // bbglOptions.windowOptions.maxHeight = 712;
    // bbglOptions.windowOptions.maxWidth = 712;
    bbglOptions.windowOptions.allowResize = false;
    bbglOptions.windowOptions.allowMaximised = false;
    bbglOptions.bufferOptions.clearBufferOnDraw = true;
    bbgl = new BBGL(bbglOptions);
    bbgl->update = update;

    setup();
    bbgl->start();

    std::cout << "GoodBye World!" << std::endl;
    return 0;
}

