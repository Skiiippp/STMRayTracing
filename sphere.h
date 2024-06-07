/*
 * sphere.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_SPHERE_H_
#define SRC_SPHERE_H_

#include "vec3.h"
#include "rtx_material.h"

#define NUM_SPHERES 5

typedef struct sphere {
    vec3 center;
    float radius;
    rtx_material material;
} sphere;

#endif /* SRC_SPHERE_H_ */
