#include "header.h"

class Menu;

class Roulette;

class BlackJack;

class Chips
{
private:
    friend Roulette;
    friend Menu;
    friend BlackJack;

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

    short count;

    int quantity;

    int col;

    string moneysleft;

    vector<pair<string, int>> chipscol{};

public:

    static void printchips()
    {
        cout << "white - " << white << endl;
        cout << "red - " << red << endl;
        cout << "blue - " << blue << endl;
        cout << "green - " << green << endl;
        cout << "black - " << black << endl;
        cout << "purple - " << purple << endl;
        cout << "orange - " << orange << endl;
    }

    int chipschange() {
        cin >> moneys;

        if (moneys <= 0) {
            cout << "Вы не можете прийти в каизно с отрицательным балансом";
            return 0;
        }
        else if (moneys > INT_MAX) {
            cout << "У вас нет столько денег";
            return 0;
        }

        Chips::printchips();

        while (moneys != 0) 
        { 

            count++;

            if (count == 6)
            {
                system("cls");
                Chips::printchips();
                count = 0;
            }

            cout << "Введите количество и тип фишек" << endl;

            cin >> col >> moneysleft;

            if (col <= 0) {
                cout << "Неизвестное количество" << endl;
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
                    if (!found) { chipscol.push_back({ moneysleft, col }); }    
                        
                }
                else { cout << "Вы не можете это сделать" << endl; }

            }
            else { cout << "Неизвестный тип фишек" << endl; }

            cout << "\nОставшиеся деньги - " << moneys << endl;

        }

        system("cls");

        return 0;
    }

    void GetChips() 
    {
        sort(chipscol.begin(), chipscol.end(), [](auto& a, auto& b) { return a.second > b.second; });

        for (const auto& chip : chipscol) {
            cout << chip.first << " " << chip.second << endl;
        }
    }

    void DelChips(string &chip, short &col)
    {
        for (auto& val : chipscol)
        {
            if (val.first == chip)
                val.second -= col;
            if (val.second == 0)
                erase(chipscol, val);
        }
        cout << "You Lose -  " << col << endl;
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

class Roulette : public Chips
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

    int Game(Chips& chipsvalue)
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

        cout << "Введите кол-во фишек и ставку" << endl;
        cin >> col >> chip;

        for (auto& it : chipsvalue.chipscol)
        {
            if (it.first != chip)
            {
                cout << "Неизвестный тип фишек" << endl;
                system("pause");
                system("cls");

                return 0;
            }
            if (it.second < col)
            {

                cout << "У вас нет такого количества фишек" << endl;
                return 0;
            }
        }

        cout << "1 - Ставка на любое число" << endl;
        cout << "2 - Ставка на красное / черное" << endl;
        cout << "3 - Сатвка на чет / нечет" << endl;
        cout << "4 - Ставка на ряды" << endl;
        cout << "5 - Ставка на половину" << endl;

        cin >> betchoose;

        switch (betchoose)
        {

        case (1):
        {

            cout << "Куда хотите поставить?" << endl;
            cin >> bet;

            if (bet == res)
            {
                for (auto& val : chipsvalue.chipscol)
                {

                    if (getValue(chip)) { val.second += col * 34; }

                }
                cout << "You Win - " << col * 34 << endl;
            }
            else
            {
                chipsvalue.DelChips(chip, col);
            }

            break;
        }
        case(2):
        {
            cout << "red or black?" << endl;

            cin >> betcolor;

            if (betcolor == "red")
            {
                if (res == 1 || res == 3 || res == 5 || res == 7 || res == 9 || res == 12 ||
                    res == 14 || res == 16 || res == 18 || res == 19 || res == 21 || res == 23 ||
                    res == 25 || res == 27 || res == 30 || res == 32 || res == 34 || res == 36)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }

            }
            else if (betcolor == "black")
            {
                if (res == 2 || res == 4 || res == 6 || res == 8 || res == 10 || res == 11 ||
                    res == 13 || res == 15 || res == 17 || res == 20 || res == 22 || res == 24 ||
                    res == 26 || res == 28 || res == 29 || res == 31 || res == 33 || res == 35)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
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
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
            }
            else if (betcolor == "odd")
            {
                if (res % 2 == 1)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
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
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col * 2; }
                    }
                    cout << "You Win - " << col * 2 << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
            }
            else if (betcolor == "2nd")
            {
                if (res <= 24 && res > 12)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col * 2; }
                    }
                    cout << "You Win - " << col * 2 << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
            }
            else if (betcolor == "3d")
            {
                if (res <= 36 && res > 24)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col * 2; }
                    }
                    cout << "You Win - " << col * 2 << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }

            }


            break;
        }
        case (5):
        {
            cout << "1to18 or 19to36?" << endl;
            cin >> betcolor;

            if (betcolor == "1to18")
            {
                if (res > 0 && res < 19)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }

            }
            else if (betcolor == "19to36")
            {
                if (res > 18 && res < 37)
                {
                    for (auto& val : chipsvalue.chipscol)
                    {
                        if (getValue(chip)) { val.second += col; }
                            
                    }
                    cout << "You Win - " << col << endl;
                }
                else
                {
                    chipsvalue.DelChips(chip, col);
                }
            }
        }
        default:
        {
            cout << "Uknown bet" << endl;
        }
        }
        system("pause");
        system("cls");
    }
};

class BlackJack 
{

private:

    class Cardshand
    {
    protected:
        
        string cards[54];
    public:
        
        void cardsinit() {
            short rank[] = { 2,3,4,5,6,7,8,9,10,11 };
            short suit[] = { 0,1,2,3 };//0 - pika 1 - cherva 2 - kresti 3 - buba
            int i = 0;
            for (int rank = 1; rank <= 11; rank++) {
                for (int suit = 0; suit <= 3; suit++) {
                    i++;
                    string strrank = to_string(rank);
                    string strsuit = to_string(suit);
                    cards[i] = strrank + strsuit;
                }
            }
        }

    };

    class Player : public Cardshand
    {
    public:
        int playercards() {
            string choise;
            int cardrank, cardsuit, playerCardSum = 0;
            cardsinit();
            cout << "\nPlayer cards: ";
        restart:
            while (true) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dis(0, 53);

                const int randvalue = dis(gen);

                try 
                {
                    cardrank = stoi(cards[randvalue]) / 10;
                    cardsuit = stoi(cards[randvalue]) % 10;
                }
                catch (const invalid_argument &err) 
                {
                    goto restart;
                }
                cout << "[";
                switch (cardrank)
                {
                case 0: goto restart;
                case 1: cout << "Ace"; break;
                case 2: cout << "2"; break;
                case 3: cout << "3"; break;
                case 4: cout << "4"; break;
                case 5: cout << "5"; break;
                case 6: cout << "6"; break;
                case 7: cout << "7"; break;
                case 8: cout << "8"; break;
                case 9: cout << "9"; break;
                case 10: cout << "10"; break;
                case 11: cout << "Jack"; break;
                case 12: cout << "Qween"; break;
                case 13: cout << "King"; break;
                default: break;
                }
                switch (cardsuit)
                {
                case 0: cout << " Spades"; break;
                case 1: cout << " Hearts"; break;
                case 2: cout << " Clubs"; break;
                case 3: cout << " Diamonds"; break;
                default: break;
                }
                playerCardSum += cardrank;
                if (playerCardSum > 21) {
                    cout << "], Sum: " << playerCardSum << endl;
                    playerCardSum = 0;
                    break;
                }
                cout << "], Sum = " << playerCardSum;
                cout << "\nDo you want more card? (y/n)\n";
                cin >> choise;
                if (choise == "n") {
                    cout << "Sum: " << playerCardSum << endl;
                    break;
                }
            }
            return playerCardSum;
        }
    };

    class Dealer : public Cardshand
    {
    public:
        int dealercards() {
            int cardrank, cardsuit, dealerCardSum = 0;
            system("cls");
            cardsinit();
            cout << "Dealer cards: ";
        restart:
            while (true) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dis(0, 53);

                const auto randvalue = dis(gen);

                try 
                {
                    cardrank = stoi(cards[randvalue]) / 10;
                    cardsuit = stoi(cards[randvalue]) % 10;
                }
                catch (const invalid_argument& err) 
                {

                    goto restart;
                }
                cout << "[";
                switch (cardrank)
                {
                case 0: goto restart;
                case 1: cout << "Ace"; break;
                case 2: cout << "2"; break;
                case 3: cout << "3"; break;
                case 4: cout << "4"; break;
                case 5: cout << "5"; break;
                case 6: cout << "6"; break;
                case 7: cout << "7"; break;
                case 8: cout << "8"; break;
                case 9: cout << "9"; break;
                case 10: cout << "10"; break;
                case 11: cout << "Jack"; break;
                case 12: cout << "Qween"; break;
                case 13: cout << "King"; break;
                default: break;
                }
                switch (cardsuit)
                {
                case 0: cout << " Spades"; break;
                case 1: cout << " Hearts"; break;
                case 2: cout << " Clubs"; break;
                case 3: cout << " Diamonds"; break;
                default: break;
                }
                cout << "], ";
                dealerCardSum += cardrank;
                if (dealerCardSum >= 17) {
                    cout << "Sum: " << dealerCardSum << endl;
                    break;
                }
            }
            return dealerCardSum;
        }

    };

    public:
    
    void BJGame(Chips &chipsvalue)
    {
        short col;
        string chip;

        cout << "Введите вашу ставку" << endl;

        cin >> col >> chip;

        for (auto& val : chipsvalue.chipscol)
        {
            if (val.first != chip)
            {
                cout << "You don`t have this type of chips" << endl;
            }
        }

        Cardshand cards;
        Player playerlogic;
        Dealer dealerlogic;
        int dealerCardSum, playerCardSum;

        cards.cardsinit();
        dealerCardSum = dealerlogic.dealercards();
        playerCardSum = playerlogic.playercards();

        if (dealerCardSum > 21)
        {
            for (auto& val : chipsvalue.chipscol)
            {
                val.second -= col;
                val.second += (col * 2);
            }
            cout << "Dealer Cards Sum > 21" << endl;
            cout << "You Win - " << col * 2 << endl;
            
        }

        if (playerCardSum > dealerCardSum)
        {
            for (auto& val : chipsvalue.chipscol)
            {
                val.second -= col;
                val.second += (col * 2);
            }
            cout << "You Win - " << col * 2 << endl;
        }
        else if (playerCardSum < dealerCardSum)
        {
            chipsvalue.DelChips(chip, col);
        }
        else
        {
            for (auto& val : chipsvalue.chipscol)
            {
                val.second -= col;
                val.second += col;
            }
            cout << "Draw - You haven't lost anything" << endl;
        }
        

    }
};

class Menu : public Chips
{
private:
    int choise;
    
    string name;

public:
    void menu(Chips& chips) 
    {
        
        while (1)
        {

            if (chips.chipscol.empty())
            {
                cout << "До скорых встреч.." << endl;
                exit (0);

            }

            cout << "\nДобро пожаловать в Меню\n";

            cout << "\t\t\t-------------------------------------\n"
                "\t\t\t| 1. Roulette                       |\n"
                "\t\t\t| 2. Black Jack                     |\n"
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
                BlackJack BJ;
                BJ.BJGame(chips);
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

        cout << "Как я могу к вам обращатся?" << endl;

        bool letter = true;
       
        while (letter)
        {
            
            cin >> name;
            
            for (char iter : name)
            {

                if (isalpha(iter))
                {
                    letter = false;
                    
                }    
            }
            if (letter)
            {
                cout << "Name, not a phone number" << endl;
                
            }
        }
       
        system("cls");

        cout << name << ", Какую сумму вы хотите обменять на фишки?" << endl;
    }

};

int main()
{
    setlocale(LC_ALL, "RU");
    Menu console;

    Chips casino;

    console.startmsg();

    casino.chipschange();

    console.menu(casino);

    return 0;
}