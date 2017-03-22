#include "../headers/styling.h"
#include "../headers/buffer.h"
#include <vector>


    Button b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, bDot, bPlus, bMinus, bDivide, bMultiply, bPercent, bSq, bCube,bNpow, bFact,bLeftB,bRightB,bReciprocal,bSin,bCos, bTan, bASin, bACos, bATan,
    bSqrt, bCbRt, bNroot, bLog, bLn, bExp, b10x, bPie,bEquals,bBackspace,bClear; //global objects

    vector<string> buttonString = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "/", "*", "%", "x2", "x3", "^", "!", "(", ")", "x-1", "sin", "cos", "tan", "sin-1", "cos-1", "tan-1","sqrt", "cbrt", "nthrt"
                                        "log", "ln", "e", "*10^", "pi","=", "BSP", "C"};

    vector<string> showString = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "/", "*", "%", "^2", "^3", "^", "!", "(", ")", "^(-1)", "sin", "cos", "tan", "asin", "acos", "atan","^(1/2)", "^(1/3)", "^(1/"
                                        "log", "ln", "e^", "10^", "pi","", "", ""};

    vector<string> returnString = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "/", "x", "%", "^2", "^3", "^", "!", "(", ")", "^(-1)", "s", "c", "t", "S", "C", "T", "^(1/2)","^(1/3)", "^(1/",
                                        "L", "l", "e^", "10^", "p","", "", ""};

    sf::Font font;
    loadFile("fonts/DroidSansMono.ttf",font);

    sf::SoundBuffer buffer;
    loadFile("audios/Click2-Sebastian-759472264.wav",buffer);

    vector<Button*> bAll = {&b0,&b1,&b2,&b3,&b4,&b5,&b6,&b7,&b8,&b9,&bDot,&bPlus,&bMinus,&bDivide,&bMultiply,&bPercent,&bSq, &bCube,&bNpow,&bFact,&bLeftB,&bRightB,&bReciprocal,&bSin,&bCos, &bTan, &bASin, &bACos, &bATan,
    &bSqrt, &bCbRt, &bNroot, &bLog, &bLn, &bExp, &b10x, &bPie,&bEquals,&bBackspace,&bClear};
    vector<Button*> bNums = {&b0,&b1,&b2,&b3,&b4,&b5,&b6,&b7,&b8,&b9};
    vector<Button*> bOperator = {&bPlus,&bMinus,&bMultiply,&bDivide,&bPercent,&bNpow};
    vector<Button*> bPowers = {&bSq,&bCube,&bReciprocal,&bSqrt,&bCbRt,&bNroot};
    vector<Button*> bFunctions = {&bSin,&bCos, &bTan, &bASin, &bACos, &bATan,&bLog, &bLn};
    vector<Button*> bRemovers = (&bClear,&bBackspace);

    void setClickable(vector<Button*> b, bool val)
    {
        for(unsigned int i=0; i<b.size(); ++i)
            b[i]->setClickable(val);
    }

    void setProps()
    {
        for(unsigned int i=0; i<bAll.size(); ++i)
        {

        }
    }
