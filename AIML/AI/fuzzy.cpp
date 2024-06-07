#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;
unordered_map<string, float> Union( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;

    // Iterate through M1 and add its entries to F
    for ( auto &entry : M1)
    {
        F[entry.first] = entry.second;
    }

    // Iterate through M2
    for ( auto &entry : M2)
    {
        // If entry already exists in F, take the maximum of its current value and the value from M2
        if (F.find(entry.first) != F.end())
        {
            F[entry.first] = max(F[entry.first], entry.second);
        }
        // If entry doesn't exist in F, add it to F
        else
        {
            F[entry.first] = entry.second;
        }
    }

    return F;
}

unordered_map<string, float> Intersection( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;
    for ( auto &entry : M1)
    {
        if (M2.find(entry.first) != M2.end())
        {
            F[entry.first] = min(entry.second, M2.at(entry.first));
        }
    }
    return F;
}

unordered_map<string, float> Complement( unordered_map<string, float> &M)
{
    unordered_map<string, float> F;
    for ( auto &entry : M)
    {
        F[entry.first] = 1 - entry.second;
    }
    return F;
}

unordered_map<string, float> Difference( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> M2c = Complement(M2);
    return Intersection(M1, M2c);
}

unordered_map<string, float> VectorProduct( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;
    for ( auto &entry : M1)
    {
        if (M2.find(entry.first) != M2.end())
        {
            F[entry.first] = entry.second * M2[entry.first];
        }
    }
    return F;
}

unordered_map<string, float> ScalarProduct( unordered_map<string, float> &M1, float C)
{
    unordered_map<string, float> F;
    for ( auto &entry : M1)
    {
        F[entry.first] = entry.second * C;
    }
    return F;
}

unordered_map<string, float> Sum( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;

    // Iterate through M1
    for ( auto &entry : M1)
    {
        // If entry exists in M2, compute the sum using the formula A + B - A * B
        if (M2.find(entry.first) != M2.end())
        {
            F[entry.first] = entry.second + M2.at(entry.first) - entry.second * M2.at(entry.first);
        }
        // If entry doesn't exist in M2, add it with its value from M1
        else
        {
            F[entry.first] = entry.second;
        }
    }

    // Iterate through M2 to add elements not present in M1
    for ( auto &entry : M2)
    {
        if (M1.find(entry.first) == M1.end())
        {
            F[entry.first] = entry.second;
        }
    }

    return F;
}

unordered_map<string, float> DisjunctiveSum( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> M1c = Complement(M1);
    unordered_map<string, float> M2c = Complement(M2);
    unordered_map<string, float> I1 = Intersection(M1c, M2);
    unordered_map<string, float> I2 = Intersection(M1, M2c);
    return Union(I1, I2);
}

unordered_map<string, float> BoundedSum( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;

    // Iterate through M1
    for ( auto &entry : M1)
    {
        // Check if the key exists in M2
        if (M2.find(entry.first) != M2.end())
        {
            // Calculate the sum of membership values and bound it by 1
            float sum = entry.second + M2.at(entry.first);
            F[entry.first] = min(1.0f, sum);
        }
        else
        {
            // If the key doesn't exist in M2, add it to the result with its value bounded by 1
            F[entry.first] = min(1.0f, entry.second);
        }
    }

    // Iterate through M2 to add elements not present in M1
    for ( auto &entry : M2)
    {
        // If the key doesn't exist in M1, add it to the result with its value bounded by 1
        if (M1.find(entry.first) == M1.end())
        {
            F[entry.first] = min(1.0f, entry.second);
        }
    }

    return F;
}

unordered_map<string, float> BoundedDifference( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    unordered_map<string, float> F;

    // Iterate through M1
    for ( auto &entry : M1)
    {
        // Check if the key exists in M2
        if (M2.find(entry.first) != M2.end())
        {
            // Calculate the difference of membership values and bound it by 0
            float diff = entry.second + M2.at(entry.first) - 1;
            F[entry.first] = max(0.0f, diff);
        }
        else
        {
            // If the key doesn't exist in M2, add it to the result with its value bounded by 0
            F[entry.first] = max(0.0f, entry.second - 1);
        }
    }

    // Iterate through M2 to add elements not present in M1
    for ( auto &entry : M2)
    {
        // If the key doesn't exist in M1, add it to the result with its value bounded by 0
        if (M1.find(entry.first) == M1.end())
        {
            F[entry.first] = max(0.0f, 1 - entry.second);
        }
    }

    return F;
}

bool Equality( unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    if (M1.size() != M2.size())
    {
        return false;
    }
    for ( auto &entry : M1)
    {
        if (M2.find(entry.first) == M2.end() || M2.at(entry.first) != entry.second)
        {
            return false;
        }
    }
    return true;
}

unordered_map<string, float> Power( unordered_map<string, float> &M, float p)
{
    unordered_map<string, float> F;
    for ( auto &entry : M)
    {
        F[entry.first] = pow(entry.second, p);
    }
    return F;
}


void printMenu()
{
    cout << "Fuzzy Operations Menu:" << endl;
    cout << "1. Union" << endl;
    cout << "2. Intersection" << endl;
    cout << "3. Complement" << endl;
    cout << "4. Difference" << endl;
    cout << "5. Vector Product" << endl;
    cout << "6. Scalar Product" << endl;
    cout << "7. Sum" << endl;
    cout << "8. Disjunctive Sum" << endl;
    cout << "9. Bounded Sum" << endl;
    cout << "10. Bounded Difference" << endl;
    cout << "11. Equality" << endl;
    cout << "12. Power" << endl;
    cout << "0. Exit" << endl;
}

unordered_map<string, float> takeInput()
{
    unordered_map<string, float> M;
    cout << "Enter membership function: " << endl;
    int n;
    cout << "Enter the number of key-value pairs: ";
    cin >> n;
    while (n > 0)
    {
        string k;
        float v;
        cout << "Enter key-value pair (space-separated): ";
        cin >> k >> v;
        M[k] = v;
        n--;
    }
    return M;
}
unordered_map<string, float> performOperation(int choice,  unordered_map<string, float> &M1,  unordered_map<string, float> &M2)
{
    if (choice == 1)
    {
        return Union(M1, M2);
    }
    else if (choice == 2)
    {
        return Intersection(M1, M2);
    }
    else if (choice == 3)
    {
        return Complement(M1);
    }
    else if (choice == 4)
    {
        return Difference(M1, M2);
    }
    else if (choice == 5)
    {
        return VectorProduct(M1, M2);
    }
    else if (choice == 6)
    {
        float C;
        cout << "Enter scalar value: ";
        cin >> C;
        return ScalarProduct(M1, C);
    }
    else if (choice == 7)
    {
        return Sum(M1, M2);
    }
    else if (choice == 8)
    {
        return DisjunctiveSum(M1, M2);
    }
    else if (choice == 9)
    {
        return BoundedSum(M1, M2);
    }
    else if (choice == 10)
    {
        return BoundedDifference(M1, M2);
    }
    else if (choice == 11)
    {
        bool result = Equality(M1, M2);
        cout << "Result: " << (result ? "True" : "False") << endl;
        return unordered_map<string, float>(); // Return empty map
    }
    else if (choice == 12)
    {
        float p;
        cout << "Enter power value: ";
        cin >> p;
        return Power(M1, p);
    }
    else if (choice == 0)
    {
        cout << "Exiting program." << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid choice. Please enter a valid option." << endl;
        return unordered_map<string, float>(); // Return empty map
    }
}

int main()
{
    auto M1 = takeInput();
    auto M2 = takeInput();

    while (true)
    {
        printMenu();
        int choice;
        cout << "Enter your choice (0-13): ";
        cin >> choice;
        auto result = performOperation(choice, M1, M2);
        if (!result.empty())
        {
            cout << "Resultant Membership Function:" << endl;
            for ( auto &kv : result)
            {
                cout << kv.first << ": " << kv.second << endl;
            }
        }
    }
    return 0;
}