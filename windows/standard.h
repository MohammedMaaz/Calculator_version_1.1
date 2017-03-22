#ifndef STANDARD_H_INCLUDED
#define STANDARD_H_INCLUDED

#include "../headers/styling.h"
#include "../headers/buffer.h"
#include "../headers/evaluate.h"
#include <vector>
#include <iostream> //for debugging
using namespace std;




void screen1()
{
    sf::RenderWindow win(sf::VideoMode(710,400),"Scientific Calculator");
    win.setVerticalSyncEnabled(true);

    displayRect box(win,font); //display screen of the calculators

    std::vector<sf::Keyboard::Key> keys = {sf::Keyboard::Num0,sf::Keyboard::Num1,sf::Keyboard::Num2,sf::Keyboard::Num3,sf::Keyboard::Num4,sf::Keyboard::Num5,sf::Keyboard::Num6,sf::Keyboard::Num7,sf::Keyboard::Num8,sf::Keyboard::Num9,sf::Keyboard::Period,sf::Keyboard::Add,sf::Keyboard::Dash,
                sf::Keyboard::Divide,sf::Keyboard::Multiply,sf::Keyboard::Unknown,sf::Keyboard::Unknown,sf::Keyboard::Unknown,sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown,
                sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown,sf::Keyboard::Return,sf::Keyboard::BackSpace,sf::Keyboard::Escape};
    std::vector<string> stringStack;

    std::vector<string> sendStr;

    sf::Text text;
    text.setFont(font);
    text.setPosition(58.5,40);


    //setting button properties
    for(unsigned int i=0; i<buttonArray.size(); ++i)
    {
        short x1 = 27+0.7*(i%11)+60*(i%11), y1 = 150+60*(i/11);
        buttonArray[i]->setDimensions(x1,y1,x1+50,y1+50);
        buttonArray[i]->syncWithWindow(&win);
        buttonArray[i]->setTextFont(font);
        buttonArray[i]->setColor(7,7,7);
        buttonArray[i]->setOutline(11,129,148,255,1);
        buttonArray[i]->setHoverColor(99,99,99,255);
        buttonArray[i]->setClickColor(29,29,29);
        buttonArray[i]->setClickSound(buffer);
        buttonArray[i]->setClickDimensions(x1+1,y1+1,x1+49,y1+49);
        buttonArray[i]->setTextColor(255,255,255);
        buttonArray[i]->ShowValue = showValues[i];
        buttonArray[i]->ReturnValue = returnValues[i];
        if(i>21 && i<33)
        {
            buttonArray[i]->writeText( toSfString(showValues[i]+")") );
        }
        else if(i==33 || i==34)
        {
            buttonArray[i]->writeText( toSfString(showValues[i].substr(0,showValues[i].size()-1)) );
        }
        else
            buttonArray[i]->writeText( toSfString(showValues[i]) );
        buttonArray[i]->setTextOffset(0,4);
        buttonArray[i]->setClickKey(keys[i]);
        buttonArray[i]->text.setCharacterSize(14u);
    }
    for(int i=22; i<33; ++i)
    {
        if(i==22||i==32)
            buttonArray[i]->setTextOffset(14,0);
        else
            buttonArray[i]->setTextOffset(29,0);
    }
    b10x.setTextOffset(12,1);
    bPie.setTextOffset(12,4);
    bBackspace.writeText("BSP"); //for backspace
    bClear.writeText("C");
    bEquals.writeText("=");
    bEquals.setColor(245,18,47);
    bEquals.setHoverColor(245,18,47);


    //Program Loop
    while(win.isOpen())
    {
        sf::Event event;
        std::string str;

        while(win.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                win.close();

            for(unsigned int i=0; i<buttonArray.size()-3; ++i)
            {
                if(buttonArray[i]->IsClicked(event) )
                {
                    stringStack.push_back(buttonArray[i]->ShowValue);
                    sendStr.push_back(buttonArray[i]->ReturnValue);
                    //for brackets
                    if(i>19&&i<35)
                        brChecker++;
                    if(i==21)
                        brChecker-=2;
                }
            }

            if(bBackspace.IsClicked(event)) //checking for backspace
            {
                //for brackets
                if(sendStr.back().at(sendStr.back().size()-1)=='(')
                    brChecker--;
                else if(sendStr.back().at(sendStr.back().size()-1)==')')
                    brChecker++;
                //actual backspace action
                stringStack.pop_back();
                sendStr.pop_back();
            }
            else if(bClear.IsClicked(event))
            {
                stringStack.clear();
                sendStr.clear();
            }
            else if(bEquals.IsClicked(event))
            {
                string res = "";
                for(int i=0; i<sendStr.size(); ++i)
                    res+=sendStr[i];
                stringStack.clear();
                sendStr.clear();
                res = doubleToStr(evaluateExpression(res));
                if(res[0]=='-')
                    sendStr.push_back("0");
                string buff;
                for(int i=0; i<res.size(); ++i)
                {
                    buff = "";
                    buff+=res[i];
                    stringStack.push_back(buff);
                    sendStr.push_back(buff);
                }
                //bEquals.setClickable(false);
            }

            buttonValidator(stringStack);
            cout << brChecker << endl;
        }


        for(unsigned int i=0; i<stringStack.size(); ++i) //update box string
                str+=stringStack[i];


        box.writeTextAtPos(str,58.5,70); //updating display box's text
        //text.setString(prevStr);


        win.clear(sf::Color(40,40,40));
        for(unsigned int i=0; i<buttonArray.size(); ++i) //drawing buttons
            buttonArray[i]->Draw(); //drawing the buttons
        box.Draw(); //drawing display box
        win.display();
    }
}


#endif // STANDARD_H_INCLUDED
