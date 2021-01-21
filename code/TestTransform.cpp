/// \file TestTransform.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Ethan Gingrich
/// \version A05

#include <sstream>
#include <string>
#include <glm/gtc/epsilon.hpp>

#include "Transform.hpp"

#define CATCH_CONFIG_MAIN
#define INIT Transform t = init ();
#include <catch.hpp>

/*
 *  Easy Initialization of a Transform cuz me lazy :)
 *  This also tests set/getOrientation
 *  
 *  Rotate Matrix is set to --- Position Matrix is set to
 *    [1.0    4.0    7.0]                [2.0]
 *    [2.0    5.0    8.0]                [4.0]
 *    [3.0    6.0    9.0]                [6.0]
 * 
 *        Overall Tranformation Matrix looks like so
 *                [1.0    4.0    7.0    2.0]
 *                [2.0    5.0    8.0    4.0]
 *                [3.0    6.0    9.0    6.0]
 *                [0.0    0.0    0.0    1.0]
 */
Transform
init ()
{
    Matrix3 r (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Vector3 p (2.0f, 4.0f, 6.0f);

    Transform t;
    t.setOrientation (r);
    t.setPosition (p);

    return t;
}

/// CONSTRUCTOR TEST
SCENARIO ("Transform constructor", "[Transform][A06]") {
    GIVEN ("Nothing") {
        WHEN ("I use the constructor") {
            Transform t;
            THEN ("The Identity Transformation Matrix is created") {
            Matrix3 r;
            Vector3 p;
    REQUIRE (t.getOrientation () == r);
    REQUIRE (t.getPosition () == p);
            }
        }
    }
}

                        ///SET/GET TESTS///

/// SET/GETORIENTATION TESTS
SCENARIO ("set/getOrientation", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        WHEN ("I get the orientation matrix") {
            Matrix3 m (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
            THEN ("Matrix m is the orientation matrix of t") {
    REQUIRE (m == t.getOrientation ());
            }
        }

        WHEN ("I set the orientation matrix to [9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f]") {
            Matrix3 m (9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
            t.setOrientation (m);
            THEN ("The orientation matrix of t is set to m") {
    REQUIRE (m == t.getOrientation ());
            }
        }

        WHEN ("I set the orientation matrix using vectors [1.0f, 2.0f, 3.0f], [4.0f, 5.0f, 6.0f], [7.0f, 8.0f, 9.0f]") {
            Vector3 v1 (1.0f, 2.0f, 3.0f);
            Vector3 v2 (4.0f, 5.0f, 6.0f);
            Vector3 v3 (7.0f, 8.0f, 9.0f);
            Matrix3 m (v1, v2, v3);
            t.setOrientation (v1, v2, v3);
            THEN ("The orientation matrix of t is set to the three vectors") {
    REQUIRE (m == t.getOrientation ());
            }
        }
    }
}

/// GETTRANSFORM TESTS
SCENARIO ("getTransform", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT 
        /*WHEN ("I get the transform matrix") {
            glm::mat4 tr1 = t.getTransform ();
            glm::mat4 tr2 (1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 5.0f, 6.0f, 0.0f, 7.0f, 8.0f, 9.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
            THEN ("A mat4 object tr is made out of t") {
                bool equal = glm::epsilonEqual (tr1, tr2, 0.00001f);
    REQUIRE ();
            }
        }*/

        WHEN ("I get the transform matrix and pass in an array") {
            float array[16];
            t.getTransform (array);
            THEN ("The array is filled with the contents of the transform matrix, in column-major order") {
                float key[16] = {1.0f, 4.0f, 7.0f, 0.0f, 2.0f, 5.0f, 8.0f, 0.0f, 3.0f, 6.0f, 9.0f, 0.0f, 2.0f, 4.0f, 6.0f, 1.0f};
    REQUIRE (*key == *array);
            }
        }
    }
}

/// SET/GETPOSITION TESTS
SCENARIO ("set/getPosition Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT 
        WHEN ("I get the position vector of t") {
            Vector3 p = t.getPosition ();
            THEN ("p is the position matrix of t") {
                Vector3 key (2.0f, 4.0f, 6.0f);
    REQUIRE (p == key);
            }
        }

        WHEN ("I set the position vector of t to [1.0f, 1.0f, 1.0f]") {
            Vector3 p (1.0f, 1.0f, 1.0f);
            t.setPosition (p);
            THEN ("The position vector of t equals p") {
    REQUIRE (p == t.getPosition ());
            }
        }

        WHEN ("I set the position vector using floats 1.0f, 2.0f, 3.0f") {
            t.setPosition (1.0f, 2.0f, 3.0f);
            THEN ("The position vector is set to [1.0f, 2.0f, 3.0f]") {
                Vector3 v (1.0f, 2.0f, 3.0f);
    REQUIRE (v == t.getPosition ());
            }
        }
    }
}

/// GETRIGHT/UP/BACK TESTS
SCENARIO ("getRight/getUp/getBack Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        WHEN ("I get the right vector of t") {
            Vector3 r = t.getRight ();
            THEN ("r is equal to the right vector of t") {
                Vector3 key (1.0f, 2.0f, 3.0f);
    REQUIRE (r == key);
            }
        }

        WHEN ("I get the up vector of t") {
            Vector3 u = t.getUp ();
            THEN ("u is equal to the up vector of t") {
                Vector3 key (4.0f, 5.0f, 6.0f);
    REQUIRE (u == key);
            }
        }

        WHEN ("I get the back vector of t") {
            Vector3 b = t.getBack ();
            THEN ("b is equal to the back vector of t") {
                Vector3 key (7.0f, 8.0f, 9.0f);
    REQUIRE (b == key);
            }
        }
    }
}
///                                                                                     ///

/// ORTHONORMALIZE TEST
SCENARIO ("Orthonormalize test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT 
        Matrix3 key = t.getOrientation ();
        WHEN ("I call orthonormalize on t") {
            t.orthonormalize ();
            THEN ("t's orientation matrix is orthonormalized") {
                key.orthonormalize ();
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// RESET TEST
SCENARIO ("Reset Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 identity;
        WHEN ("I make changes to the transform") {
            Vector3 v (7.0f, 7.0f, 7.0f);
            t.setPosition (6.0f, 6.0f, 6.0f);
            t.setOrientation (v, v, v);
            THEN ("I reset the matrix") {
                t.reset ();
    REQUIRE (t.getOrientation () == identity);
    REQUIRE (t.getPosition () == Vector3 (0.0f, 0.0f, 0.0f));
            }
        }
    }
}

                        ///MOVE TESTS///

const float DISTANCE = 4.0;
/// MOVERIGHT TEST
SCENARIO ("moveRight Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Vector3 key = t.getPosition ();
        Matrix3 og = t.getOrientation ();
        WHEN ("I move to the right by 4") {
            t.moveRight (DISTANCE);
            THEN ("The transform t has been moved to the right by 4") {
                key += (t.getRight () * DISTANCE);
    REQUIRE (t.getPosition () == key);
    REQUIRE (t.getOrientation () == og);
            }
        }
    }
}

/// MOVEUP TEST
SCENARIO ("moveUp Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Vector3 key = t.getPosition ();
        Matrix3 og = t.getOrientation ();
        WHEN ("I move up by 4") {
            t.moveUp (DISTANCE);
            THEN ("The transform t has been moved up by 4") {
                key += (t.getUp () * DISTANCE);
    REQUIRE (t.getPosition () == key);
    REQUIRE (t.getOrientation () == og);
            }
        }
    }
}

/// MOVEBACK TEST
SCENARIO ("moveBac Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Vector3 key = t.getPosition ();
        Matrix3 og = t.getOrientation ();
        WHEN ("I move back by 4") {
            t.moveBack (DISTANCE);
            THEN ("The transform t has been moved back by 4") {
                key += (t.getBack () * DISTANCE);
    REQUIRE (t.getPosition () == key);
    REQUIRE (t.getOrientation () == og);
            }
        }
    }
}

/// MOVELOCAL TEST
SCENARIO ("moveLocal Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Vector3 key = t.getPosition ();
        Matrix3 og = t.getOrientation ();
        WHEN ("I move in the direction defined as [5.0, 5.0, 5.0] by 4") {
            t.moveLocal (DISTANCE, Vector3 (5.0f, 5.0f, 5.0f));
            THEN ("The transform t has been moved by 4 in the local direction") {
                Vector3 dir (5.0f, 5.0f, 5.0f);
                key += (DISTANCE * dir);
    REQUIRE (t.getPosition () == key);
    REQUIRE (t.getOrientation () == og);
            }
        }
    }
}

/// MOVEWORLD TEST
SCENARIO ("moveWorld Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Vector3 key = t.getPosition ();
        Matrix3 og = t.getOrientation ();
        WHEN ("I move the transform 4 based on the world direction [5.0, 5.0, 5.0]") {
            t.moveWorld (DISTANCE, Vector3 (5.0f, 5.0f, 5.0f));
            THEN ("t has been moved in the direction defined as [5.0f, 5.0f, 5.0f] by a distance of 4") { 
                Vector3 dir (5.0f, 5.0f, 5.0f);
                dir.normalize ();
                key += (dir * DISTANCE);
    REQUIRE (t.getPosition () == key);
    REQUIRE (t.getOrientation () == og);
            }
        }
    }
}
///                                                                                 ///
                      ///ROTATION TESTS///

/// PITCH TESTS
SCENARIO ("Pitch tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I pitch the transform by 90 degrees") {
            t.pitch (90.0f);
            THEN ("The transform has been rotated by 90 degrees about the X axis") {
                Matrix3 pitch;
                pitch.setToRotationX (90.0f);
                key *= pitch;
    /* No need to make a whole new transform when a pitch
       will only change the rotation matrix of t */
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// YAW TEST
SCENARIO ("Yaw Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I yaw the transform by 90 degrees") {
            t.yaw (90.0f);
            THEN ("The transform has been rotated by 90 degrees about the Y axis") {
                Matrix3 yaw;
                yaw.setToRotationY (90.0f);
                key *= yaw;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// ROLL TEST
SCENARIO ("Roll Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I roll the transform by 90 degrees") {
            t.roll (90.0f);
            THEN ("The transform has been rotated by 90 degrees about the Z axis") {
                Matrix3 roll;
                roll.setToRotationZ (90.0f);
                key *= roll;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// ROTATELOCAL TEST
SCENARIO ("rotateLocal Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I rotate 90 degrees around a local axis [1.0f, 5.0f, 1.0f]") {
            t.rotateLocal (90.0f, Vector3 (1.0f, 5.0f, 1.0f));
            THEN ("The transform has been rotated by 90 degrees around the vector [1.0f, 5.0f, 1.0f]") {
                Matrix3 local;
                local.setFromAngleAxis (90.0f, Vector3 (1.0f, 5.0f, 1.0f));
                key *= local;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// ROTATEWORLD TEST
SCENARIO ("rotateWorld Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I rotate 90 degrees around the unit vector [1.0f, 0.0f, 0.0f]") {
            t.rotateWorld (90.0f, Vector3 (1.0f, 0.0f, 0.0f));
            THEN ("t has been rotated by 90 degrees around the world axis [1.0, 0.0, 0.0]") {
                Matrix3 rot;
                rot.setFromAngleAxis (90.0f, Vector3 (1.0f, 0.0f, 0.0f));
                key = rot * key;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}
///                                                                                ///

                            /// SCALE TESTS ///

const float SCALE = 2;
const float SCALEX = 1.5;
const float SCALEY = 3;
const float SCALEZ = 6;
/// SCALELOCAL TESTS
SCENARIO ("scaleLocal Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I scale t by a factor 2") {
            t.scaleLocal (SCALE);
            THEN ("The transform t is scaled up by a factor of 2") {
                Matrix3 scale;
                scale.setToScale (SCALE);
                key *= scale;
    REQUIRE (t.getOrientation () == key);
            }
        }

        WHEN ("I scale t by a factor of 1.5, 3, and 6 for x, y, and z") {
            t.scaleLocal (SCALEX, SCALEY, SCALEZ);
            THEN ("The transform t is scaled by factors 1.5, 3, and 6 for x, y, and z") {
                Matrix3 scale;
                scale.setToScale (SCALEX, SCALEY, SCALEZ);
                key *= scale;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

/// SCALEWORLD TESTS
SCENARIO ("scaleWorld Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I scale t by a factor of 2 in the world space") {
            t.scaleWorld (SCALE);
            THEN ("The transform t is scaled by a factor of 2 in the world space") {
                Matrix3 scale;
                scale.setToScale (SCALE);
                key = scale * key;
    REQUIRE (t.getOrientation () == key);
            }
        }

        WHEN ("I scale t by a factor of 1.5, 3, and 6 in the world space") {
            t.scaleWorld (SCALEX, SCALEY, SCALEZ);
            THEN ("The transform t is scaled by a factor of 1.5, 3, and 6 in the world space") {
                Matrix3 scale;
                scale.setToScale (SCALEX, SCALEY, SCALEZ);
                key = scale * key;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}

///                                                                                 ///

                            /// SHEAR TESTS ///

const float SHEARX = 2;
const float SHEARY = 3;
const float SHEARZ = 4;
/// SHEARLOCAL TESTS
SCENARIO ("shearLocalX/Y/Z Tests", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 key = t.getOrientation ();
        WHEN ("I shear t's local X by 3 and 4") {
            t.shearLocalXByYz (SHEARY, SHEARZ);
            THEN ("t's local X has been sheared by 3 and 4") {
                Matrix3 shearX;
                shearX.setToShearXByYz (SHEARY, SHEARZ);
                key *= shearX;
    REQUIRE (t.getOrientation () == key);
            }
        }

        WHEN ("I shear t's local Y by 2 and 4") {
            t.shearLocalYByXz (SHEARX, SHEARZ);
            THEN ("t's local Y has been sheared by 2 and 4") {
                Matrix3 shearY;
                shearY.setToShearYByXz (SHEARX, SHEARZ);
                key *= shearY;
    REQUIRE (t.getOrientation () == key);
            }
        }

        WHEN ("I shear t's local Z by 2 and 3") {
            t.shearLocalZByXy (SHEARX, SHEARY);
            THEN ("t's local Z has been sheared by 2 and 3") {
                Matrix3 shearZ;
                shearZ.setToShearZByXy (SHEARX, SHEARY);
                key *= shearZ;
    REQUIRE (t.getOrientation () == key);
            }
        }
    }
}
///                                                                            ///

/// INVERTRT TEST
SCENARIO ("InvertRt Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Matrix3 ori = t.getOrientation ();
        WHEN ("I invert t") {
            t.invertRt ();
            THEN ("t is inverted") {
    REQUIRE (t.getOrientation () == ori);
    REQUIRE (t.getPosition () == Vector3 (-60.0f, -72.0f, -84.0f));
            }
        }
    }
}

/// COMBINE TEST
/// NOTE: This also tests '*' operator as well (combine uses *)
SCENARIO ("Combine Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        Transform t2 = init ();
        WHEN ("I combine t and t2") {
            t.combine (t2);
            THEN ("t is the combination of t and t2") {
    /// Source: symbolab 4x4 matrix multiplication calculator using t and t2
    REQUIRE (t.getRight () == Vector3 (30.0f, 36.0f, 42.0f));
    REQUIRE (t.getUp () == Vector3 (66.0f, 81.0f, 96.0f));
    REQUIRE (t.getBack () == Vector3 (102.0f, 126.0f, 150.0f));
    REQUIRE (t.getPosition () == Vector3 (62.0f, 76.0f, 90.0f));
            }
        }
    }
}

/// OUTPUT OPERATOR TEST
SCENARIO ("Output Operator Test", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        WHEN ("I put transform t into the output stream") {
            std::stringstream out;
            std::ostream& r = out << t;
            THEN ("It should have each component of t outputed in proper order, width, and precision") {

    #define SPACE std::string("      ")
    std::string line1;
    std::string line2;
    std::string line3;
    std::string line4;
    std::string t;
    line1 = SPACE + std::string("1.00") + SPACE + std::string("4.00") + SPACE + std::string("7.00") + SPACE + std::string("2.00\n");
    line2 = SPACE + std::string("2.00") + SPACE + std::string("5.00") + SPACE + std::string("8.00") + SPACE + std::string("4.00\n");
    line3 = SPACE + std::string("3.00") + SPACE + std::string("6.00") + SPACE + std::string("9.00") + SPACE + std::string("6.00\n");
    line4 = SPACE + std::string("0.00") + SPACE + std::string("0.00") + SPACE + std::string("0.00") + SPACE + std::string("1.00\n");
    t = line1 + line2 + line3 + line4;

    REQUIRE (t == out.str());
            }
            THEN ("The original stream should have returned") {
    REQUIRE (&out == &r);
            }
        }
    }
}

SCENARIO ("", "[Transform][A06]") {
    GIVEN ("An initialized transform") {
        INIT
        WHEN ("I compare with a transform whos rotation/scale matrix is [1.0000001f ... ] (rest is the same but one value)") {
            Transform t2 = init ();
            t2.setOrientation (Matrix3 (1.0000001f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,9.0f));
            bool equal = t == t2;
            THEN ("They should be equal") {
    REQUIRE (true == equal);
            }
        }

        WHEN ("I compare with a transform whos position vector is [2.0000001f, ...] (again, one small diff)") {
            Transform t2 = init ();
            t2.setPosition (Vector3 (2.0000001f, 4.0f, 6.0f));
            bool equal = t == t2;
            THEN ("They should be equal") {
    REQUIRE (true == equal);
            }
        }

        WHEN ("I compare with a transform whos rotation/scale matrix is [1.01f, ...]") {
            Transform t2 = init ();
            t2.setOrientation (Matrix3 (1.01f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,9.0f));
            bool equal = t == t2;
            THEN ("They shouldn't be equal") {
    REQUIRE (false == equal);
            }
        }

        WHEN ("I compare with a transform whos rotation/scale matrix is [1.01f, ...]") {
            Transform t2 = init ();
            t2.setPosition (Vector3 (2.01f, 4.0f, 6.0f));
            bool equal = t == t2;
            THEN ("They shouldn't be equal") {
    REQUIRE (false == equal);
            }
        }
    }
}
