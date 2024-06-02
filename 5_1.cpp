#include <iostream>
#include <vector>

using namespace std;

// Линейный конгруэнтный генератор
vector<int> linearCongruentialGenerator(int X0, int A, int B, int C) {
    vector<int> sequence;
    int current = X0;
    sequence.push_back(current);

    do {
        current = (A * current + B) % C;
        sequence.push_back(current);
    } while (current != X0);

    return sequence;
}

int main() {
    // Входные данные
    int X0, A, B, C;
    cout << "Введите начальное значение X0: ";
    cin >> X0;
    cout << "Введите множитель A: ";
    cin >> A;
    cout << "Введите инкрементирующее значение B: ";
    cin >> B;
    cout << "Введите диапазон значений C: ";
    cin >> C;

    // Генерация последовательности
    vector<int> sequence = linearCongruentialGenerator(X0, A, B, C);

    // Вывод последовательности
    cout << "Последовательность: ";
    for (int i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << " ";
    }
    cout << endl;

    // Нахождение индекса, с которого начинается повторение последовательности
    int repeatIndex = sequence.size() - 1;
    cout << "Индекс повторения: " << repeatIndex << endl;

    return 0;
}
