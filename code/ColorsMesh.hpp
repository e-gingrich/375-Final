/// \file ColorsMesh.hpp
/// \brief Declaration of ColorsMesh class.
/// \author Ethan Gingrich
/// \version A08

#ifndef COLORSMESH_HPP
#define COLORSMESH_HPP

#include "Mesh.hpp"

class ColorsMesh : public Mesh 
{   
    
public:
    // Creates a new ColorsMesh class
    ColorsMesh (OpenGLContext* context, ShaderProgram* shader);

    // Empty destructor
    virtual ~ColorsMesh ();

    // getFloatsPerVertex override
    virtual unsigned int
    getFloatsPerVertex () const;

protected:
    // enableAttributes override
    virtual void
    enableAttributes ();
};

#endif //COLORSMESH_HPP