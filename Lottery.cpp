#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>
#include <algorithm> // For sorting
#include <vector>

using namespace std;

const int Maxnumbers = 70;
const int Megaball = 25;
const int Numbercount = 5;
const int Basejackpot = 20000000; // Starting jackpot ($20 million)
const long double Jackpotodds = 1.0 / 302575350.0; // Odds of winning the jackpot
const long double Prizeodds = 1.0 / 24.0; // Odds of winning any prize

const double Ticketprice = 2.00; // Base price per ticket
const double Megapliercost = 1.00; // Extra cost for MegaPlier per board

// Function to generate a unique ticket code (alphanumeric with special characters)
string generateUniqueCode() {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";
    string uniqueCode;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, charset.length() - 1);

    for (int i = 0; i < 20; ++i) {
        uniqueCode += charset[dis(gen)];
    }
    return uniqueCode;
}

// Function to generate random numbers for Mega Millions
void generateMegaMillionsNumbers(int mainNumbers[], int &megaBall) {
    bool used[Maxnumbers] = {false};

    for (int i = 0; i < Numbercount; ++i) {
        int num;
        do {
            num = rand() % Maxnumbers + 1;
        } while (used[num - 1]);

        mainNumbers[i] = num;
        used[num - 1] = true;
    }

    megaBall = rand() % Megaball + 1;
}

// Function to calculate winnings
int calculateWinnings(const int userNumbers[], int userMegaBall, const int winningNumbers[], int winningMegaBall) {
    int matchedNumbers = 0;

    for (int i = 0; i < Numbercount; ++i) {
        for (int j = 0; j < Numbercount; ++j) {
            if (userNumbers[i] == winningNumbers[j]) {
                matchedNumbers++;
                break;
            }
        }
    }

    bool megaBallMatch = (userMegaBall == winningMegaBall);

    if (matchedNumbers == 5 && megaBallMatch) return Basejackpot;
    if (matchedNumbers == 5) return 1000000;
    if (matchedNumbers == 4 && megaBallMatch) return 10000;
    if (matchedNumbers == 4) return 500;
    if (matchedNumbers == 3 && megaBallMatch) return 200;
    if (matchedNumbers == 3) return 10;
    if (matchedNumbers == 2 && megaBallMatch) return 10;
    if (matchedNumbers == 1 && megaBallMatch) return 4;
    if (megaBallMatch) return 2;

    return 0;
}

int main() {
    srand(time(0));

    cout << "Welcome to Mega Millions Lottery....\n";
    cout << "_________________________________\n\n";

    char playMode;
    cout << "ENTER Q for quick pick or M for manual: ";
    cin >> playMode;

    if (playMode == 'Q' || playMode == 'q') {
        int numBoards, numDraws, numTickets;
        char cashOrAnnuity, megaPlierChoice;

        cout << "Enter number of boards: ";
        cin >> numBoards;
        cout << "Enter number of draws: ";
        cin >> numDraws;
        cout << "Enter number of tickets purchased: ";
        cin >> numTickets;
        cout << "Choose Cash value option (C) or Annuity option (A): ";
        cin >> cashOrAnnuity;
        cout << "Do you want to apply MegaPlier? (Y/N): ";
        cin >> megaPlierChoice;

        int winningNumbers[Numbercount];
        int winningMegaBall;
        generateMegaMillionsNumbers(winningNumbers, winningMegaBall);
        string winningCode = generateUniqueCode();

        // Sort the winning numbers in ascending order
        sort(winningNumbers, winningNumbers + Numbercount);

        // Variables to track total winnings (but do not show immediately)
        int totalWinnings = 0;

        for (int i = 0; i < numTickets; ++i) {
            int userNumbers[Numbercount];
            int userMegaBall;
            generateMegaMillionsNumbers(userNumbers, userMegaBall);
            string userCode = generateUniqueCode();

            // Sort user numbers in ascending order
            sort(userNumbers, userNumbers + Numbercount);

            cout << "\n[ Mega Million Ticket " << i + 1 << " ]\n\n";
            cout << "Numbers: ";
            for (int j = 0; j < Numbercount; ++j) {
                cout << userNumbers[j] << " ";
            }
            cout << "\nMega Ball: " << userMegaBall << "\n";
            cout << "Ticket Code: " << userCode << "\n";

            // Calculate winnings for this ticket
            int winnings = calculateWinnings(userNumbers, userMegaBall, winningNumbers, winningMegaBall);
            if (winnings > 0) {
                cout << "You won! Prize: $" << winnings << "\n";
                totalWinnings += winnings;
            }
        }

        // Correct calculation for total cost
        double totalCost = numTickets * numBoards * numDraws * Ticketprice;
        if (megaPlierChoice == 'Y' || megaPlierChoice == 'y') {
            totalCost += numTickets * numBoards * numDraws * Megapliercost;
        }

        cout << "\nTotal cost: $" << totalCost << "\n\n";

        // Prompt to view results and total winnings
        char viewResults;
        cout << "Enter R to see the results: ";
        cin >> viewResults;

        if (viewResults == 'R' || viewResults == 'r') {
            cout << "\nResults:\n";
            cout << "Winning Numbers: ";
            for (int i = 0; i < Numbercount; ++i) {
                cout << winningNumbers[i] << " ";
            }
            cout << "\nWinning Mega Ball: " << winningMegaBall << "\n";
            cout << "Winning Ticket Code: " << winningCode << "\n";
            
            cout << "\nTotal Win: $" << totalWinnings << "\n";
        }

        char buyMore;
        cout << "Do you want to buy more tickets? (Y/N): ";
        cin >> buyMore;
        if (buyMore == 'Y' || buyMore == 'y') {
            main(); // Restart the game
        }
    }

    if (playMode == 'M' || playMode == 'm') {
        int numBoards, numDraws, numTickets, userMegaBall;
        char cashOrAnnuity, megaPlierChoice;
        vector<int> userMainNumbers(Numbercount);

        cout << "Enter number of boards: ";
        cin >> numBoards;
        cout << "Enter number of draws: ";
        cin >> numDraws;
        cout << "Enter number of tickets purchased: ";
        cin >> numTickets;
        cout << "Choose Cash value option (C) or Annuity option (A): ";
        cin >> cashOrAnnuity;
        cout << "Do you want to apply MegaPlier? (Y/N): ";
        cin >> megaPlierChoice;

        int winningNumbers[Numbercount];
        int winningMegaBall;
        generateMegaMillionsNumbers(winningNumbers, winningMegaBall);
        string winningCode = generateUniqueCode();

        // Sort the winning numbers in ascending order
        sort(winningNumbers, winningNumbers + Numbercount);

        // Variables to track total winnings (but do not show immediately)
        int totalWinnings = 0;

        for (int i = 0; i < numTickets; ++i) {
            cout << "\n[ Enter Numbers for Ticket " << i + 1 << " ]\n\n";

            // Prompt user to input 5 numbers (from 1 to 70)
            cout << "Enter 5 numbers (space-separated, 1-70): ";
            string line;
            cin.ignore();  // Ignore leftover newline from previous input
            getline(cin, line);

            stringstream ss(line);
            int num, count = 0;
            while (ss >> num && count < Numbercount) {
                if (num >= 1 && num <= Maxnumbers) {
                    userMainNumbers[count++] = num;
                } else {
                    cout << "Invalid number entered. Please enter numbers between 1 and 70.\n";
                    return 1; // Exit the program if invalid number
                }
            }

            // Prompt for MegaBall number (1-25)
            do {
                cout << "Enter your Mega Ball (1-25): ";
                cin >> userMegaBall;
            } while (userMegaBall < 1 || userMegaBall > Megaball);

            string userCode = generateUniqueCode();

            // Sort user numbers in ascending order
            sort(userMainNumbers.begin(), userMainNumbers.end());

            cout << "\n[ Mega Million Ticket " << i + 1 << " ]\n\n";
            cout << "Numbers: ";
            for (int j = 0; j < Numbercount; ++j) {
                cout << userMainNumbers[j] << " ";
            }
            cout << "\nMega Ball: " << userMegaBall << "\n";
            cout << "Ticket Code: " << userCode << "\n";

            // Calculate winnings for this ticket
            int winnings = calculateWinnings(userMainNumbers.data(), userMegaBall, winningNumbers, winningMegaBall);
            if (winnings > 0) {
                cout << "You won! Prize: $" << winnings << "\n";
                totalWinnings += winnings;
            }
        }

        // Correct calculation for total cost
        double totalCost = numTickets * numBoards * numDraws * Ticketprice;
        if (megaPlierChoice == 'Y' || megaPlierChoice == 'y') {
            totalCost += numTickets * numBoards * numDraws * Megapliercost;
        }

        cout << "\nTotal cost: $" << totalCost << "\n\n";

        // Prompt to view results and total winnings
        char viewResults;
        cout << "Enter R to see the results: ";
        cin >> viewResults;

        if (viewResults == 'R' || viewResults == 'r') {
            cout << "\nResults:\n";
            cout << "Winning Numbers: ";
            for (int i = 0; i < Numbercount; ++i) {
                cout << winningNumbers[i] << " ";
            }
            cout << "\nWinning Mega Ball: " << winningMegaBall << "\n";
            cout << "Winning Ticket Code: " << winningCode << "\n";
            
            cout << "\nTotal Win: $" << totalWinnings << "\n";
        }

        char buyMore;
        cout << "Do you want to buy more tickets? (Y/N): ";
        cin >> buyMore;
        if (buyMore == 'Y' || buyMore == 'y') {
            main(); // Restart the game
        }
    }

    return 0;
}
