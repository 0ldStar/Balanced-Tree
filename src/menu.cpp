//
// Created by loki on 22.10.22.
//
#include "menu.h"

#define START_LENGTH 10
extern BTree<int> bTree;

void printFillMenu() {
    int command = -1;
    while (command != 4) {
        printf("What you want to do?\n"
               "1) Fill random value.\n"
               "2) Fill stepped value.\n"
               "3) Add new value to the bTree.\n"
               "4) Back to main menu.\n"
               ":");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        system("clear");
        switch (command) {
            case 1:
                fillRandom();
                return;
            case 2:
                fillStepped();
                return;
            case 3:
                fillValue();
                return;
            default:
                break;
        }
    }
}

void getElementMenu() {
    int key = -1;
    std::cout << "Enter key:";
    std::cin >> key;
    int value = bTree[key];
    if (bTree.getLaboriousness() != -1)
        std::cout << std::endl << "Value: " << value << std::endl;
    else
        std::cout << std::endl << "Bad key!" << std::endl;

}

void fillRandom() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < START_LENGTH; ++i) {
        bTree.push((START_LENGTH - i) / 2 - 1, 1 + (int) (std::rand() / ((RAND_MAX + 1u) / 20)));
    }
}

void fillStepped() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < START_LENGTH; ++i) {
        bTree.push((START_LENGTH / 2 - i) - 1, (START_LENGTH / 2 - i) - 1);
    }
}

void fillValue() {
    int key, num;
    std::cout << "Enter key:";
    std::cin >> key;
    std::cout << "Enter value:";
    std::cin >> num;
    std::cout << std::endl;
    bTree.push(key, num);
}

void deleteValue() {
    int key;
    std::cout << "Enter key:";
    std::cin >> key;
    std::cout << std::endl;
    bTree.pop(key);
}

void straightIterMenu() {
    int command = -1;
    BTreeStraightIterator<int> iter = BTreeStraightIterator<int>(nullptr, 0, -2);

    while (command != 7) {
        printf("What you want to do?\n"
               "1) Set iterator to the start of the bTree.\n"
               "2) Set iterator to step by value.\n"
               "3) Increment iterator.\n"
               "4) Decrement iterator.\n"
               "5) Get element from iterator.\n"
               "6) Print keys.\n"
               "7) Back to main menu.\n"
               ":");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        system("clear");
        switch (command) {
            case 1:
                iter = bTree.begin();
                break;
            case 2:
                unsigned step;
                std::cout << "Enter step: ";
                std::cin >> step;
                if (step > 0 && step < bTree.getSize()) {
                    iter = bTree.begin();
                    for (unsigned i = 0; i < step; ++i) iter++;
                } else {
                    std::cout << "[Error] Invalid step" << std::endl;
                }
                break;
            case 3:
                if (iter.getInd() >= 0 && iter.getInd() != bTree.getSize() - 1) {
                    iter++;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            case 4:
                if (iter.getInd() > 0) {
                    iter--;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            case 5:
                if (iter.getInd() != -2) {
                    std::cout << "Value: " << *iter << std::endl;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            case 6:
                if (!bTree.isEmpty()) {
                    for (auto it = bTree.begin(); it != bTree.end(); it++) {
                        std::cout << it.getKey() << " ";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "List is empty." << std::endl;
                }
                break;
            default:
                break;
        }
    }
}

void backIterMenu() {
    int command = -1;
    BTreeBackIterator<int> iter = BTreeBackIterator<int>(nullptr, 0, -2);

    while (command != 6) {
        printf("What you want to do?\n"
               "1) Set iterator to the end of the bTree.\n"
               "2) Set iterator to step by value.\n"
               "3) Increment iterator.\n"
               "4) Decrement iterator.\n"
               "5) Get element from iterator.\n"
               "6) Back to main menu.\n"
               ":");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {}
        }
        system("clear");
        switch (command) {
            case 1:
                iter = bTree.rbegin();
                break;
            case 2:
                unsigned step;
                std::cout << "Enter step: ";
                std::cin >> step;
                if (step > 0 && step < bTree.getSize()) {
                    iter = bTree.rbegin();
                    for (unsigned i = 0; i < step; ++i) iter++;
                } else {
                    std::cout << "[Error] Invalid step" << std::endl;
                }
                break;
            case 3:
                if (iter.getInd() > 0) {
                    iter++;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            case 4:
                if (iter.getInd() >= 0 && iter.getInd() != bTree.getSize() - 1) {
                    iter--;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            case 5:
                if (iter.getInd() >= 0) {
                    std::cout << "Value: " << *iter << std::endl;
                } else {
                    std::cout << "[Error] Bad iterator" << std::endl;
                }
                break;
            default:
                break;
        }
    }
}