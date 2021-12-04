#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#pragma
#include "cliOutputFunctions.h"
#include "functions.h"

std::map<std::string, std::vector<std::vector<int>>> standardShapeMap = {
    {"square",{{0,0}, {0,1}, {1,1}, {1,0}}}
};


class windowObject {
    private:
        std::string stdPixel = "#";
        bool allowRenderOutsideBorder = false; //without this you can have ugly pixels outside the window.
        int width;
        int height;
        int colour; //Current Console Colour;
        std::vector<int> origin;
        int windowBgColour;
        std::vector<std::pair<std::vector<int>, std::vector<int>>> lineBuffer;

    public:
        void plotPoint(std::vector<int> vect);
        void drawLine(std::pair<std::vector<int>, std::vector<int>> line);

        void updateFgColour(int colour);
        void updateBgColour(int colour);
        void updateBgAndFgColour(int fg, int bg);

        void loadShapeToBuffer(std::vector<std::vector<int>> shapeVerticies);
        void loadStandardShapeToBuffer(std::string name, std::vector<int> origin, int scaleFactor);

        void plotBufferIndex(int indexVal);
        void plotBuffer();
        void addParsedSpriteMapToBuffer(std::vector< std::pair<std::vector<std::vector<int>>, std::vector<int>>> spriteMapData);
        void addToBuffer(std::pair<std::vector<int>, std::vector<int>> lineData);
        void clearBuffer();
        
        void refreshWindow();

        windowObject(int widthArg, int heightArg, int bgColour, std::vector<int> originArg={0,0}) {
            width = widthArg; height = heightArg;
            windowBgColour = bgColour;
            origin = originArg;

            setCursor(false);
            clearScreen();
            updateBorder(origin.at(0), origin.at(0)+width, origin.at(1), origin.at(1)+height, allowRenderOutsideBorder);
            
            refreshWindow();
        }
};



void windowObject::loadShapeToBuffer(std::vector<std::vector<int>> shapeVerticies) {
    std::vector<int> previousVert = shapeVerticies.at(shapeVerticies.size()-1);
    for (std::vector<int> vert: shapeVerticies) {
        lineBuffer.push_back({{previousVert.at(0)+origin.at(0), previousVert.at(1)+origin.at(1)}, {vert.at(0)+origin.at(0), vert.at(1)+origin.at(1)}});
        previousVert = vert;
    }
}

void windowObject::loadStandardShapeToBuffer(std::string name, std::vector<int> origin, int scaleFactor) {
    std::vector<std::vector<int>> shape = standardShapeMap[name];
    for (int vertPtr=0; vertPtr<shape.size(); vertPtr++) {
        shape.at(vertPtr) = {shape.at(vertPtr).at(0)*scaleFactor, shape.at(vertPtr).at(1)*scaleFactor};
    }

    loadShapeToBuffer(shape);
}



void windowObject::refreshWindow() {
    plotSolidRectangle(origin.at(0), origin.at(1), origin.at(0)+width, origin.at(1)+height, windowBgColour, stdPixel);
}


//Low level graphical Functions:
void windowObject::plotPoint(std::vector<int> vect) {
    if (vect.at(0) >= origin.at(0) && vect.at(0) < origin.at(0)+width   &&   vect.at(1) >= origin.at(1) && vect.at(1) < origin.at(1)+height) {
        plotPixel(vect.at(0), vect.at(1), colour); 
    }
}

void windowObject::drawLine(std::pair<std::vector<int>, std::vector<int>> line) { plotLine(line.first.at(0)+origin.at(0), line.first.at(1)+origin.at(1), line.second.at(0)+origin.at(0), line.second.at(1)+origin.at(1), colour); }


//Colour Functions:
void windowObject::updateFgColour(int colourArg) { colour = colourArg; }

void windowObject::updateBgColour(int colourArg) { colour = colourArg*16; }

void windowObject::updateBgAndFgColour(int fg, int bg) { colour = bg*16 + fg; }


//Higher level graphical functions:
void windowObject::plotBuffer() {
    for (std::pair<std::vector<int>, std::vector<int>> line: lineBuffer) {
        plotLine(line.first.at(0), line.first.at(1), line.second.at(0), line.second.at(1), colour);
    }
}

void windowObject::addToBuffer(std::pair<std::vector<int>, std::vector<int>> lineData) { lineBuffer.push_back(lineData); }

void windowObject::clearBuffer() { lineBuffer.clear(); }

void windowObject::plotBufferIndex(int indexVal) {
    std::pair<std::vector<int>, std::vector<int>> line = lineBuffer.at(indexVal);
    plotLine(line.first.at(0), line.first.at(1), line.second.at(0), line.second.at(1), colour);
}










class textWindowObject {
    private:
        std::string rawText;
        std::vector<std::string> formattedText;

        std::string pad = "#";
        std::string windowName;
        int width;
        int height;
        int padding = 1;

        std::vector<int> origin;

        void formatStringToVector(); //Autmatically called process for parsing data into diffarent lines.

    public:
        int colour=15;

        void updateText(std::string newText);
        void renderText();


        textWindowObject(int widthArg, int heightArg, std::string windowNameArg, std::vector<int> originArg={0,0}) {
            width = widthArg; height = heightArg; origin = originArg; windowName = windowNameArg;
        }
};

void textWindowObject::formatStringToVector() { //So it fits on the screen.
    formattedText.clear();
    std::vector<std::string> seperatedWords = splitString(rawText, (char)" "[0]);
    std::stringstream line;
    
    int currentLength = 0;
    for (std::string word: seperatedWords) {
        if (line.str().size() + word.size() + 1 >= width) {
            formattedText.push_back(line.str());
            line.str(std::string());
        }
        line << word << " ";
    }
    formattedText.push_back(line.str());
}


void textWindowObject::updateText(std::string newText) {
    rawText = newText;
    formatStringToVector();
}

void textWindowObject::renderText() {
    int linePtr = 0;
    setColour(colour);

    gotoxy(origin.at(0), origin.at(1), true);
    setColour(4);
    std::cout << pad << "NAME: " << windowName;
    setColour(colour);
    for (std::string line: formattedText) {
        gotoxy(origin.at(0), origin.at(1)+linePtr+1, true);
        for (int i=0; i<padding; i++) {
            std::cout << pad;
        }
        std::cout << line;
        linePtr += 1;
    }
}
