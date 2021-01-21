/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg & Ethan Gingrich
/// \version A04

#include <sstream>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


// Note: I included just a few representative / unusually tricky test cases here.  You should write the others, for every function declared in Vector3.hpp.

/// CONSTRUCTOR TESTS
SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
	REQUIRE (0.0f == Approx (v.m_x));
	REQUIRE (0.0f == Approx (v.m_y));
	REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
	REQUIRE (5.3f == Approx (v.m_x));
	REQUIRE (5.3f == Approx (v.m_y));
	REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
	REQUIRE (3.4f == Approx (v.m_x));
	REQUIRE (9.1f == Approx (v.m_y));
	REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}

/// SET TESTS
SCENARIO ("Vector3 set.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.0f, 2.0f, 3.0f)") {
    Vector3 v (1.0f, 2.0f, 3.0f);
    WHEN ("I pass 4.0 into the set function") {
      v.set (4.0f);
      THEN ("All the values in v should be set to 4.0f") {
        REQUIRE (4.0f == Approx (v.m_x));
        REQUIRE (4.0f == Approx (v.m_y));
        REQUIRE (4.0f == Approx (v.m_z));
      }
    }
  }

  GIVEN ("A vector initialized to (0.1f, 0.2f, 0.3f)") {
    Vector3 v (0.1f, 0.2f, 0.3f);
    WHEN ("I pass 1.0f, 2.0f, 3.0f into the set function") {
      v.set (1.0f, 2.0f, 3.0f);
      THEN ("The values in v should be 1.0f, 2.0f, and 3.0f"){
        REQUIRE (1.0f == Approx (v.m_x));
        REQUIRE (2.0f == Approx (v.m_y));
        REQUIRE (3.0f == Approx (v.m_z));
      }
    }
  }
}


/// NEGATE TESTS
SCENARIO ("Vector negate", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.0f, 1.0f, 1.0f)") {
  Vector3 v (1.0f);
    WHEN ("The vector is negated") {
    v.negate();
      THEN ("The values in v should be (-1.0f, -1.0f, -1.0f)") {
        REQUIRE (-1.0f == Approx (v.m_x));
        REQUIRE (-1.0f == Approx (v.m_y));
        REQUIRE (-1.0f == Approx (v.m_z)); 
      }
    }
  }

  GIVEN ("A vector initialized to (0.0f, 0.0f, 0.0f)") {
  Vector3 v (0.0f);
    WHEN ("The vector is negated") {
    v.negate();
      THEN ("The values in v should be (0.0f, 0.0f, 0.0f)") {
        REQUIRE (0.0f == Approx (v.m_x));
        REQUIRE (0.0f == Approx (v.m_y));
        REQUIRE (0.0f == Approx (v.m_z));
      }
    }
  }

  GIVEN ("A vector initialized to (-1.0f)") {
    Vector3 v (-1.0f);
    WHEN ("The vector is negated") {
      v.negate();
      THEN ("The values in v should be (1.0f, 1.0f, 1.0f") {
        REQUIRE (1.0f == Approx (v.m_x));
        REQUIRE (1.0f == Approx (v.m_y));
        REQUIRE (1.0f == Approx (v.m_z));
      }
    }
  }
}

/// DOT-PRODUCT TESTS
SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
	// Source: typed "dot product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}


/// ANGLE-BETWEEN TESTS
SCENARIO ("Vector3 angle between", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.0f, 0.0f, 0.0f) and (0.0f, 1.0f, 0.0f).") {
    Vector3 v1 (1.0f, 0.0f, 0.0f);
    Vector3 v2 (0.0f, 1.0f, 0.0f);
    WHEN ("I find the angle between the two vectors") {
      float angle = v1.angleBetween(v2);
      THEN ("The angle between them should be 90 degrees or 1/2pi radians.") {
        REQUIRE (M_PI_2 == Approx (angle));
      }
    }
  }

  GIVEN ("Two vectors initialized to (1.0f, 1.0f, 1.0f) and (3.0f, 2.0f, 1.0f)") {
    Vector3 v1 (1.0f, 1.0f, 1.0f);
    Vector3 v2 (3.0f, 2.0f, 1.0f);
    WHEN ("I find the angle between the two vectors") {
      float angle = v1.angleBetween(v2);
      THEN ("The angle between them should be 0.9258") {
        // Source: used symbolab vector angle calculator
        REQUIRE (0.3875966668 == Approx (angle));
      }
    }
  }
}


/// CROSS PRODUCT TESTS
SCENARIO ("Vector cross product", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (2.0f, 3.0f, 10.0f) and (1.0f, 4.0f, 1.0f)") {
    Vector3 v1 (2.0f, 3.0f, 10.0f);
    Vector3 v2 (1.0f, 4.0f, 1.0f);
    WHEN ("I find the cross product between the two vectors") {
      Vector3 cross = v1.cross (v2);
      THEN ("The cross product should be (-37.0f, 8.0f, 5.0f)") {
        // Source: onlinemschool cross product calculator
        REQUIRE (-37.0 == Approx (cross.m_x));
        REQUIRE (8.0 == Approx (cross.m_y));
        REQUIRE (5.0 == Approx (cross.m_z));
      }
    }
  }
}

SCENARIO ("Vector length", "[Vector3][A04]") {
  GIVEN ("A vector intialized to (5.0f, 2.0f, 2.0f") {
    Vector3 v (5.0f, 2.0f, 2.0f);
    WHEN ("I find the length of vector v") {
      float length = v.length ();
      THEN ("The length should be sqrt(33)") {
        REQUIRE (sqrt(33) == Approx (length));
      }
    }
  }
}


/// NORMALIZE TESTS
SCENARIO ("Vector normalize", "[Vector3][A04]") {
  GIVEN ("A vector intialized to (5.0f, 3.0f, 6.0f)") {
    Vector3 v (5.0f, 3.0f, 6.0f);
    WHEN ("The vector is normalized") {
      v.normalize();
      THEN ("The length of v should be 1") {
        REQUIRE (1.0 == Approx (v.length()));
      }
    }
  }

  GIVEN ("A vecter initialized to (1.0f, 0.0f, 0.0f)") {
    Vector3 v (1.0f, 0.0f, 0.0f);
    WHEN ("The vector is normalized and the old length is saved") {
      v.normalize();
      float oldLength = v.length();
      THEN ("The length of v should not have changed") {
        REQUIRE (oldLength == v.length ());
      }
    }
  }
}

/// +/+= OPERATOR TESTS
SCENARIO ("Vector + and +=", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.0f) and (2.0f)") {
    Vector3 v1 (1.0f);
    Vector3 v2 (2.0f);
    WHEN ("The vectors are added using '+='") {
      v1 += v2;
      THEN ("Vector v1 should be (3.0f, 3.0f, 3.0f)") {
        REQUIRE (3.0f == Approx(v1.m_x));
        REQUIRE (3.0f == Approx(v1.m_y));
        REQUIRE (3.0f == Approx(v1.m_z));
      }
    }
    
    /// In order for this test to work, gotta add it again in the scope of this next assertion
    v1 += v2;
    WHEN ("A new vector is initialized to (1.0f) and added with v2 using '+'") {
      Vector3 v3 (1.0f);
      Vector3 v4 = v2 + v3;
      THEN ("Vector v4 should be the addition of v2 and v3 AND be equal to v1 (3.0f, 3.0f, 3.0f") {
        REQUIRE (3.0f == Approx(v4.m_x));
        REQUIRE (3.0f == Approx(v4.m_y));
        REQUIRE (3.0f == Approx(v4.m_z));
        REQUIRE (v1 == v4);
      }
    }
  }
}

/// -/-= OPERATOR TESTS
SCENARIO ("Vector - and -= ", "[Vector3][A04]") {
  GIVEN ("Three Vectors initialized the following way: v1 (1.0f), v2 (2.0f), v3 (1.0f)") {
    Vector3 v1 (1.0f);
    Vector3 v2 (2.0f);
    Vector3 v3 (1.0f);
    WHEN ("v2 is subtracted from v1 using '-='") {
      v1 -= v2;
      THEN ("v1 should equal (-1.0f, -1.0f, -1.0f") {
        REQUIRE (-1.0f == Approx (v1.m_x));
        REQUIRE (-1.0f == Approx (v1.m_y));
        REQUIRE (-1.0f == Approx (v1.m_z));
      }
    }

    /// Set v1 again for next test
    v1 -= v2;
    WHEN ("v2 is subtracted from v3 using '-'") {
      Vector3 v4 = v3 - v2;
      THEN ("v4 should equal (-1.0f, -1.0f, -1.0f AND be equal to v1 (-1.0f, -1.0f, -1.0f") {
        REQUIRE (-1.0f == Approx (v4.m_x)); 
        REQUIRE (-1.0f == Approx (v4.m_y));
        REQUIRE (-1.0f == Approx (v4.m_z));
        REQUIRE (v1 == v4);
      }
    }

    WHEN ("v2 is negated using '-'") {
      v2 = -v2;
      THEN ("v2 should be negated") {
        REQUIRE (-2.0f == Approx (v2.m_x));
        REQUIRE (-2.0f == Approx (v2.m_y));
        REQUIRE (-2.0f == Approx (v2.m_z));
      }
    }
  }
}

/// */*= OPERATOR TESTS
SCENARIO ("Vector * and *=", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to v1(2.0f) and v2(3.0f) and two scalars (2 and 3)") {
    Vector3 v1 (2.0f);
    Vector3 v2 (3.0f);
    const float SCALAR_1 = 2.0;
    const float SCALAR_2 = 3.0;
    WHEN ("v1 is multiplied by scalar 3.0 using '*='") {
      v1 *= SCALAR_2;
      THEN ("v1 should be equal to (6.0f, 6.0f, 6.0f)") {
        REQUIRE (6.0f == Approx (v1.m_x));
        REQUIRE (6.0f == Approx (v1.m_y));
        REQUIRE (6.0f == Approx (v1.m_z));
      }
    }
    /// multiply v1 again for next test
    v1 *= SCALAR_2;

    WHEN ("v2 is multipled by scalar 2.0 using '*', creating vector v3") {
      Vector3 v3 = v2 * SCALAR_1;
      THEN ("v3 should be equal to to (6.0f, 6.0f, 6.0f) AND v1") {
        REQUIRE (6.0f == Approx (v3.m_x));
        REQUIRE (6.0f == Approx (v3.m_y));
        REQUIRE (6.0f == Approx (v3.m_z));
        REQUIRE (v1 == v3);
      }
    }
  }
}

/// '/' AND /= OPERATOR TESTS
SCENARIO ("Vector / and /=", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to v1(12.0f) and v2(18.0f) and two scalars (2 and 3)") {
    Vector3 v1 (12.0f);
    Vector3 v2 (18.0f);
    const float SCALAR_1 = 2.0;
    const float SCALAR_2 = 3.0;
    WHEN ("v1 is divided by scalar 2.0 using '/='") {
      v1 /= SCALAR_1;
      THEN ("v1 should be equal to (6.0f, 6.0f, 6.0f)") {
        REQUIRE (6.0f == Approx (v1.m_x));
        REQUIRE (6.0f == Approx (v1.m_y));
        REQUIRE (6.0f == Approx (v1.m_z));
      }
    }
    /// multiply v1 again for next test
    v1 /= SCALAR_1;

    WHEN ("v2 is divided by scalar 3.0 using '/', creating vector v3") {
      Vector3 v3 = v2 / SCALAR_2;
      THEN ("v3 should be equal to to (6.0f, 6.0f, 6.0f) AND v1") {
        REQUIRE (6.0f == Approx (v3.m_x));
        REQUIRE (6.0f == Approx (v3.m_y));
        REQUIRE (6.0f == Approx (v3.m_z));
        REQUIRE (v1 == v3);
      }
    }
  }
}

// ... lots of missing functions ...


SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	REQUIRE (false == equal);
      }
    }
  }
}
