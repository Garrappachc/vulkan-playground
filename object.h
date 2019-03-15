#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>

class ObjectPrivate;

class Object {
public:
    enum Status { Empty, Loading, Complete, Error };

    Object(const std::string& name);
    virtual ~Object();

    const std::string& name() const;

    Status status() const;
    std::string statusText() const;

    void load(const std::string& fileName);

private:
    std::unique_ptr<ObjectPrivate> d;

};

#endif // OBJECT_H
