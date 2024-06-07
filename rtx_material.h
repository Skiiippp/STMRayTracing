/*
 * rtx_material.h
 *
 *  Created on: Jun 5, 2024
 *      Author: danie
 */

#ifndef SRC_RTX_MATERIAL_H_
#define SRC_RTX_MATERIAL_H_

#include "vec3.h"

typedef struct rtx_material {
    vec3 color;

    vec3 emissionColor;
    float emissionStrength;

    float smoothness;

    float specularProbability;
    vec3 specularColor;
} rtx_material;

#endif /* SRC_RTX_MATERIAL_H_ */
