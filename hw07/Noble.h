//
// Created by 刘禹辰 on 2019-10-30.
//

#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H
#include <string>
#include <vector>

namespace WarriorCraft {

    class Protector;

    class Noble {
    public:
        Noble(const std::string &name, double strength = 0);

        virtual void battle(Noble &other);

        const std::string &getName() const;

        bool isAlive() const;

        virtual void fightback(double amount);

        double getStrength() const;

        double &getStrength();

    private:
        std::string name;
        bool isDead = false;
        double strength;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string &name);

        bool hires(Protector &other);

        bool fires(Protector &other);

        void fightback(double amount);

    private:
        std::vector<Protector *> allprotectors;

        size_t find(const Protector &other) const;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string &name, double strength);
    };

}
#endif //HW07_NOBLE_H
