#ifndef VERTEX_H
#define VERTEX_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vulkan/vulkan.h>
#include <array>

class Vertex {
public:
    glm::vec3 position;
    glm::vec2 texCoords;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

};

bool operator==(const Vertex& a, const Vertex& b);

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec2>()(vertex.texCoords) << 1)) >> 1);
        }
    };
}

#endif // VERTEX_H
