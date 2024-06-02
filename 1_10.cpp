#include <iostream>  
#include <cmath>     
#include <iomanip>   
#include <vector>    
using namespace std;   

const double EPSILON = 0.0001;
const int MAX_ITERATIONS = 1000;
const double PI = 3.14159265358979323846;

double f(double x) {
    return 2 * x + tan(x);
}

double df(double x) {
    return 2 + 1 / (cos(x) * cos(x)); // Производная от f
}

// Структура для хранения результатов метода половинного деления
struct BisectionResult {
    int iteration;   // Номер итерации
    double a;        // Левая граница интервала
    double b;        // Правая граница интервала
    double interval; // Длина интервала
};

// Метод половинного деления
vector<BisectionResult> bisection(double a, double b) {
    vector<BisectionResult> results;
    double c;
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        c = (a + b) / 2;
        results.push_back({i, a, b, b - a});
        if (fabs(f(c)) < EPSILON || (b - a) / 2 < EPSILON) { // Проверка, достигнута ли заданная точность
            break;
        }
        if (f(c) * f(a) > 0) { // Определение, в каком из подинтервалов находится корень
            a = c; // [c;b]
        } else {
            b = c; // [a;c]
        }
    }
    return results;
}

// Для хранения результатов итерационных методов
struct IterationResult {
    int iteration;   // Номер итерации
    double xn;       // Значение x на текущей итерации
    double xn1;      // Значение x на следующей итерации
    double interval; // Разница между xn и xn1
};

// Метод Ньютона
vector<IterationResult> newton(double x0) {
    vector<IterationResult> results;
    double x = x0;
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        double fx = f(x);
        double dfx = df(x);
        double x_next = x - fx / dfx;
        results.push_back({i, x, x_next, fabs(x_next - x)});
        if (fabs(x_next - x) < EPSILON) {
            break;
        }
        x = x_next;
    }
    return results;
}

// Метод простых итераций
vector<IterationResult> iteration(double x0) {
    vector<IterationResult> results;
    double x = x0;
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        double x_next = -tan(x) / 2; // Преобразование в g(x)
        results.push_back({i, x, x_next, fabs(x_next - x)});
        if (fabs(x_next - x) < EPSILON) {
            break;
        }
        x = x_next;
    }
    return results;
}

int main() {
    cout << setprecision(6) << fixed;

    double a = -PI / 4;
    double b = PI / 4;
    double x0 = 0.1; // Начальное значение для Ньютона

    // Метод половинного деления
    auto bisection_results = bisection(a, b);
    cout << "Метод половинного деления:" << std::endl;
    cout << "N         a             b           b-a" << endl;
    cout << "_______________________________________" << endl;
    for (const auto& res : bisection_results) {
        cout << res.iteration << "  " << setw(12) << res.a << "  " << setw(12) << res.b << "  " << setw(12) << res.interval << endl;
    }
    cout << "Найденный корень методом половинного деления: x = " << (bisection_results.back().a + bisection_results.back().b) / 2 << endl;

    // Метод Ньютона
    auto newton_results = newton(x0);
    cout << "\nМетод Ньютона:" << endl;
    cout << "Iteration         x               difference" << endl;
    cout << "__________________________________________________" << endl;
    for (const auto& res : newton_results) {
        cout << res.iteration << "  " << setw(16) << res.xn << "  " << setw(16) << res.interval << endl;
    }
    cout << "Найденный корень методом Ньютона: x = " << newton_results.back().xn1 << endl;

    // Метод простых итераций
    auto iteration_results = iteration(x0);
    cout << "\nМетод простых итераций:" << endl;
    cout << "Iteration        xn           xn+1          difference" << endl;
    cout << "__________________________________________________" << endl;
    for (const auto& res : iteration_results) {
        cout << res.iteration << "  " << setw(12) << res.xn << "  " << setw(12) << res.xn1 << "  " << setw(12) << res.interval << endl;
    }
    cout << "Найденный корень простым итерационным методом: x = " << iteration_results.back().xn1 << endl;

    return 0;
}
