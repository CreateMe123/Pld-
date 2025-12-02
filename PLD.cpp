#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

int findwidth() {
    return 50;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

enum Alignment {
    LEFT,
    CENTER,
    DUAL_ALIGN
};

static string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

void text(const std::string& textStr, int width, Alignment mode = LEFT, int offset = 0, const std::string& rightText = "") {
    int innerWidth = width - 4;
    if (innerWidth < 0) innerWidth = 0;
    std::string line(innerWidth, ' ');

    switch (mode) {
        case LEFT:
            if ((int)textStr.size() <= innerWidth)
                line.replace(0, textStr.size(), textStr);
            else
                line.replace(0, innerWidth, textStr.substr(0, innerWidth));
            break;
        case CENTER: {
            int start = max(0, (innerWidth - (int)textStr.size()) / 2);
            if (start + (int)textStr.size() <= innerWidth)
                line.replace(start, textStr.size(), textStr);
            else
                line.replace(start, innerWidth - start, textStr.substr(0, innerWidth - start));
            break;
        }
        case DUAL_ALIGN: {
            int leftLen = min((int)textStr.size(), innerWidth);
            line.replace(0, leftLen, textStr.substr(0, leftLen));
            int rightLen = (int)rightText.size();
            int rightStart = innerWidth - rightLen;
            if (rightStart > leftLen)
                line.replace(rightStart, rightLen, rightText);
            break;
        }
    }

    cout << "| " << line << " |" << endl;
}

bool isIntString(const string& s) {
    string t = trim(s);
    if (t.empty()) return false;
    size_t i = 0;
    if (t[0] == '+' || t[0] == '-') i = 1;
    if (i >= t.size()) return false;
    for (; i < t.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(t[i]))) return false;
    }
    return true;
}

int getInt(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        if (!std::getline(cin, line)) { // handle EOF gracefully
            cin.clear();
            line = "";
        }
        if (isIntString(line)) {
            try {
                long long v = stoll(trim(line));
                // clamp to int range
                if (v > numeric_limits<int>::max()) v = numeric_limits<int>::max();
                if (v < numeric_limits<int>::min()) v = numeric_limits<int>::min();
                return static_cast<int>(v);
            } catch (...) {
                // fallthrough to ask again
            }
        }
        cout << "Invalid input. Numbers only. Try again.\n";
    }
}

bool lookSt(const string arr[], int size, const string& target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) return true;
    }
    return false;
}

// save/load
void saveDat(const vector<int>& Stack,
             const vector<int>& Price,
             const vector<string>& Prod,
             const vector<string>& marker)
{
    ofstream file("inventory.dat");
    if (!file) return;

    file << Prod.size() << "\n";
    for (size_t i = 0; i < Prod.size(); ++i) {
        file << Prod[i] << "\n";
        file << Price[i] << "\n";
        file << Stack[i] << "\n";
        file << marker[i] << "\n";
    }
}

void loadDat(vector<int>& Stack,
             vector<int>& Price,
             vector<string>& Prod,
             vector<string>& marker)
{
    ifstream file("inventory.dat");
    if (!file) return;

    int count = 0;
    if (!(file >> count)) return;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    Prod.clear();
    Price.clear();
    Stack.clear();
    marker.clear();

    for (int i = 0; i < count; ++i) {
        string name;
        if (!getline(file, name)) name = "Unknown";

        int price = 0;
        if (!(file >> price)) price = 0;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        int stock = 0;
        if (!(file >> stock)) stock = 0;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        string mark;
        if (!getline(file, mark)) mark = "";

        Prod.push_back(name);
        Price.push_back(price);
        Stack.push_back(stock);
        marker.push_back(mark);
    }

    for (size_t i = 0; i < Stack.size(); ++i) {
        if (Stack[i] <= 0) marker[i] = " <Not Available>";
        // ensure marker vector length matches
    }
}

void Line(char edge = '=', int width = 50) {
    if (width < 0) width = 0;
    cout << "+" << string(width, edge) << "+" << endl;
}

void Home(const vector<string>& Prod, const vector<int>& Price, const vector<string>& marker, int width) {
    for (size_t b = 0; b < Prod.size(); ++b) {
        string price = (b < Price.size()) ? to_string(Price[b]) : "0";
        string mark = (b < marker.size()) ? marker[b] : "";
        text(to_string(b + 1) + ". " + Prod[b] + mark, width, DUAL_ALIGN, 0, price);
    }
    Line('=', width - 2);
}

void Header(const string& title) {
    int width = findwidth();
    if (width < 30) width = 30;
    Line('=', width - 2);
    text(title, width, CENTER);
    Line('=', width - 2);
}

void order(int productquant, int sugar) {
    int width = findwidth();
    string P = to_string(productquant);
    string S = to_string(sugar);
    text("Quantity", width, DUAL_ALIGN, 0, "*" + P);
    text("Sugar Level(%)", width, DUAL_ALIGN, 0, S + "%");
    text("Addons:", width, LEFT);
    text(" Cookies", width, DUAL_ALIGN, 0, "$3");
    text(" Sprinkler", width, DUAL_ALIGN, 0, "$2");
    text(" Ice Cream", width, DUAL_ALIGN, 0, "$3");
    text(" Peanuts", width, DUAL_ALIGN, 0, "$2");
    Line('=', width - 2);
}

struct Product {
    int addonValue{0};
    int addonQuant{0};
    int productValue{0};
    int quantity{0};
    int stack{0};
    string addon;
    string product;
};

int main() {
    int width = findwidth();

    vector<string> marker = {"", "", "", "", ""};
    vector<int> Stack = {15, 20, 19, 20, 56};
    vector<int> Price = {40, 40, 45, 45, 50};
    vector<string> Prod = {"Classic Choco", "Rocky Road", "Creamy Vanilla", "Tropical Mango", "Caramel Delight"};

    string A[13] = {
        "Sprinkler", "SPRINKLER", "sprinkler",
        "COOKIES", "Cookies", "cookies",
        "ICE cream", "ICE CREAM", "Ice cream", "Ice Cream",
        "Peanuts", "PEANUTS", "peanuts"
    };

    // load saved data (if any)
    loadDat(Stack, Price, Prod, marker);

    while (true) {
        int set = 0;
        clearScreen();
        Header("Frozen MilkShake Shop");
        text("Choose System To Operate", width, CENTER);
        Line('=', width - 2);
        text("1. Inventory System <Type 4-digit pin instead>", width, LEFT);
        text("2. Order System", width, LEFT);
        Line('=', width - 2);

        set = getInt(">> ");

        // Inventory (PIN 1057)
        if (set == 1057) {
            bool backToMain = false;
            int set2;
            int idx;
            int addQty;
            int cont;
            int newPrice;
            int Del;
            int newStack;
            while (!backToMain) {
                clearScreen();
                Header("Inventory System");
                text("1.) Add stacks", width, LEFT);
                text("2.) Change price", width, LEFT);
                text("3.) Add product", width, LEFT);
                text("4.) Delete product", width, LEFT);
                text("0.) Back to Main Menu", width, LEFT);
                Line('=', width - 2);

                set2 = getInt(">> ");
                while (set2 < 0 || set2 > 4) {
                    set2 = getInt("Invalid. Enter 0-4 >> ");
                }

                if (set2 == 0) { backToMain = true; continue; }

                if (set2 == 1) { // Add stacks
                    if (Prod.empty()) {
                        clearScreen();
                        Header("No products available to restock.");
                        this_thread::sleep_for(chrono::milliseconds(3200));
                        continue;
                    }
                    clearScreen();
                    Header("Add stacks");
                    text("Product:", width, DUAL_ALIGN, 0, "Stack:");
                    Home(Prod, Stack, marker, width);
                    text("Choose product number:", width, CENTER);
                    Line('=', width - 2);

                    idx = getInt(">> ") - 1;
                    while (idx < 0 || idx >= (int)Prod.size()) {
                        idx = getInt("Invalid. Try again >> ") - 1;
                    }

                    addQty = getInt("Add how many? >> ");
                    while (addQty < 0) addQty = getInt("Invalid. Enter non-negative number >> ");

                    Stack[idx] += addQty;
                    if (Stack[idx] > 0) marker[idx] = "";

                    clearScreen();
                    Header("Stack Updated");
                    text(Prod[idx], width, LEFT);
                    text("New Stack: " + to_string(Stack[idx]), width, LEFT);
                    Line('=', width - 2);
                    
                }

                if (set2 == 2) { // Change price
                    if (Prod.empty()) {
                        clearScreen();
                        Header("No products to change price.");
                        continue;
                    }
                    clearScreen();
                    Header("Change Price");
                    text("Product:", width, DUAL_ALIGN, 0, "Price:");
                    Home(Prod, Price, marker, width);
                    text("Choose product number:", width, CENTER);
                    Line('=', width - 2);

                    idx = getInt(">> ") - 1;
                    while (idx < 0 || idx >= (int)Prod.size()) {
                        idx = getInt("Invalid. Try again >> ") - 1;
                    }

                    newPrice = getInt("Enter new price >> ");
                    while (newPrice < 0) newPrice = getInt("Invalid. Enter non-negative price >> ");

                    Price[idx] = newPrice;
                    clearScreen();
                    Header("Price Updated");
                    text(Prod[idx], width, LEFT);
                    text("New Price: " + to_string(Price[idx]), width, LEFT);
                    Line('=', width - 2);
                    this_thread::sleep_for(chrono::milliseconds(900));
                }

                if (set2 == 3) { // Add product
                    clearScreen();
                    Header("New Product Name");
                    string newName;
                    //input validation
                    while (true) {
                        cout << "Enter product name: ";
                        if (!getline(cin, newName)) newName = "";
                        newName = trim(newName);
                        if (!newName.empty()) break;
                        cout << "Name cannot be empty.\n";
                    }

                    newPrice = getInt("Enter price >> ");
                    while (newPrice < 0) newPrice = getInt("Invalid. Enter non-negative price >> ");

                    newStack = getInt("Enter initial stack >> ");
                    while (newStack < 0) newStack = getInt("Invalid. Enter non-negative stack >> ");

                    Prod.push_back(newName);
                    Price.push_back(newPrice);
                    Stack.push_back(newStack);
                    marker.push_back(newStack > 0 ? "" : " <Not Available>");

                    clearScreen();
                    Header("Product Added");
                    text("Name: " + newName, width, LEFT);
                    text("Price: " + to_string(newPrice), width, LEFT);
                    text("Stack: " + to_string(newStack), width, LEFT);
                    Line('=', width - 2);
                    this_thread::sleep_for(chrono::milliseconds(900));
                }

                if (set2 == 4) { // Delete product
                    //If no Product Exist
                    if (Prod.empty()) {
                        clearScreen();
                        Header("No products to delete.");
                        this_thread::sleep_for(chrono::milliseconds(3200));
                        continue;
                    }
                    clearScreen();
                    Header("Delete Product");
                    text("Product:", width, DUAL_ALIGN, 0, "Price:");
                    Home(Prod, Price, marker, width);
                    text("Choose product number to delete:", width, CENTER);
                    Line('=', width - 2);

                     Del= getInt(">> ") - 1;
                    while (Del < 0 || Del >= (int)Prod.size()) {
                        Del = getInt("Index not match. Try again >> ") - 1;
                    }

                    string deletedName = Prod[Del];
                    Prod.erase(Prod.begin() + Del);
                    Stack.erase(Stack.begin() + Del);
                    Price.erase(Price.begin() + Del);
                    marker.erase(marker.begin() + Del);

                    clearScreen();
                    Header("Successfully Deleted");
                    text("Deleted: " + deletedName, width, LEFT);
                    Line('=', width - 2);
                    this_thread::sleep_for(chrono::milliseconds(2000));
                }

                // continuity prompt
                clearScreen();
                Header("Inventory Menu");
                text("Back to Main Menu? (1 = Yes, 0 = Continue Inventory)", width, CENTER);
                Line('=', width - 2);
                cont = getInt(">> ");
                while (cont != 0 && cont != 1) cont = getInt("Enter 1 or 0 >> ");
                if (cont == 1) backToMain = true;
            }
        } // end inventory

        // Order system
        if (set == 2) {
            vector<Product> em;
            while (true) {
                string dummy;
                int qty;
                int pick;
                int aq;
                int sugar;
                int grandTotal = 0;
                int wantAddon;
                string addonName;
                if (Prod.empty()) {
                    clearScreen();
                    Header("No products available.");
                    this_thread::sleep_for(chrono::milliseconds(900));
                    break;
                }

                clearScreen();
                Header("Order Menu");
                text("Product:", width, DUAL_ALIGN, 0, "Price:");
                Line('=', width - 2);
                Home(Prod, Price, marker, width);
                text("Choose order (product number):", width, CENTER);
                Line('=', width - 2);

                pick = getInt(">> ") - 1;
                while (pick < 0 || pick >= (int)Prod.size()) {
                    pick = getInt("Invalid. Try again >> ") - 1;
                }

                Product Que;
                Que.product = Prod[pick];
                Que.productValue = Price[pick];
                Que.stack = (pick < (int)Stack.size()) ? Stack[pick] : 0;

                if (Que.stack <= 0) {
                    clearScreen();
                    Header("Product needs restock");
                    text("Ask admin to restock", width, CENTER);
                    Line('=', width - 2);
                    if (pick < (int)marker.size()) marker[pick] = " <Not Available>";
                    text("Press Enter to continue...", width, CENTER);
                    Line('=', width - 2);
                    getline(cin, dummy);
                    continue;
                }

                clearScreen();
                Header(Que.product);
                order(Que.quantity, 0);
                qty = getInt("How many (Max. " + to_string(Que.stack) + ")? >> ");
                while (qty < 1 || qty > Que.stack) {
                    qty = getInt("Invalid. Enter 1.." + to_string(Que.stack) + " >> ");
                }
                Que.quantity = qty;

                // reduce stocks immediately (persist in memory for session)
                Stack[pick] -= Que.quantity;
                if (pick < (int)marker.size() && Stack[pick] <= 0) marker[pick] = " <Not Available>";

                clearScreen();
                Header(Que.product);
                order(Que.quantity, 0);
                sugar = getInt("Sugar Levels (0-100)? >> ");
                while (sugar < 0 || sugar > 100) sugar = getInt("Invalid. Enter 0-100 >> ");

                clearScreen();
                Header(Que.product);
                order(Que.quantity, sugar);
                text("You want Addons? 1 = Yes, 0 = No", width, CENTER);
                Line('=', width - 2);
                
                wantAddon = getInt(">> ");
                while (wantAddon != 0 && wantAddon != 1) wantAddon = getInt("Enter 1 or 0 >> ");

                if (wantAddon == 1) {
                    clearScreen();
                    Header(Que.product);
                    order(Que.quantity, sugar);
                    string addonName;
                    cout << "Enter Addon Name >> ";
                    getline(cin, addonName);
                    addonName = trim(addonName);

                    // Validate against allowed list (case-sensitive variants preserved)
                    bool ok = lookSt(A, 13, addonName);
                    while (!ok) {
                        cout << "Invalid addon. Try again >> ";
                        if (!getline(cin, addonName)) addonName = "";
                        addonName = trim(addonName);
                        ok = lookSt(A, 13, addonName);
                    }

                    Que.addon = addonName;

                    aq = getInt("Addon Quantity For Each Order (Max 4) >> ");
                    while (aq < 0 || aq > 4) aq = getInt("Invalid. Enter 0..4 >> ");
                    Que.addonQuant = aq;

                    // assign addonValue using case-insensitive comparison
                    
                    transform(addonName.begin(), addonName.end(), addonName.begin(), ::tolower);
                    if (addonName.find("cookies") != string::npos) Que.addonValue = 3;
                    else if (addonName.find("sprinkler") != string::npos) Que.addonValue = 2;
                    else if (addonName.find("ice") != string::npos && addonName.find("cream") != string::npos) Que.addonValue = 3;
                    else if (addonName.find("peanuts") != string::npos) Que.addonValue = 2;
                    else Que.addonValue = 0;
                }

                em.push_back(Que);

                // continue or pay
                clearScreen();
                Header("Order Summary");
                text("Want another order? 1 = Yes, 0 = Pay", width, CENTER);
                Line('=', width - 2);
                int tap;
                tap = getInt(">> ");
                while (tap != 0 && tap != 1) tap = getInt("Enter 1 or 0 >> ");
                if (tap == 1) continue;

                // Receipt: compute totals without mutating em entries
                clearScreen();
                Header("Receipt");
                for (size_t i = 0; i < em.size(); ++i) {
                    int prodTotal = em[i].productValue * em[i].quantity;
                    int addonsQtyTotal = em[i].addonQuant * em[i].quantity;
                    int addonTotal = em[i].addonValue * addonsQtyTotal;
                    int total = prodTotal + addonTotal;
                    grandTotal += total;

                    text(em[i].product, width, DUAL_ALIGN, 0, "$" + to_string(prodTotal));
                    text("   " + to_string(em[i].quantity) + " pcs", width, LEFT);

                    text("Addons ", width, DUAL_ALIGN, 0, "$" + to_string(addonTotal));
                    text("   " + to_string(em[i].addonQuant) + " pcs each order", width, LEFT);

                    text("Total", width, DUAL_ALIGN, 0, "$" + to_string(total));
                    Line('=', width - 2);
                }

                text("Bills", width, DUAL_ALIGN, 0, "$" + to_string(grandTotal));
                Line('=', width - 2);
                text("Please proceed to counter", width, CENTER);
                text("Returning to menu in 10 seconds...", width, CENTER);
                Line('=', width - 2);

                this_thread::sleep_for(chrono::milliseconds(10000));
                em.clear();
                break;
            } // end order inner loop
        } // end order system

        // Save data after each top-level action
        saveDat(Stack, Price, Prod, marker);
    } // end main loop

    return 0;
}
