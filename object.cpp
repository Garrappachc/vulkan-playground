#include "object.h"

class ObjectPrivate {
public:
    std::string name;
    Object::Status status;

    ObjectPrivate(const std::string& name);

};

ObjectPrivate::ObjectPrivate(const std::string& name) :
    name(name),
    status(Object::Status::Empty)
{

}

Object::Object(const std::string& name) : d(new ObjectPrivate(name))
{

}

Object::~Object()
{

}

const std::string&Object::name() const
{
    return d->name;
}

Object::Status Object::status() const
{
    return d->status;
}

std::string Object::statusText() const
{
    switch (d->status) {
        case Object::Empty:
            return "empty";

        case Object::Loading:
            return "loading";

        case Object::Complete:
            return "complete";
    }
}
