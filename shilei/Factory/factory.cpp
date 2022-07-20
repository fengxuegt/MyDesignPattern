/*
 * Created 2022-07-20 21:45:18
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 * 简单工厂
 * 把对象的创建封装在一个接口函数中，通过传入不同的标识，返回创建的对象，客户不用自己负责new对象，不用了解对象的详细创建过程
 * 缺点是：提供创建实例的接口函数不是闭合的，不符合开闭原则。
 * 
 * 工厂方法：
 * Factory基类，提供了一个纯虚函数（创建产品），定义派生类负责创建对应的产品，可以做到不同的产品，在不同的工厂当中创建，符合开闭原则
 * 缺点是：很多产品都是相关联的，属于同一个产品簇，不应该放到不同的工厂当中去创建，而且一个产品一个工厂类，会导致工厂类的膨胀
 * 
 * 抽象工厂
 * 把有关系的，属于一个产品簇的产品创建的接口函数，放在一个抽象工厂里面，派生类（具体产品的工厂）应该负责创建该产品簇里面所有的产品
 * 
 * 工厂模式
 * 主要是封装了对象的创建
 * 
 * Note:只要是作为基类的，都要实现虚析构函数！！！！！！！！
 */
#include<iostream>
#include<memory.h>

using namespace std;
class Car {
public:
    virtual void Run() = 0;
    virtual ~Car(){

    }
};

class BmwCar : public Car {
public:
    BmwCar() {

    }
    void Run() {
        cout << "BmwCar run" << endl;
    }
};

class AudiCar : public Car {
public:
    AudiCar() {

    }
    void Run() {
        cout << "AudiCar run" << endl;
    }
};

class Light {
    public:

};

class BmwLight : public Light {
    public:
    BmwLight() {
        cout << "create a BmwLight" << endl;
    }
};

class AudiLight : public Light {
    public:
    AudiLight() {
        cout << "create a AudiLight" << endl;
    }
};


enum class CarType {
    BMW,
    AUDI
};

class SimpleFactory {
    public:
        static Car* create(CarType type) {
            switch (type) {
                case CarType::BMW:
                    return new BmwCar();
                case CarType::AUDI:
                    return new AudiCar();
                default:
                    cout << "error occured" << endl;
            }
        }
};

class Factory {
public:
    virtual Car * createCar() = 0;
    virtual Light *createLight() = 0;
    virtual ~Factory() {}
};

class BmwFactory : public Factory{
public:
    Car * createCar() {
        return new BmwCar();
    }

    Light * createLight() {
        return new BmwLight();
    }
};

class AudiFactory : public Factory {
    Car * createCar() {
        return new AudiCar();
    }

    Light * createLight() {
        return new AudiLight();
    }
};




int main()
{
    // 普通产生对象方式
    // unique_ptr<Car> p1(new BmwCar());
    // unique_ptr<Car> p2(new AudiCar());

    // 简单工厂
    // SimpleFactory simpleFactory;
    // CarType type = CarType::BMW;
    // Car * p1 = simpleFactory.create(type);
    // Car * p2 = simpleFactory.create(CarType::AUDI);

    // 工厂方法模式
    // Factory *bmwFactory = new BmwFactory();
    // Factory *audiFactory = new AudiFactory();
    // unique_ptr<Car> p1(bmwFactory->createCar());
    // unique_ptr<Car> p2(audiFactory->createCar());

    // 抽象工厂模式

    Factory *bmwFactory = new BmwFactory();
    Factory *audiFactory = new AudiFactory();
    unique_ptr<Car> p1(bmwFactory->createCar());
    unique_ptr<Car> p2(audiFactory->createCar());
    unique_ptr<Light> q1(bmwFactory->createLight());
    unique_ptr<Light> q2(audiFactory->createLight());

    delete bmwFactory;
    delete audiFactory;
    p1->Run();
    p2->Run();



}

