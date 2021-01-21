/// \file TestMatrix3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Ethan Gingrich
/// \version A05

#include <sstream>

#include "Matrix3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

/// Right vector macro definitions
#define COL1ROW1 getRight().m_x
#define COL1ROW2 getRight().m_y
#define COL1ROW3 getRight().m_z
/// Up vector macro definitions
#define COL2ROW1 getUp().m_x
#define COL2ROW2 getUp().m_y
#define COL2ROW3 getUp().m_z
/// Back vector macro definitions
#define COL3ROW1 getBack().m_x
#define COL3ROW2 getBack().m_y
#define COL3ROW3 getBack().m_z
/// Degrees to radians conversion
#define DEG2RAD 90.0f * M_PI / 180

/// CONSTRUCTOR TESTS
SCENARIO ("Matrix3 constructors", "[Matrix3][A05]") {
    GIVEN ("Nothing.") {
        WHEN ("I use the default constructor") {
            Matrix3 m;
            THEN ("The identity matrix is created (1.0f on main diagonal, 0.0f everywhere else)") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));
            }
        }
        
        WHEN ("I pass 1.0f 2.0f 3.0f 4.0f 5.0f 6.0f 7.0f 8.0f 9.0f into the Matrix constructor with 9 parameters") {
            Matrix3 m (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            THEN ("The matrix is initialized to [1.0f 2.0f 3.0f 4.0f 5.0f 6.0f 7.0f 8.0f 9.0f]"){
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (2.0f == Approx (m.COL1ROW2));
    REQUIRE (3.0f == Approx (m.COL1ROW3));
    REQUIRE (4.0f == Approx (m.COL2ROW1));
    REQUIRE (5.0f == Approx (m.COL2ROW2));
    REQUIRE (6.0f == Approx (m.COL2ROW3));
    REQUIRE (7.0f == Approx (m.COL3ROW1));
    REQUIRE (8.0f == Approx (m.COL3ROW2));
    REQUIRE (9.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I pass 3 vectors declared to <1.0f, 2.0f, 3.0f>, <4.0f, 5.0f, 6.0f>, <7.0f, 8.0f, 9.0f>") {
            Vector3 v (1.0f, 2.0f, 3.0f);
            Vector3 v2 (4.0f, 5.0f, 6.0f);
            Vector3 v3 (7.0f, 8.0f, 9.0f);
            Matrix3 m (v, v2, v3);
            THEN ("The matrix is initialized to [1.0f 2.0f 3.0f 4.0f 5.0f 6.0f 7.0f 8.0f 9.0f]") {
    REQUIRE (1.0f == m.COL1ROW1);
    REQUIRE (2.0f == m.COL1ROW2);
    REQUIRE (3.0f == m.COL1ROW3);
    REQUIRE (4.0f == m.COL2ROW1);
    REQUIRE (5.0f == m.COL2ROW2);
    REQUIRE (6.0f == m.COL2ROW3);
    REQUIRE (7.0f == m.COL3ROW1);
    REQUIRE (8.0f == m.COL3ROW2);
    REQUIRE (9.0f == m.COL3ROW3);
            }
        }

        WHEN ("I pass 2 vectors declared to <4.0f, 2.0f, 1.0f> and <2.0f, 5.0f, 2.0f> and DO NOT orthonormalize the matrix.") {
            Vector3 v (4.0f, 2.0f, 1.0f);
            Vector3 v2 (2.0f, 5.0f, 2.0f);
            Matrix3 m (v, v2, false);
            THEN ("The matrix is initialized to [4.0f, 2.0f, 1.0f, 2.0f, 5.0f, 2.0f, -1.0f, -6.0f, 16.0f], where the back vector is the cross of the right and up vector") {
    REQUIRE (4.0f == Approx (m.COL1ROW1));
    REQUIRE (2.0f == Approx (m.COL1ROW2));
    REQUIRE (1.0f == Approx (m.COL1ROW3));
    REQUIRE (2.0f == Approx (m.COL2ROW1));
    REQUIRE (5.0f == Approx (m.COL2ROW2));
    REQUIRE (2.0f == Approx (m.COL2ROW3));
    REQUIRE (-1.0f == Approx (m.COL3ROW1));
    REQUIRE (-6.0f == Approx (m.COL3ROW2));
    REQUIRE (16.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I pass 2 vectors declared to <4.0f, 2.0f, 1.0f> and <2.0f, 5.0f, 2.0f> and DOES orthonormalize the matrix.") {
            Vector3 v (4.0f, 2.0f, 1.0f);
            Vector3 v2 (2.0f, 5.0f, 2.0f);
            /// Back Vector (-1, -6, 16)
            Matrix3 m (v, v2, true);
            Vector3 orthoBack (-1.0f/sqrt (293.0f), -6.0f/sqrt (293.0f), 16.0f/sqrt (293.0f));
            Vector3 orthoRight (92.0f/sqrt (9669.0f), -34.0f/sqrt (9669.0f), -7.0f/sqrt (9669.0f));
            Vector3 orthoUp = orthoBack.cross (orthoRight);
            orthoUp.normalize ();
            THEN ("The matrix is initialized to [4.0f, 2.0f, 1.0f, 2.0f, 5.0f, 2.0f, 0.0f, 0.0f, 0.0f], where the back vector is the cross of the right and up vector") {
    REQUIRE (orthoRight == m.getRight());
    REQUIRE (orthoUp == m.getUp ());
    REQUIRE (orthoBack == m.getBack ());
            }
        }
    }
    /// Source for matrix entries:
    /// Used emathhelp.net orthonomalize calculator using the Gram-Schmidt process
}

/// SET TO IDENTITY/ZERO TESTS
SCENARIO ("setToIdentity/Zero Tests", "[Matrix3][A05]") {
    GIVEN ("A matrixinitialized to [2.0f, 1.0f, 3.0f, 4.0f, 6.0f, 5.0f, 8.0f, 9.0f, 7.0f]") {
        Matrix3 m (2.0f, 1.0f, 3.0f, 4.0f, 6.0f, 5.0f, 8.0f, 9.0f, 7.0f);
        WHEN ("I call setToIdentity on m") {
            m.setToIdentity ();
            THEN ("Matrix m is the identity matrix") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I call setToZero on m") {
            m.setToZero();
            THEN ("Matrix m is a matrix of all zeroes") {
    REQUIRE (0.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (0.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (0.0f == Approx (m.COL3ROW3)); 
            }
        }
    }
}

/// DATA TESTS
SCENARIO ("Data tests", "[Matrix3][A05]") {
    GIVEN ("A matrix that is initialized to the identity matrix (default constructor)") {
        Matrix3 m;
        WHEN ("I call data on the matrix") {
            float* point = m.data();
            THEN ("The point is equal to Matrix entry (1,1)") {
    REQUIRE (1.0f == *point);
            }

            point += 1;
            THEN ("I add 1 to the point and point is now equal to (1,2)") {
    REQUIRE (0.0f == *point);
            }
        }

        WHEN ("I call const data on the matrix") {
            const float* point = m.data();
            THEN ("The point is equal to Matrix entry (1,1)") {
    REQUIRE (1.0f == *point);
            }

            point +=1;
            THEN ("The point is equal to Matrix entry (1,2)") {
    REQUIRE (0.0f == *point);
            }
        }
    }
}

/// GETTER AND SETTER TESTS
SCENARIO ("Getters and Setters", "[Matrix3][A05]") {
    GIVEN ("A matrix set to the identity matrix (default constructor).") {
        Matrix3 m;
        WHEN ("I set the right vector to <3.0f, 2.0f, 1.0f>") {
            Vector3 v (3.0f, 2.0f, 1.0f);
            m.setRight (v);
            THEN ("The Right vector of the matrix is <3.0f, 2.0f, 1.0f>") {
    REQUIRE (v == m.getRight());
            }
        }

        WHEN ("I set the up vector to <6.0f, 5.0f, 4.0f>") {
            Vector3 v (6.0f, 5.0f, 4.0f);
            m.setUp (v);
            THEN ("The Up vector of the matrix is <6.0f, 5.0f, 4.0f>") {
    REQUIRE (v == m.getUp());
            }
        }

        WHEN ("I set the back vector to <9.0f, 8.0f, 7.0f>") {
            Vector3 v (9.0f, 8.0f, 7.0f);
            m.setBack (v);
            THEN ("The Back vector of the matrix is <9.0f, 8.0f, 7.0f>") {
    REQUIRE (v == m.getBack());
            }
        }

        WHEN ("I set the forward vector to <1.0f, 2.0f, 3.0f>") {
            Vector3 v (1.0f, 2.0f, 3.0f);
            m.setForward (v);
            THEN ("The Back vector is now the negated vector v, getForward returns the negated back vector") {
    REQUIRE (v == m.getForward());
            }
        }
    }
}

/// INVERT TESTS
SCENARIO ("Invert Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix defined that is a rotation matrix of 90 degrees across the X axis") {
        Matrix3 m;
        m.setToRotationX (90.0f);
        WHEN ("The matrix is inverted using invertRotation") {
            m.invertRotation ();
            THEN ("The matrix is inverted") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL2ROW2));
    REQUIRE (-sin(DEG2RAD) == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (sin(DEG2RAD) == Approx (m.COL3ROW2));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL3ROW3));
            }
        }
    }  

    GIVEN ("A matrix defined as [2.0f, 2.0f, 3.0f, 3.0f, 5.0f, 3.0f, 2.0f, 4.0f, 4.0f]") {
        Matrix3 m (2.0f, 2.0f, 3.0f, 3.0f, 5.0f, 3.0f, 2.0f, 4.0f, 4.0f);
        WHEN ("The matrix is inverted using invert") {
            m.invert ();
            THEN ("The matrix is inverted") {
    REQUIRE (4.0/5.0 == Approx (m.COL1ROW1));
    REQUIRE (2.0/5.0 == Approx (m.COL1ROW2));
    REQUIRE (-9.0/10.0 == Approx (m.COL1ROW3));
    REQUIRE (-3.0/5.0 == Approx (m.COL2ROW1));
    REQUIRE (1.0/5.0 == Approx (m.COL2ROW2));
    REQUIRE (3.0/10.0 == Approx (m.COL2ROW3));
    REQUIRE (1.0/5.0 == Approx (m.COL3ROW1));
    REQUIRE (-2.0/5.0 == Approx (m.COL3ROW2));
    REQUIRE (2.0/5.0 == Approx (m.COL3ROW3));
            }
        }
    } 
}

/// DETERMINANT TEST
SCENARIO ("Determinant Test", "[Matrix3][A05]") {
    GIVEN ("The identity matrix") {
        Matrix3 m;
        WHEN ("I find the determinant of the matrix") {
            float det = m.determinant();
            THEN ("The determinant is set to the variable det") {
    REQUIRE (1.0f == det); 
    /// Source: Used symbolab determinant calculator
            }
        }
    }
}

/// Transpose Tests
SCENARIO ("Transpose Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix initialized to [1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9]") {
        Matrix3 m (1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f);
        WHEN ("The call the transpose function on the matrix") {
            m.transpose ();
            THEN ("The matrix m is now a transposed matrix of the original") {
    REQUIRE (1.1f == Approx (m.COL1ROW1));
    REQUIRE (1.4f == Approx (m.COL1ROW2));
    REQUIRE (1.7f == Approx (m.COL1ROW3));
    REQUIRE (1.2f == Approx (m.COL2ROW1));
    REQUIRE (1.5f == Approx (m.COL2ROW2));
    REQUIRE (1.8f == Approx (m.COL2ROW3));
    REQUIRE (1.3f == Approx (m.COL3ROW1));
    REQUIRE (1.6f == Approx (m.COL3ROW2));
    REQUIRE (1.9f == Approx (m.COL3ROW3));
            }
        }
    }
}

/// ORTHONORMALIZE TESTS
SCENARIO ("Orthonormalize Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix initialized to [4.0f, 2.0f, 1.0f, 2.0f, 5.0f, 2.0f, -1.0f, -6.0f, 16.0f") {
        Vector3 right (4.0f, 2.0f, 1.0f);
        Vector3 up (2.0f, 5.0f, 2.0f);
        Vector3 back (-1.0f, -6.0f, 16.0f);
        Matrix3 m (right, up, back);
        WHEN ("I call the orthonormalize function on the matrix.") {
            m.orthonormalize ();
            Vector3 orthoBack (-1.0f/sqrt (293.0f), -6.0f/sqrt (293.0f), 16.0f/sqrt (293.0f));
            Vector3 orthoRight (92.0f/sqrt (9669.0f), -34.0f/sqrt (9669.0f), -7.0f/sqrt (9669.0f));
            Vector3 orthoUp = orthoBack.cross (orthoRight);
            orthoUp.normalize ();
            THEN ("The matrix is initialized to [4.0f, 2.0f, 1.0f, 2.0f, 5.0f, 2.0f, 0.0f, 0.0f, 0.0f], where the back vector is the cross of the right and up vector") {
    REQUIRE (orthoRight == m.getRight());
    REQUIRE (orthoUp == m.getUp ());
    REQUIRE (orthoBack == m.getBack ());
            }
        }
    }
}

/// SCALE TESTS
SCENARIO ("Scale Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix intialized to all 1's") {
        Matrix3 m (1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        WHEN ("I scale the matrix by 2") {
            m.setToScale (2.0f);
            THEN ("The matrix is uniformely scaled by two.") {
    REQUIRE (2.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (2.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (2.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I scale the X by 2, the Y by 3, and the Z by 4") {
            m.setToScale(2.0f, 3.0f, 4.0f);
            THEN ("The matrix is non-uniformely scaled by 2 for x, 3 for y, and 4 for z") {
    REQUIRE (2.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (3.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (4.0f == Approx (m.COL3ROW3));
            }
        }
    }
}

/// SHEAR TESTS
SCENARIO ("Shear Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix initialized to all 1's") {
        Matrix3 m (1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        WHEN ("I shear the X values in mby a factor of 2.0 for Y and 3.0 for X") {
            m.setToShearXByYz (2.0f, 3.0f);
            THEN ("m is now the matrix that shears X by 2.0 and 3.0") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3)); 
    REQUIRE (2.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (3.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I shear the Y values in m by a factor of 2.0 for X and 3.0 for Z") {
            m.setToShearYByXz (2.0f, 3.0f);
            THEN ("m is now the matrix that shears Y by 2.0 for X and 3.0 for Z") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (2.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (3.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I shear the Z values in m by a factor of 2.0 for X and 3.0 for Y") {
            m.setToShearZByXy (2.0f, 3.0f);
            THEN ("m is now the matrix that shears Z by 2.0 for X and 3.0 for Y") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (2.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (3.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));        
            }
        }
    }
}

/// SETTOROTATION TESTS
SCENARIO ("setRotation Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix initialized to the default constructor") {
        Matrix3 m; 
        WHEN ("I rotate matrix m by 90 degrees around the x axis using the rotation function") {
            m.setToRotationX (90.0f);
            THEN ("The matrix m is now a rotation matrix of 90 degrees around the x axis") {
    REQUIRE (1.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL2ROW2));
    REQUIRE (sin(DEG2RAD) == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (-sin(DEG2RAD) == Approx (m.COL3ROW2));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I rotate matrix m by 90 degrees around the y axis") {
            m.setToRotationY (90.0f);
            THEN ("The matrix m is now a rotation matrix of 90 degrees around the y axis") {
    REQUIRE (cos(DEG2RAD) == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (-sin (DEG2RAD) == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (1.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (sin(DEG2RAD) == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL3ROW3));
            }
        }

        WHEN ("I rotate matrix m by 90 degrees around the z axis") {
            m.setToRotationZ (90.0f);
            THEN ("The matrix m is now a rotation matrix of 90 degrees around the z axis") {
    REQUIRE (cos(DEG2RAD) == Approx (m.COL1ROW1));
    REQUIRE (sin(DEG2RAD) == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (-sin(DEG2RAD) == Approx (m.COL2ROW1));
    REQUIRE (cos(DEG2RAD) == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (1.0f == Approx (m.COL3ROW3));   
            }
        }

        WHEN ("I rotate matrix m by 90 degrees around a vector v (2/sqrt(21), -4.0/sqrt(21), 1.0/sqrt(21)). This is the normalized vector of (2, -4, 1)") {
            const Vector3 v (2.0f/sqrt(21.0f), -4.0f/sqrt(21.0f), 1.0f/sqrt(21.0f));
            m.setFromAngleAxis (90.0f, v);
            THEN ("The matrix m is now a rotation matrix of 90 degrees around the normalized vector v") {
    REQUIRE ((pow(v.m_x, 2.0f)) + cos(DEG2RAD) * (1.0f - (pow(v.m_x, 2.0f))) == Approx (m.COL1ROW1));
    REQUIRE ((v.m_x * v.m_y * (1.0f - cos(DEG2RAD))) + v.m_z * sin (DEG2RAD) == Approx (m.COL1ROW2));
    REQUIRE ((v.m_x * v.m_z * (1.0f - cos(DEG2RAD))) - v.m_y * sin (DEG2RAD) == Approx (m.COL1ROW3));
    REQUIRE ((v.m_x * v.m_y * (1.0f - cos(DEG2RAD))) - v.m_z * sin (DEG2RAD) == Approx (m.COL2ROW1));
    REQUIRE ((pow(v.m_y, 2.0f)) + cos(DEG2RAD) * (1.0f - (pow(v.m_y, 2.0f))) == Approx (m.COL2ROW2));
    REQUIRE ((v.m_y * v.m_z * (1.0f - cos(DEG2RAD))) + v.m_x * sin (DEG2RAD) == Approx (m.COL2ROW3));
    REQUIRE ((v.m_x * v.m_z * (1.0f - cos(DEG2RAD))) + v.m_y * sin (DEG2RAD) == Approx (m.COL3ROW1));
    REQUIRE ((v.m_y * v.m_z * (1.0f - cos(DEG2RAD))) - v.m_x * sin (DEG2RAD) == Approx (m.COL3ROW2));
    REQUIRE ((pow(v.m_z, 2.0f)) + cos(DEG2RAD) * (1.0f - (pow(v.m_z, 2.0f))) == Approx (m.COL3ROW3));
            }
        }
    }
}

/// NEGATE TESTS
SCENARIO ("Negate tests", "[Matrix3][A05]") {
    GIVEN ("A matrix of all 1's") {
        float x = 1.0;
        Matrix3 m (x, x, x, x, x, x, x, x, x);
        WHEN ("I call the negate function on the matrix") {
            m.negate ();
            THEN ("The matrix is negated") {
    REQUIRE (-1.0f == Approx (m.COL1ROW1));
    REQUIRE (-1.0f == Approx (m.COL1ROW2));
    REQUIRE (-1.0f == Approx (m.COL1ROW3));
    REQUIRE (-1.0f == Approx (m.COL2ROW1));
    REQUIRE (-1.0f == Approx (m.COL2ROW2));
    REQUIRE (-1.0f == Approx (m.COL2ROW3));
    REQUIRE (-1.0f == Approx (m.COL3ROW1));
    REQUIRE (-1.0f == Approx (m.COL3ROW2));
    REQUIRE (-1.0f == Approx (m.COL3ROW3));
            }
        }
    }
}

/// TRANSFORM TESTS
SCENARIO ("Transform Tests", "[Matrix3][A05]") {
    GIVEN ("The identity matrix and a vector [2.0f, 4.0f, 5.0f]") {
        Matrix3 m;
        const Vector3 v (2.0f, 4.0f, 5.0f);
        WHEN ("I transform matrix m by vector v") {
            Vector3 w = m.transform (v);
            THEN ("Vector w is now the result of m * v") {
    REQUIRE (2.0f == Approx (w.m_x));
    REQUIRE (4.0f == Approx (w.m_y));
    REQUIRE (5.0f == Approx (w.m_z));
            }
        }
    }
}

/// +/+= OPERATOR TESTS
SCENARIO ("+ and += Operator Tests", "[Matrix3][A05]") {
    GIVEN ("Two identity matrices") {
        Matrix3 m;
        Matrix3 m2;
        WHEN ("I add the two matrices together using '+='") {
            m += m2;
            THEN ("Matrix m is the sum of m and m2") {
    REQUIRE (2.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (2.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (2.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("m2 is summed with another identity matrix, m3, using the '+' operator") {
            Matrix3 m3;
            Matrix3 m4 = m2 + m3;
            THEN ("Matrix m4 is created by the addition of m2 and m3 AND is equal to m += m2") {
    REQUIRE (2.0f == Approx (m4.COL1ROW1));
    REQUIRE (0.0f == Approx (m4.COL1ROW2));
    REQUIRE (0.0f == Approx (m4.COL1ROW3));
    REQUIRE (0.0f == Approx (m4.COL2ROW1));
    REQUIRE (2.0f == Approx (m4.COL2ROW2));
    REQUIRE (0.0f == Approx (m4.COL2ROW3));
    REQUIRE (0.0f == Approx (m4.COL3ROW1));
    REQUIRE (0.0f == Approx (m4.COL3ROW2));
    REQUIRE (2.0f == Approx (m4.COL3ROW3));
    m += m2;
    REQUIRE (m == m4);
            }
        }
    }
}

/// -/-= OPERATOR TESTS
SCENARIO ("- and -= Operator Tests.", "[Matrix3][A05]") {
    GIVEN ("Two identity matrices") {
        Matrix3 m;
        Matrix3 m2;
        WHEN ("I subtract the two matrices together using '-='") {
            m -= m2;
            THEN ("Matrix m is the sum of m and m2") {
    REQUIRE (0.0f == Approx (m.COL1ROW1));
    REQUIRE (0.0f == Approx (m.COL1ROW2));
    REQUIRE (0.0f == Approx (m.COL1ROW3));
    REQUIRE (0.0f == Approx (m.COL2ROW1));
    REQUIRE (0.0f == Approx (m.COL2ROW2));
    REQUIRE (0.0f == Approx (m.COL2ROW3));
    REQUIRE (0.0f == Approx (m.COL3ROW1));
    REQUIRE (0.0f == Approx (m.COL3ROW2));
    REQUIRE (0.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("m2 is summed with another identity matrix, m3, using the '-' operator") {
            Matrix3 m3;
            Matrix3 m4 = m2 - m3;
            THEN ("Matrix m4 is created by the addition of m2 and m3 AND is equal to m += m2") {
    REQUIRE (0.0f == Approx (m4.COL1ROW1));
    REQUIRE (0.0f == Approx (m4.COL1ROW2));
    REQUIRE (0.0f == Approx (m4.COL1ROW3));
    REQUIRE (0.0f == Approx (m4.COL2ROW1));
    REQUIRE (0.0f == Approx (m4.COL2ROW2));
    REQUIRE (0.0f == Approx (m4.COL2ROW3));
    REQUIRE (0.0f == Approx (m4.COL3ROW1));
    REQUIRE (0.0f == Approx (m4.COL3ROW2));
    REQUIRE (0.0f == Approx (m4.COL3ROW3));
    m -= m2;
    REQUIRE (m == m4);
            }
        }
    }
}

/// */*= OPERATOR TESTS
SCENARIO ("* and *= Operator Tests", "[Matrix3][A05]") {
    GIVEN ("Two matrices initialized to all 2's") {
        float a = 2.0;
        Matrix3 m (a, a, a, a, a, a, a, a, a);
        Matrix3 m2 (a, a, a, a, a, a, a, a, a);
        WHEN ("I multiply the two matrices together using '*='") {
            m *= m2;
            THEN ("Matrix m is the sum of m and m2") {
    REQUIRE (12.0f == Approx (m.COL1ROW1));
    REQUIRE (12.0f == Approx (m.COL1ROW2));
    REQUIRE (12.0f == Approx (m.COL1ROW3));
    REQUIRE (12.0f == Approx (m.COL2ROW1));
    REQUIRE (12.0f == Approx (m.COL2ROW2));
    REQUIRE (12.0f == Approx (m.COL2ROW3));
    REQUIRE (12.0f == Approx (m.COL3ROW1));
    REQUIRE (12.0f == Approx (m.COL3ROW2));
    REQUIRE (12.0f == Approx (m.COL3ROW3));
            }
        }

        WHEN ("m2 is summed with another 2's matrix, m3, using the '*' operator") {
            Matrix3 m3 (2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
            Matrix3 m4 = m2 * m3;
            THEN ("Matrix m4 is created by the addition of m2 and m3 AND is equal to m += m2") {
    REQUIRE (12.0f == Approx (m4.COL1ROW1));
    REQUIRE (12.0f == Approx (m4.COL1ROW2));
    REQUIRE (12.0f == Approx (m4.COL1ROW3));
    REQUIRE (12.0f == Approx (m4.COL2ROW1));
    REQUIRE (12.0f == Approx (m4.COL2ROW2));
    REQUIRE (12.0f == Approx (m4.COL2ROW3));
    REQUIRE (12.0f == Approx (m4.COL3ROW1));
    REQUIRE (12.0f == Approx (m4.COL3ROW2));
    REQUIRE (12.0f == Approx (m4.COL3ROW3));
    m *= m2;
    REQUIRE (m == m4);
            }
        }

        WHEN ("m is multiplied by the scalar 2.0 using '*='") {
            m *= 2.0f;
            THEN ("Matrix m is the product of m * 2.0") {
    REQUIRE (4.0f == Approx (m.COL1ROW1));
    REQUIRE (4.0f == Approx (m.COL1ROW2));
    REQUIRE (4.0f == Approx (m.COL1ROW3));
    REQUIRE (4.0f == Approx (m.COL2ROW1));
    REQUIRE (4.0f == Approx (m.COL2ROW2));
    REQUIRE (4.0f == Approx (m.COL2ROW3));
    REQUIRE (4.0f == Approx (m.COL3ROW1));
    REQUIRE (4.0f == Approx (m.COL3ROW2));
    REQUIRE (4.0f == Approx (m.COL3ROW3));  
            }
        }

        WHEN ("m2 is multiplied by the scalar 2.0 using '*'") {
            Matrix3 m3 = m2 * 2.0f;
            THEN ("Matrix m3 is the product of m2 * 2.0") {
    REQUIRE (4.0f == Approx (m3.COL1ROW1));
    REQUIRE (4.0f == Approx (m3.COL1ROW2));
    REQUIRE (4.0f == Approx (m3.COL1ROW3));
    REQUIRE (4.0f == Approx (m3.COL2ROW1));
    REQUIRE (4.0f == Approx (m3.COL2ROW2));
    REQUIRE (4.0f == Approx (m3.COL2ROW3));
    REQUIRE (4.0f == Approx (m3.COL3ROW1));
    REQUIRE (4.0f == Approx (m3.COL3ROW2));
    REQUIRE (4.0f == Approx (m3.COL3ROW3));            
            }
        }

        WHEN ("m2 is multiplied by the scalar 2.0 using '*'") {
            Matrix3 m3 = 2.0f * m2;
            THEN ("Matrix m3 is the product of m2 * 2.0") {
    REQUIRE (4.0f == Approx (m3.COL1ROW1));
    REQUIRE (4.0f == Approx (m3.COL1ROW2));
    REQUIRE (4.0f == Approx (m3.COL1ROW3));
    REQUIRE (4.0f == Approx (m3.COL2ROW1));
    REQUIRE (4.0f == Approx (m3.COL2ROW2));
    REQUIRE (4.0f == Approx (m3.COL2ROW3));
    REQUIRE (4.0f == Approx (m3.COL3ROW1));
    REQUIRE (4.0f == Approx (m3.COL3ROW2));
    REQUIRE (4.0f == Approx (m3.COL3ROW3)); 
            }
        }

        WHEN ("m2 is multiplied by the vector v [2.0, 2.0, 2.0] using '*'") {
            Vector3 v (2.0f, 2.0f, 2.0f);
            Vector3 v2 = m2 * v;
            THEN ("Vector v2 is the product of m2 * v") {
    REQUIRE (12.0f == Approx (v2.m_x));
    REQUIRE (12.0f == Approx (v2.m_y));
    REQUIRE (12.0f == Approx (v2.m_z));
            }
        }
    }
}

/// << OUTPUT OPERATOR TESTS
SCENARIO ("<< Output operator tests.", "[Matrix3][A05]") {
    GIVEN ("The identity matrix") {
        Matrix3 m;
        WHEN ("I use the << operator on m") {
            std::stringstream out;
            std::ostream& r = out << m;
            THEN ("It should have included each component of the matrix in correct order with a precision of two and a field width of 10") {
    REQUIRE ("      1.00      0.00      0.00\n      0.00      1.00      0.00\n      0.00      0.00      1.00\n" == out.str ());
            }
            THEN ("The original stream should have returned") {
    REQUIRE (&out == &r);
            }
        }
    }
}

/// == OPERATOR TESTS
SCENARIO ("== Operator Tests", "[Matrix3][A05]") {
    GIVEN ("A matrix initialized to the identity matrix") {
        Matrix3 m;
        WHEN ("I compare with a matrix intialized to [1.00000001, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]") {
            Matrix3 m2 (1.00000001f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
            bool equal = m == m2;
            THEN ("They should be equal") {
    REQUIRE (true == equal);
            }
        }
        WHEN ("I compare with a matrix initialized to [1.001, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]") {
            Matrix3 m2 (1.001f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
            bool equal = m == m2;
            THEN ("They should not be equal") {
    REQUIRE (false == equal);
            }
        }
    }
}