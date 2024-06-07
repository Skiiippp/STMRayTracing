/*
 * ray.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include "vec3.h"
#include "sphere.h"
#include "tri.h"

typedef struct ray {
    vec3 origin;
    vec3 dir;
} ray;

vec3 at(ray r, float t);
vec3 trace(ray ray, int maxBounceCount, sphere *spheres, tri *tris);

#endif /* SRC_RAY_H_ */
