//
// Created by loki on 17.11.22.
//

#include "Laboriousness.h"

using namespace std;
ofstream outputFile;


void sRand() {
    srand(time(0));
    RRand = (INT_64) rand();
}

INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

//Тест трудоёмкости операций случайного BST-дерева

void test_rand(int n) {
    outputFile.open("../Rand1.txt", ios::app);
    outputFile << n << " ";
    BTree<int> tree;
    INT_64 *m = new INT_64[n];
    sRand();

    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree.push(m[i], 1);
    }

//    cout << "Items count: " << tree.getLength() << endl;

    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {
            tree.pop(LineRand());
            D += tree.getLaboriousness();
            tree.push(m[rand() % n], 1);
            I += tree.getLaboriousness();

            tree[LineRand()];
            if (tree.getLaboriousness() != -1)
                S += tree.getLaboriousness();

        } else {
            int ind = rand() % n;
            tree.pop(m[ind]);
            D += tree.getLaboriousness();
            INT_64 key = LineRand();
            tree.push(key, 1);
            I += tree.getLaboriousness();
            m[ind] = key;

            tree[m[rand() % n]];
            if (tree.getLaboriousness() != -1)
                S += tree.getLaboriousness();
        }

//теоретической оценки трудоёмкости операций BTree
    outputFile << log2((double) n) << " ";
//экспериментальной оценки трудоёмкости вставки
    outputFile << I / (n / 2.0) << " ";
//экспериментальной оценки трудоёмкости удаления
    outputFile << D / (n / 2.0) << " ";
//экспериментальной оценки трудоёмкости поиска
    outputFile << S / (n / 2.0) << endl;
    delete[] m;
    outputFile.close();
}

//Тест трудоёмкости операций вырожденного BTree-дерева

void test_ord(int n) {
    outputFile.open("../Rand2.txt", ios::app);
    BTree<int> tree;
    auto m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.push(m[i], 1);
    }

//    cout << "Items count: " << tree.getLength() << endl;

    double I = 0;
    double D = 0;
    double S = 0;
    sRand();

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);
            tree.pop(k);
            D += tree.getLaboriousness();
            tree.push(m[rand() % n], 1);
            I += tree.getLaboriousness();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            tree[k];
            if (tree.getLaboriousness() != -1)
                S += tree.getLaboriousness();
        } else {
            int ind = rand() % n;
            tree.pop(m[ind]);
            D += tree.getLaboriousness();
            int k = LineRand() % (10000 * n);
            k = k + k % 2;
            tree.push(k, 1);
            I += tree.getLaboriousness();
            m[ind] = k;

            tree[m[rand() % n]];
            if (tree.getLaboriousness() != -1)
                S += tree.getLaboriousness();
        }
    }

//    cout << "Items count: " << tree.getLength() << endl;
//теоретической оценки трудоёмкости операций BTree
//    cout << "n/2 = " << n / 2 << endl;
    outputFile << n / 2.0 << " ";
//экспериментальной оценки трудоёмкости вставки
//    cout << "Count push: " << I / (n / 2) << endl;
    outputFile << I / (n / 2.0) << " ";
//экспериментальной оценки трудоёмкости удаления
//    cout << "Count delete: " << D / (n / 2) << endl;
    outputFile << D / (n / 2.0) << " ";
//экспериментальной оценки трудоёмкости поиска
//    cout << "Count search: " << S / (n / 2) << endl;
    outputFile << S / (n / 2.0) << endl;
    outputFile.close();
    delete[] m;
}
