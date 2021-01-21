/// \file Camera.hpp
/// \brief Initialization of Camera class.
/// \author Ethan Gingrich
/// \version A03

/// HEADER FUNCTIONS
#include <math.h>

#include "Camera.hpp"
#include "OpenGLContext.hpp"

/// MACRO DEFINITIONS
#define localRight m_world.getRight()
#define localUp m_world.getUp()
#define localBack m_world.getBack()
#define toRadians(degrees) degrees*(M_PI/180)

Camera::Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	float nearClipPlaneDistance, float farClipPlaneDistance,
	float aspectRatio, float verticalFieldOfViewDegrees)
{
    m_eyePosition.set (eyePosition.m_x, eyePosition.m_y, eyePosition.m_z);
    // Since setPosition/Projection does the setting for it, use that to keep code clean *chef's kiss*
    setPosition (eyePosition);
    setProjectionSymmetricPerspective(verticalFieldOfViewDegrees, aspectRatio, nearClipPlaneDistance, farClipPlaneDistance);
    m_localBackDirection = localBackDirection;
    Vector3 up (0.0, 1.0, 0.0); /// assuming Up w/ magn. of 1 is ortho
    Vector3 right = up.cross (localBackDirection);
    up = localBackDirection.cross (right);

    m_world.setOrientation (right , up, localBackDirection);
    m_world.orthonormalize ();
}

Camera::~Camera()
{
}

void
Camera::setPosition (const Vector3& position)
{
    m_world.setPosition (position.m_x, position.m_y, position.m_z);
    viewRecalculate = true;
}

void 
Camera::moveRight (float distance)
{
    m_world.moveRight (distance);
    viewRecalculate = true;
}

void 
Camera::moveUp (float distance)
{
    m_world.moveUp (distance);
    viewRecalculate = true;
}

void 
Camera::moveBack (float distance)
{
    m_world.moveBack (distance);
    viewRecalculate = true;
}

void
Camera::yaw (float degrees)
{
    m_world.yaw (degrees);
    viewRecalculate = projRecalculate = true; 
}

void
Camera::pitch (float degrees)
{
    m_world.pitch (degrees);
    viewRecalculate = projRecalculate = true;
}

void
Camera::roll (float degrees)
{
    m_world.roll (degrees);
    viewRecalculate = projRecalculate = true;
}

Transform
Camera::getViewMatrix ()
{
    if (viewRecalculate)
    {
        m_viewMatrix.setOrientation (m_world.getOrientation ());
        m_viewMatrix.setPosition (m_world.getPosition ());

        m_viewMatrix.invertRt ();
    }
    return m_viewMatrix;
}

void
Camera::setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
	double nearZ, double farZ)
{
    m_projectionMatrix.setToPerspectiveProjection (toRadians(verticalFovDegrees), aspectRatio, 
                            nearZ, farZ);
}

void
Camera::setProjectionAsymmetricPerspective (double left, double right,
                    double top, double bottom, double nearZ, double farZ)
{
    m_projectionMatrix.setToPerspectiveProjection (left, right, bottom, top, nearZ, farZ);
}

void
Camera::setProjectionOrthographic (double left, double right, double top,
                    double bottom, double nearZ, double farZ)
{
    m_projectionMatrix.setToOrthographicProjection (left, right, bottom, top, nearZ, farZ);
}

Matrix4 
Camera::getProjectionMatrix ()
{   
    return m_projectionMatrix;
}

void
Camera::resetPose()
{
    setPosition (m_eyePosition);
    Vector3 up (0.0, 1.0, 0.0); /// assuming Up w/ magn. of 1 is ortho
    Vector3 right = up.cross (m_localBackDirection);
    up = m_localBackDirection.cross (right);

    m_world.setOrientation (right , up, m_localBackDirection);
    m_world.orthonormalize ();
    
    viewRecalculate = projRecalculate = true;
    getViewMatrix();
    getProjectionMatrix();
}   
