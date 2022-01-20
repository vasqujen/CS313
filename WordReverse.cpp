//  Jeniffer Vasquez
//  HW#2Q6
//  Program designed to read text file (CNjokes) with Chuck Norris jokes and reverse each word and print them.

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

//FUNCTION to reverse words in each joke
void reverseWords( string joke ){
    stack<char> s; //create stack named s
    
    for (int i = 0; i < joke.length(); ++i) {
        if (joke[i] != ' ') // goes through each char in a word until it encounters a space
            s.push(joke[i]); //pushes each char in the stack one by one
        
        else { //does this if encountered a space
            while (s.empty() == false) { //while the stack is not empty
                cout << s.top(); //prints the top char in the stack
                s.pop(); //pops the top char
            }
            cout << " "; //after printing the reversed word, print a space
        }
    }
    
    //This while loop does the same as above, but this takes the last word without a space into consideration
    while (s.empty() == false) {
        cout << s.top();
        s.pop();
    }
    
}

int main() {
    
    ifstream inFile; //allows you to read the file
    string fileName, line; // declare line and fileName
    cout << "Enter file pathname: " << endl; //Enter the pathname to the text file
    cin >> fileName;
    inFile.open(fileName); //opens the text file
    
    for (int i = 0; i < 3 ; i++){ // for loop to run through each line in the text file
        getline(inFile,line); //gets the line in file
        cout << line << endl; // prints the original line
        reverseWords(line); //prints reversed line
        cout << "\n\n";
        
    }
    return 0;
}
