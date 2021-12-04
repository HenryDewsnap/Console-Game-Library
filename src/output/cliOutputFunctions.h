#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

//----------------------//
//     colors:
//     0 = Black
//     1 = Blue
//     2 = Green
//     3 = Cyan
//     4 = Red
//     5 = Magenta
//     6 = Yellow
//     7 = LightGray
//     8 = DarkGray
//     9 = LightBlue
//     10 = LightGreen
//     11 = LightCyan
//     12 = LightRed
//     13 = LightMagenta
//     14 = LightYellow
//     15 = White
//----------------------//

class outputConditions {
    public:
        
        int xMax, xMin;
        int yMax, yMin;
        bool exeption;

        void setConditions(bool exeptionArg, int xMaxArg, int xMinArg, int yMaxArg, int yMinArg) {
            xMax = xMaxArg; xMin = xMinArg; yMax = yMaxArg; yMin = yMinArg; exeption = exeptionArg;
        }
};



bool renderOutsideBorder = false;
int xMultiplier = 2; //This multiples the coord of any x location by 2 so you





void setCursor(bool visibility) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; info.bVisible = visibility;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}



void gotoxy(int x, int y, outputConditions conditionObj) {
    
    if (conditionObj.exeption != true) {
        if (renderOutsideBorder != true) {
            if (x >= conditionObj.xMax) { x = conditionObj.xMax-1; }
            if (x < conditionObj.xMin)  { x = conditionObj.xMin;   }
            if (y >= conditionObj.yMax) { y = conditionObj.yMax-1; }
            if (y < conditionObj.yMin)  { y = conditionObj.yMin;   }
        }
    }
    COORD coord;
    coord.X = x * xMultiplier; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}


void setColour(WORD colour) { //A word is a 2 byte piece of info.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    return;
}

void setFgAndBgColour(int fg, int bg) {
    int colour = bg * 16  + fg; //The reason i multiply the background by 16 is because i needed to convert its value to hexidecimal.
    setColour(colour);
    return;
}

//https://www.fileformat.info/info/unicode/block/geometric_shapes/list.htm
void plotPixel(int x, int y, int colour, outputConditions conditionObj) {
    setColour(colour);
    gotoxy(x,y, conditionObj); std::cout<<"#";
    return;
}


void plotSolidRectangle(int x1, int y1, int x2, int y2, int colour, std::string bgPixel, outputConditions conditionObj) {
    setColour(colour);
    for (int y=y1; y<y2; y++) {
        for (int x=x1; x<x2; x++) {
            gotoxy(x,y, conditionObj); std::cout << bgPixel;
        }
    }
}


void plotLine(int x0, int y0, int x1, int y1, int colour, outputConditions conditionObj) { //DDA Line Algo
    int dx = x1-x0;
    int dy = y1-y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); //Calculating the number of steps requiresd to complete the line.

    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    float X = x0;
    float Y = y0;

    for (int i=0; i<=steps; i++) {
        plotPixel((int)X, (int)Y, colour, conditionObj);
        X += Xinc;
        Y += Yinc;
    }
}



