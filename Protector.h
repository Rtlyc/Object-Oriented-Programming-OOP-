//
// Created by 刘禹辰 on 2019-10-30.
//

#ifndef HW07_PROTECTOR_H
#define HW07_PROTECTOR_H
#include <string>

namespace WarriorCraft {

    class Noble;

    class Protector {
    public:
        Protector(const std::string &name, double strength);

        virtual void defend(double amount);

        const std::string &getName() const;

        Noble *getNoble() const;

        Noble *&getNoble();

        double getStrength() const;

        bool isAlive() const;

    private:
        std::string name;
        bool isDead = false;
        double strength;
        Noble *mynoble = nullptr;
    };

    class Wizard : public Protector {
    public:
        using Protector::Protector;

        void defend(double amount);
    };

    class Warrior : public Protector {
    public:
        using Protector::Protector;

        void defend(double amount);
    };

    class Archer : public Warrior {
    public:
        using Warrior::Warrior;

        void defend(double amount);
    };

    class Swordsman : public Warrior {
    public:
        using Warrior::Warrior;

        void defend(double amount);
    };
}

#endif //HW07_PROTECTOR_H
