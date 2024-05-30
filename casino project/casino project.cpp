#include "header.h"



class Games;

class Menu;

class Bets;

class Roulette;

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

    void GetChips() 
    {
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

class Roulette
{
private:

    friend Menu;

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

    void Game(Chips& chipsvalue)
    {

        Bets roulette;
        roulette.inter();

        short betchoose;

        short bet{};
        string chip;
        
        string betcolor;

        short col;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 36);

        const int res = dis(gen);
            
        cout << "1 - Ставка на любое число" << endl;
        cout << "2 - Ставка на красное / черное" << endl;
        cout << "3 - Сатвка на чет / нечет" << endl;
        cout << "4 - Ставка на ряды" << endl;

        cin >> betchoose;

        cout << "Введите кол-во фишек и ставку" << endl;
        cin >> col >> chip;

        switch (betchoose)
        {

        case (1):
        {

            cout << "Куда хотите поставить?" << endl;
            cin >> bet;

            if (bet == res)
            {
                for (auto& ex : chipsvalue.chipscol)
                {
                    if (ex.first == chip)
                        ex.second *= 35;
 
                }
                cout << "Вы выиграли!" << endl;
            }
            else
            {
                for (auto& ex : chipsvalue.chipscol)
                {
                    if (ex.first == chip)
                        ex.second -= col;
                }
                cout << "You Lose :(" << endl;
            }
            
            break;
        }
        case(2):
        {
            int red[18] = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
            int black[18] = { 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };
            
            cout << "red or black?" << endl;

            cin >> betcolor;

            if (betcolor == "red")
            {

                for (int i = 0; i < size(red); i++)
                {
                    if (res == red[i])
                    {
                        for (auto& ex : chipsvalue.chipscol)
                        {
                            if (ex.first == chip)
                                ex.second *= 2;

                        }
                        cout << "You Win!!!" << endl;
                    }
                    
                }

            }
            else if (betcolor == "black")
            {
                for (int i = 0; i < size(black); i++)
                {
                    if (res == black[i])
                    {
                        for (auto& ex : chipsvalue.chipscol)
                        {
                            if (ex.first == chip)
                                ex.second *= 2;
                        }
                        cout << "You Win!!!" << endl;
                    }
                    
                }
            }
            else
            {
                for (auto& ex : chipsvalue.chipscol)
                {
                    if (ex.first == chip)
                        ex.second -= col;
                }
                cout << "You Lose :(" << endl;
            }
            
            break;
        }
        case(3):
        {
            cout << "even or odd?" << endl;
            cin >> betcolor;

            if (betcolor == "even")
            {
                
                if (res % 2 == 0)
                {
                    for (auto& ex : chipsvalue.chipscol)
                    {
                        if (ex.first == chip)
                            ex.second *= 2;
                    }
                    cout << "You Win!!!" << endl;
                }
            }
            else if (betcolor == "odd")
            {
                if (res % 2 == 1)
                {
                    for (auto& ex : chipsvalue.chipscol)
                    {
                        if (ex.first == chip)
                            ex.second *= 2;
                    }
                    cout << "You Win!!!" << endl;
                }
            }
            else
            {
                for (auto& ex : chipsvalue.chipscol)
                {
                    if (ex.first == chip)
                        ex.second -= col;
                }
                cout << "You Lose :(" << endl;
            }
            
            break;
        }
        case(4):
        {
            cout << "1st, 2nd or 3d?" << endl;
            cin >> betcolor;

            if (betcolor == "1st")
            {
                if (res <= 12 && res > 0)
                {
                    for (auto& ex : chipsvalue.chipscol)
                    {
                        if (ex.first == chip)
                            ex.second *= 3;
                    }
                    cout << "You Win!!!" << endl;
                }
            }
            else if (betcolor == "2nd")
            {
                if (res <= 24 && res > 12)
                {
                    for (auto& ex : chipsvalue.chipscol)
                    {
                        if (ex.first == chip)
                            ex.second *= 3;
                    }
                    cout << "You Win!!!" << endl;
                }
            }
            else if (betcolor == "3d")
            {
                if (res <= 36 && res > 24)
                {
                    for (auto& ex : chipsvalue.chipscol)
                    {
                        if (ex.first == chip)
                            ex.second *= 3;
                    }
                    cout << "You Win!!!" << endl;
                }
                
            }
            else
            {
                for (auto& ex : chipsvalue.chipscol)
                {
                    if (ex.first == chip)
                        ex.second -= col;
                }
                cout << "You Lose :(" << endl;
            }
            
            break;
        }
        }
        system("pause");
        system("cls");
    }
    };

class Menu
{
private:
    int choise;
    
    string name;
    
public:
    int menu(Chips& chips) 
    {
        
        if (chips.chipscol.empty())
        {
            cout << "See you soon" << endl;
            return 0;
            
        }
       
        while (1)
        {

            cout << "Welcome to the menu\n";

            cout << "\t\t\t-------------------------------------\n"
                "\t\t\t| 1. Roulette(in development)       |\n"
                "\t\t\t| 2. Black Jack(in development)     |\n"
                "\t\t\t| 3. Balance                        |\n"
                "\t\t\t| 4. Exit                           |\n"
                "\t\t\t-------------------------------------\n";

            cin >> choise;
            system("cls");

            switch (choise)
            {
            case(1):
            {
                Roulette roulette;
                roulette.Game(chips);
                break;
            }
            case(2):
            {

                break;
            }
            case(3):
            {
                cout << "Balance:\n";
                chips.GetChips();
                cout << endl;
                break;
            }
            case(4):
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
                break;
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


int main()
{
    setlocale(LC_ALL, "RU");


    Roulette a;

    Menu console;

    Chips casino;

    console.startmsg();

    casino.chipschange();

    console.menu(casino);

    a.Game(casino);

}