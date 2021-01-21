/// \file Scene.cpp
/// \brief Initialization of Scene class and any associated global functions.
/// \author Ethan Gingrich
/// \version A02

#include "Scene.hpp"

// Scene Constructor
Scene::Scene ()
{
}

// Scene Destructor
Scene::~Scene ()
{
    Scene::clear ();
}

// Adds a Mesh to the Scene using the Meshes map
void
Scene::add (const std::string& meshName, Mesh* mesh)
{
    meshes.insert (std::pair<std::string, Mesh*>(meshName, mesh));
    if (meshes.size () == 1)
        setActiveMesh (meshName);
}

// Removes a Mesh from the Scene
void
Scene::remove (const std::string& meshName)
{
    std::map<std::string, Mesh*>::iterator itr;
    itr = meshes.find(meshName);
    delete itr->second;
    meshes.erase (meshName);
}

// Clears all Mesh pointers and key names from the Map
// Also clears all mesh keys from the Vector
void
Scene::clear ()
{
    std::map<std::string, Mesh*>::iterator itr;
    for (itr = meshes.begin(); itr != meshes.end(); ++itr) 
    {
        delete itr->second;
    }
    meshes.clear();
}

// Draws all Meshes from this Scene
void
Scene::draw (const Transform viewMatrix, const Matrix4& projectionMatrix)
{
    std::map<std::string, Mesh*>::iterator itr;
    for (itr = meshes.begin (); itr != meshes.end(); ++itr)
    {
        itr->second->draw(viewMatrix, projectionMatrix);
    }
}

// Tests whether or not a Mesh exists in this Scene
bool
Scene::hasMesh (const std::string& meshName)
{
    std::map<std::string, Mesh*>::iterator itr;
    for (itr = meshes.begin (); itr != meshes.end(); ++itr)
    {
        if (itr->first == meshName)
        {
            return true;
        }
    }
    return false;
}

// Find and return a certain Mesh from this scene
Mesh*
Scene::getMesh (const std::string& meshName)
{
    return meshes.find(meshName)->second;
}

/*****************************************************************************/
                        //TRANSFORM FUNCTIONS START HERE//
/*****************************************************************************/

/// \brief Sets the active mesh to the mesh named "meshName".
/// The active mesh is the one affected by transforms.
/// \param[in] meshName The name of the mesh that should be active.
/// \pre The scene contains a mesh with that name.
/// \post The mesh with that name becomes the active mesh.
void
Scene::setActiveMesh (const std::string& meshName)
{
    activeMesh = meshes.find (meshName);
}

/// \brief Gets the active mesh.
/// \pre The scene has at least one mesh.
/// \return The active mesh.
Mesh*
Scene::getActiveMesh ()
{
    return activeMesh->second;
}

/// \brief Switches active meshes in the forward direction.
/// \pre The scene has at least one mesh.
/// \post The next mesh becomes active.  If the last mesh was active, the
///   first mesh becomes active.
void
Scene::activateNextMesh ()
{
    activeMesh++;
    if (activeMesh == meshes.end ())
        activeMesh = meshes.begin ();
}

/// \brief Switches active meshes in the backward direction.
/// \pre The scene has at least one mesh.
/// \post The previous mesh becomes active.  If the first mesh was active,
///   the last mesh becomes active.
void
Scene::activatePreviousMesh ()
{
    if (activeMesh == meshes.begin ())
    {
        activeMesh = meshes.end ();
    }
    activeMesh--;
}
