/// \file MyScene.hpp
/// \brief Declaration of MyScene class.
/// \author Ethan Gingrich
/// \version A02

#ifndef MYSCENE_HPP
#define MYSCENE_HPP

#include "OpenGLContext.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"
#include "ColorsMesh.hpp"
#include "NormalsMesh.hpp"

class MyScene : public Scene
{
public:

    /// Creates a new MyScene class
    MyScene (OpenGLContext* context, ShaderProgram* colors, ShaderProgram* normals);

    /// Per code requirements, we are not using delete...
    MyScene (const MyScene&) = delete;

    /// ...or the copy constructor
    MyScene&
    operator= (const MyScene&) = delete;
};

#endif //MYSCENE_HPP