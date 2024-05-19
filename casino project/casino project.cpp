#include "header.h"

class Roulette;

class Games;

class Menu;

class Bets;

class Chips
{
private:
    friend Roulette;
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

    int col;

    string moneysleft;


protected:
    vector<pair<string, int>> chipscol{}; 

public:


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

    int getValue(const string& chipType);

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


class Menu
{
private:
    int choise;
    
    string name;
    
public:
    int menu(Chips& chips, Roulette& a) 
    {
        
        if (chips.chipscol.empty())
        {
            cout << "See you soon" << endl;
            return 0;
            
        }
       
        while (1)
        {

            cout << "What game do you want to play?\n";



            cout << "\t\t\t-------------------------------------\n"
                "\t\t\t| 1. Roulette(in development)       |\n"
                "\t\t\t| 2. Black Jack(in development)     |\n"
                "\t\t\t| 3. Exit                           |\n"
                "\t\t\t-------------------------------------\n";

            cin >> choise;
            system("cls");

            switch (choise)
            {
            case(1):
            {
               
                break;
            }
            case(2):
            {

                break;
            }
            case(3):
            {
                cout << "See you soon" << endl;

                exit(0);
                break;
            }
            default:
            {
                cout << "Unknown command" << endl;
                system("PAUSE");
                system("cls");
            }

            }
        }

    }

    void startmsg()
    { 

        cout << "\t\t\t            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            "\t\t\t           $    wellcome to the casino     $\n"
            "\t\t\t            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";

        cout << "How should I address you?" << endl;

        bool test = true;
       
        while (test)
        {

            cin >> name;

            for (char iter : name)
            {

                if (isalpha(iter))
                {
                    test = false;

                }    
            }
            if (test) 
            {
                cout << "Name, not a phone number" << endl;
                
            }
        }
       
        system("cls");

        cout << name <<" Hello, How much do you want to exchange for chips?" << endl;
    }

};


class Roulette 
{
private:
    
    class Bets
    {
    public:

        void inter()
        {
            cout <<
                " __________________________________________________\n"
                "/                                                  \\\n"
                "|                                                   |\n"
                "|      | 3 6 9 12 |15 18 21 24|27 30 33 36|         |\n"
                "|    0 | 2 5 8 11 |14 17 20 23|26 29 32 35|         |\n"
                "|      | 1 4 7 10 |13 16 19 22|25 28 31 34|         |\n"
                "|   _____________________________________________   |\n"
                "|  |   |  1st 12  |  2nd 12   |   3d 12   |      |  |\n"
                "|  |___|__________|___________|___________|______|  |\n"
                "|  | 1 to 18| EVEN | red | black | ODD | 19 to 36|  |\n"
                "|  |________|______|_____|_______|_____|_________|  |\n"
                "|                                                   |\n"
                "|___________________________________________________|\n"
                "\n";

        }
    };

public:

    void Game(Chips& a)
    {
        
        Bets roulette;
        roulette.inter();

        cout << "Where do you want to put it?" << endl;
        
        short bet;
        short col;
        cin >> col >> bet;
      
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 1);
        
        if (bet == dis(gen))
        {
            cout << "You win!!" << endl;

        }
        else
        {
            cout << "You lose" << endl;
           

           
        }
        cout << dis(gen) << endl;
    }

    
};

int main() 
{
    setlocale(LC_ALL, "RU");

    Roulette a;

    Menu console;

    Chips casino;

    console.startmsg();

    casino.chipschange();

    /*console.menu(casino, a);*/

    a.Game(casino);
    string chipbalance;
    cin >> chipbalance;

    if (chipbalance == "balance") {
        casino.GetChips();
        cout << endl;
    }

    
    
}