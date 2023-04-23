#include <mesh.h>
#include <iostream>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
{

    initialize(vertices, elements);

    //// create the triangle and attach all settings in following code
    //glGenVertexArrays(1, &vao);

    //// for multiple triangles/vbo's
    ////unsigned int vertexBufferObject[3];
    ////glGenBuffers(3, vertexBufferObject);

    //// for single triangle, we only need 1 vbo
    //glGenBuffers(1, &vbo);

    //// create ebo buffer
    //glGenBuffers(1, &ebo);

    //// bind the vao first
    //glBindVertexArray(vao);

    //// next, set vbo and buffer data
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
    //    vertices.data(), GL_STATIC_DRAW);


    //// bind ebo - used for sharing vertices
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(uint32_t)),
    //    elements.data(), GL_STATIC_DRAW);


    //// next, define vertex attributes (tell the shape of struct attributes
    //// 1st position is location# in your vertex struct
    //// next is how many elements of given type (position has 3 floats)
    //// next is the type (GL_FLOAT)
    //// next is false
    //// next is stride (how many total bytes in a vertex)
    //// next is offset
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //    reinterpret_cast<void*>(offsetof(Vertex, Position)));
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //    reinterpret_cast<void*>(offsetof(Vertex, Color)));
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //    reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    //glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    //    reinterpret_cast<void*>(offsetof(Vertex, Uv)));

    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);
    //glEnableVertexAttribArray(3);


    //// unbind buffer as vbo is already registered, and unbind vao
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);


    ////glBindVertexArray(0);
    ////glBindVertexArray(1);
    ////glBindVertexArray(2);
    ////glBindVertexArray(3);

    //
    //elementCount = elements.size();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements, const glm::vec3& color)
{

    for (auto& vertex : vertices) {
        vertex.Color = color;

    }

    initialize(vertices, elements);

}

void Mesh::Draw() const
{
    

    // bind vao
    glBindVertexArray(vao);

    // gl draw calls
    // change 6 to 3 (or vice versa for drawing one triangle instead of two
    //glDrawArrays(GL_TRIANGLES, 0, 6);   // not sharing vertices
    glDrawElements(GL_TRIANGLES, static_cast<int>(elementCount), GL_UNSIGNED_INT, nullptr);
}

void Mesh::initialize(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
{
    // automate normals
    for (auto i = 0; i < elements.size(); i += 3) {
        auto p1Idx = elements[i];
        auto p2Idx = elements[i + 1];
        auto p3Idx = elements[i + 2];

        PredefinedShapes::UpdateNorms(vertices[p1Idx], vertices[p2Idx], vertices[p3Idx]);

    }

    // create the triangle and attach all settings in following code
    glGenVertexArrays(1, &vao);

    // for multiple triangles/vbo's
    //unsigned int vertexBufferObject[3];
    //glGenBuffers(3, vertexBufferObject);

    // for single triangle, we only need 1 vbo
    glGenBuffers(1, &vbo);

    // create ebo buffer
    glGenBuffers(1, &ebo);

    // bind the vao first
    glBindVertexArray(vao);

    // next, set vbo and buffer data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
        vertices.data(), GL_STATIC_DRAW);


    // bind ebo - used for sharing vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(uint32_t)),
        elements.data(), GL_STATIC_DRAW);


    // next, define vertex attributes (tell the shape of struct attributes
    // 1st position is location# in your vertex struct
    // next is how many elements of given type (position has 3 floats)
    // next is the type (GL_FLOAT)
    // next is false
    // next is stride (how many total bytes in a vertex)
    // next is offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, Position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, Color)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, Normal)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, Uv)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);


    // unbind buffer as vbo is already registered, and unbind vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //glBindVertexArray(0);
    //glBindVertexArray(1);
    //glBindVertexArray(2);
    //glBindVertexArray(3);


    elementCount = elements.size();
}

