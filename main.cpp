#include "node.h"
#include <fstream>
#include <cstring>
#include "rbtree.h"
using namespace std;

/*
 *Used geesforgeeks.org for some of the logic & learning in this project
 */

int main() {
    RedBlackTree myTree;
    while (true) {
        char input[100] = "";
        cout << "What would you like to do? (ADD/PRINT/QUIT): ";
        cin.getline(input, 100);

        if (strcasecmp(input, "ADD") == 0) {
            memset(input, 0, sizeof(input)); // Clears input array
            cout << "Read in manually or with file? (FILE/MAN): ";
            cin.getline(input, 100);

            if (strcasecmp(input, "FILE") == 0) {
                ifstream file("numbers.txt");
                if (!file.is_open()) {
                    cout << "Error opening numbers.txt" << endl;
                    continue;
                }
                int num;
                while (file >> num) {
                    myTree.add(num);
                }
                cout << "Numbers added from file successfully." << endl;
            }
            else if (strcasecmp(input, "MAN") == 0) {
                cout << "Enter numbers between 1 and 999 seperated by spaces: ";
                int num;
                cin >> num;
                myTree.add(num);
                while (cin.peek() != '\n' and cin >> num) {
                    myTree.add(num);
                }
                cin.ignore(1000, '\n');
                cout << "Numbers added manually succesfully." << endl;
            }
        }
        else if (strcasecmp(input, "PRINT") == 0) {
            myTree.print();
        }
        else if (strcasecmp(input, "QUIT") == 0) {
            return 0;
        }
        else {
            cout << "Invalid input." << endl;
        }
    }
}
