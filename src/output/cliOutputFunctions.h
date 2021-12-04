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

int xMultiplier = 2; //This multiples the coord of any x location by 2 so you
bool renderOutsideBorder = false;
int xMax, xMin;
int yMax, yMin;

void updateBorder(int xMinArg, int xMaxArg, int yMinArg, int yMaxArg, bool ROBArg) {
    renderOutsideBorder = ROBArg;
    xMin = xMinArg; xMax = xMaxArg; yMin = yMinArg; yMax = yMaxArg;
}


void setCursor(bool visibility) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; info.bVisible = visibility;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}



void gotoxy(int x, int y, bool exception) {
    
    if (exception != true) {
        if (renderOutsideBorder != true) {
            if (x >= xMax) { x = xMax-1; }
            if (x < xMin)  { x = xMin;   }
            if (y >= yMax) { y = yMax-1; }
            if (y < yMin)  { y = yMin;   }
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
void plotPixel(int x, int y, int colour) {
    setColour(colour);
    gotoxy(x,y, false); std::cout<<"#";
    return;
}


void plotSolidRectangle(int x1, int y1, int x2, int y2, int colour, std::string bgPixel) {
    setColour(colour);
    for (int y=y1; y<y2; y++) {
        for (int x=x1; x<x2; x++) {
            gotoxy(x,y, false); std::cout << bgPixel;
        }
    }
}


void plotLine(int x0, int y0, int x1, int y1, int colour) { //DDA Line Algo
    int dx = x1-x0;
    int dy = y1-y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); //Calculating the number of steps requiresd to complete the line.

    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    float X = x0;
    float Y = y0;

    for (int i=0; i<=steps; i++) {
        plotPixel((int)X, (int)Y, colour);
        X += Xinc;
        Y += Yinc;
    }
}



void clearScreen(){
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
    return;
}
