/*
 * vec3.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_VEC3_H_
#define SRC_VEC3_H_

#include "main.h"

typedef struct vec3 {
    float x;
    float y;
    float z;
} vec3;

float random_f();
vec3 scale(vec3 v1, float scale);
vec3 add(vec3 v1, vec3 v2);
vec3 subtract(vec3 v1, vec3 v2);
float dot(vec3 v1, vec3 v2);
vec3 cross(vec3 v1, vec3 v2);
vec3 normalize(vec3 v1);
vec3 multiply(vec3 v1, vec3 v2);
vec3 random_in_unit_sphere();
vec3 reflect(vec3 v1, vec3 n);
vec3 lerp(vec3 v1, vec3 v2, float lerpval);

#endif /* SRC_VEC3_H_ */
