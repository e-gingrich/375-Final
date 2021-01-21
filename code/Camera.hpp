/// \file Camera.hpp
/// \brief Declaration of Camera class and any associated global functions.
/// \author Chad Hogg
/// \version A03

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "OpenGLContext.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Transform.hpp"
#include "Matrix4.hpp"

/// \brief An eye that is viewing the scene.
class Camera
{
public:

  /// \brief Constructs a new Camera.
  ///
  /// \param eyePosition The location (in world coordinates) where the camera
  ///   is located.
  /// \param localBackDirection A vector pointing backwards from the camera.
  /// \param nearClipPlaneDistance The distance to the closest things the
  ///   camera can "see".
  /// \param farClipPlaneDistance The distance to the farthest things the
  ///   camera can "see".
  /// \param aspectRatio The window's width divided by height.
  /// \param verticalFieldOfViewDegrees The angle determining how much the
  ///   camera "sees".
  /// \post All of the parameters have been copied into their respective data
  ///   members, and the local right and up have been calculated to be
  ///   orthonormal to the local back.
  Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	  float nearClipPlaneDistance, float farClipPlaneDistance,
	  float aspectRatio, float verticalFieldOfViewDegrees);

  /// \brief Destructs a Camera.
  ~Camera();

  /// \brief Sets the position (eye point) of the camera.
  /// \param[in] position The new position of the camera.
  /// \post The camera's location has been changed.
  void
  setPosition (const Vector3& position);

  /// \brief Moves the position (eye point) of the camera right or left.
  /// \param[in] distance How far to move along the right vector.
  /// \post The camera's location has been changed.
  void
  moveRight (float distance);

  /// \brief Moves the position (eye point) of the camera up or down.
  /// \param[in] distance How far to move along the up vector.
  /// \post The camera's location has been changed.
  void
  moveUp (float distance);

  /// \brief Moves the position (eye point) of the camera back or forward.
  /// \param[in] distance How far to move along the back vector.
  /// \post The camera's location has been changed.
  void
  moveBack (float distance);

  /// \brief Rotates the camera counterclockwise around the up vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  yaw (float degrees);

  /// \brief Rotates the camera counterclockwise around the right vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  pitch (float degrees);

  /// \brief Rotates the camera counterclockwise around the back vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  roll (float degrees);

  /// \brief Gets the view matrix, recalculating it only if necessary.
  /// \return A view matrix based on the camera's location and axis vectors.
  Transform
  getViewMatrix ();

  /// \brief Sets the values needed to specify a symmetric projection.
  /// \param[in] verticalFovDegrees The viewing angle.
  /// \param[in] aspectRatio The width / height.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
		 double nearZ, double farZ); 

  /// \brief Sets the values needed to specify an asymmetric projection.
  /// \param[in] left The x-value of the left side of the projection plane.
  /// \param[in] right The x-value of the right side of the projection plane.
  /// \param[in] bottom The y-value of the bottom of the projection plane.
  /// \param[in] top The y-value of the top of the projection plane.
  /// \param[in] nearZ The distance to the near clip plane.
  /// \param[in] farZ The distance to the far clip plane.
  void
  setProjectionAsymmetricPerspective (double left, double right,
            double top, double bottom, double nearZ, double farZ);

  /// \brief Sets the values needed to specify an orthographic projection.
  /// \param[in] left The x-value of the left plane.
  /// \param[in] right The x-value of the right plane.
  /// \param[in] bottom The y-value of the bottom plane.
  /// \param[in] top The y-value of the top plane.
  /// \param[in] nearZ The distance to the near clip plane.
  /// \param[in] farZ The distance to the far clip plane.
  void
  setProjectionOrthographic (double left, double right, double top,
            double bottom, double nearZ, double farZ);

  /// \brief Gets the projection matrix, recalculating it only if necessary.
  /// \return A projection matrix based on the vertical field of view,
  ///   aspect ratio, and near and far planes.
  Matrix4
  getProjectionMatrix ();

  /// \brief Resets the camera to its original pose.
  /// \post The position (eye point) is the same as what had been specified in
  ///   the constructor.
  /// \post The back vector is the same as what had been specified in the
  ///   constructor.
  /// \post The up and right vectors are computed as they had been in the
  ///   constructor.
  void
  resetPose ();

private:

  /// The location of the camera.
  Vector3 m_eyePosition;
  /// The original vector pointing back from the camera.
  Vector3 m_localBackDirection;

  /// The world transform matrix
  Transform m_world;

  /// The projection matrix.
  Matrix4 m_projectionMatrix;
  /// The view matrix.
  Transform m_viewMatrix;

  /// Determines whether the projection matrix needs to be recalculated
  bool projRecalculate;
  /// Determines whether the view matrix needs to be recalculated
  bool viewRecalculate;
};

#endif//CAMERA_HPP
