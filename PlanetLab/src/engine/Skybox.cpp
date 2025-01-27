﻿#include "engine/Skybox.hpp"

namespace PlanetLab
{

Skybox::Skybox(const std::vector<std::string>& faces)
    : _faces(faces),
      _id(ResourceManager::Get().LoadCubemap(_faces)),
      _shader(ResourceManager::Get().GetShader("Skybox"))
{
    GenerateMesh();
}


void Skybox::GenerateMesh()
{
    std::vector<ShapeVertex> vertices;
    int index = 0;
    for (size_t i = 0; i < 36; i++)
    {
        ShapeVertex vertex;
        vertex.position.x = _SkyboxVertices[index++];
        vertex.position.y = _SkyboxVertices[index++];
        vertex.position.z = _SkyboxVertices[index++];

        vertex.normal.x = 1;
        vertex.normal.y = 1;
        vertex.normal.z = 1;

        vertex.texCoords.x = 0;
        vertex.texCoords.y = 0;

        vertices.push_back(vertex);
    }
    _mesh = std::make_shared<Mesh>(vertices, std::make_shared<Material>());
}

void Skybox::Draw()
{
    glDepthFunc(GL_LEQUAL);
    
    _shader->Bind();
    
    SendUniforms();

    glBindVertexArray(_mesh->GetVAO());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    _shader->Unbind();

    glDepthFunc(GL_LESS); 
}

void Skybox::SendUniforms()
{

    Renderer::Get().SendTransMatrixUniforms(glm::mat4(1.0f), _shader, true);
}


// Just a simple cube, no TexCoords needed
// ---------------------------------------
const float Skybox::_SkyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

}

