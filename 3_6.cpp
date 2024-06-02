#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <numeric>
#include <chrono>
using namespace std;

// Функция для заполнения массива случайными числами от 1 до 100
void fillArray(vector<int>& arr) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux48_base gen(seed);
    uniform_real_distribution<> dis(1, 100);

    for (int& num : arr) {
        num = dis(gen);
    }
}

int typeOfElementCount(const vector<int>& container, int element) { //подсчет количества вхождений заданного элемента в вектор
    int count = 0;
    for (const int& value : container) {
        if (value == element) count++;
    }
    return count;
}

// Функция для расчета реального математического ожидания
double calculateMean(const vector<int>& arr) {
    double sum = 0;
    for (const int& value : arr) {
        sum += value;
    }
    return sum / arr.size();
}

// Функция для расчета дисперсии для вычисления стандартного отклонения
double Dispersion(const vector<int>& arr) {
    double mean = calculateMean(arr);
    double sum = 0;
    for (const int& value : arr) {
        //Для каждого элемента вычисляем квадрат отклонения от среднего и добавляем его к сумме
        sum += (value - mean) * (value - mean);
    }
    return sum / (arr.size() - 1);
}

// Вспомогательная функция для расчета функции Лапласа для нахождения ожидаемых частот
double laplaceCdf(double z) {
    return 0.5 * (1.0 + erf(z / sqrt(2.0))); //erf - функция ошибок 
}

double calculateChiSquare(const vector<int>& arr) { // Функция для вычисления критерия хи-квадрат
    int size = arr.size();
    double chi2 = 0;
    double mean = calculateMean(arr); //ожидание
    double stdDev = sqrt(Dispersion(arr)); // дисперсия

    for (int i = 1; i <= 100; i++) { //разность между наблюдаемой и ожидаемой частотой, возводится в квадрат и делится на ожидаемую частоту
        double expectedFreq = size * (laplaceCdf((i - mean) / stdDev) - laplaceCdf((i - 1 - mean) / stdDev));//ожидаемое число попаданий в i-ый интервал
        double observedFreq = typeOfElementCount(arr, i);//количество элементов, попавших в i-ый интервал;
        chi2 += pow(observedFreq - expectedFreq, 2) / expectedFreq;//значение хи-квадрат суммируется на каждом элементе
    }
    return chi2;
}

int main() {
    // Создаем 3 массива размером 50, 100 и 1000
    vector<int> array50(50), array100(100), array1000(1000);

    // Заполняем массивы случайными числами от 1 до 100
    fillArray(array50);
    fillArray(array100);
    fillArray(array1000);


    // Рассчитываем значение критерия Хи-квадрат для каждого массива
    double chiSquare50 = calculateChiSquare(array50);
    double chiSquare100 = calculateChiSquare(array100);
    double chiSquare1000 = calculateChiSquare(array1000);

    // Выводим результаты
    cout << "Массив размером 50:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare50 << endl;
    if (chiSquare50 < 67.5) { // Критическое значение для уровня значимости 0.05 и 49 степеней свободы
        cout << "Гипотеза о нормальном распределении не отвергается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << calculateMean(array50) << endl;
    cout << endl;
    
    cout << "Массив размером 100:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare100 << endl;
    if (chiSquare100 < 124.342) { // Критическое значение для уровня значимости 0.05 и 99 степеней свободы
        cout << "Гипотеза о нормальном распределении не отвергается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << calculateMean(array100) << endl;
    cout << endl;
    
    cout << "Массив размером 1000:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare1000 << endl;
    if (chiSquare1000 < 1072.6) { // Критическое значение для уровня значимости 0.05 и 999 степеней свободы
        cout << "Гипотеза о нормальном распределении не отвергается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << calculateMean(array1000) << endl;
    }