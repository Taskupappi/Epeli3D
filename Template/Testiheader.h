#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>



// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

// lodePNG
#include "lodepng.h"

// RapidXML
#include "RapidXML\rapidxml.hpp"

//FREETYPE
//#include <ft2build.h>
#include <freetype-2.6.1\include\ft2build.h>
#include FT_FREETYPE_H