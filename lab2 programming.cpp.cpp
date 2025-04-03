#include <iostream>
#include <vector>

// Класс вектор (vect)
class vect {
private:
    int dim; // Размерность вектора
    double* b; // Указатель на массив значений
    int num; // Номер объекта
    static int count; // Статическая переменная для отслеживания количества объектов

public:
    // Конструктор с параметром
    vect(int d) : dim(d), num(++count) {
        b = new double[dim](); // Выделение памяти и инициализация нулями
        std::cout << "Создан vect " << num << "\n";
    }
    
    // Деструктор
    ~vect() {
        delete[] b; // Освобождение памяти
        std::cout << "Уничтожен vect " << num << "\n";
    }
    
    // Конструктор копирования
    vect(const vect& v) : dim(v.dim), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) b[i] = v.b[i];
        std::cout << "Скопирован vect " << num << "\n";
    }
    
    // Оператор присваивания
    vect& operator=(const vect& v) {
        if (this != &v) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
            for (int i = 0; i < dim; i++) b[i] = v.b[i];
            std::cout << "Присвоен vect " << num << "\n";
        }
        return *this;
    }
    
    // Оператор сложения
    vect operator+(const vect& v) {
        vect result(dim);
        for (int i = 0; i < dim; i++) result.b[i] = b[i] + v.b[i];
        std::cout << "Сложены vect " << num << " и " << v.num << "\n";
        return result;
    }
};

int vect::count = 0; // Инициализация статической переменной

// Класс матрица (matr)
class matr {
private:
    int dim; // Размерность матрицы (квадратная матрица dim x dim)
    double* a; // Указатель на массив значений
    int num; // Номер объекта
    static int count; // Статическая переменная для отслеживания количества объектов

public:
    // Конструктор с параметром
    matr(int d) : dim(d), num(++count) {
        a = new double[dim * dim](); // Выделение памяти и инициализация нулями
        std::cout << "Создана matr " << num << "\n";
    }
    
    // Деструктор
    ~matr() {
        delete[] a; // Освобождение памяти
        std::cout << "Уничтожена matr " << num << "\n";
    }
    
    // Конструктор копирования
    matr(const matr& m) : dim(m.dim), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) a[i] = m.a[i];
        std::cout << "Скопирована matr " << num << "\n";
    }
    
    // Оператор присваивания
    matr& operator=(const matr& m) {
        if (this != &m) {
            delete[] a;
            dim = m.dim;
            a = new double[dim * dim];
            for (int i = 0; i < dim * dim; i++) a[i] = m.a[i];
            std::cout << "Присвоена matr " << num << "\n";
        }
        return *this;
    }
};

int matr::count = 0; // Инициализация статической переменной

int main() {
    vect v1(3), v2(3);
    vect v3 = v1 + v2; // Создание вектора v3 путем сложения v1 и v2
    
    matr m1(3), m2(3);
    matr m3 = m1; // Копирование матрицы m1 в m3
    
    return 0;
}
