#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>

class ObjectPrivate;

class Object {
public:
    enum Status { Empty, Loading, Complete };

    Object(const std::string& name);
    virtual ~Object();

    const std::string& name() const;

    Status status() const;
    std::string statusText() const;

private:
    std::unique_ptr<ObjectPrivate> d;

};

#endif // OBJECT_H
