#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class FileSystemNode {
public:
    virtual int getSize() const = 0;
    virtual void display() const = 0;
    virtual string _name()const=0;
    virtual ~FileSystemNode() = default;
};

class File : public FileSystemNode {
public:
    File(const string& name_1, int size_1) : name{name_1}, size{size_1} {}

    int getSize() const override {
        return size;
    }
    
    string _name()const override{
       return name;
    } 

    void display() const override {
        cout << "File size: " << size << endl;
        cout << "File name: " << name << endl;
    }
private:
    int size;
    string name;
};

class Directory : public FileSystemNode,public std::enable_shared_from_this<Directory> {
    vector<shared_ptr<FileSystemNode>> direct;
    weak_ptr<Directory>parent;
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

    string _name()const override{
       return name;
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
    void add(shared_ptr<FileSystemNode>node){
        if(auto iter=dynamic_pointer_cast<Directory>(node)){
            iter->parent=shared_from_this();
        }
        direct.push_back(node);
    } 
    void delet(string& name){
              for(auto iter=direct.begin();iter!=direct.end();iter++){
                   if((*iter)->_name()==name){
                    direct.erase(iter);
                    break;
                   }
                }
              }


              
    };
    




