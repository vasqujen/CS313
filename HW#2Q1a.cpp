//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator
// This program evaluates postfix expressions.
//***********************************************************
//Jeniffer Vasquez Question 1, commenting code

#include <iostream>
#include <iomanip>
#include <fstream>
#include "mystack.h"

using namespace std;

void evaluateExpression(ifstream& inpF, ofstream& outF,
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100); //declare stack of sz 100
    ifstream infile; //allows to read file
    ofstream outfile; //allows to write in file
    
    infile.open("RpnData.txt"); //opens RpnData text file
    
    if (!infile) //if file is unable to open to read, then print error message
    {
        cout << "Cannot open the input file. "
        << "Program terminates!" << endl;
        return 1;
    }
    
    outfile.open("RpnOutput.txt");
    
    outfile << fixed << showpoint; //force the output to show the decimal point and trailing zeros
    outfile << setprecision(2); //sets amount of decimal places
    
    infile >> ch;
    while (infile)
    {
        stack.initializeStack(); //initializes stack
        expressionOk = true;
        outfile << ch;
        
        evaluateExpression(infile, outfile, stack, ch,
                           expressionOk); //calls function to evaluate expression
        printResult(outfile, stack, expressionOk); //prints function
        infile >> ch; //begin processing the next expression
    } //end while
    
    infile.close(); //close
    outfile.close(); //close
    
    return 0;
    
} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    
    while (ch != '=') //while char is not '='
    {
        switch (ch) //begins cases with ch
        {
            case '#':
                inpF >> num; //read num
                outF << num << " "; //write num
                if (!stack.isFullStack()) // if the stack is not full, then push num into stack
                    stack.push(num);
                else //if stack is full, print message 0
                {
                    cout << "Stack overflow. "
                    << "Program terminates!" << endl;
                    exit(0);  //terminate the program
                }
                
                break;
            default:
                evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch
        
        if (isExpOk) //if no error
        {
            inpF >> ch;
            outF << ch;
            
            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk)
{
    double op1, op2;
    
    if (stack.isEmptyStack()) // if stack is empty
    {
        out << " (Not enough operands)"; //prints message
        isExpOk = false; //sets isExpOk to false
    }
    else //if stack is not empty
    {
        op2 = stack.top(); //sets op2 to be the top of stack
        stack.pop();// pops off stack
        
        if (stack.isEmptyStack()) //if the stack is empty, print  message
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
            op1 = stack.top(); //sets op1 to the top of stack
            stack.pop(); //pops the top
            
            switch (ch)//begins cases dealing with chars
            {
                case '+':
                    stack.push(op1 + op2); //if '+' then add
                    break;
                case '-':
                    stack.push(op1 - op2);//if '-' then subtract
                    break;
                case '*':
                    stack.push(op1 * op2);//if '*' then multiply
                    break;
                case '/': // if '/' then divide
                    if (op2 != 0) // checks that you dont divide by 0
                        stack.push(op1 / op2);//divides
                    else
                    {
                        out << " (Division by 0)"; //print error message if divide by zero
                        isExpOk = false;
                    }
                    break;
                default:
                    out << " (Illegal operator)";
                    isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result; //declare result as double
    
    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack()) // if stack is not empty
        {
            result = stack.top();// sets the top of stack to result
            stack.pop(); // pops the stack
            
            if (stack.isEmptyStack()) //if stack is empty
                outF << result << endl; // write result
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl; //if stack is empty
    }
    else
        outF << " (Error in the expression)" << endl; //if isExpOk is false
    
    outF << "_________________________________"
    << endl << endl;
} //end printResult
