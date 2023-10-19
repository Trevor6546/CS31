#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main(){
    string id, location;
    double amount, fine = 0;
    double rate1 =  6.666;
    double rate2_fn = 16.2;
    double rate2 = 13.77;
    bool id_fail = false;
    bool amount_fail = false;
    bool location_fail = false;
    cout << "Identification: " << endl;
    getline(cin, id);
    if(id == ""){
        id_fail = true;
    }
    cout << "Overstated amount (in millions): " << endl;
    cin>>amount;
    cin.ignore(10000, '\n');
    if(amount <= 0){
        amount_fail = true;
    }
    cout << "Location: " << endl;
    getline(cin, location);
    if(location == ""){
        location_fail = true;
    }
    if(amount > 150){
        fine += rate1;
        if(location == "new york" || location == "florida"){
            fine += rate2_fn;
        }
        else{
            fine += rate2;
        }
        fine += (amount-150)*0.21;
    }
    else if(amount > 60){
        fine += rate1;
        if(location == "new york" || location == "florida"){
            fine += (amount-60)*0.18;
        }
        else{
            fine += (amount-60)*0.153;
        }
    }
    else{
        fine += amount*0.1111;
    }
    cout<<"---"<<endl;
    if(id_fail){
        cout<<"You must enter a property identification."<<endl;
    }
    else if(amount_fail){
        cout<<"The overstated amount must be positive."<<endl;
    }
    else if(location_fail){
        cout<<"You must enter a location."<<endl;
    }
    else{
        cout << "The fine for " << id << " is $" << fixed << setprecision(3) << fine << " million dollars." << endl;
    }
}