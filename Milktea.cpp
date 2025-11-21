#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <thread> 
#include <chrono>
#include <algorithm>
#include <cctype>
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
#include <sys/ioctl.h> 
#include <unistd.h> 
#endif
#include <sstream> 
#include "Milktea_Head.h" 
using namespace std; 
int main() { 
    int pick,addonValue,addonQuant,productValue;
    int width=findwidth(); 
    int quantity{0};
    string product,pickS,sugarS, b;
    string A[13]={
    "Sprinkler", "SPRINKLER", "sprinkler",
    "COOKIES", "Cookies", "cookies",
    "ICE cream", "ICE CREAM", "Ice cream", "Ice Cream",
    "Peanuts", "PEANUTS", "peanuts"
}; 
    bool ch2; 
    while(true) 
    { 
     clearScreen(); 
     Header("Order Menu"); 
     Home(); 
     text("Chose order",width,CENTER); 
     Line('=',width-2); 
     pick=getInt("",pickS);
     
     while(pick>5){
     	clearScreen(); 
     Header("Order Menu"); 
     Home(); 
     text("Chose order",width,CENTER); 
     Line('=',width-2);
     cout<<"Invalid Try again>> ";
     pick=getInt("",pickS);}
     
     switch(pick) 
     { 
      case 1: 
      product="Classic Choco"; 
      productValue=40; 
      break; 
      case 2: 
      product="Rocky Road"; 
      productValue=40; 
      break; 
      case 3: 
      product="Creamy Vanilla"; 
      productValue=45; 
      break; 
      case 4: 
      product="Tropical Mango"; 
      productValue=45; 
      break; 
      case 5: 
      product="Avocado Swirl"; 
      productValue=50; 
      break; 
     }
      //product Stream 
      string quantityS; 
      int sugar{0}; 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      quantity=getInt("How many?>> ",quantityS);
      while(quantity>=26){ 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Invalid Input"; 
      this_thread::sleep_for(chrono::milliseconds(800)); 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      quantity=getInt("How many?>> ",quantityS);
     } 
      //Sugar Stream 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      sugar=getInt("Sugar Levels?>> ",sugarS); 
      if(sugar>100) 
      { 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Invalid Input"; 
      this_thread::sleep_for(chrono::milliseconds(800)); 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      sugar=getInt("Sugar Levels?>> ",sugarS);} 
      //Addon Stream 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar);  
      cout<<"Addon>> "; 
      getline(cin,b); 
      bool ch2=lookSt(A,13,b); 
      while(ch2!=true) 
      { 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Invalid Input"; 
      this_thread::sleep_for(chrono::milliseconds(800)); 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Addon>> "; 
      getline(cin,b); 
      ch2=lookSt(A,13,b); 
      }  
      //Addon Quantity Stream 
      string addonQuantS; 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      addonQuant=getInt("Addon Quantity>> ",addonQuantS); 
      if(addonQuant>=4||addonQuant==0) 
      { 
       clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Invalid Input"; 
      this_thread::sleep_for(chrono::milliseconds(800)); 
      clearScreen(); 
      Header(product); 
      order(quantity,sugar); 
      cout<<"Addon Quantity>> "; 
      cin>>addonQuant; 
      } 
      //Billing Stream 
      // Addon Values 
      if(b=="Cookies"||b=="cookies"||b=="COOKIES") 
      { 
       addonValue=3; 
      }; 
      if(b=="Sprinkler"||b=="sprinkler"||b=="SPRINKLER") 
      { 
       addonValue=2; 
      }; 
      if(b=="Ice cream"||b=="ICE CREAM"||b=="Ice Cream") 
      { 
       addonValue=3; 
      }; 
      if(b=="Peanuts"||b=="peanuts"||b=="PEANUTS") 
      { 
       addonValue=2; 
      }; 
      //Total Bill Stream
     for(int t{0};t<=2;t++){ 
     bill(productValue,quantity,addonValue,addonQuant); 
     this_thread::sleep_for(chrono::milliseconds(5000));
      }}}
