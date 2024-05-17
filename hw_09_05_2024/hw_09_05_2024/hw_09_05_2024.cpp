#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
using namespace std;

// Напишите программу для расчёта оплаты за электроэнергию.
// Создайте базовый класс для всех типов счетчиков электроэнергии, 
// имеющий метод для вычисления стоимости потребленной электроэнергии.
// Реализуйте несколько подклассов счетчиков, например, обычный, двухтарифный, многотарифный и т.д.
// Переопределите метод для каждого подкласса так, чтобы он корректно вычислял 
// стоимость в соответствии с тарифами.Создайте вектор указателей на объекты базового класса и заполните его объектами 
// каждого из подклассов.Напишите функцию для вывода стоимости потребленной электроэнергии для каждого счетчика

class Meter
{
protected:
    float kwH;
public:
    Meter()
    {
        kwH = rand() % 100 + 1;
    }

    float GetKwH() const
    {
        return kwH;
    }

    virtual float Calculate() = 0;
};

class MechanicalMeter : public Meter
{
public:
    MechanicalMeter() : Meter() {}

    virtual float Calculate()
    {
        float price = 1.67;
        return kwH * price;
    }
};

class DayNightMeter : public Meter
{
private:
    float dayKwH;
    float nightKwH;
public:
    DayNightMeter()
    {
        dayKwH = rand() % 500 + 1;
        nightKwH = rand() % 500 + 1;
        kwH = dayKwH + nightKwH;
    }

    virtual float Calculate()
    {
        float dayPriceKwH = 1.67;
        float nightPriceKwH = 1.15;
        return (dayKwH * dayPriceKwH) + (nightKwH * nightPriceKwH);
    }
};

__interface IMPrinter {
    virtual void Print(Meter* c) = 0;
};

class ConsolePrinter : public IMPrinter {
public:

    void Print(Meter* c) {
        cout << "Price: " << c->Calculate() << " UAH" << "\n";
    }
};

int main()
{
    srand(time(NULL));

    MechanicalMeter m;
    DayNightMeter d;
    ConsolePrinter printer;

    vector<Meter*> meters;
    meters.push_back(&m);
    meters.push_back(&d);

    for (int i = 0; i < meters.size(); i++) {
        printer.Print(meters[i]);
    }
}