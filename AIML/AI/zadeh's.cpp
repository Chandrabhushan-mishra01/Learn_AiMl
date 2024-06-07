#include <iostream>
#include <vector>

using namespace std;

// Zadeh's max-min composition rule
double maxMinComposition(const vector<vector<double>>& rel1, const vector<vector<double>>& rel2) {
    int r1 = rel1.size();
    int c1 = rel1[0].size();
    int r2 = rel2.size();
    int c2 = rel2[0].size();

    // Check if dimensions are compatible for composition
    if (c1 != r2) {
        cerr << "Error: Incompatible dimensions for composition." << endl;
        return -1; // Invalid result
    }

    vector<vector<double>> composition(r1, vector<double>(c2, 0.0));

    // Compute composition using max-min rule
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            double maxMin = 0.0;
            for (int k = 0; k < c1; ++k) {
                maxMin = max(maxMin, min(rel1[i][k], rel2[k][j]));
            }
            composition[i][j] = maxMin;
        }
    }

    // Print the composition
    cout << "Composition using Zadeh's max-min rule:" << endl;
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            cout << composition[i][j] << " ";
        }
        cout << endl;
    }

    return 0; // Successful composition
}

int main() {
    // Example fuzzy relations
    vector<vector<double>> rel1 = {{0.3, 0.5},
                                   {0.7, 0.2}};
    vector<vector<double>> rel2 = {{0.6, 0.4},
                                   {0.1, 0.9}};

    // Compute composition using Zadeh's max-min rule
    maxMinComposition(rel1, rel2);

    return 0;
}
