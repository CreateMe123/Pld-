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
#include "Libs.hpp"
using namespace std;

int main() {

    // ============================
    // Persistent inventory values
    // ============================
    int sugar{0};
    int width = findwidth();
    // Product availability markers
    vector<string> marker = {"", "", "", "", ""};
    //Default product stacks
    vector<int> Stack = {
        15,
        20,
        19,
        20,
        56
    };
    // Default product prices
    vector<int> Price = {40,40,45,45,50};
    // Default product names
    vector<string> Prod = {
        "Classic Choco",
        "Rocky Road",
        "Creamy Vanilla",
        "Tropical Mango",
        "Caramel Delight"
    };
    // Valid addon names (different capitalizations)
    string A[13] = {
        "Sprinkler", "SPRINKLER", "sprinkler",
        "COOKIES", "Cookies", "cookies",
        "ICE cream", "ICE CREAM", "Ice cream", "Ice Cream",
        "Peanuts", "PEANUTS", "peanuts"
    };
    // Product structure for order processing
    struct Product {
        int addonValue{0}, addonQuant{0}, productValue,quantity{0},stack;
        string addon, product;
    };
    //Load data from inventory.dat file
    loadDat(Stack,Price,Prod,marker);
    // ============================
    // Main program loop
    // ============================

    while (true) {

        int set = 0;
        int enl,enl2;
        int Con = 0;
        string setS;
        // Main menu
        Header("Frozen MilkShake Shop");
        text("Choose System To Operate", width, CENTER);
        Line('=', width - 2);
        text("1. Inventory System <Type 4-digit pin instead>", width, LEFT);
        text("2. Order System", width, LEFT);
        Line('=', width - 2);
        //store and validate input of "set"
        set = getInt(">> ", setS);

        // ============================
        // INVENTORY SYSTEM (PIN 1057)
        // ============================

        if (set == 1057) {

            
            while (Con == 0) {
            	int set2,newPrice{0},newStack{0},Del;
            	string set2S,enl2S, enlS,tS,DelS,newPriceS,newStackS,newName{""};
                clearScreen();
                Header("Inventory System");
                text("1.) Add stacks", width, LEFT);
                text("2.) Change price", width, LEFT);
                text("3.) Add product", width, LEFT);
                text("4.) Delete product", width, LEFT);
                text("0.) Back to Main Menu", width, LEFT);
                Line('=', width - 2);
             	//store and validate input of "set2"
               set2 = getInt(">> ", set2S);
            	//I/O exception
            	while(set2>4)
            	{
            	set2 = getInt("Invalid Try again>> ", set2S);
            	}
               // Return to main menu
                if (set2 == 0) {  
                    Con = 1;
                    continue;
                }
                
                // ============================
                // Add stacks interface
                // ============================
                if (set2 == 1) {
                
                	
                    clearScreen();
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                	//store and validate input of "enl"
                   enl = getInt(">> ", enlS)-1;
                	
                   // I/O exception
                	while (enl >= Prod.size()) {
                    enl = getInt("Invalid Try again>> ", enlS)-1;
                }

                    // Ask add quantity Display
                    clearScreen();
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Quantity", width, CENTER);
                    Line('=', width - 2);
                    //store and validate input of "enl2"
                    enl2 = getInt(">> ", enl2S);
                    //Display new stack
                    clearScreen();
                    Stack[enl] += enl2;
                    // Remove marker if restocked
                   if(Stack[enl]>=1){
                        marker[enl]="";
                    }
                    Header("Stack: " + to_string(Stack[enl]));
                    Header("Stack: " + to_string(Stack[enl]));
                    
                }

                // ============================
                // Change price
                // ============================
                if (set2 == 2) {
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    //store and validate input of "enl"
                   enl = getInt(">> ", enlS)-1;
                   while (enl >= Prod.size()) {
                    enl = getInt("Invalid Try again>> ", enlS)-1;
                }
                    //Ask new price
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Price", width, CENTER);
                    Line('=', width - 2);
                    
                    enl2 = getInt(">> ", enl2S);
                    //Display new price
                    Price[enl] = enl2;
                   clearScreen();
                    Header("Price: " + to_string(Price[enl]));
                }

                // ============================
                // Add new product interface
                // ============================
                if(set2 == 3){
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    text("Enter Product Name:", width, LEFT);
                    Line('=', width - 2);
                    cout << ">>> ";
                    cin >> newName;
                    //Enter Price
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    text("Enter Price:", width, LEFT);
                    Line('=', width - 2);
                    newPrice = getInt(">>", newPriceS);
                    //Enter Stack
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                    text("Enter Stack:", width, LEFT);
                    Line('=', width - 2);
                    newStack = getInt(">>", newStackS);
                    //Push all Contents 
                    Prod.push_back(newName);
                    Price.push_back(newPrice);
                    Stack.push_back(newStack);
                    //Display New Product
                    clearScreen();
                    Header("Product Added");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                }
                //Delete Product Interface
                if(set2==4)
                {
                	
                	clearScreen();
                    Header("Delete Product");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    Del = getInt(">>", DelS);
                    if(Del>Prod.size())
                    {
                    Del = getInt("Index not match>>", DelS);
                    }
                    Prod.erase(Prod.begin()+Del);
                    Stack.erase(Stack.begin()+Del);
                    Price.erase(Price.begin()+Del);
                    clearScreen();
                    Header("Succsefully Deleted");
                }
                //Ask Continuity
                text("Back to Main Menu?",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"1 = Continue Inventory");
                Line('=', width - 2);
               int t = getInt(">>", tS);
                if (t == 0) {
                    Con = 1;
                }

            } // END INVENTORY LOOP

        } // END set==1057 block
        
        
        // ============================
        // ORDER SYSTEM DISPLAY
        // ============================
        if (set == 2) {

            int tap = 0;
            vector<Product> em;
            while (true) {
            	
                Product Que;
                int totalP = 0;
                sugar = 0;
                int pick,pick2;
                string pickS,pick2S,tS,
                qtyS,sugarS,aqS,tapS;
                //Order Menu Interface
                clearScreen();
                Header("Order Menu");
                text("Product:",width,DUAL_ALIGN,0,"Price:");
                Home(Prod,Price,marker,width);
                text("Chose order", width, CENTER);
                Line('=', width - 2);
                pick = getInt(">>", pickS)-1;
                //Input Validation
                while (pick >= Prod.size()) {
                    pick = getInt("Invalid Try again>> ", pickS)-1;
                }
                //Push all input vector
                Que.product = Prod[pick];
                Que.productValue = Price[pick];
                Que.stack = Stack[pick];
                //Display if Product is Out of Stock
                if(Stack[pick]==0){
                    clearScreen();
                    Header("Product needs restock");
                    text("Ask admin to restock",width,CENTER);
                    Line('=', width - 2);
                    marker[pick]=" <Not Available>";
                    text("Back to Interface",width,LEFT);
                     text("*note your order will be cancel",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"Any number= Order Other");
                Line('=', width - 2);
                //Backer
               int t = getInt(">>", tS);
                if (t == 0) {
                    break;
                }
                	continue;
                }
                //Product Attributes Display
                //Quantity  Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                Que.quantity = getInt("How many (Max. "+to_string(Que.stack)+")?>> ", qtyS);
                //input Validation
                while (Que.quantity >Que.stack) {
                    Que.quantity = getInt("Invalid Try again>>", qtyS);
                }
                //Update Stocks
                Stack[pick] = Stack[pick] - Que.quantity;
                //Sugar Level Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                sugar = getInt("Sugar Levels?>> ", sugarS);
                //input Validation
                while (sugar > 100) {
                    sugar = getInt("Invalid Try again>> ", sugarS);
                }
                //Addon Condition
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                text("You want Addons?",width,CENTER);
                Line('=',width-2);
                text("1 = Yes",width,DUAL_ALIGN,0,"0 = No");
                Line('=',width-2);
                pick2= getInt(">> ", pick2S);
                //If user want addon
                if(pick2==1){
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                cout << "Enter Addon Name>> ";
                getline(cin, Que.addon);
                bool ch2 = lookSt(A, 13, Que.addon);
                //I/O Exeption
                while (!ch2) {
                	
                    cout << "Invalid Try again>> ";
                    getline(cin, Que.addon);
                    ch2 = lookSt(A, 13, Que.addon);
                }
                //Addon Quantity 
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                Que.addonQuant = getInt("Addon Quantity For Each Order (Max *4)>> ", aqS);
                ///IO exception
                while (Que.addonQuant > 4) {
                    Que.addonQuant = getInt("Invalid Try again>> ", aqS);
                }
                //Addon Value Assignement
                if (Que.addon == "Cookies" || Que.addon == "cookies" || Que.addon == "COOKIES"){
                    Que.addonValue = 3;}

                if (Que.addon == "Sprinkler" || Que.addon == "sprinkler" || Que.addon == "SPRINKLER"){
                    Que.addonValue = 2;}

                if (Que.addon == "Ice cream" || Que.addon == "ICE CREAM" || Que.addon == "Ice Cream"){
                    Que.addonValue = 3;}

                if (Que.addon == "Peanuts" || Que.addon == "peanuts" || Que.addon == "PEANUTS"){
                    Que.addonValue = 2;}
                }
                //Push all contents of Que
                em.push_back(Que);
                //Transaction Continuity Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                tap = getInt("Want another order?\n(press 1 to continue or 0 to pay)>> ", tapS);
                //Reciept Display
                if (tap == 0) {
                    clearScreen();
                    Header("Reciept");
                    //Display Every Products Overall Details,Price,and Addon Price

                    for (size_t i = 0; i < em.size(); i++) {
                        em[i].productValue *= em[i].quantity;
                        int t =em[i].addonQuant*em[i].quantity;
                        em[i].addonValue *= t;
                        int total = em[i].productValue + em[i].addonValue;

                        text(em[i].product, width, DUAL_ALIGN, 0, "$" + to_string(em[i].productValue));
                        text("   " + to_string(em[i].quantity) + "pcs", width, LEFT);

                        text("Addons ", width, DUAL_ALIGN, 0, "$" + to_string(em[i].addonValue));
                        text("   " + to_string(em[i].addonQuant) + " pcs. each order", width, LEFT);
                        
                        text("Total", width, DUAL_ALIGN, 0, "$" + to_string(total));
                        totalP += total;
                        Line('=', width - 2);
                    }
                    text("Bills", width, DUAL_ALIGN, 0, "$" + to_string(totalP));
                    Line('=', width - 2);
                    text("Please Proceeds to Counter", width, CENTER);
                    text("Return Menu in 10 sec", width, CENTER);
                    Line('=', width - 2);
                    //stop for 10 sec
                    this_thread::sleep_for(chrono::milliseconds(10000));
                   
                    em.clear();
                    break;
                }
                
            } // end transaction loop
          

        } // end order system
        //save data into file
        saveDat(Stack, Price, Prod, marker);
        clearScreen();

    } // end outer program loop

}
    vector<int> Price = {40,40,45,45,50};
    // Default product names
    vector<string> Prod = {
        "Classic Choco",
        "Rocky Road",
        "Creamy Vanilla",
        "Tropical Mango",
        "Caramel Delight"
    };
    // Valid addon names (different capitalizations)
    string A[13] = {
        "Sprinkler", "SPRINKLER", "sprinkler",
        "COOKIES", "Cookies", "cookies",
        "ICE cream", "ICE CREAM", "Ice cream", "Ice Cream",
        "Peanuts", "PEANUTS", "peanuts"
    };
    // Product structure for order processing
    struct Product {
        int addonValue, addonQuant, productValue,quantity{0},stack;
        string addon, product;
    };
    //Load data from inventory.dat file
    loadDat(Stack,Price,Prod,marker);
    // ============================
    // Main program loop
    // ============================

    while (true) {

        int set = 0;
        int enl,enl2;
        int Con = 0;
        string setS;
        // Main menu
        Header("Frozen MilkShake Shop");
        text("Choose System To Operate", width, CENTER);
        Line('=', width - 2);
        text("1. Inventory System <Type 4-digit pin instead>", width, LEFT);
        text("2. Order System", width, LEFT);
        Line('=', width - 2);
        //store and validate input of "set"
        set = getInt(">> ", setS);

        // ============================
        // INVENTORY SYSTEM (PIN 1057)
        // ============================

        if (set == 1057) {

            
            while (Con == 0) {
            	int set2;
            	int newPrice{0};
                int newStack{0};
                int Del;
            	string set2S;
            	string enl2S;
            	string enlS;
            	string tS;
                string DelS;
                string newPriceS;
                string newStackS;
            	string newName{""};
                clearScreen();
                Header("Inventory System");
                text("1.) Add stacks", width, LEFT);
                text("2.) Change price", width, LEFT);
                text("3.) Add product", width, LEFT);
                text("4.) Delete product", width, LEFT);
                text("0.) Back to Main Menu", width, LEFT);
                Line('=', width - 2);
             	//store and validate input of "set2"
               set2 = getInt(">> ", set2S);
                //I/O Exception
                while(set2>4)
            	{
            	cout<<"Invalid Try again ";
            	set2 = getInt(">> ", set2S);
                } 
               // Return to main menu
            
                if (set2 == 0) {  
                    Con = 1;
                    continue;
                }
                
                // ============================
                // Add stacks interface
                // ============================
                if (set2 == 1) {
                
                	
                    clearScreen();
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                	//store and validate input of "enl"
                   enl = getInt(">> ", enlS)-1;
                	
                   // I/O exception
                	while (enl >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                	//store and validate input of "enl"
                    enl = getInt(">> ", enlS)-1;
                }

                    // Ask add quantity Display
                    clearScreen();
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Quantity", width, CENTER);
                    Line('=', width - 2);
                    //store and validate input of "enl2"
                    enl2 = getInt(">> ", enl2S);
                    //Display new stack
                    clearScreen();
                    Stack[enl] += enl2;
                    // Remove marker if restocked
                   if(Stack[enl]>=1){
                        marker[enl]="";
                    }
                    Header("Stack: " + to_string(Stack[enl]));
                    Header("Stack: " + to_string(Stack[enl]));
                    
                }

                // ============================
                // Change price
                // ============================
                if (set2 == 2) {
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    //store and validate input of "enl"
                   enl = getInt(">> ", enlS)-1;
                    // I/O exeception
                   while (enl >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                    //store and validate input of "enl"
                    enl = getInt(">> ", enlS)-1;
                }
                    //Ask new price
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Price", width, CENTER);
                    Line('=', width - 2);
                    
                    enl2 = getInt(">> ", enl2S);
                    //Display new price
                    Price[enl] = enl2;
                   clearScreen();
                    Header("Price: " + to_string(Price[enl]));
                }

                // ============================
                // Add new product interface
                // ============================
                if(set2 == 3){
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    text("Enter Product Name:", width, LEFT);
                    Line('=', width - 2);
                    cout << ">>> ";
                    cin >> newName;
                    //Enter Price
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    text("Enter Price:", width, LEFT);
                    Line('=', width - 2);
                    newPrice = getInt(">>", newPriceS);
                    //Enter Stack
                    clearScreen();
                    Header("New Product");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                    text("Enter Stack:", width, LEFT);
                    Line('=', width - 2);
                    newStack = getInt(">>", newStackS);
                    //Push all Contents 
                    Prod.push_back(newName);
                    Price.push_back(newPrice);
                    Stack.push_back(newStack);
                    //Display New Product
                    clearScreen();
                    Header("Product Added");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                }
                //Delete Product Interface
                if(set2==4)
                {
                	
                	clearScreen();
                    Header("Delete Product");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    Del = getInt(">>", DelS);
                    if(Del>Prod.size())
                    {
                    clearScreen();
                    Header("Delete Product");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    Del = getInt("Index not match>>", DelS);
                    }
                    Prod.erase(Prod.begin()+Del);
                    Stack.erase(Stack.begin()+Del);
                    Price.erase(Price.begin()+Del);
                    clearScreen();
                    Header("Succsefully Deleted");
                }
                //Ask Continuity
                text("Back to Main Menu?",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"1 = Continue Inventory");
                Line('=', width - 2);
               int t = getInt(">>", tS);
                if (t == 0) {
                    Con = 1;
                }

            } // END INVENTORY LOOP

        } // END set==1057 block
        
        
        // ============================
        // ORDER SYSTEM DISPLAY
        // ============================
        if (set == 2) {

            int tap = 0;
            vector<Product> em;
            while (true) {
            	
                Product Que;
                int totalP = 0;
                sugar = 0;
                string pickS;
                string tS;
                string qtyS;
                string sugarS;
                string aqS;
                string tapS;
                //Order Menu Interface
                clearScreen();
                Header("Order Menu");
                text("Product:",width,DUAL_ALIGN,0,"Price:");
                Home(Prod,Price,marker,width);
                text("Chose order", width, CENTER);
                Line('=', width - 2);
                int pick = getInt(">>", pickS)-1;
                //Input Validation
                while (pick >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose order", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                    pick = getInt(">>", pickS)-1;
                }
                //Push all input vector
                Que.product = Prod[pick];
                Que.productValue = Price[pick];
                Que.stack = Stack[pick];
                //Display if Product is Out of Stock
                if(Stack[pick]==0){
                    clearScreen();
                    Header("Product needs restock");
                    text("Ask admin to restock",width,CENTER);
                    Line('=', width - 2);
                    marker[pick]=" <Not Available>";
                    text("Back to Interface",width,LEFT);
                     text("*note your order will be cancel",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"Any number= Order Other");
                Line('=', width - 2);
                //Backer
               int t = getInt(">>", tS);
                if (t == 0) {
                    break;
                }
                	continue;
                }
                //Product Attributes Display
                //Quantity  Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                Que.quantity = getInt("How many (Max. "+to_string(Que.stack)+")?>> ", qtyS);
                //input Validation
                while (Que.quantity >Que.stack) {
                    Que.quantity=0;
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    Que.quantity = getInt("How many (Max. "+to_string(Que.stack)+")?>> ", qtyS);
                }
                //Update Stocks
                Stack[pick] = Stack[pick] - Que.quantity;
                //Sugar Level Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                sugar = getInt("Sugar Levels?>> ", sugarS);
                //input Validation
                while (sugar > 100) {
                    clearScreen();
                    sugar=0;
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    sugar = getInt("Sugar Levels?>> ", sugarS);
                }
                //Addon Picking
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);

                cout << "Enter Addon Name>> ";
                getline(cin, Que.addon);
                bool ch2 = lookSt(A, 13, Que.addon);
                //I/O Exeption
                while (!ch2) {
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Enter Addon Name>> ";
                    getline(cin, Que.addon);
                    ch2 = lookSt(A, 13, Que.addon);
                }
                //Addon Quantity 
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                Que.addonQuant = getInt("Addon Quantity For Each Order (Max *4)>> ", aqS);
                ///IO exception
                while (Que.addonQuant > 4 || Que.addonQuant == 0) {
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    Que.addonQuant = getInt("Addon Quantity Max *4>> ", aqS);
                }
                //Addon Value Assignement
                if (Que.addon == "Cookies" || Que.addon == "cookies" || Que.addon == "COOKIES")
                    Que.addonValue = 3;

                if (Que.addon == "Sprinkler" || Que.addon == "sprinkler" || Que.addon == "SPRINKLER")
                    Que.addonValue = 2;

                if (Que.addon == "Ice cream" || Que.addon == "ICE CREAM" || Que.addon == "Ice Cream")
                    Que.addonValue = 3;

                if (Que.addon == "Peanuts" || Que.addon == "peanuts" || Que.addon == "PEANUTS")
                    Que.addonValue = 2;
                //Push all contents of Que
                em.push_back(Que);
                //Transaction Continuity Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                tap = getInt("Want another order?\n(press 1 to continue or 0 to pay)>> ", tapS);
                //Reciept Display
                if (tap == 0) {
                    clearScreen();
                    Header("Reciept");
                    //Display Every Products Overall Details,Price,and Addon Price

                    for (size_t i = 0; i < em.size(); i++) {
                        em[i].productValue *= em[i].quantity;
                        int t =em[i].addonQuant*em[i].quantity;
                        em[i].addonValue *= t;
                        int total = em[i].productValue + em[i].addonValue;

                        text(em[i].product, width, DUAL_ALIGN, 0, "$" + to_string(em[i].productValue));
                        text("   " + to_string(em[i].quantity) + "pcs", width, LEFT);

                        text("Addons ", width, DUAL_ALIGN, 0, "$" + to_string(em[i].addonValue));
                        text("   " + to_string(em[i].addonQuant) + " pcs. each order", width, LEFT);
                        
                        text("Total", width, DUAL_ALIGN, 0, "$" + to_string(total));
                        totalP += total;
                        Line('=', width - 2);
                    }
                    text("Bills", width, DUAL_ALIGN, 0, "$" + to_string(totalP));
                    Line('=', width - 2);
                    text("Please Proceeds to Counter", width, CENTER);
                    text("Return Menu in 10 sec", width, CENTER);
                    Line('=', width - 2);
                    //stop for 10 sec
                    this_thread::sleep_for(chrono::milliseconds(10000));
                   
                    em.clear();
                    break;
                }
                
            } // end transaction loop
          

        } // end order system
        //save data into file
        saveDat(Stack, Price, Prod, marker);
        clearScreen();

    } // end outer program loop

}
    vector<int> Price = {40,40,45,45,50};
    // Default product names
    vector<string> Prod = {
        "Classic Choco",
        "Rocky Road",
        "Creamy Vanilla",
        "Tropical Mango",
        "Caramel Delight"
    };
    // Valid addon names (different capitalizations)
    string A[13] = {
        "Sprinkler", "SPRINKLER", "sprinkler",
        "COOKIES", "Cookies", "cookies",
        "ICE cream", "ICE CREAM", "Ice cream", "Ice Cream",
        "Peanuts", "PEANUTS", "peanuts"
    };
    // Product structure for order processing
    struct Product {
        int addonValue, addonQuant, productValue;
        int quantity{0};
        int stack;
        string addon, product;
    };
    loadDat(Stack,Price,Prod,marker);
    // ============================
    // Main program loop
    // ============================

    while (true) {

        int set = 0;
        int enl;
        int enl2;
        int Con = 0;
        // Main menu
        Header("Frozen MilkShake Shop");
        text("Choose System To Operate", width, CENTER);
        Line('=', width - 2);
        text("1. Inventory System <Type 4-digit pin instead>", width, LEFT);
        text("2. Order System", width, LEFT);
        Line('=', width - 2);
        string setS;
        set = getInt(">> ", setS);

        // ============================
        // INVENTORY SYSTEM (PIN 1057)
        // ============================

        if (set == 1057) {

            // Return to main menu
            while (Con == 0) {
            	
                clearScreen();
                Header("Inventory System");
                text("1.) Add stacks", width, LEFT);
                text("2.) Change price", width, LEFT);
                text("3.) Add product", width, LEFT);
                text("4.) Delete product", width, LEFT);
                text("0.) Back to Main Menu", width, LEFT);
                Line('=', width - 2);
                int set2;
               string set2S;
               set2 = getInt(">> ", set2S);
               // Return to main menu
                if (set2 == 0) {  
                    Con = 1;
                    continue;
                }
                
                // ============================
                // Add stacks
                // ============================
                if (set2 == 1) {
                
                    clearScreen();
                	
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                   string enlS;
                   enl = getInt(">> ", enlS)-1;
                	
                   // Input validation
                	while (enl >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                    enl = getInt(">> ", enlS)-1;
                }

                    // Ask add quantity
                    clearScreen();
                    Header("Add stacks");
                    text("Product:",width,DUAL_ALIGN,0,"Stack:");
                    Home(Prod,Stack,marker,width);
                    text("Quantity", width, CENTER);
                    Line('=', width - 2);
                   string enl2S;
                   enl2 = getInt(">> ", enl2S);
                    clearScreen();
                    Stack[enl] += enl2;
                   // Remove marker if restocked
                   if(Stack[enl]>=1){
                        marker[enl]="";
                    }
                    Header("Stack: " + to_string(Stack[enl]));
                }

                // ============================
                // Change price
                // ============================
                if (set2 == 2) {
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    string enlS;
                   enl = getInt(">> ", enlS)-1;
                    // Input validation
                   while (enl >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose order", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                    enl = getInt(">> ", enlS)-1;
                }
                    clearScreen();
                    Header("Change Price");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Price", width, CENTER);
                    Line('=', width - 2);
                    string enl2S;
                    enl2 = getInt(">> ", enl2S);
                    Price[enl] = enl2;
                   clearScreen();
                    Header("Price: " + to_string(Price[enl]));
                }

                // ============================
                // Add new product
                // ============================
                if(set2 == 3){
                    clearScreen();
                    Header("Add Product");

                    string newName{""};
                    int newPrice{0};
                    int newStack{0};
                    // Enter name
                    clearScreen();
                    Header("New Product");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    text("Enter Product Name:", width, LEFT);
                    Line('=', width - 2);
                    cout << ">>> ";
                    cin >> newName;
                    //Enter Price
                    clearScreen();
                    Header("New Product");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                    text("Enter Price:", width, LEFT);
                    Line('=', width - 2);
                    string newPriceS;
                    newPrice = getInt(">>", newPriceS);
                    //Enter Stack
                    clearScreen();
                    Header("New Product");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                    text("Enter Stack:", width, LEFT);
                    Line('=', width - 2);
                    string newStackS;
                    newStack = getInt(">>", newStackS);
                    //Push all Contents 
                    Prod.push_back(newName);
                    Price.push_back(newPrice);
                    Stack.push_back(newStack);
                    //Display New Product
                    clearScreen();
                    Header("Product Added");

                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: "+ to_string(newStack), width, LEFT);

                    Line('=', width - 2);
                }
                //Delete Product
                if(set2==4)
                {
                	int Del;
                	clearScreen();
                    Header("Delete Product");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    string DelS;
                    Del = getInt(">>", DelS);
                    if(Del>Prod.size())
                    {
                    clearScreen();
                    Header("Delete Product");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose products", width, CENTER);
                    Line('=', width - 2);
                    Del = getInt("Index not match>>", DelS);
                    }
                    Prod.erase(Prod.begin()+Del);
                    Stack.erase(Stack.begin()+Del);
                    Price.erase(Price.begin()+Del);
                    clearScreen();
                    Header("Succsefully Deleted");
                }
                //Ask Continuity
                text("Back to Main Menu?",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"1 = Continue Inventory");
                Line('=', width - 2);
                string tS;
               int t = getInt(">>", tS);
                if (t == 0) {
                    Con = 1;
                }

            } // END INVENTORY LOOP

        } // END set==1057 block
        
        
        // ============================
        // ORDER SYSTEM
        // ============================
        if (set == 2) {

            int tap = 0;
            vector<Product> em;
            
            while (true) {
            	
                Product Que;
                int totalP = 0;
                sugar = 0;
                //Order Menu
                clearScreen();
                Header("Order Menu");
                text("Product:",width,DUAL_ALIGN,0,"Price:");
                Home(Prod,Price,marker,width);
                text("Chose order", width, CENTER);
                Line('=', width - 2);
                string pickS;
                int pick = getInt(">>", pickS)-1;
                //Input Validation
                while (pick >= Prod.size()) {
                    clearScreen();
                    Header("Order Menu");
                    text("Product:",width,DUAL_ALIGN,0,"Price:");
                    Home(Prod,Price,marker,width);
                    text("Chose order", width, CENTER);
                    Line('=', width - 2);
                    cout << "Invalid Try again>> ";
                    pick = getInt(">>", pickS)-1;
                }
                //Push all input vector
                Que.product = Prod[pick];
                Que.productValue = Price[pick];
                Que.stack = Stack[pick];
                //Display if Product is Out of Stock
                if(Stack[pick]==0){
                    clearScreen();
                    Header("Product needs restock");
                    text("Ask admin to restock",width,CENTER);
                    Line('=', width - 2);
                    marker[pick]=" <Not Available>";
                    text("Back to Interface",width,LEFT);
                     text("*note your order will be cancel",width,LEFT);
                text("0 = Yes",width,DUAL_ALIGN,0,"1 = Order Other");
                Line('=', width - 2);
                //Backer
                string tS;
               int t = getInt(">>", tS);
                if (t == 0) {
                    break;
                }
                if(t==1){
                	continue;
                	}
                }
                
                //Quantity  Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                string qtyS;
                Que.quantity = getInt("How many (Max. "+to_string(Que.stack)+")?>> ", qtyS);
                //input Validation
                while (Que.quantity >Que.stack) {
                    Que.quantity=0;
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    Que.quantity = getInt("How many (Max. "+to_string(Que.stack)+")?>> ", qtyS);
                }
                //Update Stocks
                Stack[pick] = Stack[pick] - Que.quantity;
                //Sugar Level Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                string sugarS;
                sugar = getInt("Sugar Levels?>> ", sugarS);
                //input Validation
                while (sugar > 100) {
                    clearScreen();
                    sugar=0;
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    sugar = getInt("Sugar Levels?>> ", sugarS);
                }
                //Addon Picking
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);

                cout << "Pick Addon>> ";
                getline(cin, Que.addon);
                bool ch2 = lookSt(A, 13, Que.addon);
                //input Validation
                while (!ch2) {
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Pick Addon>> ";
                    getline(cin, Que.addon);
                    ch2 = lookSt(A, 13, Que.addon);
                }
                //Addon Qunatity Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                string aqS;
                Que.addonQuant = getInt("Addon Quantity For Each Order (Max *4)>> ", aqS);
                //input Validation
                while (Que.addonQuant > 4 || Que.addonQuant == 0) {
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    cout << "Invalid Input";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    Que.addonQuant = getInt("Addon Quantity Max *4>> ", aqS);
                }
                //Addon Value Assignement
                if (Que.addon == "Cookies" || Que.addon == "cookies" || Que.addon == "COOKIES")
                    Que.addonValue = 3;

                if (Que.addon == "Sprinkler" || Que.addon == "sprinkler" || Que.addon == "SPRINKLER")
                    Que.addonValue = 2;

                if (Que.addon == "Ice cream" || Que.addon == "ICE CREAM" || Que.addon == "Ice Cream")
                    Que.addonValue = 3;

                if (Que.addon == "Peanuts" || Que.addon == "peanuts" || Que.addon == "PEANUTS")
                    Que.addonValue = 2;
                //Push all contents of Que
                em.push_back(Que);
                //Transaction Continuity Display
                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                string tapS;
                tap = getInt("Want another order?\n(press 1 to continue or 0 to pay)>> ", tapS);
                //Reciept Display
                if (tap == 0) {
                    clearScreen();
                    Header("Reciept");

                    for (size_t i = 0; i < em.size(); i++) {
                        em[i].productValue *= em[i].quantity;
                        int t =em[i].addonQuant*em[i].quantity;
                        em[i].addonValue *= t;
                        int total = em[i].productValue + em[i].addonValue;

                        text(em[i].product, width, DUAL_ALIGN, 0, "$" + to_string(em[i].productValue));
                        text("   " + to_string(em[i].quantity) + "pcs", width, LEFT);

                        text("Addons ", width, DUAL_ALIGN, 0, "$" + to_string(em[i].addonValue));
                        text("   " + to_string(em[i].addonQuant) + " pcs. each order", width, LEFT);

                        text("Total", width, DUAL_ALIGN, 0, "$" + to_string(total));
                        totalP += total;
                        Line('=', width - 2);
                    }
                    text("Bills", width, DUAL_ALIGN, 0, "$" + to_string(totalP));
                    Line('=', width - 2);
                    text("Please Proceeds to Counter", width, CENTER);
                    text("Return Menu in 10 sec", width, CENTER);
                    Line('=', width - 2);

                    this_thread::sleep_for(chrono::milliseconds(10000));

                    em.clear();
                    break;
                }
                
            } // end transaction loop
          

        } // end order system
        saveDat(Stack, Price, Prod, marker);
        clearScreen();

    } // end outer program loop

}
