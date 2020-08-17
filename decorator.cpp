/*
 * Copyright(c) All rights reserved.
 * Author: seuyang@163.com
 * Create: 2019-10-01
 */

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 抽象类Tank
class Tank {
public:
    Tank() = default;

    virtual ~Tank() { cout << "in the destructor of Tank" << endl; }

    virtual void shot() = 0;

    virtual void run() = 0;
};

// 具体类 T50
class T50 : public Tank {
public:
    T50() = default;

    ~T50() override { cout << "In the destructor of T50" << endl; }

    void shot() override { cout << "Tank T50 shot()" << endl; }

    void run() override { cout << "Tank T50 run()" << endl; }
};

// 具体类 T75
class T75 : public Tank {
public:
    T75() = default;

    ~T75() override { cout << "In the destructor of T75" << endl; }

    void shot() override { cout << "Tank T75 shot()" << endl; }

    void run() override { cout << "Tank T75 run()" << endl; }
};

//抽象类，Decorator
class Decorator : public Tank {
public:
    explicit Decorator(Tank *tank) : tank(tank) {} //具体的坦克的装饰类

    ~Decorator() override { cout << "In the destructor of Decorator" << endl; }

    void shot() override { tank->shot(); }

    void run() override { tank->run(); }

protected:
    Tank *tank;
};

class InfraredDecorator : public Decorator {
public:
    explicit InfraredDecorator(Tank *tank) : Decorator(tank) {}

    ~InfraredDecorator() override { cout << "in the destructor of InfraredDecorator" << endl; }

    void set_infrared(const string &infrared) { this->infrared = infrared; }

    string get_infrared() const { return infrared; }

    void run() override
    {
        tank->run();
        set_infrared("+Infrared");
        cout << get_infrared() << endl;
    }

    void shot() override { tank->shot(); }

private:
    string infrared; // 这就是所谓的addAtrribute
};

class AmphibianDecorator : public Decorator {
public:
    explicit AmphibianDecorator(Tank *tank) : Decorator(tank) {}

    ~AmphibianDecorator() override { cout << "in the destructor of AmphibianDecorator" << endl; }

    void set_amphibian(const string &hibian) { this->amphibian = hibian; }

    string get_amphibian() const { return amphibian; }

    void run() override
    {
        tank->run();
        set_amphibian("+amphibian");
        cout << get_amphibian() << endl;
    }

    void shot() override { tank->shot(); }

private:
    string amphibian;
};

int main(int argc, char **argv)
{
    // 给T50增加红外功能
    Tank *tank1(new T50);
    Tank *pid1(new InfraredDecorator(tank1));
    pid1->shot();
    cout << endl;
    pid1->run();
    cout << endl;
    cout << endl << "---------------" << endl;

    //给t75增加红外、两栖功能
    Tank *tank2(new T75);
    tank2->run();
    Tank *pid2(new InfraredDecorator(tank2));
    Tank *pad2(new AmphibianDecorator(pid2));
    pad2->shot();
    cout << endl;
    pad2->run();
    cout << endl;
    cout << endl << "--------------" << endl;

    // 动态撤销其他装饰
    tank2->run();

    Tank *tank3(tank2);
    tank3->run();

    return 0;
}
