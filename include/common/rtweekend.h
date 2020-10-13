#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

//using

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//utility function

inline double degrees_to_radians(double degrees)
{
	return degrees * (pi / 180.0);
}

////random
//inline double random_double()
//{
//	//random range to [0-1]
//	return rand() / RAND_MAX + 1.0;
//}

//new random
inline double random_double()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max)
{
	//random range to [min - max]
	return min + random_double() * (max - min);
}

#include "ray.h"
#include "vec3.h"

#endif