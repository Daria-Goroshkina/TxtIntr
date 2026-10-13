#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void printHelp() {
    cout << "Статистический калькулятор (вариант 7)\n";
    cout << "Использование:\n";
    cout << "  ./calc -o mean   <числа...>   - среднее арифметическое\n";
    cout << "  ./calc -o median <числа...>   - медиана\n";
    cout << "  ./calc -h | --help            - эта справка\n\n";
    cout << "Количество чисел: от 7 до 9\n";
    cout << "Пример: ./calc -o mean 1 2 3 4 5 6 7\n";
}

double calcMean(const vector<double>& v) {
    double sum = 0;
    for (double x : v) sum += x;
    return sum / v.size();
}

double calcMedian(vector<double> v) {
    sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0)
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    else
        return v[n/2];
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    string operation;
    vector<double> numbers;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                cerr << "Ошибка: не указана операция после " << arg << "\n";
                return 1;
            }
        } else {
            try {
                numbers.push_back(stod(arg));
            } catch (...) {
                cerr << "Ошибка: '" << arg << "' не является числом\n";
                return 1;
            }
        }
    }

    if (operation.empty()) {
        cerr << "Ошибка: не задана операция (-o mean или -o median)\n";
        printHelp();
        return 1;
    }

    if (numbers.size() < 7 || numbers.size() > 9) {
        cerr << "Ошибка: количество чисел должно быть от 7 до 9 (сейчас " 
             << numbers.size() << ")\n";
        return 1;
    }

    if (operation == "mean") {
        cout << "Среднее арифметическое: " << calcMean(numbers) << "\n";
    } else if (operation == "median") {
        cout << "Медиана: " << calcMedian(numbers) << "\n";
    } else {
        cerr << "Ошибка: неизвестная операция '" << operation << "'\n";
        printHelp();
        return 1;
    }

    return 0;
}
