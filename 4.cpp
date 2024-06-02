#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

bool alwaysCooperate(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return true;
}

bool alwaysBetray(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return false;
}

bool titForTat(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) return true; // В первом раунде сотрудничаем
    return enemy_choices[round_number - 1]; // Повторяем последний выбор противника
}

// Тип данных для стратегии
typedef bool (*Strategy)(int, const vector<bool>&, const vector<bool>&);

// Функция для проведения игры между двумя стратегиями
void playGame(Strategy strategyA, const string& nameA, Strategy strategyB, const string& nameB) {
    // Генерация случайного количества раундов от 100 до 200
    srand(time(0));
    int num_rounds = rand() % 101 + 100;

    vector<bool> choicesA(num_rounds);
    vector<bool> choicesB(num_rounds);

    int scoreA = 0;
    int scoreB = 0;

    for (int round = 0; round < num_rounds; ++round) {
        bool choiceA = strategyA(round, choicesA, choicesB);
        bool choiceB = strategyB(round, choicesB, choicesA);

        choicesA[round] = choiceA;
        choicesB[round] = choiceB;

        if (choiceA && choiceB) {
            scoreA += 24;
            scoreB += 24;
        } else if (!choiceA && !choiceB) {
            scoreA += 4;
            scoreB += 4;
        } else if (choiceA && !choiceB) {
            scoreB += 20;
        } else if (!choiceA && choiceB) {
            scoreA += 20;
        }
    }

    // Вывод результатов
    cout << "Итоги игры между " << nameA << " и " << nameB << ":\n";
    cout << nameA << " набрал: " << scoreA << " очков.\n";
    cout << nameB << " набрал: " << scoreB << " очков.\n";
    cout << endl;
}

int main() {
    // Массив стратегий
    Strategy strategies[] = { alwaysCooperate, alwaysBetray, titForTat };
    string strategy_names[] = { "Always Cooperate", "Always Betray", "Tit for Tat" };

    // Проводим игры между всеми парами стратегий
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != j) {
                playGame(strategies[i], strategy_names[i], strategies[j], strategy_names[j]);
            }
        }
    }

    return 0;
}
