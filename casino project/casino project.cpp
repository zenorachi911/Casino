#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//Реализовать класс Menu
//system("cls") - для обновления текста в консоли
// Узнать имя пользователя, который будет играть

class Menu;

class Chips 
{
private:
    friend Menu;
   enum chipses
    {
        white = 1,
        red = 5,
        blue = 10,
        green = 25,
        black = 100,
        purple = 500,
        orange = 1000
    };

    int moneys;

    int quantity;

    vector<pair<string, int>> chipscol{}; 

    int col;

    string moneysleft;

public:

    int Getmoneys()
    {
        return this->moneys;
    }

    int chipschange() {
        cin >> moneys;

        if (moneys <= 0) {
            cout << "Fuck the casino, scammer";
            return 0;
        }
        else if (moneys > INT_MAX) {
            cout << "You don't have that kind of money";
            return 0;
        }

        cout << "white - " << white << endl;
        cout << "red - " << red << endl;
        cout << "blue - " << blue << endl;
        cout << "green - " << green << endl;
        cout << "black - " << black << endl;
        cout << "purple - " << purple << endl;
        cout << "orange - " << orange << endl;

        while (moneys != 0) {

            cout << "Enter the quantity and type of chips" << endl;

            cin >> col >> moneysleft;

            if (col <= 0) {
                cout << "incorrect quantity" << endl;
                continue;
            }

            if (moneysleft == "white" || moneysleft == "red" || moneysleft == "blue" ||
                moneysleft == "green" || moneysleft == "black" || moneysleft == "purple" ||
                moneysleft == "orange") {
                if (moneys >= getValue(moneysleft) * col) {
                    moneys -= getValue(moneysleft) * col;
                    bool found = false;
                    
                    for (auto& chip : chipscol) {
                        if (chip.first == moneysleft) {
                            chip.second += col; 
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        chipscol.push_back({ moneysleft, col }); 
                    }
                }
                else {
                    cout << "You can't do that" << endl;
                }
            }
            else {
                cout << "Unknown chip name" << endl;
            }

            cout << "Your remaining moneys - " << moneys << endl;
        }

        cout << "Chip distribution completed" << endl;

        sort(chipscol.begin(), chipscol.end(), [](auto& a, auto& b) { return a.second > b.second; });

        return 0;
    }

    void GetChips() {
        for (const auto& chip : chipscol) {
            cout << chip.first << " " << chip.second << endl;
        }
    }

    private: int getValue(const string& chipType);

};

int Chips::getValue(const string& chipType) {
    if (chipType == "white") return white;
    else if (chipType == "red") return red;
    else if (chipType == "blue") return blue;
    else if (chipType == "green") return green;
    else if (chipType == "black") return black;
    else if (chipType == "purple") return purple;
    else if (chipType == "orange") return orange;
    else return 0;
}
//Надо сделать обновялемый текст в консоли
//Сделать Блэкджэк и рулетку
// Реализовать приветсиве в этих играх

class Menu
{
private:
    int choise;

public:
    int menu(Chips &chips)
    {

        if (chips.chipscol.empty())
        {
            cout << "See you soon" << endl;
            return 0;
            
        }

        cout << "What game do you want to play?\n";
        
        

        cout << "\t\t\t-------------------------------------\n"
            "\t\t\t| 1. Roulette(in development)       |\n"
            "\t\t\t| 2. Black Jack(in development)     |\n"
            "\t\t\t| 3. Exit                           |\n"
            "\t\t\t-------------------------------------\n";
        
        cin >> choise;

        switch (choise)
        {
        case(1):
        {

        }
        case(2):
        {

        }
        case(3):
        {
            /*cout << "See you soon" << endl;
            return 0;
            system("cls");*/
        }
        default:
        {
            cout << "Unknown command" << endl;
        }
        }

    }
};

int main() {
    setlocale(LC_ALL, "RU");

    cout << "Welcome to the casino! " << endl;

    cout << "How much do you want to exchange for chips?" << endl;
    
    Menu console;

    Chips casino;


    casino.chipschange();

    console.menu(casino);
    
    string chipbalance;
    cin >> chipbalance;

    if (chipbalance == "balance") {
        casino.GetChips();
        cout << endl;
    }
    
   
    return 0;
}