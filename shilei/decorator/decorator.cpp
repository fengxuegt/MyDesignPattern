/*
 * Created 2022-07-24 21:10:01
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 * 
 * 装饰器模式
 * 通过子类实现功能增强的问题：为了增强现有类的功能，通过实现自类的方式重写接口，是可以完成功能扩展的，但是会
 * 造成类的膨胀，会产生非常多的子类
 */

#include<iostream>
using namespace std;

class Car {
    public:
        virtual void show() = 0;
    virtual ~Car() {}
};

class Bmw : public Car {
public:
    void show() {
        cout << "this a bmw" << endl;
    }
};

class Audi : public Car {
public:
    void show() {
        cout << "this is a audi" << endl;
    }
};

class Bnze : public Car {
public:
    void show() {
        cout << "this is a bnze" << endl;
    }
};

class CarDecorator : public Car {
public:
    CarDecorator(Car *car): m_car(car) {}
protected:
    Car *m_car;
};

class ConcreteDecorator01 : public CarDecorator {
public:
    ConcreteDecorator01(Car *car) : CarDecorator(car) {}
    void show() {
        m_car->show();
        cout << "自动驾驶"  << endl;
    }
};



int main()
{
    Car *bmw = new Bmw();
    CarDecorator *de01 = new ConcreteDecorator01(bmw);
    de01->show();

    delete bmw;
    delete de01;
    return 0;
}