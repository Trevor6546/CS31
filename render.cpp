#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cctype>
#include <sstream>
#include <streambuf>
#include <cstring>
#include <cassert>
using namespace std;

void dashCheck(char* word, char finalFinalWords[][181], int &count);
//a function created to handle words that are longer than the lineLength variable
bool tooBig(char words[181][181], char finalFinalWords[][181], int lineLength, int &cnt){
    int i = 0;
    bool problem = false;
    int num = 0;
    //iterates through each word
    while(words[i][0] != '\0'){
        int j = 0;
        int m = 0;
        int len = strlen(words[i]);
        //if the length of the word is longer than the lineLength variable
        if(len > lineLength){
            problem = true;
            char ch[251] = {0};
            int x = 0;
            //iterates through the word character-by-character
            while(x <= len){
                //creates a new word from the characters of the original
                ch[j] = words[i][m];
                //if the new word exceeds the lineLength, it will add the new word to finalWords and erase the memory space of it.
                if(j >= (lineLength-1)){
                    ch[j+1] = '\0';
                    strcpy(finalFinalWords[num], ch);
                    memset(ch, 0, strlen(ch));
                    num++;
                    j = 0;
                    cnt++;
                }
                else{
                    j++;
                }
                x++;
                m++;
            }
            //adds a new string from the remaining characters
            if(len % lineLength != 0){
                if(strlen(ch) != 0){
                    ch[j+1] = '\0';
                    strcpy(finalFinalWords[num], ch);
                    memset(ch, 0, strlen(ch));
                    num++;
                    cnt++;
                }
            }
        }
        //if the word does not exceed the character limit
        else{
            strcpy(finalFinalWords[num], words[i]);
            num++;
            cnt++;
        }
        i++;
    }
    return problem;
}

//function that takes the inputLine and creates individual words out of it
int wordMaker(char* inputLine, char words[181][181]){
    int i=0;
    int count=0;
    bool firstChar = true;
    int j = 0;
    while(inputLine[i] != '\0'){
        //if there is not a space, the word is added to the 'count'th word
        if(!isspace(inputLine[i])){
            firstChar = false;
            words[count][j] = inputLine[i]; 
            i++;
            j++;
        }
        else if(isspace(inputLine[i]) && firstChar){
            i++;
            continue;
        }
        //a new space in the words array is accessed for the next word in the string.
        else if(inputLine[i+1] != '\0' && isspace(inputLine[i+1]) && !firstChar){
            firstChar = false;
            i++;
            j = 0;
        }
        else{
            firstChar = false;
            count++;
            i++;
            j = 0;
        }
    }
    //the total number of words is returned.
    return count+1;
}
void wordMakerII(char finalWords[181][181], char finalFinalWords[][181], int c){
    int count = 0;
    //each word is individually checked for '-'
    for(int i=0; i<=c;i++){
        dashCheck(finalWords[i], finalFinalWords, count);
    }
}
void dashCheck(char finalWords[181], char finalFinalWords[][181], int &count){
    int len = strlen(finalWords);
    int numDash = 0;
    int dashes = 0;
    int dashPos[181] = {0};
    bool endDash = false;
    bool hasDash = false;
    //goes through the word and finds the number of dashes and their respective locations
    for(int i=0; i<len;i++){
        if(finalWords[i] == '-'){
            hasDash = true;
            dashPos[numDash] = i;
            numDash++;
            if(i == len-1){
                endDash = true;
            }
        }
    }
    int pos = 0;
    //returns the same string if there are no dashes present
    if(numDash == 0){
        strcpy(finalFinalWords[count], finalWords);
        count++;
    }
    //condition if the first character is a dash
    if(finalWords[0] == '-'){
        char str1[2] = {'-'};
        strcpy(finalFinalWords[count], str1);
        pos++;
        count++;
        dashes++;
        numDash--;
    }
    //condition for a >0 number of dashes
    while(numDash != 0){
        char str2[181] = {0};
        int cnt = 0;
        //goes from the start pos to the location of the next dash and creates a string from the characters between.
        for(int i=pos; i<=dashPos[dashes]; i++){
            str2[cnt] = finalWords[i];
            cnt++;
        }
        //copies the newly created string to the finalFinalWords array and erases the string's contents so it can be used again.
        strcpy(finalFinalWords[count], str2);
        memset(str2, 0, strlen(str2));
        pos = dashPos[dashes]+1;
        dashes++;
        count++;
        numDash--;
    }
    //accounts for a word that has a dash but it isn't at the end
    if(!endDash && hasDash){
        char str4[181] = {0};
        int cnt2 = 0;
        for(int i=pos; i<len;i++){
            str4[cnt2] = finalWords[i];
            cnt2++;
        }
        strcpy(finalFinalWords[count], str4);
        memset(str4, 0, strlen(str4));
        count++;
    }
}
//function that returns true or false depending on if a new paragraph command is present.
bool checkParagraph(char* word){
    bool isParagraph = false;
    if(word[0] == '@' && word[1] == 'P' && word[2] == '@' && strlen(word)==3){
        isParagraph = true;
    }
    return isParagraph;
}
int render(int lineLength, istream& inf, ostream& outf){
    //returns 2 if the lineLength is too small or too large
    if(lineLength < 0 || lineLength > 250){
        return 2;
    }
    //defines variables and arrays used in the function
    char c[181] = {0};
    char full[10000] = {0};
    char words[181][181] = {0};
    char finalWords[181][181] = {0};
    char finalFinalWords[181][181] = {0};
    bool roundOne = true;
    //takes lines from the array and adds them to a larger string
    while(inf.getline(c, 251)){
        char letter[2] = {' ', '\0'};
        //accounts for blank lines
        if(strlen(c) != 0){
            //two different lines would have no space between them, this if statement creates that space
            if(!roundOne){
                strcat(full,letter);
            }
            strcat(full, c);
            roundOne = false;
        }
    }
    //calls functions that turn raw string of text into proper words
    int nums = wordMaker(full, words);
    int temp = nums;
    wordMakerII(words, finalWords, nums);
    bool issue = tooBig(finalWords, finalFinalWords, lineLength, nums);
    //defines even more variables
    int currentLen = 0;
    int num = 0;
    bool notB2B = true;
    bool noSpace = false;
    bool lastWord = false;
    bool specialCase = false;
    bool lastDash = false;
    //iterates through each word
    nums -= (temp+1);
    if(lineLength == 1){
        for(int i=0; i<nums;i++){
            if(nums == i-1){
                outf<<finalFinalWords[i];
            }
            else{
                outf<<finalFinalWords[i]<<'\n';
            }
        }
    }
    while(finalFinalWords[num][0] != '\0' && lineLength != 1){
        //even more variables
        int len = strlen(finalFinalWords[num]);
        bool weird = false;
        char end = finalFinalWords[num][len-1];
        int nextLen = strlen(finalFinalWords[num+1]);
        bool finalWord = false;
        bool isParagraph = checkParagraph(finalFinalWords[num]);
        bool nextParagraph = false;
        bool isFirst = false;
        if(num == 0){
            isFirst = true;
        }
        //statement to see if the next word is a paragraph command
        if(finalFinalWords[num+1][0] != '\0'){
            nextParagraph = checkParagraph(finalFinalWords[num+1]);
        }
        //checks if the word being analyzed is the final word
        if(finalFinalWords[num+1][0] == '\0'){
            finalWord = true;
        }
        //checks if the word being analyzed is the last word in a line
        if(currentLen + len  > lineLength){
            lastWord = true;
        }
        else{
            lastWord = false;
        }
        //adds a space between words that aren't at the start, the end, or a paragraph command
        if(currentLen != 0 && !lastWord && !noSpace && !isParagraph && !lastDash){ //!noSpace taken out
            if(currentLen + len != lineLength){
                outf<<" ";
            }
            currentLen++;
        }
        //checks for conditions that would result in a double space
        if((end == '.' || end == '?' || end == ':' || end == '!') && notB2B){
            weird = true;
            len++;
        }
        //for strange case in which the last word of a line is a character that would warrant a double space 
        
        if((currentLen + len + nextLen > lineLength) && weird){
            specialCase = true;
        }
        else{
            specialCase = false;
        }
        
        //checks if the new word fits on the line
        if(currentLen + len <= lineLength){
            //checks if the word is a new paragraph command
            if(isParagraph && (!notB2B || isFirst || (finalWord && !lastDash))){
                num++;
            }
            else if(isParagraph && notB2B && !lastDash){ //handle if back-to-back @P@s
                //creates new paragraph and moves to next word
                if(currentLen != 0){
                    outf<<'\n';
                }
                outf<<'\n';
                currentLen = 0;
                num++;
                notB2B = false;
            }
            //checks if the word requires a double space after it
            else if(weird && notB2B && !finalWord){
                //creates additional space and moves to next word
                if(nextParagraph || lastWord || specialCase){
                    outf<<finalFinalWords[num];
                    num++;
                    notB2B = true;
                    currentLen += len;
                }
                else{
                    outf<<finalFinalWords[num]<<" ";
                    num++;
                    currentLen += len;
                    notB2B = true;
                }
            }
            //if nothing wacky is there the word is printed
            else{
                outf<<finalFinalWords[num];
                num++;
                currentLen += len;
                notB2B = true;
            }
            lastDash = false;
        }
        //if the line would be too long, a new line is formed and the currentLen variable is reset to 0
        else{
            if(!finalWord || !isParagraph){
                outf<<'\n';
            }
            lastDash = false;
            currentLen = 0;
        }
        if(end == '-'){
            lastDash = true;
        }
    }
    outf<<'\n';
    //if a word exceeded the line limit
    if(issue){
        return 1;
    }
   return 0;
}

int main()
{   
    const int MAX_FILENAME_LENGTH = 100;

    for (;;)
    {
        cout << "Enter input file name (or q to quit): ";
        char filename[MAX_FILENAME_LENGTH];
        cin.getline(filename, MAX_FILENAME_LENGTH);
        if (strcmp(filename, "q") == 0)
            break;
        ifstream infile(filename);
        ofstream outf("output.txt");
        if (!infile)
        {
            cerr << "Cannot open " << filename << "!" << endl;
            continue;
        }
        cout << "Enter maximum line length: ";
        int len;
        cin >> len;
        cin.ignore(10000, '\n');
        int returnCode = render(len, infile, outf);
        cout << "Return code is " << returnCode << endl;
    }
}
