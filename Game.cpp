#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>
#include <queue>

#include "Student.hpp"
#include "Question.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include "Leaderboard.hpp"
using namespace std;

class TreeNode {
public:
    Student student;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Student& student) : student(student), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    TreeNode* root;

    void displayTree(TreeNode* root) const {
        if (!root) return;

        queue<TreeNode*> q;
        q.push(root);

        int level = 0;
        while (!q.empty()) {
            int count = q.size();
            cout << "Level " << level++ << ": ";
            while (count--) {
                TreeNode* node = q.front();
                q.pop();
                cout << node->student.getName() << " (" << node->student.getTotalScore() << ") ";
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            cout << endl;
        }
    }

    void displayHorizontalTree(TreeNode* root, ostream& out) const {
        if (!root) return;

        queue<TreeNode*> q;
        q.push(root);

        Vector<Vector<TreeNode*>> levels;
        while (!q.empty()) {
            int count = q.size();
            Vector<TreeNode*> level;
            while (count--) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node);
                if (node) {
                    q.push(node->left);
                    q.push(node->right);
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                }
            }
            bool allNull = true;
            for (size_t i = 0; i < level.getSize(); ++i) {
                if (level[i] != nullptr) {
                    allNull = false;
                    break;
                }
            }
            if (allNull) break;
            levels.push_back(level);
        }

        // Center the root node
        out << "                                                                                                                       " << root->student.getName() << " (" << root->student.getTotalScore() << ")\n";

        // Level 1
        if (root->left || root->right) {
            out << "                                                                                                                            |\n";
            out << "                                                                                                                            |\n";
            out << "                                                           +----------------------------------------------------------------+-------------------------------------------------------------------+\n";
            out << "                                                           |                                                                                                                                    |\n";
            out << "                                                       " << (root->left ? root->left->student.getName() + " (" + to_string(root->left->student.getTotalScore()) + ")" : "                         ")
                << "                                                                                                                           " << (root->right ? root->right->student.getName() + " (" + to_string(root->right->student.getTotalScore()) + ")" : "                         ") << "\n";
        }

        // Level 2
        if ((root->left && (root->left->left || root->left->right)) || (root->right && (root->right->left || root->right->right))) {
            out << "                                                           |                                                                                                                                    |\n";
            out << "                                                           |                                                                                                                                    |\n";
            out << "                               +-----------------------------+--------------------------------+                                                                 +-------------------------------+----------------------------------+\n";
            out << "                               |                                                              |                                                                 |                                                                  |\n";
            out << "                            " << (root->left && root->left->left ? root->left->left->student.getName() + " (" + to_string(root->left->left->student.getTotalScore()) + ")" : "           ")
                << "                                                    " << (root->left && root->left->right ? root->left->right->student.getName() + " (" + to_string(root->left->right->student.getTotalScore()) + ")" : "           ")
                << "                                                         " << (root->right && root->right->left ? root->right->left->student.getName() + " (" + to_string(root->right->left->student.getTotalScore()) + ")" : "           ")
                << "                                                      " << (root->right && root->right->right ? root->right->right->student.getName() + " (" + to_string(root->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
        }

        // Level 3
        if ((root->left && root->left->left && (root->left->left->left || root->left->left->right)) ||
            (root->left && root->left->right && (root->left->right->left || root->left->right->right)) ||
            (root->right && root->right->left && (root->right->left->left || root->right->left->right)) ||
            (root->right && root->right->right && (root->right->right->left || root->right->right->right))) {
            out << "              +----------------+---------------+                               +--------------+--------------+                                 +----------------+----------------+                                 +---------------+----------------+\n";
            out << "           " << (root->left && root->left->left && root->left->left->left ? root->left->left->left->student.getName() + " (" + to_string(root->left->left->left->student.getTotalScore()) + ")" : "                    ")
                << "                    " << (root->left && root->left->left && root->left->left->right ? root->left->left->right->student.getName() + " (" + to_string(root->left->left->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->left && root->left->right && root->left->right->left ? root->left->right->left->student.getName() + " (" + to_string(root->left->right->left->student.getTotalScore()) + ")" : "                      ")
                << "                    " << (root->left && root->left->right && root->left->right->right ? root->left->right->right->student.getName() + " (" + to_string(root->left->right->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->right && root->right->left && root->right->left->left ? root->right->left->left->student.getName() + " (" + to_string(root->right->left->left->student.getTotalScore()) + ")" : "                      ")
                << "                          " << (root->right && root->right->left && root->right->left->right ? root->right->left->right->student.getName() + " (" + to_string(root->right->left->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->right && root->right->right && root->right->right->left ? root->right->right->left->student.getName() + " (" + to_string(root->right->right->left->student.getTotalScore()) + ")" : "                      ")
                << "                       " << (root->right && root->right->right && root->right->right->right ? root->right->right->right->student.getName() + " (" + to_string(root->right->right->right->student.getTotalScore()) + ")" : "                      ") << "\n";
        }

        // Level 4
        if ((root->left && root->left->left && root->left->left->left && (root->left->left->left->left || root->left->left->left->right)) ||
            (root->left && root->left->left && root->left->left->right && (root->left->left->right->left || root->left->left->right->right)) ||
            (root->left && root->right && root->right->left && (root->right->left->left || root->right->left->right)) ||
            (root->left && root->right && root->right->right && (root->right->right->left || root->right->right->right))) {
            out << "     +--------+---------+             +--------+---------+            +--------+---------+          +--------+---------+              +--------+---------+              +--------+---------+              +--------+---------+               +------+-------+\n";
            out << "     |                  |             |                  |            |                  |          |                  |              |                  |              |                  |              |                  |               |               \n";
            out << (root->left && root->left->left && root->left->left->left && root->left->left->left->left ? root->left->left->left->left->student.getName() + " (" + to_string(root->left->left->left->left->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->left && root->left->left->left && root->left->left->left->right ? root->left->left->left->right->student.getName() + " (" + to_string(root->left->left->left->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->left && root->left->left->right && root->left->left->right->left ? root->left->left->right->left->student.getName() + " (" + to_string(root->left->left->right->left->student.getTotalScore()) + ")" : "           ")
                << "        " << (root->left && root->left->left && root->left->left->right && root->left->left->right->right ? root->left->left->right->right->student.getName() + " (" + to_string(root->left->left->right->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->left ? root->left->right->left->left->student.getName() + " (" + to_string(root->left->right->left->left->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->right ? root->left->right->left->right->student.getName() + " (" + to_string(root->left->right->left->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->right && root->left->right->right->left ? root->left->right->right->left->student.getName() + " (" + to_string(root->left->right->right->left->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->right && root->left->right->right && root->left->right->right->right ? root->left->right->right->right->student.getName() + " (" + to_string(root->left->right->right->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->right && root->right->left && root->right->left->left && root->right->left->left->left ? root->right->left->left->left->student.getName() + " (" + to_string(root->right->left->left->left->student.getTotalScore()) + ")" : "           ")
                << "       " << (root->right && root->right->left && root->right->left->left && root->right->left->left->right ? root->right->left->left->right->student.getName() + " (" + to_string(root->right->left->left->right->student.getTotalScore()) + ")" : "           ")
                << "   " << (root->right && root->right->left && root->right->left->right && root->right->left->right->left ? root->right->left->right->left->student.getName() + " (" + to_string(root->right->left->right->left->student.getTotalScore()) + ")" : "           ")
                << "        " << (root->right && root->right->left && root->right->left->right && root->right->left->right->right ? root->right->left->right->right->student.getName() + " (" + to_string(root->right->left->right->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->right && root->right->right && root->right->right->left && root->right->right->left->left ? root->right->right->left->left->student.getName() + " (" + to_string(root->right->right->left->left->student.getTotalScore()) + ")" : "           ")
                << "         " << (root->right && root->right->right && root->right->right->left && root->right->right->left->right ? root->right->right->left->right->student.getName() + " (" + to_string(root->right->right->left->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->left ? root->right->right->right->left->student.getName() + " (" + to_string(root->right->right->right->left->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->right ? root->right->right->right->right->student.getName() + " (" + to_string(root->right->right->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
        }
    }

    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    TreeNode* find(TreeNode* node, const string& id) const {
        if (node == nullptr)
            return nullptr;
        if (id == node->student.getID())
            return node;
        if (id < node->student.getID())
            return find(node->left, id);
        return find(node->right, id);
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() {
        deleteTree(root);
    }

    TreeNode* find(const string& id) const {
        return find(root, id);
    }

    void buildTree(LinkedList<Student>& students) {
        if (students.getSize() == 0) return;
        root = new TreeNode(students.get(0));

        queue<TreeNode*> q;
        q.push(root);
        size_t index = 1;

        while (!q.empty() && index < students.getSize()) {
            TreeNode* current = q.front();
            q.pop();

            if (index < students.getSize()) {
                current->left = new TreeNode(students.get(index++));
                q.push(current->left);
            }

            if (index < students.getSize()) {
                current->right = new TreeNode(students.get(index++));
                q.push(current->right);
            }
        }
    }

    void displayTree() const {
        displayTree(root);
    }

    void displayHorizontalTree() const {
        displayHorizontalTree(root, cout);
    }
};

class Game {
private:
    LinkedList<Student> studentList;
    Vector<Question> questionList; // decide should use linkedlist or what...
    Stack<Question, 5> discardedCards;
    Stack<Question, 295> unansweredCards;
    LinkedList<Question> answeredCards;
    Student newStudent;

public:
    void loadStudentData() {
        ifstream file("students.csv");
        if (!file.is_open()) {
            cerr << "Error opening students.csv file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string id, name;
            getline(iss, id, '|');
            getline(iss, name, '|');

            Student student(id, name);

            string questionIdStr, scoreStr;
            while (getline(iss, questionIdStr, '|') && getline(iss, scoreStr, '|')) {
                int questionID, score;
                try {
                    questionID = stoi(questionIdStr);
                    score = stoi(scoreStr);
                    student.updateScore(questionID, score);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid value in CSV: " << questionIdStr << " or " << scoreStr << endl;
                }
            }

            studentList.append(student);
        }

        file.close();
        // for (int i = 0; i < studentList.getSize(); i++) {
        //     Student student = studentList[i];
        //     student.printScores();
        // }
    }

    void loadQuestionData() {
        ifstream file("questions.csv");
        string line;
        if (!file.is_open()) {
            cerr << "Error opening questions.csv file." << endl;
            return;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            string idStr, category, questionText, correctAnswer;
            Vector<string> options;

            getline(iss, idStr, '|');
            getline(iss, category, '|');
            getline(iss, questionText, '|');

            string option;
            while (getline(iss, option, '|')) {
                options.push_back(option);
            }

            correctAnswer = options.at(options.getSize() - 1);
            options.pop_back();

            int id = stoi(idStr);

            questionList.push_back(Question(id, category, questionText, options, correctAnswer));
        }
        file.close();
    }

    void startGame() {
        int choice;
        cout << "     Trivial Flash Card Game     " << endl
            << "<< --------------------------- >>" << endl
            << "Would you like to play" << endl
            << "1. Yes" << endl
            << "2. No" << endl
            << "Enter your choice: ";
        validateInput("playGame", choice);
        
        if (choice == 1) {
            string id;
            string name;
            cout << "Ready to play? Enter your student details below." << endl
                << "TP number: ";
            cin >> id;
            cout << "Name: ";
            cin >> name;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
            
            newStudent = Student(id, name);
            studentList.append(newStudent);
            repeatRound();
        }
        else if (choice == 2) {
            cout << "I guess you are not up for the challenge, pussy...";
        }
    }


    void setUpDecks() { // delegate the questions into unanswered and discarded decks
        random_device rd;
        mt19937 gen(rd());
        
        // Shuffle the vector 
        shuffle(questionList.begin(), questionList.end(), gen); 

        // Add 5 questions from questionList to discardedCards
        for (int i = 0; i < 5 && i < questionList.getSize(); i++) {
            discardedCards.push(questionList[i]);
        }
        cout << "total count: " << questionList.getSize() << endl;
        cout << "discarded count: " << discardedCards.getSize() << endl;

        // Add remaining questions from questionList to unansweredCards
        for (int i = 5; i < questionList.getSize(); i++) {
            unansweredCards.push(questionList[i]);
        }

        cout << "unanswered count: " << unansweredCards.getSize() << endl;
    }

    // void updateScore() {

    // }
    
    int countCharAnswer(string& formattedUserAnswer, string& formattedCardAnswer) {
        int numCorrect = 0;
        for (char ch : formattedUserAnswer) {
            if (formattedCardAnswer.find(ch) != string::npos) {
                numCorrect++;
            }
        }
        return numCorrect;
    }

    string removeCommas(const string& answer) {
        string result;
        for (char ch : answer) {
            if (ch != ',') {
                result += ch;
            }
        }
        return result;
    }

    void validateInput(const string& inputType, int& choice) { // check user input whether is 1 or 2
        bool validInput = false;
        
        do {
            cin >> choice;
            
            if (choice == 1 || choice == 2) {
                validInput = true;
            } else {
                if (inputType == "chooseQuestion") {
                    cout << "Invalid input! Please enter 1 for discarded or 2 for unanswered questions: ";
                } else if (inputType == "answerQuestion") {
                    cout << "Invalid input! Please enter 1 to accept or 2 to decline: ";
                } else if (inputType == "playGame") {
                    cout << "Invalid input! Please enter 1 for YES or 2 for NO: ";
                } else if (inputType == "viewRanking") {
                    cout << "Invalid input! Please enter 1 to view leaderboard or 2 to view hierarchy: ";
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!validInput);
    }


    void answerDiscardedQuestion(Question card) {
        cout << "Question " << card.id << ": " << card.text << endl;
        for (size_t i = 0; i < card.options.getSize(); i++) {
            cout << card.options[i] << endl;
        }
        int choice;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round..." << endl
            << "1. Accept" << endl
            << "2. Decline" << endl
            << "Enter your choice: ";
        validateInput("answerQuestion", choice);
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (e.g., a/b,c/b,c,d): ";
            cin >> answer;
            // Remove commas from both correct and user answers for comparison
            string formattedUserAnswer = removeCommas(answer);
            string formattedCardAnswer = removeCommas(card.correctAnswers);
            int numCorrect = countCharAnswer(formattedUserAnswer, formattedCardAnswer);
            int questionScore = (numCorrect * 5) * 0.8;

            if (numCorrect == formattedCardAnswer.length()) {
                cout << "Correct answer! Well done!" << endl;
                cout << "Score for this question: " << questionScore << endl;
            } else if (numCorrect > 0) {
                cout << "Partially correct. " << numCorrect << " out of " << formattedCardAnswer.length() << " correct." << endl;
                cout << "Score for this question: " << questionScore << endl;
            } else {
                cout << "Incorrect answer. Correct answer was: " << formattedCardAnswer << endl;
                cout << "Score for this question: 0" << endl;
            }
            newStudent.updateScore(card.id, questionScore);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            newStudent.updateScore(card.id, 0);
            // Put back discarded stack
        }
        putBackCard(card);
    }



    void answerUnansweredQuestion() {
        Question card = unansweredCards.pop();
        cout << "Question " << card.id << ": " << card.text << endl;
        for (size_t i = 0; i < card.options.getSize(); i++) {
            cout << card.options[i] << endl;
        }
        int choice;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round..." << endl
            << "1. Accept" << endl
            << "2. Decline" << endl
            << "Enter your choice: ";
        validateInput("answerQuestion", choice);
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (e.g., a/b,c/b,c,d): ";
            cin >> answer;

            // Remove commas from both correct and user answers for comparison
            string formattedUserAnswer = removeCommas(answer);
            string formattedCardAnswer = removeCommas(card.correctAnswers);
            int numCorrect = countCharAnswer(formattedUserAnswer, formattedCardAnswer);
            int questionScore = numCorrect * 5;

            if (numCorrect == formattedCardAnswer.length()) {
                cout << "Correct answer! Well done!" << endl;
                cout << "Score for this question: " << questionScore << endl;
            } else if (numCorrect > 0) {
                cout << "Partially correct. " << numCorrect << " out of " << formattedCardAnswer.length() << " correct." << endl;
                cout << "Score for this question: " << questionScore << endl;
            } else {
                cout << "Incorrect answer. Correct answer was: " << formattedCardAnswer << endl;
                cout << "Score for this question: 0" << endl;
            }
            newStudent.updateScore(card.id, questionScore);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            newStudent.updateScore(card.id, 0);
        }
        putBackCard(card);
    }

    void chooseQuestion() { // user choose discarded or unanswered question
        cout << "Here is a sneak peek of the discarded question ;)" << endl
        << "if you choose a discarded question, you only receive 80 percent of the total marks..." << endl;
        Question discardedCard = discardedCards.pop(); 
        cout << "Discarded Question: " << discardedCard.text << endl;
        int choice;
        cout << "Would you like to choose a Discarded/Unanswered question?" << endl <<
        "1. Discarded" << endl <<
        "2. Unanswered" << endl <<
        "Enter your choice: ";
        validateInput("chooseQuestion", choice); 
        if (choice == 1) {
            answerDiscardedQuestion(discardedCard);
        } else if (choice == 2) {
            answerUnansweredQuestion();
        } 
    } 

    void putBackCard(Question answeredCard) { // logic not set yet, how does the discarded cards work?
        answeredCards.prepend(answeredCard);
        cout << "Unanswered cards length: " << unansweredCards.getSize() << endl;
        cout << "Discarded cards length: " << discardedCards.getSize() << endl;
        cout << "Answered cards length: " << answeredCards.getSize() << endl;
        if (discardedCards.getSize() != 5) {
            Question q = unansweredCards.pop();
            discardedCards.push(q);
        } 
    }

    void viewScoreboard() { // prompt user to select view leaderboard/hierarchy
        int choice;
        cout << "View Score:" << endl 
        << "1. Leaderboard" << endl 
        << "2. Rank hierarchy" << endl 
        << "Enter your choice: ";
        validateInput("viewRanking", choice);
        if (choice == 1) {
            showLeaderboard();
        } else if (choice == 2) {
            showHierarchy();
        } 
    }

    void repeatRound() { // 3 rounds then calculate the total score for each student
        for (size_t i = 1; i < 4; i++)
        {
            cout << "Round " << i << ":" << endl;
            chooseQuestion();
            
        }
        newStudent.printScores();
        viewScoreboard();
    }


    void showLeaderboard() {
        char sortOrder;
        cout << "Select sort order: [A]scending or [D]escending: ";
        cin >> sortOrder;

        if (sortOrder == 'A' || sortOrder == 'a') {
            studentList.sort([](const Student& a, const Student& b) {
                return a.getTotalScore() < b.getTotalScore(); // Ascending order
            });
        } else {
            studentList.sort([](const Student& a, const Student& b) {
                return a.getTotalScore() > b.getTotalScore(); // Descending order
            });
        }

        const int pageSize = 20;  // Number of students per page
        int totalPages = (studentList.getSize() + pageSize - 1) / pageSize;
        int currentPage = 0;

        while (true) {
            int start = currentPage * pageSize;
            int end = min(start + pageSize, studentList.getSize());

            cout << "\nLeaderboard - Page " << (currentPage + 1) << " of " << totalPages << ":\n";
            cout << setw(10) << left << "Rank"
                << setw(15) << left << "ID"
                << setw(25) << left << "Name"
                << setw(15) << left << "Total Score" << endl;
            cout << "---------------------------------------------------------\n";

            for (int i = start; i < end; i++) {
                Student student = studentList.get(i);
                cout << setw(10) << left << (i + 1)
                    << setw(15) << left << student.getID()
                    << setw(25) << left << student.getName()
                    << setw(15) << left << student.getTotalScore() << endl;
            }

            // Navigation
            cout << "\nNavigation: [N]ext page, [P]revious page, [S]earch, [E]xit\n";
            cout << "Enter choice: ";
            char choice;
            cin >> choice;

            if (choice == 'N' || choice == 'n') {
                if (currentPage < totalPages - 1) {
                    currentPage++;
                } else {
                    cout << "This is the last page.\n";
                }
            } else if (choice == 'P' || choice == 'p') {
                if (currentPage > 0) {
                    currentPage--;
                } else {
                    cout << "This is the first page.\n";
                }
            } else if (choice == 'S' || choice == 's') {
                searchStudent();
            } else if (choice == 'E' || choice == 'e') {
                break;
            }
        }
    }


    void showHierarchy() {
        studentList.sort([](const Student& a, const Student& b) {
            return a.getTotalScore() > b.getTotalScore(); 
        });

        int topSize = min(studentList.getSize(), 30);
        LinkedList<Student> top30List;
        for (int i = 0; i < topSize; ++i) {
            top30List.append(studentList.get(i));
        }

        Tree tree;
        tree.buildTree(top30List);

        cout << "Displaying hierarchy of top 30 students:" << endl;
        tree.displayHorizontalTree();

        while (true) {
            cout << "\nOptions: [B]ack to Scoreboard, [C]heck student ID, [E]xit\n";
            cout << "Enter choice: ";
            char choice;
            cin >> choice;

            if (choice == 'B' || choice == 'b') {
                viewScoreboard();
                break;
            } else if (choice == 'C' || choice == 'c') {
                string searchID;
                cout << "Enter the student ID to check if they are in the top 30: ";
                cin >> searchID;

                TreeNode* foundStudent = tree.find(searchID);
                if (foundStudent) {
                    cout << "Student " << searchID << " is in the top 30 winners!" << endl;
                } else {
                    // Check if the ID exists in the overall student list
                    Student* student = studentList.search(searchID);
                    if (student) {
                        cout << "Student " << searchID << " exists but is not in the top 30 winners." << endl;
                    } else {
                        cout << "Student ID " << searchID << " is invalid." << endl;
                    }
                }
            } else if (choice == 'E' || choice == 'e') {
                break;
            } else {
                cout << "Invalid choice! Please enter B, C, or E." << endl;
                cin.clear();// Clear the error flag on cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            }
        }
    }
    
    void searchStudent() { // working code!
        string studentID;
        cout << "Enter the student number to search: ";
        cin >> studentID;

        Student* student = studentList.search(studentID);
        if (student) {
            cout << "\nStudent found:\n";
            cout << setw(15) << left << "ID"
                    << setw(25) << left << "Name"
                    << setw(15) << left << "Total Score" << endl;
            cout << "---------------------------------------------------\n";
            cout << setw(15) << left << student->getID()
                    << setw(25) << left << student->getName()
                    << setw(15) << left << student->getTotalScore() << endl;
        } else {
            cout << "Student with ID " << studentID << " not found." << endl;
            }
        }

    };

int main() {
    Game game;
    game.loadStudentData();
    game.loadQuestionData();
    game.setUpDecks();
    game.startGame();
    return 0;
}