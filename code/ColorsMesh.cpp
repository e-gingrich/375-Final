/// \file ColorsMesh.cpp
/// \brief Initialization of ColorsMesh class.
/// \author Ethan Gingrich
/// \version A08

#include "ColorsMesh.hpp"

ColorsMesh::ColorsMesh (OpenGLContext* context, ShaderProgram* shader) : Mesh (context, shader)
{
}

ColorsMesh::~ColorsMesh ()
{
}

unsigned int
ColorsMesh::getFloatsPerVertex () const
{
    return 6;
}

void
ColorsMesh::enableAttributes ()
{
    const GLint COLOR_ATTRIB_INDEX = 1;
     
    Mesh::enableAttributes ();
    m_context->enableVertexAttribArray (COLOR_ATTRIB_INDEX);
    // Colors have 3 parts, each are floats, and start at 10th position in array
    m_context->vertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, (getFloatsPerVertex() * sizeof(float)),
				  reinterpret_cast<void*> (3 * sizeof(float)));
}