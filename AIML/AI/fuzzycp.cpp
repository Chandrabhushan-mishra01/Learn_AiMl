#include <iostream>
#include <vector>

using namespace std;

void cartesian() {
    int n, m;
    cout << "\nEnter number of elements in first set (A): ";
    cin >> n;
    vector<double> A(n);
    vector<double> B;
    cout << "Enter elements for A:\n";
    for (int i = 0; i < n; ++i) {
        double ele;
        cin >> ele;
        A[i] = ele;
    }
    cout << "\nEnter number of elements in second set (B): ";
    cin >> m;
    B.resize(m);
    cout << "Enter elements for B:\n";
    for (int i = 0; i < m; ++i) {
        double ele;
        cin >> ele;
        B[i] = ele;
    }
    cout << "A = {";
    for (int i = 0; i < n; ++i) {
        cout << A[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "B = {";
    for (int i = 0; i < m; ++i) {
        cout << B[i];
        if (i < m - 1)
            cout << ", ";
    }
    cout << "}\n";
    vector<vector<double>> cart_prod(n, vector<double>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cart_prod[i][j] = min(A[i], B[j]);
        }
    }
    cout << "A x B = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << cart_prod[i][j] << "  ";
        }
        cout << "\n";
    }
}

void minmax() {
    int r1, c1;
    cout << "Enter number of rows of first relation (R1): ";
    cin >> r1;
    cout << "Enter number of columns of first relation (R1): ";
    cin >> c1;
    vector<vector<double>> rel1(r1, vector<double>(c1));
    cout << "Enter the elements for R1:\n";
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c1; ++j) {
            cin >> rel1[i][j];
        }
    }
    
    int r2, c2;
    cout << "Enter number of rows of second relation (R2): ";
    cin >> r2;
    cout << "Enter number of columns of second relation (R2): ";
    cin >> c2;
    vector<vector<double>> rel2(r2, vector<double>(c2));
    cout << "Enter the elements for R2:\n";
    for (int i = 0; i < r2; ++i) {
        for (int j = 0; j < c2; ++j) {
            cin >> rel2[i][j];
        }
    }
    
    cout << "\nR1 = \n";
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c1; ++j) {
            cout << rel1[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\nR2 = \n";
    for (int i = 0; i < r2; ++i) {
        for (int j = 0; j < c2; ++j) {
            cout << rel2[i][j] << " ";
        }
        cout << "\n";
    }
    
    vector<vector<double>> comp(r1, vector<double>(c2));
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            vector<double> l;
            for (int k = 0; k < r2; ++k) {
                l.push_back(min(rel1[i][k], rel2[k][j]));
            }
            comp[i][j] = *max_element(l.begin(), l.end());
        }
    }
    
    cout << "\nR1 composition R2 =\n";
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            cout << comp[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int ch = 1;
    while (ch == 1) {
        cout << "MENU:\n----\n1->Cartesian Product\n2->Minmax Composition\n3->Exit\n";
        int op;
        cout << "Enter Your Choice: ";
        cin >> op;
        if (op == 1) {
            cartesian();
        } else if (op == 2) {
            minmax();
        } else if (op == 3) {
            break;
        } else {
            cout << "Wrong Choice!\n";
        }
        cout << "Do you wish to continue (1-Yes | 0-No): ";
        cin >> ch;
        cout << "\n";
    }
    return 0;
}
