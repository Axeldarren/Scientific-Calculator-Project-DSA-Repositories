#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

class Calculator {
public:
    Calculator(string);
    string inputEquation;
    queue<string> equationQueue;
    queue<string> tempEquationQueue;
    double  tempResult;
    double finalResult;

    void toStringQueue();
    double calculate();
    void printConversion();
    void trigonometric();
    void logarithmic();
    bool isNumber(string);
    void exponent();
    void multDiv();
    void bracketDetect();
    void squareRoot();
    void symbolCheck();
}; 

// Constructor
Calculator::Calculator(string inputEquation)
{
    this->inputEquation = inputEquation;
    toStringQueue();
}

// Function to check the first element and determine the operation
void Calculator::symbolCheck()
{
    if (equationQueue.front() == "log" || equationQueue.front() == "ln")
    {
        logarithmic();
    }
    else if (equationQueue.front() == "sin" || equationQueue.front() == "cos" || equationQueue.front() == "tan")
    {
        trigonometric();
    }
    else if (equationQueue.front() == "V")
    {
        squareRoot();
    }
}

// Function to check if a string is a valid number
bool Calculator::isNumber(string toCheck)
{
    for (int i = 0; i < toCheck.size(); i++)
    {
        if (!isdigit(toCheck[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to convert the input string to a queue of elements
void Calculator::toStringQueue() {
    
    string tempNum = "", tempSymbol = "", tempBase = "";

    while (!inputEquation.empty()) {
        if (inputEquation.front() == ' ') 
        {
            inputEquation.erase (inputEquation.begin());
        } 
        else if (isdigit(inputEquation.front()) || inputEquation.front() == '-' || inputEquation.front() == '.') 
        {
            tempNum += inputEquation.front();
            inputEquation.erase (inputEquation.begin());
        } 
        else if (inputEquation.front() == '(' || inputEquation.front() == '+' || inputEquation.front() == '^' || inputEquation.front() == 'V' || inputEquation.front() == '*' || inputEquation.front() == '/')
        {
            tempSymbol += inputEquation.front();
            equationQueue.push(tempSymbol);
            inputEquation.erase (inputEquation.begin());
            tempSymbol = "";
        } 
        else if (inputEquation.front() == 's' || inputEquation.front() == 'c' || inputEquation.front() == 't') 
        {
            for (int i = 0; i < 3; i++) 
            {
                tempSymbol += inputEquation.front();
                inputEquation.erase (inputEquation.begin());
            }

            equationQueue.push(tempSymbol);
            tempSymbol = "";
        }
        else if (inputEquation.front() == 'l')
        {
            tempSymbol += inputEquation.front();
            inputEquation.erase (inputEquation.begin());
            if (inputEquation.front() == 'o') 
            {
                tempSymbol += inputEquation.front();
                inputEquation.erase (inputEquation.begin());
                tempSymbol += inputEquation.front();
                inputEquation.erase (inputEquation.begin());
                equationQueue.push(tempSymbol);
                tempSymbol = "";

                if (isdigit(inputEquation.front()))
                {
                    while (!(inputEquation.front() == '('))
                    {
                        tempBase += inputEquation.front();
                        inputEquation.erase (inputEquation.begin());
                    }

                    if (!(tempBase == ""))
                    {
                        equationQueue.push(tempBase);
                        tempBase = "";
                    } else 
                        continue;
                }
                else
                    continue;  
            }  
            else if (inputEquation.front() == 'n')
            {
                tempSymbol += inputEquation.front();
                inputEquation.erase (inputEquation.begin());
                equationQueue.push(tempSymbol);
                tempSymbol = "";
            }

        }

        if (inputEquation.front() == '-' || inputEquation.front() == '+' || inputEquation.front() == '*' || inputEquation.front() == '/' || inputEquation.front() == '^' || inputEquation.front() == 'V' || inputEquation.empty()) 
        {
            if (!(tempNum == ""))
            {
                equationQueue.push(tempNum);
                tempNum = "";
            }
        } 
        else if (inputEquation.front() == ')') 
        {   
            if (!(tempNum == ""))
            {
                equationQueue.push(tempNum);
                tempNum = "";
            }
            
            tempSymbol += inputEquation.front();
            equationQueue.push(tempSymbol);
            inputEquation.erase (inputEquation.begin());
            tempSymbol = "";
        }
    }
}

// Function to handle square root calculations
void Calculator::squareRoot()
{
    queue<string> tempEquation;

    while (!equationQueue.empty())
    {
        string tempResult = "";

        if (equationQueue.front() == "V")
        {
            equationQueue.pop(); //delete symbol from queue
            if (equationQueue.front() == "(")
            {
                bracketDetect();
                tempResult += to_string(sqrt(stod(equationQueue.front())));
                equationQueue.pop();
                tempEquation.push(tempResult);
            }
            else
            {
                tempResult += to_string(sqrt(stod(equationQueue.front())));
                equationQueue.pop();
                tempEquation.push(tempResult);
            }
            
        }
        else 
        {
            tempEquation.push(equationQueue.front());
            equationQueue.pop();
        }   
    }

    while (!tempEquation.empty()) 
    {
        equationQueue.push(tempEquation.front());
        tempEquation.pop();
    }

}

// Function to handle exponentiation and multiplication/division calculations
void Calculator::exponent()
{
    queue<string> tempEquation, tempNum;
    string Num1;
    
    while (!equationQueue.empty())
    {   
        if (equationQueue.front() == "^")
        {
            equationQueue.pop();
            double tempResult;
            
            if (equationQueue.front() == "(") bracketDetect();
            else symbolCheck();

            tempResult = pow(stod(tempNum.front()), stod(equationQueue.front()));

            tempEquation.push(to_string(tempResult));
            tempNum.pop();
            equationQueue.pop();
        }
        else if (equationQueue.front() == "*")
        {
            equationQueue.pop();
            double tempResult;
            
            if (equationQueue.front() == "(") bracketDetect();
            else symbolCheck();

            tempResult = stod(tempNum.front()) * stod(equationQueue.front());

            tempEquation.push(to_string(tempResult));
            tempNum.pop();
            equationQueue.pop();
        }
        else if (equationQueue.front() == "/")
        {
            equationQueue.pop();
            double tempResult;
            
            if (equationQueue.front() == "(") bracketDetect();
            else symbolCheck();

            tempResult = stod(tempNum.front()) / stod(equationQueue.front());

            tempEquation.push(to_string(tempResult));
            tempNum.pop();
            equationQueue.pop();
        }
        else
        {   
            if (equationQueue.front() == "(")
            {
                bracketDetect();
            }
            else symbolCheck();

            if (!tempNum.empty())
            {
                tempEquation.push(tempNum.front());
                tempNum.pop();
            }
            tempNum.push(equationQueue.front());
            equationQueue.pop();
        }
    }   

    while (!tempNum.empty())
    {
        tempEquation.push(tempNum.front());
        tempNum.pop();
    }
    

    while (!tempEquation.empty())
    {
        equationQueue.push(tempEquation.front());
        tempEquation.pop();
    }
}

// Function to handle logarithmic calculations
void Calculator::logarithmic()
{
    queue<string> tempEquation;

    while (!equationQueue.empty())
    {
        string tempNum = ""; 
        double num;
        
        if (equationQueue.front() == "log" || equationQueue.front() == "ln") 
        {
            string base = "";
            
            if (equationQueue.front() == "log") 
            {
                equationQueue.pop();
                if (equationQueue.front() == "(")
                {
                    bracketDetect();
                    tempNum = to_string(log10(stod(equationQueue.front())));
                    tempEquation.push(tempNum);
                }
                else if (isNumber(equationQueue.front()))
                {
                    base += equationQueue.front();
                    equationQueue.pop(); // pop base
                    bracketDetect();
                    tempNum = to_string(log(stod(equationQueue.front())) / log(stod(base)));
                    tempEquation.push(tempNum);
                }
            }
            else if (equationQueue.front() == "ln")
            {
                equationQueue.pop();
                tempNum = to_string(log(stod(equationQueue.front())));
                tempEquation.push(tempNum);
            }

            equationQueue.pop();
        }
        else
        {
            tempEquation.push(equationQueue.front());
            equationQueue.pop();
        }
    }

    while (!tempEquation.empty()) 
    {
        equationQueue.push(tempEquation.front());
        tempEquation.pop();
    }
}

// Function to handle trigonometric calculations
void Calculator::trigonometric() 
{
    queue<string> tempEquation, tempEquation0;

    while (!equationQueue.empty())
    {
        string tempNum = ""; 
        double num;
        
        if (equationQueue.front() == "sin") 
        {
            equationQueue.pop();
            if (equationQueue.front() == "(")
            {
                bracketDetect();
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(sin(num));
                tempEquation.push(tempNum);
            }
            else
            {
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(sin(num));
                tempEquation.push(tempNum);
            }
            
        }
        else if (equationQueue.front() == "cos")
        {
            equationQueue.pop();
            if (equationQueue.front() == "(")
            {
                bracketDetect();
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(cos(num));
                tempEquation.push(tempNum);
            }
            else
            {
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(cos(num));
                tempEquation.push(tempNum);
            }
        }
        else if (equationQueue.front() == "tan")
        {
            equationQueue.pop();
            if (equationQueue.front() == "(")
            {
                bracketDetect();
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(tan(num));
                tempEquation.push(tempNum);
            }
            else
            {
                num = stod(equationQueue.front())*3.14159/180;
                tempNum = to_string(tan(num));
                tempEquation.push(tempNum);
            }
        }
        else 
        {
            tempEquation.push(equationQueue.front());
        }

        equationQueue.pop();
    }

    while (!tempEquation.empty()) 
    {
        equationQueue.push(tempEquation.front());
        tempEquation.pop();
    }
}

// Function to detect and calculate expressions enclosed in parentheses
void Calculator::bracketDetect()
{
    queue<string> tempEquation;

    equationQueue.pop();

    string tempQueue = "";
    int openBracket = 1;
    int realCloseBracket = 0;
    int expectedCloseBracket = 1;

    while (expectedCloseBracket != 0)
    {
        if (equationQueue.front() == "(")
        {
            openBracket++;
            expectedCloseBracket++;
            tempQueue += equationQueue.front();
            equationQueue.pop();
        }
        else if (equationQueue.front() == ")" && expectedCloseBracket != 1)
        {
            expectedCloseBracket--;
            realCloseBracket++;
            tempQueue += equationQueue.front();
            equationQueue.pop();
        }
        else if (equationQueue.front() == ")" && expectedCloseBracket == 1)
        {
            realCloseBracket++;
            if (openBracket == realCloseBracket)
            {
                equationQueue.pop();
                Calculator bracketCalculator(tempQueue);
                tempEquation.push(to_string(bracketCalculator.calculate()));
                expectedCloseBracket--;
            }
            else
            {
                throw invalid_argument ("Too many bracket.");
            }
        } 
        else
        {
            tempQueue += equationQueue.front();
            equationQueue.pop();
        }
    }

    while (!equationQueue.empty())
    {
        tempEquation.push(equationQueue.front());
        equationQueue.pop();
    }

    while (!tempEquation.empty())
    {
        equationQueue.push(tempEquation.front());
        tempEquation.pop();
    }
}

// Function to perform the calculation
double Calculator::calculate()
{	

    while (!equationQueue.empty())
    {
        if (equationQueue.front() == "(")
        {
            bracketDetect();
        }
        else 
        {
            if (equationQueue.front() == "+") 
            {
                equationQueue.pop();
            }
            else
            {
                symbolCheck();
                exponent();
                finalResult += stod(equationQueue.front());
                equationQueue.pop();
            }
            
        }
    }

    return finalResult;
}

#endif