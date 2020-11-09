// Jeniffer Vasquez
// HW#2Q2
// The following program is made to calculate prefix operations utilizing stacks data structure.

#include <iostream>
#include <stack>
#include <ctype.h> //for isdigit function
using namespace std;

//FUNCTION to check if char is a digit
bool isDigit(char c){ // checks that the i'th chracter is a digit
    return isdigit(c); // if the char is a digit, will return true
}

//FUNCTION to calculate prefix expression
double calcPrefix(string exp){
    stack<double> s; // initializes stack s
    
    for(int i = exp.size() - 1; i >= 0; i--){  //run the code as long as there is exp left
        
        if( isDigit(exp[i]) == true){ //If the char is a digit, then push the number into the stack
            s.push(exp[i] - '0');    // while converting to int by subtracting from char '0'
        }
        else {
            
            double op1 = s.top(); //get value from top of stack and assign to op1
            s.pop(); // pop top value from stack
            double op2 = s.top (); //get next value from top of stack and assign to op2
            s.pop(); // pop top value from stack
            
            switch(exp[i]) { //Checks the operator on the i'th position and compares to the cases
                case '+':
                    s.push(op1 + op2); //if '+' then add
                    break;
                case '-':
                    s.push(op1 - op2); // if '-' then subtract
                    break;
                case '*':
                    s.push(op1 * op2); // if '*' then multiply
                    break;
                case '/':
                    s.push(op1 / op2); // if '/' then divide
                    break;
                    
            }
            
        }
    }
    return s.top(); // returns final value to calcPrefix
}

int main() {
    
    string exp;
    cout << "Enter a single digit Prefix Expression: " << endl;
    cin >> exp;
    cout << "The expression " << exp << " is equal to " << calcPrefix(exp) << endl;
    
    return 0;
}
