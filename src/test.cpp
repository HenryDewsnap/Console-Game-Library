#include <iostream>

#pragma
#include "output/graphicManager.hpp"

int main() {
    windowObject win(25,25,1,{0,0});

    for (int i=0; i<25; i++) {
        win.updateFgColour(i%16);
        win.drawLine({{i,0},{i,24}});
    }


    /*    
    win.updateFgColour(4);

    for (int i=0; i<6; i++) {
    win.loadStandardShapeToBuffer("square", {i*4,i*4}, 4);
    }

    win.plotBuffer();
    win.clearBuffer();

    win.updateFgColour(5);
    win.drawLine({{0,4},{20,24}});
    win.drawLine({{4,0},{24,20}});

    for (int i=0; i<6; i++) {
        win.loadStandardShapeToBuffer("square", {20-(i*4),(i*4)}, 4);
    }
    win.updateFgColour(6);
    win.plotBuffer();
    win.clearBuffer();

    win.updateFgColour(8);
    win.drawLine({{5,3},{17,21}});
    */
}
