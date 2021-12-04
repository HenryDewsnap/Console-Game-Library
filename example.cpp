#include <iostream>

#pragma
#include "src/output/graphicManager.hpp"
#include "src/sprite/spriteManager.hpp"

class program {
    private:
        

    public:


        program() {
            clearScreen();

            windowObject window(25, 25, 1, {0,0});
            window.loadShapeToBuffer({{0,0}, {10,0}, {10,10}, {0,10}});
            window.loadShapeToBuffer({{0,0}, {10,10}});
            window.loadShapeToBuffer({{0,10}, {10,0}});
            window.plotBuffer();

            textWindowObject textWindow(20, 10, "Console", {25,0});
            textWindow.updateText("testing testing... One Two Three, Does my bad coding appear to be working? Maybe... idk.");
            textWindow.renderText();

            textWindowObject textWindow2(20, 10, "Console 2", {25, 10});
            textWindow2.updateText("bruh this is pretty cool tbh, what do you think? I think its pretty epic and gamer if i do say so my self");
            textWindow2.renderText();

            windowObject window2(25, 25, 4, {45, 0});
            window2.loadShapeToBuffer({{24,24}, {10,24}, {10,10}, {24,10}});
            window2.loadShapeToBuffer({{24,24}, {10,10}});
            window2.loadShapeToBuffer({{24,10}, {10,24}});
            window2.plotBuffer();

            getchar();
        }
};

int main() {
    program application;
}
