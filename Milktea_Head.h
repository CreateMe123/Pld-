#ifndef MILKTEA_H 
#define MILKTEA_H 
#endif
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif
using namespace std; 
// ========== System ========== 
inline int findwidth() { 
    return 50;
} 
 
// Get dynamic terminal width 
 
// Clear screen 
inline void clearScreen() { 
    // Enable ANSI escape codes on Windows 10+
    #ifdef _WIN32
    system("cls");    // Slow, but guaranteed
#else
    system("clear");
#endif
}
//text align 
enum Alignment { 
    LEFT, 
    CENTER, 
    RIGHT, 
    CUSTOM_OFFSET, 
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
        case RIGHT: { 
            double start = innerWidth - text.size(); 
            line.replace(start, text.size(), text); 
            break; 
        } 
        case CUSTOM_OFFSET: { 
            double start = offset < innerWidth ? offset : innerWidth - text.size(); 
            line.replace(start, text.size(), text); 
            break; 
        } 
        case DUAL_ALIGN: { 
            line.replace(0, text.size(), text); 
            int rightStart = innerWidth - rightText.size(); 
            if (rightStart > (int)text.size()) 
                line.replace(rightStart, rightText.size(), rightText); 
            break; 
        } 
    } 
 
    std::cout << "| " << line << " |" << std::endl; 
} 
//For uneven text 
void textD(const std::string& text, int width, Alignment mode = LEFT, int offset = 0, const 
std::string& rightText = "") { 
    int innerWidth = width - 4; // leave border space 
    std::string line(innerWidth, ' '); 
 
    switch (mode) { 
     case DUAL_ALIGN: 
     { 
            line.replace(0, text.size(), text); 
            int rightStart = innerWidth - rightText.size()-2; 
            if (rightStart > (int)text.size()) 
                line.replace(rightStart, rightText.size(), rightText); 
            break; 
        }} 
        std::cout << "| " << line << " |" << std::endl; 
        } 
//filter letter 
int isInt(const string& s) { 
    if (s.empty()) return false; 
 
    int start = (s[0] == '-') ? 1 : 0; 
 
    if (start == 1 && s.size() == 1) return false; 
 
    return all_of(s.begin() + start, s.end(), ::isdigit); 
} 
 
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
 
//String Lookups 
bool lookSt(string arr[], int size, string target) { 
    for(int i = 0; i < size; i++) { 
        if(arr[i] == target) 
            return true; // Target found at index i 
    } 
    return false; // Target not found 
} 
//Int Lookups 
bool lookInt(int arr[], int size, int target) { 
    for(int i = 0; i < size; i++) { 
        if(arr[i] == target) 
            return true; // Target found at index i 
    } 
    return false; // Target not found 
} 
//============FrontEnd======= 
//Line 
inline void Line(char edge = '=', int width = 50) { 
    cout << "+" << string(width, edge) << "+" << endl; 
} 
// Header box 
inline void Header(const string& title) { 
    int width = findwidth(); 
    if (width < 30) width = 30; 
    Line('=', width - 2); 
    text(title, width,CENTER); 
    Line('=', width - 2); 
} 
//Home Page 
 
inline void Home() { 
 int width=findwidth(); 
 text("1. Classic Choco",width,DUAL_ALIGN,0,"$40"); 
 text("2. Rocky Road",width,DUAL_ALIGN,0,"$40"); 
 text("3. Creamy Vanilla",width,DUAL_ALIGN,0,"$45"); 
 text("4. Tropical Mango",width,DUAL_ALIGN,0,"$45"); 
 text("5. Avocado Swirl",width,DUAL_ALIGN,0,"$50"); 
 Line('=',width-2);} 
//order page 
inline void order(int productquant,int sugar) { 
 int width=findwidth(); 
 string P=to_string(productquant); 
 string S=to_string(sugar); 
 textD("Quantity",width,DUAL_ALIGN,0,"*"+P); 
 textD("Sugar Level(%)",width,DUAL_ALIGN,0,S+"%"); 
 text("Addons:",width,LEFT); 
 text("1. Cookies",width,DUAL_ALIGN,0,"$3"); 
 text("2. Sprinkler",width,DUAL_ALIGN,0,"$2"); 
 text("3. Ice Cream",width,DUAL_ALIGN,0,"$3"); 
 text("4. Peanuts",width,DUAL_ALIGN,0,"$2"); 
 Line('=',width-2);} 
//Billing Page -unf 
void bill(int prodValue,int quant,int addonValue,int addonquant) { 
 clearScreen(); 
 int width=findwidth(); 
 prodValue=prodValue*quant; 
 std::string prodValueS=to_string(prodValue); 
 Header("Bill Payments"); 
 text("Product ",width,DUAL_ALIGN,0,"$"+prodValueS); 
 addonValue=addonValue*addonquant; 
 string addonValueS=to_string(addonValue); 
 text("Addons",width,DUAL_ALIGN,0,"$"+addonValueS); 
 string total=to_string((prodValue)+addonValue); 
 text("Total",width,DUAL_ALIGN,0,"$"+total); 
 Line('=',width-2); 
 text("Please Proceeds to Counter",width,CENTER); 
 text("Return Menu in 10 sec",width,CENTER); 
 Line('=',width-2);} 
