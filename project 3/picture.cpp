#include "grid.h"
#include<bits/stdc++.h>
using namespace std;
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if(dir != 0 && dir != 1){
        return false;
    }
    if(dir == 1 && (((r+distance) < 0) || ((r+distance) > getRows()))){
        return false;
    }  
    if(dir == 1 && (((c+distance) < 0) || ((c+distance) > getRows()))){
        return false;
    }  
    if (fgbg != 0 && fgbg != 1){
        return false;
    }
    //If it is a horizontal line in the foreground
    if(dir == 0 && fgbg == 0){
        for(int i=0; i<=abs(distance);i++){
            //Plots left if distance is negative
            if(distance < 0){
                setChar(r, (c-i), plotChar);
            }
            //Plots right if distance is positive
            else{
                setChar(r, (i+c), plotChar);
            }
        }
    }
    //If it is a horizontal line in the background
    else if(dir == 0 && fgbg == 1){
        //Fix for a bug where if c/r was equal to 1, and a background function was applied, i+c would somehow become 0, crashing the program.
        //the array is used to consistenly give valid values for the "c"/"r" if the opposite value is 1.
        int arr[31] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 31};
        bool isone = false;
        if(c == 1){
            isone = true;
        }
        for(int i=0; i<=abs(distance);i++){
            if(isone){
                if(getChar(r, arr[i]) == ' ' && distance > 0){
                    setChar(r, arr[i], plotChar);
                }               
            }
            //Checks if the array element is empty
            else{
                if(getChar(r, (c-i)) == ' ' && distance < 0){
                    setChar(r, (c-i), plotChar);
                }
                else if(getChar(r, (i+c)) == ' ' && distance > 0){
                    setChar(r, (i+c), plotChar);
                }
            }
        }
    }
    //If it is a vertical line in the background
    else if(dir == 1 && fgbg == 1){
        int arr[31] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 31};
        bool isone = false;
        if(r == 1){
            isone = true;
        }
        for(int i=0; i<=abs(distance);i++){
            if(isone){
                if(getChar(arr[i], c) == ' ' && distance > 0){
                    setChar(arr[i], c, plotChar);
                }               
            }
            else{
                if(getChar((r-i), c) == ' ' && distance < 0){
                    setChar((r-i), c, plotChar);
                }
                else if(getChar((i+r), c) == ' ' && distance > 0){
                    setChar((i+r), c, plotChar);
                }
            }
        }
    }
    //If it is a vertical line in the foreground
    else{
        for(int i=0; i<=abs(distance);i++){
            if(distance < 0){
                setChar((r-i), c, plotChar);
            }
            else{
                setChar((i+r), c, plotChar);
            }
        }
    }
    //If no errors are encountered
    return true;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    //Declares variables
    int r = 1;
    int c = 1;
    int dir;
    int distance = 0;
    int change = 0;
     //checks for invalid inputs for dir, fgbg, and plotChar
    if(mode != 0 && mode != 1){
        return 2;
    }
    if(!isprint(plotChar)){
        return 2;
    }
 
    //For each character in the command string
    for(int i=0; i<commandString.size();i++){
        //Checks if the character (uppercase or lowercase) is 'h'
        if(tolower(commandString[i]) == 'h'){
            //Sets direction to 0 (horizontal)
            dir = 0;
            //checks if the distance will be negative
            if(commandString[i+1] == '-'){
                //determines how many digits follow the '-'
                if(isdigit(commandString[i+2]) && isdigit(commandString[i+3])){
                    //converts substring to integer
                    distance = stoi(commandString.substr(i+2, i+4));
                    //makes sure that certain characters in the string aren't analyzed multiple times
                    change = 3;
                    i += 3;
                }
                else if(isdigit(commandString[i+2])){
                    distance = stoi(commandString.substr(i+2,i+3));
                    i += 2;
                    change = 2;
                }
                else{
                    //throws an error
                    badPos = i+2;
                    return 1;
                }
                //accounts for '-'
                distance *= -1;
            }
            //if the distance is not negative
            else{
                if(isdigit(commandString[i+1]) && isdigit(commandString[i+2])){
                    distance = stoi(commandString.substr(i+1,i+3));
                    i += 2;
                    change = 2;
                }
                else if(isdigit(commandString[i+1])){
                    distance = stoi(commandString.substr(i+1,i+2));
                    change = 1;
                    i++;
                }
                else{
                    badPos = i+1;
                    return 1;
                }
            }
            if(dir == 0 && (((c+distance) < 0) || ((c+distance) > getCols()))){
                badPos = i-change;
                return 3;
            }
            //plots line with new distance and direction
            plotLine(r, c, distance, dir, plotChar, mode);
            //updates r after line is plotted
            c += distance;
        }
        //same as for 'h', but for 'v'
        else if(tolower(commandString[i]) == 'v'){
            dir = 1;
            if(commandString[i+1] == '-'){
                if(isdigit(commandString[i+2]) && isdigit(commandString[i+3])){
                    distance = stoi(commandString.substr(i+2, i+4));
                    i += 3;
                    change = 3;
                }
                else if(isdigit(commandString[i+2])){
                    distance = stoi(commandString.substr(i+2,i+3));
                    i += 2;
                    change = 2;
                }
                else{
                    badPos = i+2;
                    return 1;
                }
                distance *= -1;
            }
            else{
                if(isdigit(commandString[i+1]) && isdigit(commandString[i+2])){
                    distance = stoi(commandString.substr(i+1,i+3)); 
                    i += 2;
                    change = 2;
                }
                else if(isdigit(commandString[i+1])){
                    distance = stoi(commandString.substr(i+1,i+2));
                    i++;
                    change = 1;
                }
                else{
                    badPos = i+1;
                    return 1;
                }
            }
            if(dir == 1 && (((r+distance) < 0) || ((r+distance) > getRows()))){
                badPos = i-change;
                return 3;
            }  
            plotLine(r, c, distance, dir, plotChar, mode);
            r += distance;
        }
        else if(tolower(commandString[i]) == 'f'){
            //checks if a digit is given after 'f' and throws an error if so
            if(isdigit(commandString[i+1])){
                badPos = i+1;
                return 1;
            }
            //changes plotChar
            plotChar = commandString[i+1];
            //mode becomes the foreground setting.
            mode = 0;
            //increments i to prevent reanalysis
            i++;
        }
        //same as 'f' but for 'b'
        else if(tolower(commandString[i]) == 'b'){
            if(isdigit(commandString[i+1])){
                badPos = i+1;
                return 1;
            }
            plotChar = commandString[i+1];
            mode = 1;
            i++;
        }
        else if(tolower(commandString[i]) == 'c'){
            //resets all the variables and clears the grid
            clearGrid();
            r = 1;
            c = 1;
            mode = 0;
            dir = 0;
            plotChar = '*';
        }
        //if an invalid character is given, an error is thrown
        else{
            badPos = i;
            return 1;
        }
    }
    return 0;
}
int main()
{
    for (;;)
    {
        cout << "Enter the number of grid rows and columns (max 30 each): ";
        int nRows;
        int nCols;
        cin >> nRows >> nCols;
        cin.ignore(10000, '\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string (empty line to quit): ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
            cout << "Syntax error at position " << position << endl;
            break;
          case 2:
            if (!isprint(currentChar))
                cout << "Current character is not printable" << endl;
            if (currentMode != FG  &&  currentMode != BG)
                cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
            break;
          case 3:
            cout << "Cannot perform command at position " << position << endl;
            break;
          default:
              // It should be impossible to get here.
            cout << "performCommands returned " << status << "!" << endl;
        }
    }
}
