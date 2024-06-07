#include <iostream>
#include <string>

using namespace std;

// Function to implement Generalized Modus Ponens (GMP)
string generalized_modus_ponens(string premise, pair<string, string> rule) {
    if (premise == rule.first) {
        return rule.second;
    }
    return "";
}

// Function to implement Generalized Modus Tollens (GMT)
string generalized_modus_tollens(string premise, pair<string, string> rule) {
    if (premise == rule.second) {
        return rule.first;
    }
    return "";
}

int main() {
    string premise = "p";
    pair<string, string> rule = make_pair("p", "q");

    // Using Generalized Modus Ponens
    string result_gmp = generalized_modus_ponens(premise, rule);
    if (!result_gmp.empty()) {
        cout << "Using GMP: If premise '" << premise << "' is true and the rule is (" << rule.first << ", " << rule.second << "), then the conclusion is '" << result_gmp << "'" << endl;
    } else {
        cout << "GMP cannot be applied." << endl;
    }

    // Using Generalized Modus Tollens
    string result_gmt = generalized_modus_tollens(premise, rule);
    if (!result_gmt.empty()) {
        cout << "Using GMT: If premise '" << premise << "' is true and the rule is (" << rule.first << ", " << rule.second << "), then the conclusion is '" << result_gmt << "'" << endl;
    } else {
        cout << "GMT cannot be applied." << endl;
    }

    return 0;
}
