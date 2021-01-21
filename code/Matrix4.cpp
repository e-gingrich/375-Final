/// \file Matrix4.cpp
/// \brief Initialization of Matrix4 class and any associated global functions.
/// \author Ethan Gingrich
/// \version A07

/// For tangent
#include <math.h>
/// For I/O 
#include <iomanip>

#include "Matrix4.hpp"

/// \brief Initializes to the identity matrix.
/// \post rx, uy, bz, and tw are 1.0f while all other elements are 0.0f.
Matrix4::Matrix4 ()
{
    setToIdentity ();
}

/// \brief Initializes a ne matrix from the four basis vectors.
/// \param[in] right The first column of the new matrix.
/// \param[in] up The second column of the new matrix.
/// \param[in] back The third column of the new matrix.
/// \param[in] translation The fourth column of the new matrix.
Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
	   const Vector4& back, const Vector4& translation)
{
    m_right = right;
    m_up = up;
    m_back = back;
    m_translation = translation;
}

/// \brief Gets the right vector.
/// \return A copy of the first column.
Vector4
Matrix4::getRight () const
{
    const Vector4 right (m_right);
    return right;
}

/// \brief Gets the up vector.
/// \return A copy of the second column.
Vector4
Matrix4::getUp () const
{
    const Vector4 up (m_up);
    return up;
}

/// \brief Gets the back vector.
/// \return A copy of the third column.
Vector4
Matrix4::getBack () const
{
    const Vector4 back (m_back);
    return back;
}

/// \brief Gets the translation vector.
/// \return A copy of the fourth column.
Vector4
Matrix4::getTranslation () const
{
    const Vector4 trans (m_translation);
    return trans;
}

/// \brief Sets this to the identity matrix.
/// \post The elements along the main diagonal are 1.0f while all others are
///   0.0f.
void
Matrix4::setToIdentity ()
{
    m_right.set (1.0f, 0.0f, 0.0f, 0.0f);
    m_up.set (0.0f, 1.0f, 0.0f, 0.0f);
    m_back.set (0.0f, 0.0f, 1.0f, 0.0f);
    m_translation.set (0.0f, 0.0f, 0.0f, 1.0f);
}

/// \brief Sets this to the zero matrix.
/// \post All elements are 0.0f.
void
Matrix4::setToZero ()
{   
    m_right.set (0.0f);
    m_up = m_back = m_translation = m_right;
}

/// \brief Gets a const pointer to the first element.
/// \return A pointer to rx.
const float*
Matrix4::data () const
{
    return &m_right.m_x;
}

/// \brief Sets this to a symmetric perspective projection matrix.
/// \param[in] fovYDegrees The vertical field of view angle, in degrees.
/// \param[in] aspectRatio The ratio of width to height.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to a symmetric perspective projection.
void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
			      double nearPlaneZ, double farPlaneZ)
{
    m_right.set (1/(aspectRatio * tan(fovYDegrees/2)), 0.0, 0.0, 0.0);
    m_up.set (0.0, 1/tan (fovYDegrees/2), 0.0, 0.0);
    m_back.set (0.0, 0.0, (nearPlaneZ + farPlaneZ)/(nearPlaneZ - farPlaneZ), -1);
    m_translation.set (0.0, 0.0, (2 * farPlaneZ * nearPlaneZ)/(nearPlaneZ - farPlaneZ), 0.0);
}

/// \brief Sets this to an assymetric perspective projection matrix.
/// \param[in] left The x-value of the left side of the projection plane.
/// \param[in] right The x-value of the right side of the projection plane.
/// \param[in] bottom The y-value of the bottom of the projection plane.
/// \param[in] top The y-value of the top of the projection plane.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to an asymmetric perspective projection.
void
Matrix4::setToPerspectiveProjection (double left, double right,
			      double bottom, double top,
			      double nearPlaneZ, double farPlaneZ)
{
    m_right.set ((2 * nearPlaneZ)/right - left, 0.0, 0.0, 0.0);
    m_up.set (0.0, (2 * nearPlaneZ)/top - bottom, 0.0, 0.0);
    m_back.set ((right + left)/(right - left), (top + bottom)/(top - bottom), (nearPlaneZ + farPlaneZ)/(nearPlaneZ - farPlaneZ), -1.0);
    m_translation.set (0.0, 0.0, (2 * farPlaneZ * nearPlaneZ)/(nearPlaneZ - farPlaneZ), 0.0);
}

/// \brief Sets this to an orthographic projection matrix.
/// \param[in] left The x-value of the left plane.
/// \param[in] right The x-value of the right plane.
/// \param[in] bottom The y-value of the bottom plane.
/// \param[in] top The y-value of the top plane.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to an orthographic projection.
void
Matrix4::setToOrthographicProjection (double left, double right,
			       double bottom, double top,
			       double nearPlaneZ, double farPlaneZ)
{
    m_right.set (2/(right - left), 0.0, 0.0, 0.0);
    m_up.set (0.0, 2/(top - bottom), 0.0, 0.0);
    m_back.set (0.0, 0.0, 2/(nearPlaneZ - farPlaneZ), 0.0);
    m_translation.set (-(right + left)/(right - left), (top + bottom)/(top - bottom), (nearPlaneZ + farPlaneZ)/(nearPlaneZ - farPlaneZ), 1.0);
}

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///     rx ux bx tx
///     ry uy by ty
///     rz uz bz tz
///     rw uw bw tw
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
    /// X Values
    out << std::fixed << std::setprecision(2)
      << std::setw(10) << m.getRight().m_x
      << std::setw(10) << m.getUp().m_x
      << std::setw(10) << m.getBack().m_x
      << std::setw(10) << m.getTranslation().m_x << "\n";
    /// Y Values
    out << std::fixed << std::setprecision(2)
      << std::setw(10) << m.getRight().m_y
      << std::setw(10) << m.getUp().m_y
      << std::setw(10) << m.getBack().m_y
      << std::setw(10) << m.getTranslation().m_y << "\n";
    /// Z Values
    out << std::fixed << std::setprecision(2)
      << std::setw(10) << m.getRight().m_z
      << std::setw(10) << m.getUp().m_z
      << std::setw(10) << m.getBack().m_z
      << std::setw(10) << m.getTranslation().m_z << "\n";
    /// W Values
    out << std::fixed << std::setprecision(2)
      << std::setw(10) << m.getRight().m_w
      << std::setw(10) << m.getUp().m_w
      << std::setw(10) << m.getBack().m_w
      << std::setw(10) << m.getTranslation().m_w << "\n";

    return out;
}

/// \brief Checks whether or not two matrices are equal.
/// Matrices are equal if each of their respective elements are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix4& m1, const Matrix4& m2)
{
    bool right = m1.getRight() == m2.getRight();
    bool up = m1.getUp() == m2.getUp();
    bool back = m1.getBack () == m2.getBack ();
    bool trans = m1.getTranslation() == m2.getTranslation ();
    return right && up && back && trans;
}