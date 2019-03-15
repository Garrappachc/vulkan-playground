#include "object.h"
#include "vertex.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace {

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

}

class ObjectPrivate {
public:
    std::string name;
    Object::Status status;

    ObjectPrivate(const std::string& name);

    void load(const std::string& fileName);

};

ObjectPrivate::ObjectPrivate(const std::string& name) :
    name(name),
    status(Object::Status::Empty)
{

}

void ObjectPrivate::load(const std::string& fileName)
{
    status = Object::Status::Loading;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fileName.c_str());
    if (!ret) {
        std::cout << "warning: " << warn << std::endl;
        std::cerr << "error: " << err << std::endl;
        status = Object::Status::Error;
        return;
    }

    Mesh mesh;
    std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

    for (const auto& shape: shapes) {
        for (const auto& index: shape.mesh.indices) {
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * static_cast<size_t>(index.vertex_index)],
                attrib.vertices[3 * static_cast<size_t>(index.vertex_index) + 1],
                attrib.vertices[3 * static_cast<size_t>(index.vertex_index) + 2]
            };

            vertex.texCoords = {
                attrib.texcoords[2 * static_cast<size_t>(index.texcoord_index)],
                1.0f - attrib.texcoords[2 * static_cast<size_t>(index.texcoord_index) + 1]
            };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(mesh.vertices.size());
                mesh.vertices.push_back(vertex);
            }

            mesh.indices.push_back(uniqueVertices[vertex]);
        }
    }

    status = Object::Status::Complete;
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

        case Object::Error:
            return "error";
    }

    return std::string();
}

void Object::load(const std::string& fileName)
{
    d->load(fileName);
}
