/*
 * tri.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_TRI_H_
#define SRC_TRI_H_

#include "vec3.h"
#include "rtx_material.h"

#define NUM_TRIS 8

typedef struct tri {
    vec3 v0;
    vec3 v1;
    vec3 v2;
    rtx_material material;
} tri;

#endif /* SRC_TRI_H_ */
