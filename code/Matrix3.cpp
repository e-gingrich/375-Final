/// \file Matrix3.cpp
/// \brief Declaration of Matrix3 class and any associated global functions.
/// \author Ethan Gingrich
/// \version A05

/// Wrote these macros to save me from putting a permanent
/// finger print on the "_" key

/// Right vector macro definitions
#define COL1ROW1 m_right.m_x
#define COL1ROW2 m_right.m_y
#define COL1ROW3 m_right.m_z
/// Up vector macro definitions
#define COL2ROW1 m_up.m_x
#define COL2ROW2 m_up.m_y
#define COL2ROW3 m_up.m_z
/// Back vector macro definitions
#define COL3ROW1 m_back.m_x
#define COL3ROW2 m_back.m_y
#define COL3ROW3 m_back.m_z
/// Degrees to radians conversion
#define DEG2RAD angleDegrees * M_PI / 180

/// For overload of shift operator
#include <iostream>

#include "Matrix3.hpp"

/// \brief Initializes a new matrix to the identity matrix.
/// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
Matrix3::Matrix3 () 
{
	m_right.set (1.0f, 0.0f, 0.0f);
	m_up.set (0.0f, 1.0f, 0.0f);
	m_back.set (0.0f, 0.0f, 1.0f);
}

/// \brief Initializes a new matrix from its 9 elements.
/// \param[in] rx The first column, first row.
/// \param[in] ry The first column, second row.
/// \param[in] rz The first column, third row.
/// \param[in] ux The second column, first row.
/// \param[in] uy The second column, second row.
/// \param[in] uz The second column, third row.
/// \param[in] bx The third column, first row.
/// \param[in] by The third column, second row.
/// \param[in] bz The third column, third row.
/// \post Each element has the value of its matching parameter.
Matrix3::Matrix3 (float rx, float ry, float rz,
         float ux, float uy, float uz,
         float bx, float by, float bz)
{
	m_right.set (rx, ry, rz);
	m_up.set (ux, uy, uz);
	m_back.set (bx, by, bz);
}

/// \brief Initializes a new matrix from three basis vectors.
/// \param[in] right The first column of the matrix.
/// \param[in] up The second column of the matrix.
/// \param[in] back The third column of the matrix.
/// \post Each column vector has the value of its matching parameter.
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
           const Vector3& back)
{
	m_right.set (right.m_x, right.m_y, right.m_z);
	m_up.set (up.m_x, up.m_y, up.m_z);
	m_back.set (back.m_x, back.m_y, back.m_z);
}

/// \brief Initializes a new matrix from two basic vectors, computing the third.
/// \param[in] right The first column of the matrix.
/// \param[in] up The second column of the matrix.
/// \param[in] makeOrthonormal Whether or not to orthonormalize the vectors.
/// \post The right and up vectors have the value of their matching parameters.
/// \post The back vector is the cross product of the right and up vectors.
/// \post If makeOrthonormal is true, the vectors have been orthonormalized.
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
           bool makeOrthonormal)
{
	m_right.set (right.m_x, right.m_y, right.m_z);
	m_up.set (up.m_x, up.m_y, up.m_z);
	m_back = right.cross (up);

	if (makeOrthonormal)
		orthonormalize();
}

Matrix3::~Matrix3 ()
{
}

/// \brief Sets this to the identity matrix.
/// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
void
Matrix3::setToIdentity ()
{
	m_right.set (1.0f, 0.0f, 0.0f);
	m_up.set (0.0f, 1.0f, 0.0f);
	m_back.set (0.0f, 0.0f, 1.0f);
}

/// \brief Sets this to the zero matrix.
/// \post All elements are 0.0f.
void
Matrix3::setToZero ()
{
	m_right.set (0);
	m_up. set (0);
	m_back. set (0);
}

/// \brief Retrieves a pointer to the first column, first row.
/// \return A pointer to the beginning of the data.
/// Because of the way our data is stored, you can use pointer arithmetic to
///   get to the first column second row, first column third row, second
///   column first row, and so forth.
float*
Matrix3::data ()
{
	float *data = &COL1ROW1;
	return data;
}

/// \brief Retrieves a constant pointer to the first column, first row.
/// \return A constant pointer to the beginning of the data.
/// Because of the way our data is stored, you can use pointer arithmetic to
///   get to the first column second row, first column third row, second
///   column first row, and so forth.  
const float*
Matrix3::data () const
{
	const float *data = &COL1ROW1;
	return data;
}

/// \brief Sets the right vector.
/// \param[in] right The new value for the first column.
/// \post The first column is a copy of the parameter.
void
Matrix3::setRight (const Vector3& right)
{
	m_right.set (right.m_x, right.m_y, right.m_z);
}

/// \brief Gets the right vector.
/// \return A copy of the first column.
Vector3
Matrix3::getRight () const
{
	const Vector3 right (COL1ROW1, COL1ROW2, COL1ROW3);
	return right;
}

/// \brief Sets the up vector.
/// \param[in] up The new value for the second column.
/// \post The second column is a copy of the parameter.
void
Matrix3::setUp (const Vector3& up)
{
	m_up.set (up.m_x, up.m_y, up.m_z);
}

/// \brief Gets the up vector.
/// \return A copy of the second column.
Vector3
Matrix3::getUp () const
{
	const Vector3 up (COL2ROW1, COL2ROW2, COL2ROW3);
	return up;
}

/// \brief Sets the back vector.
/// \param[in] back The new value for the third column.
/// \post The third column is a copy of the parameter.
void
Matrix3::setBack (const Vector3& back)
{
	m_back.set (back.m_x, back.m_y, back.m_z);
}

/// \brief Gets the back vector.
/// \return A copy of the third column.
Vector3
Matrix3::getBack () const
{
	const Vector3 back (COL3ROW1, COL3ROW2, COL3ROW3);
	return back;
}

/// \brief Sets the forward (opposite of back) vector.
/// \param[in] forward The new forward vector.
/// \post The third column is the negation of the parameter.
void
Matrix3::setForward (const Vector3& forward)
{
	m_back.set (-forward.m_x, -forward.m_y, -forward.m_z);
}

/// \brief Gets the forward (opposite of back) vector.
/// \return A copy of the negation of the third column.
Vector3
Matrix3::getForward () const
{
	const Vector3 forward (-COL3ROW1, -COL3ROW2, -COL3ROW3);
	return forward;
}

/// \brief Inverts this matrix, using an fast algorithm that will only work for rotations.
/// \pre This matrix represents a pure rotation.
/// \post This matrix has been replaced with its inversion.
void
Matrix3::invertRotation ()
{
	transpose ();
}

/// \brief Inverts this matrix, using an expensive algorithm.
/// \post This matrix has been replaced with its inversion.
void
Matrix3::invert ()
{
	float det = determinant ();
	if (det != 0.0f)
	{
		Matrix3 temp;

		temp.COL1ROW1 = 1.0f/det * ((COL2ROW2 * COL3ROW3) - (COL3ROW2 * COL2ROW3));
		temp.COL1ROW2 = 1.0f/det * ((COL3ROW2 * COL1ROW3) - (COL1ROW2 * COL3ROW3));
		temp.COL1ROW3 = 1.0f/det * ((COL1ROW2 * COL2ROW3) - (COL2ROW2 * COL1ROW3));

		temp.COL2ROW1 = 1.0f/det * ((COL3ROW1 * COL2ROW3) - (COL2ROW1 * COL3ROW3));
		temp.COL2ROW2 = 1.0f/det * ((COL1ROW1 * COL3ROW3) - (COL3ROW1 * COL1ROW3));
		temp.COL2ROW3 = 1.0f/det * ((COL2ROW1 * COL1ROW3) - (COL1ROW1 * COL2ROW3));

		temp.COL3ROW1 = 1.0f/det * ((COL2ROW1 * COL3ROW2) - (COL3ROW1 * COL2ROW2));
		temp.COL3ROW2 = 1.0f/det * ((COL3ROW1 * COL1ROW2) - (COL1ROW1 * COL3ROW2));
		temp.COL3ROW3 = 1.0f/det * ((COL1ROW1 * COL2ROW2) - (COL2ROW1 * COL1ROW2));

		m_right = temp.m_right;
		m_up = temp.m_up;
		m_back = temp.m_back;
	}
}

/// \brief Calculates the determinant of this matrix.
/// \return The determinant.
float
Matrix3::determinant () const
{
	float det1 = (COL2ROW2 * COL3ROW3) - (COL3ROW2 * COL2ROW3);
	float det2 = (COL2ROW1 * COL3ROW3) - (COL3ROW1 * COL2ROW3);
	float det3 = (COL2ROW1 * COL3ROW2) - (COL3ROW1 * COL2ROW2);
	float part1 = COL1ROW1 * det1;
	float part2 = COL1ROW2 * det2;
	float part3 = COL1ROW3 * det3;

	return part1 - part2 + part3;
}

/// \brief Transposes this matrix.
/// \post The first column has become the first row, etc.
void
Matrix3::transpose ()
{
	Vector3 newRight (COL1ROW1, COL2ROW1, COL3ROW1);
	Vector3 newUp (COL1ROW2, COL2ROW2, COL3ROW2);
	Vector3 newBack (COL1ROW3, COL2ROW3, COL3ROW3);

	m_right = newRight;
	m_up = newUp;
	m_back = newBack;
}

/// \brief Makes the basis vectors orthonormal to each other.
/// Starts by assuming that the back vector is pointing in the correct
///   direction.  Normalizes the back vector.  Computes the right vector by
///   crossing up with back, and then normalizes it.  Computes the up vector
///   by crossing back with right, and then normalizes it.
/// \post All columns have a length of 1 and are mutually perpendicular.
/// \post The back vector points in the same direction that it did before.
void
Matrix3::orthonormalize ()
{
	m_back.normalize();

	m_right = m_up.cross (m_back);
	m_right.normalize();

	m_up = m_back.cross (m_right);
	m_up.normalize ();
}

/// \brief Makes this into a uniform scale matrix.
/// \param[in] scale The amount to scale up (or down).
/// \post This is a matrix that scales vectors by the specified factor.
void
Matrix3::setToScale (float scale) 
{
	m_right.set (scale , 0.0f, 0.0f);
	m_up.set (0.0f, scale, 0.0f);
	m_back.set (0.0f, 0.0f, scale);
}

/// \brief Makes this into a non-uniform scale matrix.
/// \param[in] scaleX The scale factor for the X direction.
/// \param[in] scaleY The scale factor for the Y direction.
/// \param[in] scaleZ The scale factor for the Z direction.
/// \post This is a matrix that scales vectors by the specified factors.
void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ) 
{
	m_right.set (scaleX , 0.0f, 0.0f);
	m_up.set (0.0f, scaleY, 0.0f);
	m_back.set (0.0f, 0.0f, scaleZ);
}

/// \brief Makes this into a matrix that shears X values.
/// \param[in] shearY The amount to shear by Y.
/// \param[in] shearZ The amount to shear by Z.
/// \post This is a matrix that shears X by the specified factors of Y and Z.
void
Matrix3::setToShearXByYz (float shearY, float shearZ) 
{
	m_right.set (1.0f, 0.0f, 0.0f);
	m_up.set (shearY, 1.0f, 0.0f);
	m_back.set (shearZ, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that shears Y values.
/// \param[in] shearX The amount to shear by X.
/// \param[in] shearZ The amount to shear by Z.
/// \post This is a matrix that shears Y by the specified factors of X and Z.
void
Matrix3::setToShearYByXz (float shearX, float shearZ) 
{
	m_right.set (1.0f, shearX, 0.0f);
	m_up.set (0.0f, 1.0f, 0.0f);
	m_back.set (0.0f, shearZ, 1.0f);
}

/// \brief Makes this into a matrix that shears Z values.
/// \param[in] shearX The amount to shear by X.
/// \param[in] shearY The amount to shear by Y.
/// \post This is a matrix that shears Z by the specified factors of X and Y.
void
Matrix3::setToShearZByXy (float shearX, float shearY) 
{
	m_right.set (1.0f, 0.0f, shearX);
	m_up.set (0.0f, 1.0f, shearY);
	m_back.set (0.0f, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that rotates around the X-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that rotates around the X-axis by the specified angle.
void
Matrix3::setToRotationX (float angleDegrees) 
{
	m_right.set (1.0f, 0.0f, 0.0f);
	m_up.set (0.0f, cos (DEG2RAD), sin (DEG2RAD));
	m_back.set (0.0f, -sin (DEG2RAD), cos (DEG2RAD));
}

/// \brief Makes this into a matrix that rotates around the Y-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that rotates around the Y-axis by the specified angle.
void
Matrix3::setToRotationY (float angleDegrees)
{
	m_right.set (cos (DEG2RAD), 0.0f, -sin (DEG2RAD));
	m_up.set (0.0f, 1.0f, 0.0f);
	m_back.set (sin (DEG2RAD), 0.0f, cos (DEG2RAD));
}

/// \brief Makes this into a matrix that rotates around the Z-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that roates around the Z-axis by the specified angle.
void
Matrix3::setToRotationZ (float angleDegrees)
{
	m_right.set (cos (DEG2RAD), sin (DEG2RAD), 0.0f);
	m_up.set (-sin (DEG2RAD), cos (DEG2RAD), 0.0f);
	m_back.set (0.0f, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that rotates around an arbitrary vector.
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The vector to rotate around.
/// \post This is a matrix that rotates around the specified vector by the specified angle.
void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis)
{
	Vector3 temp = axis;
	temp.normalize ();
	m_right.set (pow (temp.m_x, 2) + cos (DEG2RAD) * (1 - pow (temp.m_x, 2)), temp.m_x * temp.m_y * (1 - cos (DEG2RAD)) + (temp.m_z * sin(DEG2RAD)), temp.m_x * temp.m_z * (1 - cos(DEG2RAD)) - (temp.m_y * sin (DEG2RAD)));
	m_up.set (temp.m_x * temp.m_y * (1 - cos (DEG2RAD)) - (temp.m_z * sin(DEG2RAD)), pow (temp.m_y, 2) + cos (DEG2RAD) * (1 - pow (temp.m_y, 2)), temp.m_y * temp.m_z * (1 - cos (DEG2RAD)) + (temp.m_x * sin(DEG2RAD)));
	m_back.set (temp.m_x * temp.m_z * (1 - cos(DEG2RAD)) + (temp.m_y * sin (DEG2RAD)), temp.m_y * temp.m_z * (1 - cos (DEG2RAD)) - (temp.m_x * sin(DEG2RAD)), pow (temp.m_z, 2) + cos (DEG2RAD) * (1 - pow (temp.m_z, 2)));
}

/// \brief Negates this matrix.
/// \post Every element has been replaced by its negation.
void
Matrix3::negate ()
{
	m_right.negate ();
	m_up.negate ();
	m_back.negate ();
}

/// \brief Transforms a vector, computing *this * v.
/// \param[in] v The vector to multiply by this matrix.
/// \return The result of the multiplication.
Vector3
Matrix3::transform (const Vector3& v) const
{
	float x = COL1ROW1 * v.m_x + COL2ROW1 * v.m_y + COL3ROW1 * v.m_z;
	float y = COL1ROW2 * v.m_x + COL2ROW2 * v.m_y + COL3ROW2 * v.m_z;
	float z = COL1ROW3 * v.m_x + COL2ROW3 * v.m_y + COL3ROW3 * v.m_z;
	Vector3 transV (x, y, z);
	return transV;
}

/// \brief Adds another matrix to this.
/// \param[in] m The other matrix.
/// \return This matrix.
/// \post Every element of this matrix has its sum with the equivalent element in the other.
Matrix3&
Matrix3::operator+= (const Matrix3& m)
{
	m_right += m.getRight();
	m_up += m.getUp();
	m_back += m.getBack();
	return *this;
}

/// \brief Subtracts another matrix from this.
/// \param[in] m The other matrix.
/// \return This matrix.
/// \post Every element of this matrix has the difference of it and the equivalent element in the other.
Matrix3&
Matrix3::operator-= (const Matrix3& m)
{
	m_right -= m.getRight();
	m_up -= m.getUp();
	m_back -= m.getBack();
	return *this;
}

/// \brief Multiplies this matrix by a scalar.
/// \param[in] scalar The number to multiply by.
/// \return This matrix.
/// \post Every element of this matrix has the product of it and the scalar.
Matrix3&
Matrix3::operator*= (float scalar)
{
	m_right *= scalar;
	m_up *= scalar;
	m_back *= scalar;
	return *this;
}

/// \brief Multiplies this matrix by another matrix.
/// \param[in] m The matrix to multiply by.
/// \return This matrix.
/// \post This matrix contains the product of itself with m.
Matrix3&
Matrix3::operator*= (const Matrix3& m)
{
	Vector3 newR (COL1ROW1 * m.COL1ROW1 + COL2ROW1 * m.COL1ROW2 + COL3ROW1 * m.COL1ROW3, COL1ROW2 * m.COL1ROW1 + COL2ROW2 * m.COL1ROW2 + COL3ROW2 * m.COL1ROW3, COL1ROW3 * m.COL1ROW1 + COL2ROW3 * m.COL1ROW2 + COL3ROW3 * m.COL1ROW3);
	Vector3 newU (COL1ROW1 * m.COL2ROW1 + COL2ROW1 * m.COL2ROW2 + COL3ROW1 * m.COL2ROW3, COL1ROW2 * m.COL2ROW1 + COL2ROW2 * m.COL2ROW2 + COL3ROW2 * m.COL2ROW3, COL1ROW3 * m.COL2ROW1 + COL2ROW3 * m.COL2ROW2 + COL3ROW3 * m.COL2ROW3);
	Vector3 newB (COL1ROW1 * m.COL3ROW1 + COL2ROW1 * m.COL3ROW2 + COL3ROW1 * m.COL3ROW3, COL1ROW2 * m.COL3ROW1 + COL2ROW2 * m.COL3ROW2 + COL3ROW2 * m.COL3ROW3, COL1ROW3 * m.COL3ROW1 + COL2ROW3 * m.COL3ROW2 + COL3ROW3 * m.COL3ROW3);
	m_right = newR;
	m_up = newU;
	m_back = newB;
	return *this;
}

/// \brief Adds two matrices.
/// \param[in] m1 The first matrix to add.
/// \param[in] m2 The secondn matrix to add.
/// \return A new matrix that is m1 + m2.
Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 newM (m1.getRight (), m1.getUp (), m1.getBack ());
	return newM += m2;
}

/// \brief Subtracts two matrices.
/// \param[in] m1 The matrix to subtract from.
/// \param[in] m2 The matrix to subtract.
/// \return A new matrix that is m1 - m2.
Matrix3
operator- (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 newM (m1.getRight (), m1.getUp (), m1.getBack ());
	return newM -= m2;
}

/// \brief Negates a matrix.
/// \param[in] m The matrix to negate.
/// \return A new matrix that is -m.
Matrix3
operator- (const Matrix3& m)
{
	Vector3 newR = m.getRight();
	Vector3 newU = m.getUp();
	Vector3 newB = m.getBack();

	Matrix3 newM (-newR, -newU, -newB);
	return newM;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] m The matrix to multiply.
/// \param[in] scalar The number to multiply it by.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (const Matrix3& m, float scalar)
{
	Matrix3 newM (m.getRight (), m.getUp (), m.getBack ());
	return newM *= scalar;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] scalar The number to multiply it by.
/// \param[in] m The matrix to multiply.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (float scalar, const Matrix3& m)
{
	Matrix3 newM (m.getRight (), m.getUp (), m.getBack ());
	return newM *= scalar;
}

/// \brief Multiplies a matrix by another matrix.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return A new matrix rhat is m * m.
Matrix3
operator* (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 newM (m1.getRight (), m1.getUp (), m1.getBack ());
	return newM *= m2;
}

/// \brief Multiplies a matrix by a vector.
/// \param[in] m A matrix.
/// \param[in] v A vector.
/// \return A new vector that is m * v.
Vector3
operator* (const Matrix3& m, const Vector3& v)
{
	Matrix3 newM (m.getRight (), m.getUp (), m.getBack ());
	return m.transform (v);
}

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx
///      ry uy by
///      rz uz bz
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix3& m)
{
	out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
	out << std::setw (10) << m.getRight().m_x << std::setw (10) << m.getUp().m_x << std::setw (10) << m.getBack().m_x << "\n";

	out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
	out << std::setw (10) << m.getRight().m_y << std::setw (10) << m.getUp().m_y << std::setw (10) << m.getBack().m_y << "\n";

	out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
	out << std::setw (10) << m.getRight().m_z << std::setw (10) << m.getUp().m_z << std::setw (10) << m.getBack().m_z << "\n";

	return out;
}

/// \brief Checks whether or not two matrices are equal.
/// matrices are equal if each of their respective elements are within
///   0.000001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix3& m1, const Matrix3& m2)
{
	bool isRightEql = m1.getRight () == m2.getRight ();
	bool isUpEql = m1.getUp () == m2.getUp ();
	bool isBackEql = m1.getBack () == m2.getBack ();
	
	return isRightEql && isUpEql && isBackEql;
}