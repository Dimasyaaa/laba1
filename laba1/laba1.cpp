#include <iostream>
#include <stdexcept> // для std::invalid_argument
#include <cmath>

using namespace std;

//Реализуйте класс обыкновенной дроби.
// Экземпляр должен поддерживать функционал сложения, вычитания, умножения и деления с другим экземпляром, целым числом, вещественным числом.
// Операторы инкремента и декремента должны менять числитель дроби.
// Сократимая дробь должна быть сокращена. Дроби должны быть сравнимы.
// Экземпляры должны быть выводимы на экран с помощью собственного метода класса и через стандартный поток вывода.

class Drobi {
private:
    int chislitel;  // числитель
    int znamenatel; // знаменатель

    // Метод для нахождения НОД
    int NOD(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return abs(a); // возвращаем абсолютное значение НОД
    }

    // Метод для сокращения дроби
    void Sokratit() {
        int gcd = NOD(chislitel, znamenatel); // находим НОД
        chislitel /= gcd;
        znamenatel /= gcd;
        // Если знаменатель отрицательный, меняем знак числителя
        if (znamenatel < 0) {
            chislitel = -chislitel;
            znamenatel = -znamenatel;
        }
    }

public:
    // Конструктор с параметрами
    Drobi(int ch, int zn) : chislitel(ch), znamenatel(zn) {
        if (zn == 0) {
            throw invalid_argument("Знаменатель не может быть равен 0.");
        }
        Sokratit();
    }

    // Конструктор по умолчанию
    Drobi() : chislitel(1), znamenatel(1) {}

    // Другие методы: операции над дробями
    Drobi DrobiSum(const Drobi& other) const {
        return Drobi(chislitel * other.znamenatel + other.chislitel * znamenatel, znamenatel * other.znamenatel);
    }

    Drobi DrobiMinus(const Drobi& other) const {
        return Drobi(chislitel * other.znamenatel - other.chislitel * znamenatel, znamenatel * other.znamenatel);
    }

    Drobi DrobiUmnoz(const Drobi& other) const {
        return Drobi(chislitel * other.chislitel, znamenatel * other.znamenatel);
    }

    Drobi DrobiDelenie(const Drobi& other) const {
        if (other.chislitel == 0) {
            throw invalid_argument("Деление на 0 недопустимо.");
        }
        return Drobi(chislitel * other.znamenatel, znamenatel * other.chislitel);
    }

    // Перегрузка оператора вывода для дробей(украл из инета, не умею норально перегружать ф-ии)
    friend ostream& operator<<(ostream& os, const Drobi& d) {
        os << d.chislitel << "/" << d.znamenatel;
        return os;
    }

    // Метод для ввода дроби
    void Input() {
        cout << "Введите числитель: ";
        cin >> chislitel;
        cout << "Введите знаменатель: ";
        cin >> znamenatel;
        if (znamenatel == 0) {
            throw invalid_argument("Знаменатель не может быть равен 0.");
        }
        Sokratit();
    }

};

int main() {
    setlocale(LC_ALL, "Rus");
    try {
        Drobi d1, d2;

        // Ввод дробей с клавиатуры
        cout << "Введите первую дробь:\n";
        d1.Input();
        cout << "Введите вторую дробь:\n";
        d2.Input();

        cout << "d1: " << d1 << endl;
        cout << "d2: " << d2 << endl;
        cout << "Сумма: " << d1.DrobiSum(d2) << endl;
        cout << "Разность: " << d1.DrobiMinus(d2) << endl;
        cout << "Произведение: " << d1.DrobiUmnoz(d2) << endl;
        cout << "Частное: " << d1.DrobiDelenie(d2) << endl;

        // Операции с обычными числами
        int number1;
        cout << "Введите обычное число для операций с первой дробью: ";
        cin >> number1;

        Drobi d_number(static_cast<int>(number1), 1); // Преобразуем в дробь
        cout << "Сумма с обычным числом: " << d1.DrobiSum(d_number) << endl;
        cout << "Разность с обычным числом: " << d1.DrobiMinus(d_number) << endl;
        cout << "Произведение с обычным числом: " << d1.DrobiUmnoz(d_number) << endl;
        cout << "Частное с обычным числом: " << d1.DrobiDelenie(d_number) << endl;

        // Операции с вещественными числами
        double number2;
        cout << "Введите вещественное число для операций с второй дробью: ";
        cin >> number2;
        Drobi d_number_float(static_cast<int>(number2 * 100), 100); // Преобразуем в дробь с двумя десятичными
        cout << "Сумма с вещественным числом: " << d2.DrobiSum(d_number_float) << endl;
        cout << "Разность с вещественным числом: " << d2.DrobiMinus(d_number_float) << endl;
        cout << "Произведение с вещественным числом: " << d2.DrobiUmnoz(d_number_float) << endl;
        cout << "Частное с вещественным числом: " << d2.DrobiDelenie(d_number_float) << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl; // для нахождения ошибки(неправильной работы проги) рекомендуют делать :)
    }

    return 0;
}
