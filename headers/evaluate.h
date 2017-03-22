#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

long double strToDouble( const std::string& s )
 {
   std::istringstream i(s);
   long double x;
    i >> x;
   return x;
 }

 string doubleToStr(long double d)
 {
    std::ostringstream s;
    s << setprecision(19) << d;
   return s.str();
 }

 long double factorial(int op)
 {
     long double res=1;
     for(int i=op; i>0; --i)
        res = res*i;
     return res;
 }

long double evaluateExpression(string str);

void convertToElems(std::string str, std::vector<std::string>& store)
{
    std::string buffer;
    for(int i=0; i<str.size(); ++i)
    {
        char ch = str[i];
        while( ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'||ch=='.' )
        {
            buffer += ch;
            ++i;
            ch = str[i];
        }
        if(!buffer.empty())
        {
            store.push_back(buffer);
            buffer = "";
        }
        if(ch=='(')
            store.push_back("(");
        else if(ch==')')
            store.push_back(")");
        else if(ch=='e')
            store.push_back("2.718281828459");
        else if(ch=='p')
            store.push_back("3.14159265358979");
        else
        {
            std::string chStr;
            chStr += ch;
            store.push_back(chStr);
        }
    }
}

void display(vector<string>& store)
{
    cout << endl << "Store:" << endl;
    for(int i=0; i<store.size(); ++i)
        cout << store[i] << endl;
}


void evaluateBrackets(vector<string>& st)
{
    string s; short point; bool flag = false, flagR = false;
    for(int i=0; i<st.size(); ++i)
    {
        if(st[i]=="(")
        {
            flag = true; flagR = true;
            point = i;
            s="";
        }
        else if(st[i]==")"&&flagR)
        {
            flagR = false;
            st[point] = doubleToStr( evaluateExpression(s) );
            for(int j=point+1; i+j-point<st.size(); ++j)
            {
                st[j] = st[i+j-point];
            }
            for(int j=0; j<(i-point); ++j)
            {
                st.pop_back();
            }
            i = point + 1;
            //return;
            for(int j=0; j<st.size(); ++j)
            {
                if(st[j]=="("||st[j]==")")
                    evaluateBrackets(st);
            }
            flag = false;
            s="";
        }

        if(flag&&st[i+1]!=")")
            s+=st[i+1];
    }
}


void evaluateFunctions(std::vector<std::string>& store)
{
    double f = 3.141592653589793238/180.0;
    for(int i=0; i<store.size(); ++i)
    {
        if(store[i]=="s")
        {
            store[i] = doubleToStr( sin(strToDouble(store[i+1])*f) );
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="c")
        {
            store[i] = doubleToStr( cos(strToDouble(store[i+1])*f) );
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="t")
        {
            store[i] = doubleToStr( tan(strToDouble(store[i+1])*f) );
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="S")
        {
            store[i] = doubleToStr( asin(strToDouble(store[i+1]))/f );
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="C")
        {
            store[i] = doubleToStr( acos(strToDouble(store[i+1]))/f);
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="T")
        {
            store[i] = doubleToStr( atan(strToDouble(store[i+1]))/f);
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="l")
        {
            store[i] = doubleToStr( log(strToDouble(store[i+1])));
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="L")
        {
            store[i] = doubleToStr( log10(strToDouble(store[i+1])));
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="q")
        {
            store[i] = doubleToStr( sqrt(strToDouble(store[i+1])));
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
        else if(store[i]=="w")
        {
            store[i] = doubleToStr( pow(strToDouble(store[i+1]),1.0/3.0));
            for(int j=i+1; j<store.size()-1; ++j)
                    store[j] = store[j+1];
            store.pop_back();
        }
    }
}

void evaluatePowers(std::vector<std::string>& store)
{
    for(int i=0; i<store.size(); ++i)
    {
        if(store[i]=="^")
        {
            store[i-1] = doubleToStr( pow(strToDouble(store[i-1]),strToDouble(store[i+1])) );
            for(int j=i; j<store.size()-2; ++j)
            {
                store[j] = store[j+2];
            }
            store.pop_back();
            store.pop_back();
            --i;
        }
    }
}

void evaluateFactorial(std::vector<std::string>& store)
{
    for(int i=0; i<store.size(); ++i)
    {
        if(store[i]=="!")
        {
            store[i-1] = doubleToStr( factorial( strToDouble(store[i-1]) ) );
            for(int j=i; j<store.size()-1; ++j)
            {
                store[j] = store[j+1];
            }
            store.pop_back();
            --i;
        }
    }
}

void evaluateMultipliers(std::vector<std::string>& store)
{
    for(int i=0; i<store.size(); ++i)
    {
            if(store[i]=="%")
            {
                store[i-1] = doubleToStr( (strToDouble(store[i-1])/100.0) * strToDouble(store[i+1]) );
                for(int j=i; j<store.size()-2; ++j)
                {
                    store[j] = store[j+2];
                }
                store.pop_back();
                store.pop_back();
                --i;
            }
            else if(store[i]=="/")
            {
                store[i-1] = doubleToStr( strToDouble(store[i-1]) / strToDouble(store[i+1]) );
                for(int j=i; j<store.size()-2; ++j)
                {
                    store[j] = store[j+2];
                }
                store.pop_back();
                store.pop_back();
                --i;
            }
            else if(store[i]=="x")
            {
                store[i-1] = doubleToStr( strToDouble(store[i-1]) * strToDouble(store[i+1]) );
                for(int j=i; j<store.size()-2; ++j)
                {
                    store[j] = store[j+2];
                }
                store.pop_back();
                store.pop_back();
                --i;
            }
    }
}

void evaluateAdditions(std::vector<std::string>& store)
{
    for(int i=0; i<store.size(); ++i)
    {
            if(store[i]=="+")
            {
                store[i-1] = doubleToStr( strToDouble(store[i-1]) + strToDouble(store[i+1]) );
                for(int j=i; j<store.size()-2; ++j)
                {
                    store[j] = store[j+2];
                }
                store.pop_back();
                store.pop_back();
                --i;
            }
            else if(store[i]=="-")
            {
                store[i-1] = doubleToStr( strToDouble(store[i-1]) - strToDouble(store[i+1]) );
                for(int j=i; j<store.size()-2; ++j)
                {
                    store[j] = store[j+2];
                }
                store.pop_back();
                store.pop_back();
                --i;
            }
    }
}

long double evaluateExpression(string str)
{
    vector<string> store;
    convertToElems(str,store);
    evaluateBrackets(store);
    evaluateFunctions(store);
    evaluateFactorial(store);
    evaluatePowers(store);
    evaluateMultipliers(store);
    evaluateAdditions(store);
    return strToDouble(store[0]);
}



#endif // EVALUATE_H_INCLUDED
