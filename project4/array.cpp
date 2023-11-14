#include <iostream>
#include <assert.h>
using namespace std;
int reduplicate(string a[], int n){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    //concatenates each element to itself
    for(int i=0; i<n;i++){
        a[i] += a[i];
    }
    //returns length
    return n;
}
int locate(const string a[], int n, string target){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    for(int i=0; i<n;i++){
        //checks if the element is the target
        if(a[i] == target){
            //returns the index of the target
            return i;
        }
    }
    //if it isn't found -1 is returned
    return -1;
}
int locationOfMax(const string a[], int n){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    if(n == 0){
        return 0;
    }
    //defines index as -1 and a max as the first element
    int index = 0;
    string max = a[0];
    for(int i=0; i<n-1;i++){
        //checks if array is lexigrpahically greater than the "max" value
        if(a[i+1] > max){
            //switches max to the new string and records the index of the max value
            index = i+1;
            max = a[i+1];
        }
    }
    //returns the max
    return index;
}
int circleLeft(string a[], int n, int pos){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    if(n == 0){
        return 0;
    }
    //stores the first element to be swapped in its own variable
    string temp = a[pos];
    for(int i=pos;i<n-1;i++){
        //switches each element to the value of the one to the right
        a[i] = a[i+1];
    }
    //makes the last element equal to the first one
    a[n-1] = temp;
    return pos;
}
int enumerateRuns(const string a[], int n){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    int count = 0;
    //creates a 'last' string
    string last = "";
    for(int i=0; i<n; i++){
        //checks if the string is unique from the 'last' 
        if(a[i] != last){
            //a count is incremented and the last string is assigned to the current string.
            count++;
            last = a[i];
        }
    }
    return count;
}
int flip(string a[], int n){
    //checks if n is negative
    if(n<0){
        return -1;
    }
    for(int i=0; i<n/2;i++){
        //switches the 'i'th element with the 'n-i-1'th element
        string temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}
int locateDifference(const string a1[], int n1, const string a2[], int n2){
    //checks if n's are negative
    if(n1<0 || n2<0){
        return -1;
    }
    //checks if n1 or n2 is the lesser value
    int pos;
    if(n1>n2){
        pos = n2;
    }
    else{
        pos = n1;
    }
    //checks to see where the first instance that an a1 element doesn't equal an a2 element and returns that index
    for(int i=0; i<pos;i++){
        if(a1[i] != a2[i]){
            return i;
        }
    }
    //if all elements are the same, the lesser value of n1 and n2 is returned.
    return pos;
}
int subsequence(const string a1[], int n1, const string a2[], int n2){
    //checks if n's are negative
    if(n1<0 || n2<0){
        return -1;
    }
    int loc = -1;
    for(int i=0; i<n1;i++){
        //finds the first point where the two strings have a similar value
        if(a1[i] == a2[0]){
            loc = i;
            break;
        }
    }
    //spot is stored as the start of the subsequence for future use
    int spot = loc;
    int pos = 0;
    //goes while both arrays still have elements
    while(n2>0 && n1>0){
        //if an element from the substring doesn't equal a value from a2
        if(a1[loc] != a2[pos]){
            //If there isn't a match, -1 is returned
            return -1;
        }
        pos++;
        loc++;
        n2--;
        n1--;
    }
    //if the subsequence completely matches, the spot is found
    return spot;
}
int locateAny(const string a1[], int n1, const string a2[], int n2){
    //checks if n's are negative
    if(n1<0 || n2<0){
        return -1;
    }
    for(int i=0; i<n1;i++){
        for(int j=0; j<n2;j++){
            //goes through one element of a time in a1, then compares every element in a2 to see if they are the same
            if(a1[i] == a2[j]){
                //if there is a match, the index i is returned
                return i;
            }
        }
    }
    //if it reaches this point, there is no match
    return -1;
}

int divide(string a[], int n, string divider){
    //checks if n is negative
    if(n < 0){
        return -1;
    }
    //declares variables
    string temp = "";
    bool changed = false;
    int index = 0;
    for(int i=0; i<n;i++){ //finds the first string in a that is greater than divider and stores it in temp and replaces it with divider
        if(a[i] > divider){
            index =i;
            temp = a[i];
            a[i] = divider;
            changed = true;
            break;
        }
    }
    //if the divider is lexicgraphically the last, the array is sorted so you can just return n
    if(!changed){
        return n;
    }
    //bubble sort
    bool swapped;
    for(int i=0; i<n-1;i++){
        swapped=false;
        for(int j=0; j<n-i-1;j++){
            if(a[j] > a[j+1]){
                swap(a[j], a[j+1]);
                swapped = true;
            }
        }
        if(swapped==false){
            break;
        }
    }
    //finds divider and replaces it with the temp string
    //records the index of divider, and returns it
    for(int i=0; i<n;i++){
        if(a[i] == divider){
            index = i;
            a[i] = temp;
            break;
        }
    }
    return index;
}
	int main()
	{
	    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
	    assert(locate(h, 7, "chris") == 5);
	    assert(locate(h, 7, "asa") == 2);
	    assert(locate(h, 2, "asa") == -1);
	    assert(locationOfMax(h, 7) == 3);

	    string g[4] = { "nikki", "ron", "chris", "tim" };
	    assert(locateDifference(h, 4, g, 4) == 2);
	    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

	    string c[4] = { "ma", "can", "tu", "do" };
	    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

	    string e[4] = { "asa", "vivek", "", "chris" };
	    assert(subsequence(h, 7, e, 4) == 2);

	    string d[5] = { "ron", "ron", "ron", "chris", "chris" };
	    assert(enumerateRuns(d, 5) == 2);
	
	    string f[3] = { "vivek", "asa", "tim" };
	    assert(locateAny(h, 7, f, 3) == 2);
	    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
        
	    assert(divide(h, 7, "donald") == 3);
        string empty[0] = {};
        
        //My Custom Test Cases
        
        string a[5] = {"joe", "donald", "barack", "george", "bill"}; //normal names
        string b[5] = {"123", "", " ", "ab345", "@ 54"}; //"odd" names
        assert(reduplicate(a, 5) == 5 && a[0] == "joejoe" && a[3] == "georgegeorge");
        assert(reduplicate(b, 5) == 5 && b[1] == "" && b[4] == "@ 54@ 54");
        assert(reduplicate(a, -3) == -1);
        assert(reduplicate(empty, 0) == 0);
        
        string i[5] = {"joe", "donald", "barack", "george", "bill"};
        string j[5] = {"123", "", " ", "ab345", "@ 54"};
        string aa[4] = {"franklin", "harry", "joe", "joe"};
        
        assert(locate(i, -2, "joe") == -1);
        assert(locate(i, 5, "donald") == 1);
        assert(locate(i, 5, "bill") == 4);
        assert(locate(i, 5, "ronald") == -1);
        assert(locate(j, 5, "") == 1);
        assert(locate(j, 5, "normal") == -1);
        assert(locate(empty, 0, "babbabooey") == -1);
        
        assert(locationOfMax(aa, 4) == 2);
        assert(locationOfMax(i, -10) == -1);
        assert(locationOfMax(i, 5) == 0);
        assert(locationOfMax(j, 5) == 3);
        assert(locationOfMax(empty, 0) == 0);
        
        
        assert(circleLeft(i, 5, 2) == 2 && i[2] == "george" && i[4] == "barack");
        assert(circleLeft(j, 5, 1) == 1 && j[1] == " " && j[4] == "");
        assert(circleLeft(empty,0,0) == 0);
        assert(circleLeft(i, -5, 3) == -1);
        
        
        string k[8] = {"washington", "washington", "adams", "jefferson", "jefferson", "jefferson", "monroe", "monroe"};
        string l[8] = {"roosevelt", "roosevelt", "roosevelt", "truman", "truman", "eisenhower", "kennedy", "johnson"};
        string m[4] = {"trevor", "trevor", "trevor", "trevor"};
        string unique[3] = {"a", "b", "c"};
        assert(enumerateRuns(k, 8) == 4);
        assert(enumerateRuns(l, 8) == 5);
        assert(enumerateRuns(m, 4) == 1);
        assert(enumerateRuns(empty, 0) == 0);
        assert(enumerateRuns(k, -4) == -1);
        assert(enumerateRuns(unique, 3) == 3);
        assert(flip(k, 8) == 8 && k[0] == "monroe" && k[4] == "jefferson" && k[2] == "jefferson");
        assert(flip(i, 5) == 5 && i[1] == "bill" && i[4] == "joe");
        assert(flip(empty, 0) == 0);
        assert(flip(k, -5) == -1);
        string n[5] = {"", "nixon", "ford", "carter", "reagan"};
        string o[3] = {"johnson", "nixon", "ford"};
        string p[6] = {"", "nixon", "ford", "carter", "reagan", "bush"};
        string equal[3] = {"johnson", "nixon", "ford"};
        assert(locateDifference(o, 3, equal, 3) == 3);
        assert(locateDifference(n, 5, o, 3) == 0);
        assert(locateDifference(n, 5, p, 6) == 5);
        assert(locateDifference(o, 3, empty, 0) == 0);
        assert(locateDifference(o, 4, p, -3) == -1);
        assert(locateDifference(n, -4, o, 3) == -1);
        assert(locateDifference(o, -3, p, -4) == -1);
    

        string q[7] = {"harris", "pence", "biden", "chancy", "gore", "qualye", "bush"};
        string r[4] = {"pence", "biden", "chancy", "gore"};
        string s[2] = {"gore", "qualye"};
        string u[2] = {"harris", "gore"};
        string missing[1] = {"rockefeller"};

        assert(subsequence(q, 7, r, 4) == 1);
        assert(subsequence(q, 7, s, 2) == 4);
        assert(subsequence(q, 7, u, 2) == -1);
        assert(subsequence(q, 7, empty, 0) == -1);
        assert(subsequence(q, -4, r, 4) == -1);
        assert(subsequence(q, 7, r, -3) == -1);
        assert(subsequence(q, -4, r, -3) == -1);

        assert(locateAny(q, 7, r, 4) == 1);
        assert(locateAny(q, 7, s, 2) == 4);
        assert(locateAny(q, 7, empty, 0) == -1);
        assert(locateAny(q, -5, r, 4) == -1);
        assert(locateAny(q, 7, r, -4) == -1);
        assert(locateAny(q, -5, r, -4) == -1);
        assert(locateAny(q, 7, missing, 1) == -1);

        string t[4] = {"humphrey", "rockefeller", "biden", "nixon"};

        assert(locateAny(q, 7, t, 4) == 2);
        
        assert(divide(q, 7, "middle") == 5);
        assert(divide(q, 7, "vice") == 7);
        assert(divide(q, 7, "") == 0);
        assert(divide(empty, 0, "any_word") == 0);
        assert(divide(q, -4, "divider") == -1);
        assert(divide(t, 4, "milhouse") == 2);
        assert(divide(r, 4, "harris") == 3);

	    cout << "All tests succeeded" << endl;
	}