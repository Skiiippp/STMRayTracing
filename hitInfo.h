/*
 * hitInfo.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_HITINFO_H_
#define SRC_HITINFO_H_

#include "vec3.h"
#include "rtx_material.h"

typedef struct hitInfo {
    int hit;
    rtx_material material;
    vec3 normal;
    vec3 hitPoint;
    float t;
} hitInfo;

#endif /* SRC_HITINFO_H_ */
