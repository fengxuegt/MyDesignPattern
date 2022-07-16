/*
 * Created 2022-07-15 22:49:59
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 * 
 * 单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
 * A *p1 = new A();
 * A *p2 = new A();
 * A *p3 = new A();
 * 
 * 经常用到的：日志模块、数据库模块
 * 
 * 单例模式：
 * 饿汉式单例模式：还没获取实例对象，对象就已经产生了
 * 懒汉式单例模式：唯一的实例对象只有在第一次使用它的时候，它才被创建出来
 */
#include<iostream>
#include<mutex>
using namespace std;

#if 0
std::mutex mtx;
// 懒汉式单例模式 不是线程安全的
// 将构造函数推迟到第一次获取对象的时候执行
class Singleton {
public:
    // 这个函数是不是可重入函数呢，函数没有执行完的时候能不能再次执行； 使用锁+双重判断
    static Singleton* getInstance() {
        // lock_guard<std::mutex> guard(mtx); // 锁的粒度太大了，导致单线程环境下仍然需要加锁解锁
        if (instance == nullptr) {
            lock_guard<std::mutex> guard(mtx);
            if (instance == nullptr) {
                /*
                开辟内存
                构造对象
                给instance赋值
                */
                instance = new Singleton();
            }

        }
        return instance;
    }
private:
    static Singleton * volatile instance; // 阻止缓存
    Singleton(){}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton *volatile Singleton::instance = nullptr; // volatile 必须放在前面，放在后面会报错！！！！！！！

#endif

#if 0
// 饿汉式单例模式 一定是线程安全的
// 缺点是构造函数可能会耗费很多资源，理论上应该到第一次使用的时候才初始化对象
class Singleton {
public:
    static Singleton* getInstance() { // #3 获取唯一对象的接口方法
        return &instance;
    }

private:
    static Singleton instance; // #2 定义一个唯一的实例对象
    Singleton() { // #1 构造函数私有化

    }
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
};

Singleton Singleton::instance; // 类中的static成员要在类外进行初始化
#endif

// 这是最简单的懒汉式单例模式，
class Singleton {

public:
    static Singleton *getInstance() {
        // g++ -o run 单例模式
        // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了，其初始化过程是一个自然的线程安全处理过程
        static Singleton singleton;
        return &singleton;
    }
private:
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(){}
};

int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    // Singleton t = *p1; // 调用了拷贝构造函数,声明为delete之后就无法调用了
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
}



