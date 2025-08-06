#include <iostream>
#include <vector>
using namespace std;

class Item {
    string name;
    int power;

public:
    Item(const string& itm, int powers) : name{itm}, power{powers} {}

    void render() {
        cout << "you use " << name << endl;
        cout << "with power " << power << endl;
    }
};

class GameObject {
public:
    virtual void render() = 0;
    virtual void update() = 0;
    virtual ~GameObject() = default;
};

class Player : public GameObject {
    string name;
    int health;
    int level;
    vector<Item*> items;

public:
    Player(string names, int healths, int levels)
        : name{names}, health{healths}, level{levels} {}

    void add_item(Item* its) {
        items.push_back(its);
    }

    void render() override {
        cout << "name is: " << name << endl;
        cout << "health is: " << health << endl;
        cout << "level is: " << level << endl;
        for (int i = 0; i < items.size(); i++) {
            items[i]->render();
        }
    }

    void update() override {
        cout << "you update your hero";
    }

    Player(const Player& other) {
        name = other.name;
        health = other.health;
        level = other.level;
        for (int i = 0; i < other.items.size(); i++) {
            items.push_back(new Item(*other.items[i]));
        }
    }

    Player& operator=(const Player& other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        health = other.health;
        level = other.level;

        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
        items.clear();

        for (int i = 0; i < other.items.size(); i++) {
            items.push_back(new Item(*other.items[i]));
        }

        return *this;
    }

    Player(Player&& other) {
        name = move(other.name);
        health = other.health;
        level = other.level;
        items = move(other.items);
        other.items.clear();
    }

    ~Player() {
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
        items.clear();
    }
};

class Enemy : public GameObject {
    string name;
    int health;
    int level;
    vector<Item*> items;

public:
    Enemy(string names, int healths, int levels)
        : name{names}, health{healths}, level{levels} {}

    void add_item(Item* its) {
        items.push_back(its);
    }

    void render() override {
        cout << "name is: " << name << endl;
        cout << "health is: " << health << endl;
        cout << "level is: " << level << endl;
        for (int i = 0; i < items.size(); i++) {
            items[i]->render();
        }
    }

    void update() override {
        cout << "you update your hero";
    }

    Enemy(const Enemy& other) {
        name = other.name;
        health = other.health;
        level = other.level;
        for (int i = 0; i < other.items.size(); i++) {
            items.push_back(new Item(*other.items[i]));
        }
    }

    Enemy& operator=(const Enemy& other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        health = other.health;
        level = other.level;

        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
        items.clear();

        for (int i = 0; i < other.items.size(); i++) {
            items.push_back(new Item(*other.items[i]));
        }

        return *this;
    }

    Enemy(Enemy&& other) {
        name = move(other.name);
        health = other.health;
        level = other.level;
        items = move(other.items);
        other.items.clear();
    }

    ~Enemy() {
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
        items.clear();
    }
};
