#ifndef MILKTEA_H 
#define MILKTEA_H 
#endif
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif
#include <string>
using namespace std; 
// ========== System ==========
//Terminl width preset function
int findwidth() { 
    return 50;
} 
 
// Clear the screen function
void clearScreen() { 
    #ifdef _WIN32
    system("cls");    // Slow, but guaranteed
#else
    system("clear");
#endif
}
//Aligned text function
enum Alignment { 
    LEFT,
    CENTER ,
    DUAL_ALIGN 
}; 

void text(const std::string& text, int width, Alignment mode = LEFT, int offset = 0, const 
std::string& rightText = "") { 
    int innerWidth = width - 4; // leave border space 
    std::string line(innerWidth, ' '); 
 
    switch (mode) { 
        case LEFT: 
            line.replace(0, text.size(), text); 
            break; 
        case CENTER: { 
            double  start = (innerWidth - text.size()) / 2; 
            line.replace(start, text.size(), text);
            break; 
        }
        case DUAL_ALIGN: { 
            line.replace(0, text.size(), text); 
            int rightStart = innerWidth - rightText.size(); 
            if (rightStart > (int)text.size()) {
                line.replace(rightStart, rightText.size(), rightText);}
            break;
        } 
    } 
 
    std::cout << "| " << line << " |" << std::endl; 
} 
//Check if the input is int
int isInt(const string& s) { 
    if (s.empty()) 
    {return false;}
 
    int start;
    if(s[0] == ' ') {
    	start=0;
    	 }
 
    
 
    return all_of(s.begin() + start, s.end(), ::isdigit); 
} 
//Returns the int
int getInt(const string& prompt,string quant) { 
    cout << prompt; 
    getline(cin, quant); 
 
    while (!isInt(quant)) { 
        cout << "Numbers only! \n"; 
        cout << prompt; 
        getline(cin, quant); 
        
    } 
 
    return stoi(quant); 
} 
 
//Search string in array
bool lookSt(string arr[], int size, string target) { 
    for(int i = 0; i < size; i++) { 
        if(arr[i] == target) {
            return true;} // Target found at index i 
    } 
    return false; // Target not found 
}

// =============================
// SAVE FUNCTION
// =============================
void saveDat(const vector<int>& Stack,
             const vector<int>& Price,
             const vector<string>& Prod,
             const vector<string>& marker)
{
    ofstream file("inventory.dat");
    if (!file) return;

    // Save how many products first
    file << Prod.size() << "\n";

    for (size_t i = 0; i < Prod.size(); i++) {
        file << Prod[i] << "\n";
        file << Price[i] << "\n";
        file << Stack[i] << "\n";
        file << marker[i] << "\n";
    }
}

// =============================
// LOAD FUNCTION
// =============================
void loadDat(vector<int>& Stack,
             vector<int>& Price,
             vector<string>& Prod,
             vector<string>& marker)
{
    ifstream file("inventory.dat");
    if (!file) return;

    int count;
    file >> count;
    file.ignore(); // remove leftover newline

    Prod.clear();
    Price.clear();
    Stack.clear();
    marker.clear();

    for (int i = 0; i < count; i++) {
        string name;
        getline(file, name);

        int price;
        file >> price;
        file.ignore();

        int stock;
        file >> stock;
        file.ignore();

        string mark;
        getline(file, mark);

        Prod.push_back(name);
        Price.push_back(price);
        Stack.push_back(stock);
        marker.push_back(mark);
    }
}

//============FrontEnd======= 
//Line display function
void Line(char edge = '=', int width = 50) { 
    cout << "+" << string(width, edge) << "+" << endl; 
} 

void Home(const vector<string>& Prod, const vector<int>& Price, const vector<string>& marker,int width) {
    for (size_t b = 0; b < Prod.size(); b++) {
        text(to_string(b + 1) + ". " + Prod[b]+marker[b], width, DUAL_ALIGN, 0, to_string(Price[b]));
    }
    Line('=', width - 2);
}
// Header display function
void Header(const string& title) { 
    int width = findwidth(); 
    if (width < 30) 
    {width = 30;} 
    Line('=', width - 2); 
    text(title, width,CENTER); 
    Line('=', width - 2); 
} 

//Order Details function
 void order(int productquant,int sugar) { 
 int width=findwidth(); 
 string P=to_string(productquant); 
 string S=to_string(sugar); 
 text("Quantity",width,DUAL_ALIGN,0,"*"+P); 
 text("Sugar Level(%)",width,DUAL_ALIGN,0,S+"%"); 
 text("Addons:",width,LEFT); 
 text(" Cookies",width,DUAL_ALIGN,0,"$3"); 
 text(" Sprinkler",width,DUAL_ALIGN,0,"$2"); 
 text(" Ice Cream",width,DUAL_ALIGN,0,"$3"); 
 text(" Peanuts",width,DUAL_ALIGN,0,"$2"); 
 Line('=',width-2);} 
