#ifndef STYLING_H_INCLUDED
#define STYLING_H_INCLUDED

#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include<string>
#include <iostream>

int Stoi(std::string str)
{
    int res=0;
    for(unsigned int i=0; i<str.size(); ++i)
    {
        res += ((int)((char)str[i]) - 48)*pow(10.0,str.size()-i-1);
    }
    return res;
}


sf::String toSfString(std::string str)
{
    sf::String Str;

    for(unsigned int i=0; i<str.size(); ++i)
    {
        Str += (char)(str[i]);
    }

    return Str;
}


class Button : public sf::Transformable
{
public:


    //public data-members
    //NOTE: Convention for data-members followed is that there first alphabet is capitalized
    std::string ReturnValue;
    std::string ShowValue;
    sf::Text text; //to access the text such as obj.text.sfmlProp etc.



    void setDimensions(float X1, float Y1, float X2, float Y2)
    {
        x1=X1; y1=Y1; x2=X2; y2=Y2;

        //Drawing the button
        Box.setSize(sf::Vector2f(x2-x1,y2-y1));
        Box.setPosition(x1,y1);
    }


    void syncWithWindow(sf::RenderWindow* userWindow)
    {
        win = userWindow;
    }


    void setColor(short r, short g, short b, short a=255)
    {
        Clr = sf::Color(r,g,b,a);

        Box.setFillColor(Clr);
    }


    void setTextFont(sf::Font &userFont)
    {
        font = &userFont;
        text.setFont(*font);
    }


    void writeText(sf::String str)
    {
        text.setString(str);
        textX = x1 + ( (x2-x1)-text.getGlobalBounds().width )/2;
        textY = y1 + ( (y2-y1)-text.getGlobalBounds().height )/2;
        text.setPosition(textX,textY);
        boxStr = str;
    }


    void setTextOffset(float x, float y)
    {
        textX = textX + x;
        textY = textY + y;
        text.setPosition(textX,textY);
    }


    void setTextColor(short r, short g, short b, short a=255)
    {
        textClr = sf::Color(r,g,b,a);
        text.setFillColor(textClr);
    }


    void setOutline(short r, short g, short b, short a=255, float width=1)
    {
        outlineClr = sf::Color(r,g,b,a);
        outlineWidth = width;

        Box.setOutlineColor(outlineClr);
        Box.setOutlineThickness(outlineWidth);
    }


    bool isHovered()
    {
        if(win==nullptr)
            return false;

        sf::Vector2i mousePos = sf::Mouse::getPosition(*win);

        if(mousePos.x>=x1 && mousePos.x<=x2 && mousePos.y>=y1 && mousePos.y<=y2)
            return true;
        else
            return false;
    }


    void setHoverDimensions(float X1, float Y1, float X2, float Y2)
    {
        hoverDimensionsTrigger = true;
        hoverX1=X1; hoverY1=Y1; hoverX2=X2; hoverY2=Y2;
    }


    void setHoverTextColor(short r, short g, short b, short a=255)
    {
        hoverTextClr = sf::Color(r,g,b,a);
        hoverTextClrTrigger = true;
    }


    void setHoverColor(short r, short g, short b, short a=255, float time = 7.5)
    {
        hoverClr = sf::Color(r,g,b,a);
        hoverClrTrigger = true;

        if(time<=0)
        {
            rT = Clr.a;
            startRTime = Clr.a;
            startHTime = hoverClr.a;
            hT = hoverClr.a;
        }
        else
            transitionTime = time;
    }


    void writeHoverText(sf::String str)
    {
        text.setString(str);
        hoverTextX = hoverX1 + ( (hoverX2-hoverX1)-text.getLocalBounds().width )/2;
        hoverTextY = hoverY1 + ( (hoverY2-hoverY1)-text.getLocalBounds().height )/2;
        hoverBoxStrTrigger = true;
        hoverBoxStr = str;
    }


    void setHoverTextOffset(float x, float y)
    {
        hoverTextX = hoverTextX + x;
        hoverTextY = hoverTextY + y;
    }


    void setHoverOutline(short r, short g, short b, short a=255, float width=1)
    {
        hoverOutlineClr = sf::Color(r,g,b,a);
        hoverOutlineWidth = width;
        hoverOutlineTrigger = true;
    }



    bool IsClicked(sf::Event& e)
    {
        if( isClickable && ((e.type == sf::Event::MouseButtonPressed && e.mouseButton.button==sf::Mouse::Left && this->isHovered() ) || (e.type == sf::Event::KeyPressed && e.key.code==clickKey)) )
        {
            sound.play();
            realClick = true;
            return true;
        }
        else if( (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button==sf::Mouse::Left && this->isHovered() ) || (e.type == sf::Event::KeyReleased && e.key.code==clickKey) )
        {
                realClick = false;
                return false;
        }
    }


    void setClickKey(sf::Keyboard::Key userKey)
    {
        clickKey = userKey;
    }


    void setClickable(bool val)
    {
        isClickable = val;
    }


    void setClickColor(short r, short g, short b, short a=255)
    {
        clickClr = sf::Color(r,g,b,a);
        clickClrTrigger = true;
    }



    void setClickSound(sf::SoundBuffer &buffer)
    {
        soundBuffer = &buffer;
        sound.setBuffer(buffer);
    }


    void setClickDimensions(float X1, float Y1, float X2, float Y2)
    {
        clickX1 = X1; clickX2 = X2; clickY1 = Y1; clickY2 = Y2;
        clickDeimensionsTrigger = true;
    }


    void Draw()
    {

        if(hoverDimensionsTrigger)
        {
            this->setDimensions(x1,y1,x2,y2);

            if( this->isHovered())
            {
                Box.setSize(sf::Vector2f(hoverX2-hoverX1,hoverY2-hoverY1));
                Box.setPosition(hoverX1,hoverY1);
            }
        }

        if(hoverBoxStrTrigger)
        {
            text.setString(boxStr);
            text.setPosition(textX,textY);

            if(this->isHovered())
            {
                text.setString(hoverBoxStr);
                text.setPosition(hoverTextX,hoverTextY);
            }
        }

        if(hoverTextClrTrigger)
        {
            this->setTextColor(textClr.r,textClr.g,textClr.b,textClr.a);

            if( this->isHovered() )
                text.setFillColor(hoverTextClr);
        }

        if(hoverOutlineTrigger)
        {
            this->setOutline(outlineClr.r,outlineClr.g,outlineClr.b,outlineClr.a,outlineWidth);

            if( this->isHovered() )
            {
                Box.setOutlineColor(hoverOutlineClr);
                Box.setOutlineThickness(hoverOutlineWidth);
            }
        }

        if(hoverClrTrigger)
        {
            if(this->isHovered())
            {
                rT=startRTime;
                Box.setFillColor(sf::Color(hoverClr.r,hoverClr.g,hoverClr.b,hT));
                if(hT<hoverClr.a)
                    hT+=transitionTime;
            }
            else
            {
                hT=startHTime;
                Box.setFillColor(sf::Color(Clr.r,Clr.g,Clr.b,rT));
                if(rT<hoverClr.a)
                    rT+=transitionTime;
            }
        }

        if(clickDeimensionsTrigger)
        {
            if(!hoverDimensionsTrigger)
                this->setDimensions(x1,y1,x2,y2);

            if(realClick)
            {
                Box.setSize(sf::Vector2f(clickX2-clickX1,clickY2-clickY1));
                Box.setPosition(clickX1,clickY1);
            }
        }

        if(clickClrTrigger)
        {
            if(!hoverClrTrigger)
                Box.setFillColor(Clr);
            if(realClick)
                Box.setFillColor(clickClr);
        }

        win->draw(Box);
        win->draw(text);
    }





private:

    sf::RenderWindow* win;
    sf::Font* font;
    sf::SoundBuffer* soundBuffer;
    sf::Sound sound;

    float x1,y1,x2,y2,  hoverX1,hoverY1,hoverX2,hoverY2,    clickX1,clickX2,clickY1,clickY2;
    float textX, textY, hoverTextX,hoverTextY;
    sf::String boxStr, hoverBoxStr;
    sf::Color Clr, hoverClr, clickClr;
    sf::Color textClr, hoverTextClr;
    sf::Color outlineClr, hoverOutlineClr;
    float outlineWidth, hoverOutlineWidth;
    float transitionTime, hT = 30, rT = 30, startRTime=30, startHTime = 30;
    sf::Keyboard::Key clickKey = sf::Keyboard::Unknown;

    bool hoverDimensionsTrigger = false;
    bool hoverClrTrigger = false;
    bool hoverBoxStrTrigger = false;
    bool hoverTextClrTrigger = false;
    bool hoverOutlineTrigger = false;
    bool clickClrTrigger = false;
    bool isClickable = true;
    bool realClick = false;
    bool clickDeimensionsTrigger = false;






protected:

    // To access the shape and text properties by the inherited/Daughter class
    sf::RectangleShape Box; //to access the shape properties

};



class displayRect
{
public:

    displayRect(sf::RenderWindow& userWin, sf::Font &userFont)
    {
        win = &userWin;
        text.setFont(userFont);

        Box.setSize(sf::Vector2f(610,100));
        Box.setPosition(50,20);
        Box.setFillColor(sf::Color(63,63,63));
        Box.setOutlineThickness(1.65);
        Box.setOutlineColor(sf::Color(19,139,168));
    }



    void writeTextAtPos(std::string str,float x, float y)
    {
        boxStr = str;

        if(str.size() > 33)
            str = str.substr(boxStr.size()-33);

        text.setString(toSfString(str));
        text.setPosition(x,y);
    }

    void Draw()
    {
        win->draw(Box);
        win->draw(text);
    }


private:
    sf::RenderWindow* win = nullptr;
    sf::Text text;
    std::string boxStr;

    sf::RectangleShape Box;
};

Button b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, bDot, bPlus, bMinus, bDivide, bMultiply, bPercent, bSq, bCube,bNpow, bFact,bLeftB,bRightB,bReciprocal,bSin,bCos, bTan, bASin, bACos, bATan,
    bSqrt, bCbRt,bLog, bLn, bExp, b10x, bPie,bEquals,bBackspace,bClear; //global objects


std::vector<Button*> buttonArray ={&b0,&b1,&b2,&b3,&b4,&b5,&b6,&b7,&b8,&b9,&bDot,&bPlus,&bMinus,&bDivide,&bMultiply,&bPercent,&bSq, &bCube,&bNpow,&bFact,&bLeftB,&bRightB,&bReciprocal,&bSin,&bCos, &bTan, &bASin, &bACos, &bATan,
    &bSqrt, &bCbRt,&bLog, &bLn, &bExp, &b10x, &bPie,&bEquals,&bBackspace,&bClear};

std::vector<std::string> showValues = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "/", "x", "%", "^2", "^3", "^", "!", "(", ")", "1/(", "sin(", "cos(", "tan(", "asin(", "acos(", "atan(","sqrt(", "cbrt(",
                                        "log(", "ln(", "e^(", "10^(", "pi","=", "", "" };

std::vector<std::string> returnValues = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-", "/", "x", "%", "^2", "^3", "^", "!", "(", ")", "1/(", "s(", "c(", "t(", "S(", "C(", "T(","q(", "w(",
                                        "L(", "l(", "e^(", "10^(", "p","=", "", "" };

short brChecker = 0;


void buttonValidator(std::vector<std::string> _stack)
{
    for(unsigned int i=0; i<buttonArray.size(); ++i) //at every cycle set all keys click able
            buttonArray[i]->setClickable(true);

    //changing equals color
    bEquals.setColor(21,225,60);
    bEquals.setHoverColor(60,255,107);

    std::string lastString;

    if(!_stack.empty())
        lastString = _stack[_stack.size()-1];

    //multiply checking
    if(lastString=="!" || lastString=="^2" || lastString=="^3" || lastString==")" || lastString=="pi" || (Stoi(lastString)>-1 && Stoi(lastString)<10) &&(!_stack.empty()) )
    {
        for(int i=20; i<36; ++i)
        {
            buttonArray[i]->ReturnValue = "x" + returnValues[i];
        }
        buttonArray[21]->ReturnValue = returnValues[21];
    }
    else
    {
        for(int i=20; i<36; ++i)
            {
                buttonArray[i]->ReturnValue = returnValues[i];
            }
        buttonArray[21]->ReturnValue = returnValues[21];
    }

    //-checking
    bMinus.ReturnValue = returnValues[12];
    bMinus.ShowValue = showValues[12];

    if(_stack.empty())
    {
        for(int i=10; i<20; ++i)
            buttonArray[i]->setClickable(false);
        bRightB.setClickable(false);
        bBackspace.setClickable(false);
        bClear.setClickable(false);
        bEquals.setClickable(false);
        bEquals.setColor(245,18,47);
        bEquals.setHoverColor(245,18,47);
        bMinus.setClickable(true);
        bMinus.ReturnValue = "0" + returnValues[12];
        brChecker = 0;
        //bMinus.ShowValue = "0" + showValues[12];
    }
    else if(lastString.at(lastString.size()-1)=='(')
    {
        for(int i=10; i<20; ++i)
            buttonArray[i]->setClickable(false);
        bRightB.setClickable(false);
        bEquals.setClickable(false);
        bEquals.setColor(245,18,47);
        bEquals.setHoverColor(245,18,47);
        bMinus.setClickable(true);
        bMinus.ReturnValue = "0" + returnValues[12];
    }
    else if(lastString==".")
    {
        for(unsigned int i=10; i<buttonArray.size(); ++i)
        {
            buttonArray[i]->setClickable(false);
        }
        bEquals.setColor(245,18,47);
        bEquals.setHoverColor(245,18,47);
        bBackspace.setClickable(true);
        bClear.setClickable(true);
    }
    else if(lastString=="+"||lastString=="-"||lastString=="x"||lastString=="/"||lastString=="%"||lastString=="^")
    {
        for(int i=10; i<22; ++i)
            buttonArray[i]->setClickable(false);
        bLeftB.setClickable(true);
        bEquals.setClickable(false);
        bEquals.setColor(245,18,47);
        bEquals.setHoverColor(245,18,47);
    }
    else if(lastString=="!")
    {
        for(int i=0; i<11; ++i)
            buttonArray[i]->setClickable(false);
        for(int i=16; i<20; ++i)
            buttonArray[i]->setClickable(false);
    }
    else if(lastString==")" || lastString=="pi" || lastString=="xpi")
    {
        for(int i=0; i<11; ++i)
            buttonArray[i]->setClickable(false);
    }

    //validating brackets
    if(brChecker!=0)
    {
        bEquals.setClickable(false);
        bEquals.setColor(245,18,47);
        bEquals.setHoverColor(245,18,47);
    }
}



#endif // STYLING_H_INCLUDED
