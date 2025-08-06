#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class FileSystemNode {
public:
    virtual int getSize() const = 0;
    virtual void display() const = 0;
    virtual ~FileSystemNode() = default;
};

class File : public FileSystemNode {
public:
    File(const string& name_1, int size_1) : name{name_1}, size{size_1} {}

    int getSize() const override {
        return size;
    }

    void display() const override {
        cout << "File size: " << size << endl;
        cout << "File name: " << name << endl;
    }

private:
    int size;
    string name;
};

class Directory : public FileSystemNode {
    vector<shared_ptr<FileSystemNode>> direct;
    string name;

public:
    Directory(const string& name_1) : name{name_1} {}

    int getSize() const override {
        int total = 0;
        for (auto& iter : direct) {
            total += iter->getSize();
        }
        return total;
    }

    void display() const override {
        for (auto& iter : direct) {
            if (dynamic_pointer_cast<Directory>(iter)) {
                cout << "This is " << name << " directory" << endl;
                cout << iter->getSize() << endl;
            } else {
                iter->display();
            }
        }
    }

    void insert(const shared_ptr<FileSystemNode>& node) {
        direct.push_back(node);
    }
};

