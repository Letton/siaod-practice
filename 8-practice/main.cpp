#include <iostream>
#include <vector>
#include "Windows.h"

using namespace std;

long long bruteforce_count = 0;

long long dp_count = 0;

int countSequencesBruteforce(int n, int prevDigit) {
    ++bruteforce_count;
    if (n == 0) {
        return 1;
    }

    int count = 0;

    for (int nextDigit = 0; nextDigit <= 1; ++nextDigit) {
        if (prevDigit == 1 && nextDigit == 1) {
            continue;
        }

        count += countSequencesBruteforce(n - 1, nextDigit);
    }

    return count;
}

int countSequencesDP(int n) {
    vector<int> dp0(n + 1, 0);
    vector<int> dp1(n + 1, 0);

    dp0[1] = 1;
    dp1[1] = 1;

    for (int i = 2; i <= n; ++i) {
        ++dp_count;
        dp0[i] = dp0[i - 1] + dp1[i - 1];
        dp1[i] = dp0[i - 1];
    }
    return dp0[n] + dp1[n];
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    int n;
    cout << "Введите количество цифр в последовательности:\n";
    cin >> n;
    cout <<
        "Число последовательностей нулей и единиц длины n, в которых не встречаются две идущие подряд единицы (Bruteforce): "
        <<
        countSequencesBruteforce(n, 0) << "\n";
    cout <<
        "Число последовательностей нулей и единиц длины n, в которых не встречаются две идущие подряд единицы (DP): " <<
        countSequencesDP(n) << "\n";
    cout <<
        "Количество переборов (Bruteforce): "
        <<
        bruteforce_count << "\n";
    cout <<
        "Количество переборов (DP): " <<
        dp_count;
    return 0;
}
