#include "Sphere.h"
#include <array>
#include <map>

using TriangleList=std::vector<unsigned int>;
using VertexList=std::vector<Vertex>;
using Lookup = std::map< std::pair< unsigned int, unsigned int >, unsigned int >;

std::vector<Vertex> genCube(int quads);
TriangleList subdivide(VertexList &vertices, TriangleList triangles);
unsigned int vertex_for_edge(Lookup& lookup, VertexList& vertices, unsigned int first, unsigned int second);

Sphere::Sphere(SphereType type, int faces, const std::string &diffuseTexture, const std::string &specularTexture){
    glm::vec4 color{0.6f, 0.05f, 0.01f, 1.0f};
    switch (type)
    {
    case SphereType::UV_SPHERE:
        break;
    case SphereType::NORMALIZED_CUBE:
        createNormCube(color);
        break;
    case SphereType::SPHERIFIED_CUBE:
    //createSpherifiedCube(color);
        break;
    case SphereType::ICOSAHEDRON:
        createIcosahedron(5);
        break;
    default:
        break;
    }
}

void Sphere::createNormCube(glm::vec4 &color){
    m_shader.setVec4("color", color);

    std::vector<Vertex> vertices = genCube(10);
    
    for (auto &v : vertices)
    {
        v.position = glm::normalize(v.position)/2.0f;
    }

    std::vector<Vertex> vertices2;
    vertices2.insert(vertices2.end(), vertices.begin(), vertices.end());
    glm::mat4 rotation = glm::mat4(1.0f);
    // TODO fix
    for(unsigned int i = 0; i <= 3; i++){
        rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        for(auto &v : vertices){
            v.position = glm::vec4(v.position, 1.0f) * rotation;
        }
        vertices2.insert(vertices2.end(), vertices.begin(), vertices.end());
    }
    rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    for(auto &v : vertices){
        v.position = glm::vec4(v.position, 1.0f) * rotation;
    }
    vertices2.insert(vertices2.end(), vertices.begin(), vertices.end());

    rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(2*90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    for(auto &v : vertices){
        v.position = glm::vec4(v.position, 1.0f) * rotation;
    }
    vertices2.insert(vertices2.end(), vertices.begin(), vertices.end());

   for (unsigned int i = 0; i < vertices2.size()-2; i += 3){
       glm::vec3 normal;
       normal = glm::cross(vertices2[i+1].position - vertices2[i].position, vertices2[i+2].position - vertices2[i].position);
       vertices2[i].normal = normal;
       vertices2[i+1].normal = normal;
       vertices2[i+2].normal = normal;
   }
   

    m_meshes.push_back(Mesh(vertices2));
    
}

// void Sphere::createSpherifiedCube(glm::vec4 &color){
//     /*
//     for f in faces:
//         origin = get_origin(f)
//         right = get_right_dir(f)
//         up = get_up_dir(f)
//         for j in div_count:
//             for i in div_count:
//                 p = origin + 2.0 * (right * i + up * j) / div_count
//                 p2 = p * p
//                 rx = sqrt(1.0 - 0.5 * (p2.y + p2.z) + p2.y*p2.z/3.0)
//                 ry = sqrt(1.0 - 0.5 * (p2.z + p2.x) + p2.z*p2.x/3.0)
//                 rz = sqrt(1.0 - 0.5 * (p2.x + p2.y) + p2.x*p2.y/3.0)
//                 return (rx, ry, rz)

//      */
//     int quads = 10;
//     std::array<glm::vec3, 6> rightDirs{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)};
//     std::array<glm::vec3, 6> upDirs{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f)};
//     std::vector<Vertex> vertices;
//     for (unsigned int f = 0; f < 6; f++){
//         glm::vec3 origin{};
//         glm::vec3 right = rightDirs[f];
//         glm::vec3 up = upDirs[f];
//         for (unsigned int y = 0; y < quads; y++){
//             for (unsigned int x = 0; x < quads; x++){
//                 glm::vec3 p = origin + (2.0f * (right * (float)x + up * (float)y) / (float)quads);
//                 glm::vec3 p2 = p * p;
//                 float rx = sqrt(1.0f - 0.5f * (p2.y + p2.z) + p2.y * p2.z / 3.0f);
//                 float ry = sqrt(1.0f - 0.5f * (p2.z + p2.x) + p2.z * p2.x / 3.0f);
//                 float rz = sqrt(1.0f - 0.5f * (p2.x + p2.y) + p2.x * p2.y / 3.0f);
//                 vertices.push_back(Vertex{glm::vec3(rx, ry, rz)});
//                 // glm::vec3 point = origin + 2.0f * (right * static_cast<float>(x) + up * static_cast<float>(y)) / static_cast<float>(quads);
//                 // vertices.push_back(Vertex{point});
//             }
//         }
//     }
//     m_meshes.push_back(Mesh(vertices));
// }

 


void Sphere::createIcosahedron(int subdivisions){
    const float X=.525731112119133606f;
    const float Z=.850650808352039932f;
    const float N=0.f;
    
    VertexList vertices = {
    {{-X,N,Z}}, {{X,N,Z}}, {{-X,N,-Z}}, {{X,N,-Z}},
    {{N,Z,X}}, {{N,Z,-X}}, {{N,-Z,X}}, {{N,-Z,-X}},
    {{Z,X,N}}, {{-Z,X, N}}, {{Z,-X,N}}, {{-Z,-X, N}}
    };

    TriangleList triangles{
        0,1,4, 0,4,9, 9,4,5, 4,8,5, 4,1,8,
        8,1,10, 8,10,3, 5,8,3, 5,3,2, 2,3,7,
        7,3,10, 7,10,6, 7,6,11, 11,6,0, 0,6,1,
        6,10,1, 9,11,0, 9,2,11, 9,5,2, 7,11,2,
    };
        
    for (int i=0; i<subdivisions; ++i){
        triangles = subdivide(vertices, triangles);
    }
    m_meshes.push_back(Mesh(vertices, triangles));
}

TriangleList subdivide(VertexList &vertices, TriangleList triangles){
    Lookup lookup;
    TriangleList result;
    for (unsigned int i = 0; i < triangles.size()-2; i += 3){
        std::array<unsigned int, 3> mid;
        for (unsigned int edge = 0; edge < 3; edge++){
            mid[edge] = vertex_for_edge(lookup, vertices, triangles[i + edge], triangles[i + (edge+1)%3]);
        }
        result.insert(result.end(), {triangles[i + 0], mid[0], mid[2]});
        result.insert(result.end(), {triangles[i + 1], mid[1], mid[0]});
        result.insert(result.end(), {triangles[i + 2], mid[2], mid[1]});
        result.insert(result.end(), {mid[0], mid[1], mid[2]});
    }
    return result;
}

unsigned int vertex_for_edge(Lookup& lookup, VertexList& vertices, unsigned int first, unsigned int second){
    Lookup::key_type key(first, second);
    if (key.first > key.second)
        std::swap(key.first, key.second);
    
    auto inserted = lookup.insert({key, vertices.size()});
    if (inserted.second){
        auto& edge0=vertices[first];
        auto& edge1=vertices[second];
        auto point = glm::normalize(edge0.position+edge1.position);
        vertices.push_back(Vertex{point});
    }
    return inserted.first->second;
}

void Sphere::create(std::string diffuseTexture, std::string specularTexture){

}

void Sphere::create(glm::vec4 &color){

}


std::vector<Vertex> genCube(int quads){
    std::vector<Vertex> vertices;

    float quadWidth = 1.0f/quads;

    for (unsigned int y = 0; y < quads; y++){
        for (unsigned int x = 0; x < quads; x++){
            float xPos = x*quadWidth - 0.5f;
            float yPos = y*quadWidth - 0.5f;
            Vertex v;
            v.position = glm::vec3(xPos, yPos, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos, yPos);
            vertices.push_back(v);
            v.position = glm::vec3(xPos+quadWidth, yPos+quadWidth, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos+quadWidth, yPos+quadWidth);
            vertices.push_back(v);
            v.position = glm::vec3(xPos, yPos+quadWidth, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos, yPos+quadWidth);
            vertices.push_back(v);

            v.position = glm::vec3(xPos, yPos, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos, yPos);
            vertices.push_back(v);
            v.position = glm::vec3(xPos+quadWidth, yPos, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos+quadWidth, yPos);
            vertices.push_back(v);
            v.position = glm::vec3(xPos+quadWidth, yPos+quadWidth, 0.5f);
            v.normal = glm::vec3(0.0f, 0.0f, 0.5f);
            v.texCoords = glm::vec2(xPos+quadWidth, yPos+quadWidth);
            vertices.push_back(v);
        }
    }
    return vertices;
}

