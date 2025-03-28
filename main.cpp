#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <thread>
using namespace std;

struct Question {
    string questionText;
    vector<string> options;
    int correctIndex;
};

void displayQuestion(const Question &q, int index) {
    cout << "\nQ" << index + 1 << ": " << q.questionText << endl;
    for (size_t i = 0; i < q.options.size(); ++i) {
        cout << i + 1 << ". " << q.options[i] << endl;
    }
}

int getUserAnswer(int timeLimit) {
    int answer;
    thread([&]() {
        this_thread::sleep_for(chrono::seconds(timeLimit));
        cout << "\nTime's up!" << endl;
        exit(0);
    }).detach();

    cout << "Your answer (1-4): ";
    while (!(cin >> answer) || answer < 1 || answer > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and 4: ";
    }
    return answer - 1;
}

int main() {
    vector<Question> quiz = {
        {"What is 5 + 3?", {"5", "8", "10", "15"}, 1},
        {"Who wrote 'Hamlet'?", {"Shakespeare", "Dickens", "Hemingway", "Tolkien"}, 0},
        {"What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Bangkok"}, 2},
        {"Which planet is known as the Blue Planet?", {"Mars", "Venus", "Earth", "Jupiter"}, 2}
    };
    
    srand(time(0));
    random_shuffle(quiz.begin(), quiz.end());
    
    int score = 0;
    int timeLimit = 10; // Each question has 10 seconds
    
    for (size_t i = 0; i < quiz.size(); ++i) {
        displayQuestion(quiz[i], i);
        int userChoice = getUserAnswer(timeLimit);
        
        if (userChoice == quiz[i].correctIndex) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Wrong! Correct answer: " << quiz[i].options[quiz[i].correctIndex] << "\n";
        }
    }
    
    cout << "\nFinal Score: " << score << "/" << quiz.size() << endl;
    return 0;
}
