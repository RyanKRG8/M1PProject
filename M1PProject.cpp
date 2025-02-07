#include <iostream>
#include <random>
#include <string>
using namespace std;

// Function to get player's choice with input validation
string getPlayerChoice() {
    string choice;
    while (true) {
        cout << "Enter rock, paper, scissors, or quit: ";
        cin >> choice;

        for (char& c : choice) c = tolower(c);

        if (choice == "rock" || choice == "paper" || choice == "scissors" || choice == "quit")
            return choice;
        cout << "That is not a valid choise. Please enter rock, paper, scissors, or quit.\n";
    }
}

// Function to get the computer's choice
string getComputerChoice() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 3);

    int num = dist(gen);
    if (num == 1) return "rock";
    if (num == 2) return "paper";
    return "scissors";
}

// Function to determine the winner of a round
string determineWinner(string playerChoice, string computerChoice) {
    if (playerChoice == computerChoice) return "draw";
    if ((playerChoice == "rock" && computerChoice == "scissors") ||
        (playerChoice == "scissors" && computerChoice == "paper") ||
        (playerChoice == "paper" && computerChoice == "rock"))
        return "player";
    return "computer";
}

// Function to update the scores
void updateScores(string winner, int& playerScore, int& computerScore) {
    if (winner == "player") playerScore++;
    else if (winner == "computer") computerScore++;
}

// Function to display the results
void displayFinalResults(int playerScore, int computerScore) {
    cout << "\n=-=-= Game Over =-=-=\n";
    cout << "Final Score - You: " << playerScore << " | Computer: " << computerScore << "\n";

    if (playerScore > computerScore) cout << "You win the game!\n";
    else if (playerScore < computerScore) cout << "The Computer wins the game!\n";
    else cout << "It's a draw!\n";
}

// Main game
int main() {
    int playerScore = 0, computerScore = 0;

    while (true) {
        string playerChoice = getPlayerChoice();
        if (playerChoice == "quit") break;

        string computerChoice = getComputerChoice();
        cout << "Computer chose: " << computerChoice << "\n";

        string winner = determineWinner(playerChoice, computerChoice);
        if (winner == "draw") cout << "It's a draw!\n";
        else if (winner == "player") cout << "You win this round!\n";
        else cout << "The Computer wins this round!\n";

        updateScores(winner, playerScore, computerScore);
        cout << "Current Score - You: " << playerScore << " | Computer: " << computerScore << "\n\n";
    }

    displayFinalResults(playerScore, computerScore);
    cout << "Thank you for playing Rock, Paper, Scissors!\n";
    return 0;
}
