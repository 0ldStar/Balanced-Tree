#include <iostream>
#include "menu.h"

BTree<int> bTree;
BTree<int> other;
using namespace std;

int main() {
    ofstream myfile;
    system("clear");
    int command = -1;
    while (command != 13) {
        printf("\tThis is interactive menu for BTree structure.\n"
               "What you want to do?\n"
               "1) Fill the bTree.\n"
               "2) Get bTree length.\n"
               "3) Clear the bTree.\n"
               "4) Check is the bTree empty.\n"
               "5) Get value from the bTree by key.\n"
               "6) Change value from the bTree by key.\n"
               "7) Delete value from the bTree.\n"
               "8) Print tree structure.\n"
               "9) Get laboriousness.\n"
               "10) Straight iterator menu.\n"
               "11) Back iterator menu.\n"
               "12) Test laboriousness.\n"
               "13) Exit.\n"
               ":");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        system("clear");
        switch (command) {
            case 1:
                printFillMenu();
                break;
            case 2:
                cout << "BTree len = " << bTree.getLength() << endl;
                break;
            case 3:
                if (!bTree.isEmpty())
                    bTree.clear();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 4:
                cout << "Is bTree empty? " << (bTree.isEmpty() ? "True" : "False") << endl;
                break;
            case 5:
                if (!bTree.isEmpty())
                    getElementMenu();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 6:
                if (!bTree.isEmpty())
                    fillValue();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 7:
                if (!bTree.isEmpty())
                    deleteValue();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 8:
                if (!bTree.isEmpty())
                    bTree.printStructure();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 9:
                if (!bTree.isEmpty())
                    cout << "Laboriousness: " << bTree.getLaboriousness() << endl;
                else
                    cout << "BTree is empty." << endl;
                break;
            case 10:
                if (!bTree.isEmpty())
                    straightIterMenu();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 11:
                if (!bTree.isEmpty())
                    backIterMenu();
                else
                    cout << "BTree is empty." << endl;
                break;
            case 12:
                myfile.open("../Rand1.txt", ios::trunc);
                myfile.close();

                myfile.open("../Rand2.txt", ios::trunc);
                myfile.close();

                for (int i = 1; i < 100000; i *= 10) {
                    test_rand(i);
                    test_ord(i);
                }
                system("python3 ../graph.py");
                break;
            default:
                break;
        }
    }
    return 0;
}
