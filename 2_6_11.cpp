#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <chrono>
using namespace std;

// Нахождение среднего значения и вычисление суммы квадратов разностей
void func2(vector<int>& array, int n, double& mean_value, double& sum_of_squares) {
    double sum = 0;
    for (auto i : array) {// считаем сумму элементов
        sum += i;
    }
    mean_value = sum / n; // среднее значение
    sum_of_squares = 0;
    for (int i = 0; i < n; ++i) {   
        sum_of_squares += pow(array[i] - mean_value, 2);// считаем сумму квадратов разностей
    }

}

// Функция для изменения местами первый и последний разряды четных элементов с четным номером
vector<int> func3(vector<int>& array) {
    vector<int> result(array.size()); // создаём пустой вектор
    for (int i = 0; i < array.size(); i++) { // проходимся по вектору
        result[i] = array[i];
        if (i % 2 == 0 && array[i] % 2 == 0) { // если индекс чётный и само число чётное, то
            int temp = result[i]; // выполняем заменц цифр
            int last_digit = temp % 10; // берём посдеднюю цифру
            temp /= 10; // берём первую цифру
            int first_digit = temp; 
            result[i] = last_digit * 10 + first_digit;
        }
    }
    return result;
}

vector<int> func4(vector<int> array){
   int firstElement = array[0]; // Сохранение первого элемента
    // Сдвиг всех элементов на одну позицию назад
    for (size_t i = 0; i < array.size() - 1; ++i) {
        array[i] = array[i + 1];
    }
    // Помещение сохраненного первого элемента в конец массива
    array[array.size() - 1] = firstElement;
    return array; // Возврат модифицированного вектора
}

void func5(vector<int>& array_int, vector<int>& unique_elements, vector<int>& counts) {
    sort(array_int.begin(), array_int.end());

    for (int num : array_int) {
        // вектор уникальных элементов пустой или текущий элемент отличается от последнего элемента вектора
        if (unique_elements.empty() || num != unique_elements.back()) {
            unique_elements.push_back(num);
            counts.push_back(1);
        } else {
            counts.back()++; // увеличиваем счетчик для этого элемента
        }
    }

    // Вывод массива уникальных элементов
    cout << "Уникальные элементы: ";
    for (int i = 0; i < unique_elements.size(); i++) {
        cout << unique_elements[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 10;
    int n1 = 50;
    int cnt = 0;
    double mean_value, sum_of_squares;

    //генерация случайных вещественных чисел
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux48_base gen(seed);
    uniform_real_distribution<> dis(0, 100);
    
    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        array[i] = dis(gen);
    }

    
    func2(array, n, mean_value, sum_of_squares);
    cout << "Исходный массив: ";
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Среднее значение: " << mean_value << endl;
    cout << "Сумма квадратов разностей: " << sum_of_squares << endl;


    vector<int> modifiedArray = func4(array);
    cout << "Модифицированный массив: ";
    for (auto num : modifiedArray) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> array_int(n1);
    uniform_int_distribution<> dis_int(-10, 10);
    for (int i = 0; i < n1; ++i) {
        array_int[i] = dis_int(gen);
    }
    vector<int> unique_elements;
    vector<int> counts;
    func5(array_int, unique_elements, counts);

    cout << "Уникальные элементы и их количество: ";
    for (size_t i = 0; i < unique_elements.size(); ++i) {
        cout << unique_elements[i] << " = " << counts[i] << " раз(а)" << ";   ";
        cnt += counts[i];
    }
    cout << "Массив заполнен "<< cnt << " числами"<< endl;
    
    return 0;
}