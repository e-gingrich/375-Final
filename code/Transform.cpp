/// \file Transform.cpp
/// \brief Initialization of Transform class and any associated global functions.
/// \author Ethan Gingrich
/// \version A06

/*         MACRO DEFINITIONS        */
#define RX m_rotScale.getRight ().m_x
#define RY m_rotScale.getRight ().m_y
#define RZ m_rotScale.getRight ().m_z

#define UX m_rotScale.getUp ().m_x
#define UY m_rotScale.getUp ().m_y
#define UZ m_rotScale.getUp ().m_z

#define BX m_rotScale.getBack ().m_x
#define BY m_rotScale.getBack ().m_y
#define BZ m_rotScale.getBack ().m_z

#define PX m_position.m_x
#define PY m_position.m_y
#define PZ m_position.m_z

#include "Transform.hpp"

/// \brief Initializes a new transform to the identity transform: one that
///   represents no scale, rotation, shear, reflection, translation, or
///   other change.
/// \post The Matrix3 component is the identity matrix, while the Vector3
///   component is the zero vector.
Transform::Transform ()
{
    Matrix3 m_rotScale ();
    Vector3 m_position ();
}

/// \brief Orthonormalizes the Matrix3 component.
/// \post The Matrix3 component contains three perpendicular unit vectors.
void
Transform::orthonormalize ()
{
    m_rotScale.orthonormalize ();
}

/// \brief Resets to the identity transform.
/// \post The Matrix3 component is the identity matrix, while the Vector3
///   component is the zero vector.
void
Transform::reset ()
{
    m_rotScale.setToIdentity ();
    m_position.set (0);
}

/// \brief Converts this to a 4x4 GLM matrix, so that it can be passed to our
///   shader program.
/// \return A Matrix4 containing the numbers of this matrix.
Matrix4
Transform::getTransform () const
{
    Vector4 right (RX, RY, RZ, 0.0f);
    Vector4 up (UX, UY, UZ, 0.0f);
    Vector4 back (BX, BY, BZ, 0.0f);
    Vector4 trans (PX, PY, PZ, 1.0f);

    Matrix4 m_transform (right, up, back, trans);
    return m_transform;
}

/// \brief Copies the elements of this transform into an array, in column-
///   major order.
/// \param[out] array The array to fill up.
/// \post The array contains rx, ry, rz, 0, ux, ... px, py, pz, 1.
void
Transform::getTransform (float array[16]) const
{
    float matrix[16] = {RX, RY, RZ, 0.0f, UX, UY, UZ, 0.0f, BX, BY, BZ, 0.0f, PX, PY, PZ, 1.0f};
    std::copy (matrix, matrix + 16, array);
}

/// \brief Gets the position component.
/// \return A copy of the position in this transformation.
Vector3
Transform::getPosition () const
{
    const Vector3 pos = m_position;
    return pos;
}

/// \brief Sets the position component.
/// \param[in] position The new position component.
/// \post The position in this transformation has been set to position.
void
Transform::setPosition (const Vector3& position)
{
    m_position.set (position.m_x, position.m_y, position.m_z);
}

/// \brief Sets the position component.
/// \param[in] x The new x-coordinate of the position.
/// \param[in] y The new y-coordinate of the position.
/// \param[in] z The new z-coordinate of the position.
/// \post The position in this transformation has been set to [x, y, z].
void
Transform::setPosition (float x, float y, float z)
{
    m_position.set (x, y, z);
}

/// \brief Gets the right basis vector.
/// \return A copy of the right basis vector.
Vector3
Transform::getRight () const
{
    const Vector3 right (RX, RY, RZ);
    return right;
}

/// \brief Gets the up basis vector.
/// \return A copy of the up basis vector.
Vector3
Transform::getUp () const
{
    const Vector3 up (UX, UY, UZ);
    return up;
}

/// \brief Gets the back basis vector.
/// \return A copy of the back basis vector.
Vector3
Transform::getBack () const
{
    const Vector3 back (BX, BY, BZ);
    return back;
}

/// \brief Gets the orientation/scale matrix.
/// \return A copy of the orientation/scale matrix.
Matrix3
Transform::getOrientation () const
{
    const Matrix3 ori (RX, RY, RZ, 
                       UX, UY, UZ,
                       BX, BY, BZ);
    return ori;
}

/// \brief Sets the orientation/scale matrix.
/// \param[in] orientation The new orientation/scale matrix.
/// \post The orientation/scale matrix has been set to the parameter.
void
Transform::setOrientation (const Matrix3& orientation)
{
    m_rotScale.setRight (orientation.getRight ());
    m_rotScale.setUp (orientation.getUp ());
    m_rotScale.setBack (orientation.getBack ());
}

/// \brief Sets the orientation/scale matrix.
/// \param[in] right The new right vector.
/// \param[in] up The new up vector.
/// \param[in] The new back vector.
/// \post The orientation/scale matrix has been set to [right, up, back].
void
Transform::setOrientation (const Vector3& right, const Vector3& up,
		  const Vector3& back)
{
    m_rotScale.setRight (right);
    m_rotScale.setUp (up);
    m_rotScale.setBack (back);
}

/// \brief Moves "distance" units along the right vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local right direction.
void
Transform::moveRight (float distance)
{
    m_position += (distance * m_rotScale.getRight ());
}

/// \brief Moves "distance" units along the up vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local up direction.
void
Transform::moveUp (float distance)
{
    m_position += (distance * m_rotScale.getUp ());
}

/// \brief Moves "distance" units along the back vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local back direction.
void
Transform::moveBack (float distance)
{
    m_position += (distance * m_rotScale.getBack ());
}

/// \brief Moves "distance" units in "localDirection", which is relative
///   to the coordinate system defined by this transform.
/// \param[in] distance How far to move.
/// \param[in] localDirection The (local) direction to move in.
/// \post The position has been moved that far in that direction.
void
Transform::moveLocal (float distance, const Vector3& localDirection)
{   
    m_position += (distance * localDirection);
}

/*
 *      1   0   0   d * t1x         r1x u1x b1x p1x         r1x u1x b1x (p1x + t1x)
 *      0   1   0   d * t1y     *   r1y u1y b1y p1y     =   r1y u1y b1y (p1y + t1y)
 *      0   0   1   d * t1z         r1z u1z b1z p1z         r1z u1z b1z (p1z + t1z)
 *      0   0   0   1               0   0   0   1           0   0   0   1
 */
/// \brief Moves "distance" units in "worldDirection", which is relative
///   to the world coodinate system.
/// \param[in] distance How far to move.
/// \param[in] worldDirection The (world) direction to move in.
/// \post The position has been moved that far in that direction.
void
Transform::moveWorld (float distance, const Vector3& worldDirection)
{
    Vector3 world = worldDirection;
    world.normalize ();
    m_position += (world * distance); 
}

/// \brief Rotates about the local X axis.
/// \param[in] angleDegrees how much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::pitch (float angleDegrees)
{
    Matrix3 rotMat;
    rotMat.setToRotationX (angleDegrees);

    m_rotScale *= rotMat;
}

/// \brief Rotates about the local Y axis.
/// \param[in] angleDegrees How much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::yaw (float angleDegrees)
{
    Matrix3 rotMat;
    rotMat.setToRotationY (angleDegrees);

    m_rotScale *= rotMat;
}

/// \brief Rotates about the local Z axis.
/// \param[in] angleDegrees How much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::roll (float angleDegrees)
{
    Matrix3 rotMat;
    rotMat.setToRotationZ (angleDegrees);

    m_rotScale *= rotMat;
}

/// \brief Rotates locally about an arbitrary local unit vector "axis".
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The (local) vector to rotate around.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::rotateLocal (float angleDegrees, const Vector3& axis)
{
    Matrix3 rotMat;
    rotMat.setFromAngleAxis (angleDegrees, axis);

    m_rotScale *= rotMat;
}

/// \brief Sets "up" to world Y, and adjusts "back" and "right"
///   to ensure the matrix is orthogonal.
/// If "back" is pointing in the Y or -Y direction,
///   make it [ 0 0 1 ].
/// This will override any scaling, shearing, pitching,
///   or rolling that existed, while leaving yawing and
///   movement.
/// \post The up vector in the orientation/scale matrix is [0, 1, 0].
/// \post The right and back vectors in the orientation/scale matrix are
///   perpendicular to the up vector and each other.
void
Transform::alignWithWorldY ()
{
    m_rotScale.setUp (Vector3 (0.0f, 1.0f, 0.0f));

    /// Only occurs if "back" is pointing in the Y or -Y direction
    if (m_rotScale.getBack () == Vector3 (0.0f, 1.0f, 0.0f) || m_rotScale.getBack () == Vector3 (0.0f, -1.0f, 0.0f))
    {
        m_rotScale.setBack (Vector3 (0.0f, 0.0f, 1.0f));

        Vector3 newRight = m_rotScale.getUp().cross (m_rotScale.getBack ());
        newRight.normalize ();
        m_rotScale.setRight (newRight);

        return;
    }

    Vector3 newBack = m_rotScale.getRight ().cross (m_rotScale.getUp ());
    newBack.normalize ();
    m_rotScale.setBack (newBack);

    Vector3 newRight = m_rotScale.getUp ().cross (m_rotScale.getBack ());
    newRight.normalize ();
    m_rotScale.setRight (newRight);
}

/// \brief Rotates around the world unit vector "axis".
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The (world) vector to rotate around.
/// \post The orientation/scale matrix includes this rotation after whatever
///   transformations it already encoded.
void
Transform::rotateWorld (float angleDegrees, const Vector3& axis)
{
    Matrix3 rotMat;
    rotMat.setFromAngleAxis (angleDegrees, axis);

    m_rotScale = rotMat * m_rotScale;
}

/// \brief Scales locally using a uniform scale.
/// \param[in] scale The scaling factor.
/// \post The orientation/scale matrix includes this scale before whatever
///   transformations it already encoded.
void
Transform::scaleLocal (float scale)
{
    Matrix3 scaleMat;
    scaleMat.setToScale (scale);

    m_rotScale *= scaleMat;
}

/// \brief Scales locally using a non-uniform scale.
/// \param[in] scaleX The scaling factor for the X direction.
/// \param[in] scaleY The scaling factor for the Y direction.
/// \param[in] scaleZ The scaling factor for the Z direction.
/// \post The orientation/scale matrix includes this scale before whatever
///   transformations it already encoded.
void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
    Matrix3 scaleMat;
    scaleMat.setToScale (scaleX, scaleY, scaleZ);

    m_rotScale *= scaleMat;
}

/// \brief Scales with regard to world using a uniform scale.
/// \param[in] scale The scaling factor.
/// \post The orientation/scale matrix includes this scale after whatever
///   transformations it already encoded.
void
Transform::scaleWorld (float scale)
{
    Matrix3 scaleMat;
    scaleMat.setToScale (scale);

    m_rotScale = scaleMat * m_rotScale;
}

/// \brief Scales with regard to world using a non-uniform scale.
/// \param[in] scaleX The scaling factor for the X direction.
/// \param[in] scaleY The scaling factor for the Y direction.
/// \param[in] scaleZ The scaling factor for the Z direction.
/// \post The orientation/scale matrix includes this scale after whatever
///   transformations it already encoded.
void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
    Matrix3 scaleMat;
    scaleMat.setToScale (scaleX, scaleY, scaleZ);

    m_rotScale = scaleMat * m_rotScale;
}

/// \brief Shears local X by Y and Z.
/// \param[in] shearY The factor of Y to shear X by.
/// \param[in] shearZ The factor of Z to shear X by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalXByYz (float shearY, float shearZ)
{
    Matrix3 shearMat;
    shearMat.setToShearXByYz (shearY, shearZ);

    m_rotScale *= shearMat;
}

/// \brief Shears local Y by X and Z.
/// \param[in] shearX The factor of X to shear Y by.
/// \param[in] shearZ The factor of Z to shear Y by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalYByXz (float shearX, float shearZ)
{
    Matrix3 shearMat;
    shearMat.setToShearYByXz (shearX, shearZ);

    m_rotScale *= shearMat;
}

/// \brief Shears local Z by X and Y.
/// \param[in] shearX The factor of X to shear Z by.
/// \param[in] shearY The factor of Y to shear Z by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalZByXy (float shearX, float shearY)
{
    Matrix3 shearMat;
    shearMat.setToShearZByXy (shearX, shearY);

    m_rotScale *= shearMat;
}

/// \brief Inverts this transform assuming it consists of a pure rotation
///   and a translation.
/// This can be used to compute the view transform.
/// \pre This transform consists of a pure rotation and translation.
/// \post This transform has been inverted.
void
Transform::invertRt ()
{
    m_rotScale.invertRotation ();
    m_position = m_rotScale * -m_position;
}

/// \brief Combines this with "t" in the order this * t.
/// \param[in] t Another transform that should be combined with this.
/// \post This transform consists of itself times t.
void
Transform::combine (const Transform& t)
{
    *this = *this * t;
}

/// \brief Combines two transforms into their product.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return A new transform that is t1 * t2.
Transform
operator* (const Transform& t1, const Transform& t2)
{
    Transform t3;
    /// orientation matrix of the new transform
    Matrix3 ori;
    ori = t1.getOrientation () * t2.getOrientation ();

    /// position matrix of the new transform
    float x = t1.getRight ().m_x * t2.getPosition ().m_x + t1.getUp ().m_x * t2.getPosition ().m_y + t1.getBack ().m_x * t2.getPosition ().m_z + t1.getPosition ().m_x * 1.0;
    float y = t1.getRight ().m_y * t2.getPosition ().m_x + t1.getUp ().m_y * t2.getPosition ().m_y + t1.getBack ().m_y * t2.getPosition ().m_z + t1.getPosition ().m_y * 1.0;
    float z = t1.getRight ().m_z * t2.getPosition ().m_x + t1.getUp ().m_z * t2.getPosition ().m_y + t1.getBack ().m_z * t2.getPosition ().m_z + t1.getPosition ().m_z * 1.0;
    Vector3 pos (x, y, z);

    t3.setOrientation (ori);
    t3.setPosition (pos);
    return t3;
}

/// \brief Prints the complete 4x4 matrix the Transform represents.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx px
///      ry uy by py
///      rz uz bz pz
///      0  0  0  1
/// \param[inout] out An output stream.
/// \param[in] t A transform.
/// \return The output stream.
/// \post The transform has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
    Matrix3 ori = t.getOrientation ();
    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10) << ori.getRight ().m_x << std::setw(10) << ori.getUp ().m_x << std::setw(10) << ori.getBack ().m_x << std::setw(10) << t.getPosition ().m_x << "\n";

    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10) << ori.getRight ().m_y << std::setw(10) << ori.getUp ().m_y << std::setw(10) << ori.getBack ().m_y << std::setw(10) << t.getPosition ().m_y << "\n";

    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10) << ori.getRight ().m_z << std::setw(10) << ori.getUp ().m_z << std::setw(10) << ori.getBack ().m_z << std::setw(10) << t.getPosition ().m_z << "\n";

    const char* BOT = "      0.00      0.00      0.00      1.00\n";

    out << BOT;

    return out;
}

/// \brief Tests whether or not two transforms are equal.
/// Transforms are equal if their matrices and vectors are equal.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return Whether or not t1 and t2 are equal.
bool
operator== (const Transform& t1, const Transform& t2)
{
    return (t1.getOrientation () == t2.getOrientation ()) && (t1.getPosition () == t2.getPosition ());
}
