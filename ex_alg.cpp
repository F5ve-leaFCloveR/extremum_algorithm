#include <iostream>
#include <ctime>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;


float metamorph(float x) {
    float y = x * x * x - x + exp(-x);
    return y;
}

void enumeration(float left, float right, int extr) {
    float eps = 0.001;// шаг
    float min;
    float ord = 0; // переменная для x
    int count = 0; // счетчик шагов
    if (extr == 1) { // задаем минимальное значение для этой функции
        min = -999;
    }
    else {
        min = 999;
    }
    for (left; left <= right; left += eps) {
        float y = metamorph(left);
        if (extr == 1) {
            if (y > min) {
                min = y;
                ord = left;
            }
        }
        else {
            if (y < min) {
                min = y;
                ord = left;
            }
        }

        count++;
    }
    cout << '\n' << "Экстремума = " << min << '\n' << "Значение x = " << ord << '\n' << "Количество шагов = " << count << '\n';
}

void dividing(float left, float right, int extr) {
    float a = left;
    float b = right;
    float x1, a1, b1, eps = 10e-6;

    while (true) {

        float delta = (b - a) / 10;
        float alpha = ((a + b) / 2) - delta;
        float betta = alpha + 2 * delta;
        float fn_alpha = metamorph(alpha);
        float fn_betta = metamorph(betta);

        if (extr == 1) {
            if (fn_alpha >= fn_betta) {
                x1 = alpha;
                a1 = a;
                b1 = betta;
            }
            else {
                x1 = betta;
                a1 = alpha;
                b1 = b;
            }
        }
        else {
            if (fn_alpha <= fn_betta) {
                x1 = alpha;
                a1 = a;
                b1 = betta;
            }
            else {
                x1 = betta;
                a1 = alpha;
                b1 = b;
            }
        }

        if (abs(b1 - a1) < eps) {
            break;
        }
        else {
            a = a1;
            b = b1;
        }
    }
    float ord = (a1 + b1) / 2;
    cout << '\n' << "Экстремума = " << metamorph(ord) << '\n' << "Значение x = " << ord << '\n';
}

void golden_ratio(float left, float right, int extr) {
    float a = left;
    float b = right;
    float x1, a1, b1, eps = 10e-6;

    while (true) {

        float delta = b - a;
        float alpha = a + ((2 * delta) / (3 + sqrt(5)));
        float betta = a + ((2 * delta) / (1 + sqrt(5)));
        float fn_alpha = metamorph(alpha);
        float fn_betta = metamorph(betta);

        if (extr == 1) {
            if (fn_alpha >= fn_betta) {
                x1 = alpha;
                a1 = a;
                b1 = betta;
            }
            else {
                x1 = betta;
                a1 = alpha;
                b1 = b;
            }
        }
        else {
            if (fn_alpha <= fn_betta) {
                x1 = alpha;
                a1 = a;
                b1 = betta;
            }
            else {
                x1 = betta;
                a1 = alpha;
                b1 = b;
            }
        }

        if (abs(b1 - a1) < eps) {
            break;
        }
        else {
            a = a1;
            b = b1;
        }
    }
    float ord = (a1 + b1) / 2.0;
    cout << '\n' << "Экстремума = " << metamorph(ord) << '\n' << "Значение x = " << ord << '\n';
}

void fibonachi(float left, float right, int extr) {
    float a = left;
    float b = right;
    float delta = b - a;
    float eps = 0.000001;
    vector <float> fib = { 1., 1. };
    float n = 1, k = 0;
    float a1, b1;

    while (true) {
        fib.push_back(fib[n] + fib[n - 1]);
        if (delta / fib[n] <= eps) {
            break;
        }
        else {
            n++;
        }
    }
    float b_k = b, a_k = a;
    while (true) {
        float delta_k = b_k - a_k;
        float alpha_k = a_k + ((fib[n - k - 2]) / (fib[n - k])) * delta_k;
        float beta_k = a_k + ((fib[n - k - 1]) / (fib[n - k])) * delta_k;
        float f_alpha = metamorph(alpha_k), f_beta = metamorph(beta_k);

        if (extr == 2) {
            if (f_alpha <= f_beta) {
                a1 = a_k;
                b1 = beta_k;
            }
            else {
                a1 = alpha_k;
                b1 = b_k;
            }
        }
        else {
            if (f_alpha >= f_beta) {
                a1 = a_k;
                b1 = beta_k;
            }
            else {
                a1 = alpha_k;
                b1 = b_k;
            }
        }
        if ((b1 - a1) < eps) {
            break;
        }
        else {
            a_k = a1;
            b_k = b1;
            k++;
        }
    }
    float ord = (a1 + b1) / 2.0;
    cout << '\n' << "Экстремума = " << metamorph(ord) << '\n' << "Значение x = " << ord << '\n';
}

int main()
{
    int choose;
    cout << "Выберите метод для нахождения экстремумы: " << '\n'
        << "(1) Методом «пассивного поиска»" << '\n'
        << "(2) Методом «деления отрезка» пополам" << '\n'
        << "(3) Методом «золотого сечения»" << '\n'
        << "(4) Методом «Фибоначчи»" << '\n'
        << "Ваш выбор: ";
    cin >> choose;
    int left, right, extr;
    cout << "Введите границы для функции: ";
    cin >> left >> right;
    cout << "Поиск максимума (1) или минимума (2)?";
    cin >> extr;
    clock_t start = clock();
    switch (choose) {
    case 1:
        enumeration(left, right, extr);
        break;
    case 2:
        dividing(left, right, extr);
        break;
    case 3:
        golden_ratio(left, right, extr);
        break;
    case 4:
        fibonachi(left, right, extr);
        break;
    default:
        break;
    }
    clock_t end = clock();
    cout << "Время работы программы = " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
}

