#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class UIComponent {
  int x=0;
  int y=0;
  int w=0;
  int h=0;  
public:
  UIComponent(int xs,int ys,int ws,int hs):x{xs},y{ys},w{ws},h{hs}{}
    virtual void draw()const = 0;
    virtual void onClick() = 0;
    virtual unique_ptr<UIComponent> clone() = 0;
     bool contains(int xs, int ys) const {
        return xs >= x && xs < x + w && ys >= y && ys < y + h;
    }
    void setPosition(int nx, int ny) { x = nx; y = ny; }
    int getHeight() const { return h; }

};

class Button : public UIComponent {
public:
    void draw()const override {
        cout << "you called draw on Button" << endl;
    }
    void onClick() override {
        cout << "you called Click on Button" << endl;
    }
    unique_ptr<UIComponent> clone() override {
        return make_unique<Button>(*this);
    }
};

class Checkbox : public UIComponent {
public:
    void draw()const override {
        cout << "you called draw on Checkbox" << endl;
    }
    void onClick() override {
        cout << "you called Click on Checkbox" << endl;
    }
    unique_ptr<UIComponent> clone() override {
        return make_unique<Checkbox>(*this);
    }
};

class TextField : public UIComponent {
public:
    void draw()const override {
        cout << "you called draw on TextField" << endl;
    }
    void onClick() override {
        cout << "you called Click on TextField" << endl;
    }
    unique_ptr<UIComponent> clone() override {
        return make_unique<TextField>(*this);
    }
};

class AllComponents {
    vector<unique_ptr<UIComponent>> components;

public:
    void draw() const {
        for (auto& iter : components) {
            iter->draw();
        }
    }

    void onClick() const {
        for (auto& iter : components) {
            iter->onClick();
        }
    }

    AllComponents() = default;

    AllComponents(AllComponents&& other) noexcept {
        components = move(other.components);
    }

    AllComponents& operator=(AllComponents&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        components.clear();
        components = move(other.components);
        return *this;
    }

    AllComponents(const AllComponents& other) {
        for (int i = 0; i < other.components.size(); i++) {
            components.push_back(other.components[i]->clone());
        }
    }

    void addComponent(unique_ptr<UIComponent> comp) {
        components.push_back(move(comp));
    }
};
