/// \file MyScene.cpp
/// \brief Initializing the MyScene class and adding Meshes geometry vectors to the Mesh.
/// \author Ethan Gingrich
/// \version A02

#include "MyScene.hpp"
#include "Geometry.hpp"

MyScene::MyScene (OpenGLContext* context, ShaderProgram* colors, ShaderProgram* normals) 
{
  ColorsMesh* cubeMesh = new ColorsMesh(context, colors);
  std::vector<float> data;                    /// Holds unique vertex data
  std::vector<unsigned int> indices;          /// Holds index data 

  const std::vector<float> cube
  {
    0.0f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f,     /// BEGIN FIRST FACE
    -2.0f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
    0.0f, -2.0f, 0.0f, 0.2f, 0.0f, 0.0f,
    -2.0f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
    -2.0f, -2.0f, 0.0f, 0.2f, 0.0f, 0.0f,
    0.0f, -2.0f, 0.0f, 0.2f, 0.0f, 0.0f,    /// END FIRST FACE
    ///////////////////////////////////////////////////////////////
    -2.0f, 0.0f, 0.0f, 0.4f, 0.2f, 0.0f,    /// BEGIN SECOND FACE
    -2.0f, 0.0f, -2.0f, 0.4f, 0.2f, 0.0f,
    -2.0f, -2.0f, -2.0f, 0.4f, 0.2f, 0.0f,
    -2.0f, -2.0f, -2.0f, 0.4f, 0.2f, 0.0f,
    -2.0f, -2.0f, 0.0f, 0.4f, 0.2f, 0.0f,
    -2.0f, 0.0f, 0.0f, 0.4f, 0.2f, 0.0f,    /// END SECOND FACE
    ///////////////////////////////////////////////////////////////
    -2.0f, 0.0f, -2.0f, 0.6f, 0.4f, 0.2f,   /// BEGIN THIRD FACE
    0.0f, 0.0f, -2.0f, 0.6f, 0.4f, 0.2f,
    0.0f, -2.0f, -2.0f, 0.6f, 0.4f, 0.2f,
    0.0f, -2.0f, -2.0f, 0.6f, 0.4f, 0.2f,
    -2.0f, -2.0f, -2.0f, 0.6f, 0.4f, 0.2f,
    -2.0f, 0.0f, -2.0f, 0.6f, 0.4f, 0.2f,   /// END THIRD FACE
    ///////////////////////////////////////////////////////////////
    0.0f, 0.0f, -2.0f, 0.8f, 0.6f, 0.4f,    /// BEGIN FOURTH FACE
    0.0f, 0.0f, 0.0f, 0.8f, 0.6f, 0.4f,
    0.0f, -2.0f, 0.0f, 0.8f, 0.6f, 0.4f,
    0.0f, -2.0f, 0.0f, 0.8f, 0.6f, 0.4f,
    0.0f, -2.0f, -2.0f, 0.8f, 0.6f, 0.4f,
    0.0f, 0.0f, -2.0f, 0.8f, 0.6f, 0.4f,    /// END FOURTH FACE
    ///////////////////////////////////////////////////////////////
    -2.0f, 0.0f, 0.0f, 1.0f, 0.8f, 0.6f,    /// BEGIN FIFTH FACE
    0.0f, 0.0f, 0.0f, 1.0f, 0.8f, 0.6f,
    0.0f, 0.0f, -2.0f, 1.0f, 0.8f, 0.6f,
    0.0f, 0.0f, -2.0f, 1.0f, 0.8f, 0.6f,
    -2.0f, 0.0f, -2.0f, 1.0f, 0.8f, 0.6f,
    -2.0f, 0.0f, 0.0f, 1.0f, 0.8f, 0.6f,    /// END FIFTH FACE
    ///////////////////////////////////////////////////////////////
    0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.8f,    /// BEGIN SIXTH FACE
    -2.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.8f,
    -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.8f,
    -2.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.8f,
    0.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.8f,
    0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.8f    /// END SIXTH FACE
  };

  indexData (cube, cubeMesh->getFloatsPerVertex(), data, indices);
  cubeMesh->addGeometry (data);
  cubeMesh->addIndices (indices);
  //cubeMesh->moveRight (2.0f);
  cubeMesh->pitch (45.0f);
  cubeMesh->prepareVao ();

  add("cube01", cubeMesh);

  data.clear ();
  indices.clear ();

  ColorsMesh* largeLMesh = new ColorsMesh(context, colors);

  const std::vector<float> largeL 
  {
    2.5f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   /// BEGIN FRONT FACE
    1.0f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   
    1.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    1.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   //      
    4.0f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    2.5f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,    /// END FRONT FACE
    ////////////////////////////////////////////////////////////////
    1.0f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   /// BEGIN LEFT SIDE FACE
    1.0f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    //
    1.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   /// END LEFT SIDE FACE
    ////////////////////////////////////////////////////////////////
    1.0f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,   /// BEGIN BACK FACE 
    2.5f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    //
    2.5f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,     
    1.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    
    1.0f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,   //         
    2.5f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    //
    4.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    
    2.5f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    
    2.5f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,    /// END BACK FACE
    ////////////////////////////////////////////////////////////////
    2.5f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,   /// BEGIN RIGHT-TOP FACE
    2.5f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    2.5f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,   /// END RIGHT-TOP FACE
    ////////////////////////////////////////////////////////////////
    2.5f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,    /// BEGIN UPPER-LIP FACE
    2.5f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,     
    4.0f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    4.0f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,    /// END UPPER-LIP FACE
    ////////////////////////////////////////////////////////////////
    4.0f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,    /// BEGIN RIGHT-BOT FACE
    4.0f, 3.0f, 1.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    4.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,
    4.0f, 3.0f, 0.5f, 1.0f, 0.0f, 1.0f,    /// END RIGHT-BOT FACE
    ////////////////////////////////////////////////////////////////
    2.5f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   /// BEGIN TOP FACE
    2.5f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,   //
    1.0f, 6.75f, 0.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,
    2.5f, 6.75f, 1.5f, 1.0f, 0.0f, 1.0f,   /// END TOP FACE
    ////////////////////////////////////////////////////////////////
    4.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    /// BEGIN BOTTOM FACE
    4.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,    //
    1.0f, 1.5f, 1.5f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f, 
    4.0f, 1.5f, 0.5f, 1.0f, 0.0f, 1.0f,    /// END BOTTOM FACE
  };

  indexData (largeL, largeLMesh->getFloatsPerVertex(), data, indices);
  largeLMesh->addGeometry (data);
  largeLMesh->addIndices (indices);
  //largeLMesh->yaw (25.0f);
  largeLMesh->scaleLocal (2.0f);
  largeLMesh->prepareVao ();

  add("largeL01", largeLMesh);

  data.clear ();
  indices.clear ();
  
  /*                            A08 Meshes                              */
  /*                         randomFaceColors                           */         
  const std::vector<Triangle> new_cube = buildCube ();

  ColorsMesh* randomFaceColors = new ColorsMesh (context, colors);
  std::vector<Vector3> faceColors = generateRandomFaceColors (new_cube);
  std::vector<float> fc_cube_data = dataWithFaceColors (new_cube, faceColors);
  
  indexData (fc_cube_data, randomFaceColors->getFloatsPerVertex(), data, indices);
  randomFaceColors->addGeometry (data);
  randomFaceColors->addIndices (indices);
  randomFaceColors->moveRight (-5);
  randomFaceColors->prepareVao ();

  add("cube02", randomFaceColors);

  data.clear ();
  indices.clear ();

  /*                        randomVertexColors                          */ 
  ColorsMesh* randomVertexColors = new ColorsMesh (context, colors);
  std::vector<Vector3> vertexColors = generateRandomVertexColors (new_cube);
  std::vector<float> vc_cube_data = dataWithVertexColors (new_cube, vertexColors);
  
  indexData (vc_cube_data, randomVertexColors->getFloatsPerVertex (), data, indices);
  randomVertexColors->addGeometry (data);
  randomVertexColors->addIndices (indices);
  randomVertexColors->moveRight (-5);
  randomVertexColors->moveUp (2);
  randomVertexColors->prepareVao ();

  add ("cube03", randomVertexColors);

  data.clear ();
  indices.clear ();

  /*                        computedFaceNormals                         */ 
  NormalsMesh* computedFaceNormals = new NormalsMesh (context, normals);
  std::vector<Vector3> faceNormals = computeFaceNormals (new_cube);
  std::vector<float> fn_cube_data = dataWithFaceNormals (new_cube, faceNormals);

  indexData (fn_cube_data, computedFaceNormals->getFloatsPerVertex (), data, indices);
  computedFaceNormals->addGeometry (data);
  computedFaceNormals->addIndices (indices);
  computedFaceNormals->moveRight (-5);
  computedFaceNormals->moveUp (4);
  computedFaceNormals->prepareVao ();

  add ("cube04", computedFaceNormals);

  data.clear ();
  indices.clear ();

  /*                       computedVertexNormals                        */ 
  NormalsMesh* computedVertexNormals = new NormalsMesh (context, normals);
  std::vector<Vector3> vertexNormals = computeVertexNormals (new_cube, faceNormals);
  std::vector<float> vn_cube_data = dataWithVertexNormals (new_cube, vertexNormals);

  indexData (vn_cube_data, computedVertexNormals->getFloatsPerVertex (), data, indices);
  computedVertexNormals->addGeometry (data);
  computedVertexNormals->addIndices (indices);
  computedVertexNormals->moveRight (-5);
  computedVertexNormals->moveUp (6);
  computedVertexNormals->prepareVao ();

  add ("cube05", computedVertexNormals);

  data.clear ();
  indices.clear ();

  /// Bear
  NormalsMesh* bearMesh = new NormalsMesh (context, normals, "models/bear.obj", 0);
  bearMesh->prepareVao ();

  add ("bear01", bearMesh);

  data.clear ();
  indices.clear ();
}

