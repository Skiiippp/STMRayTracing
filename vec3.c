


#include "vec3.h"
#include "math.h"

// Must be 32-bit unsigned
static uint32_t state = 10;

float random_f(){
    state = state * 747796405 + 2891336453;
    uint32_t result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
    result = (result >> 22) ^ result;

    return (float)result / 4294967295.0; // 2^32 - 1
}

vec3 scale(vec3 v1, float scale) {
    vec3 scaled = {
        v1.x * scale,
        v1.y * scale,
        v1.z * scale
    };
    return scaled;
}

vec3 add(vec3 v1, vec3 v2) {
    vec3 sum = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
    return sum;
}

vec3 subtract(vec3 v1, vec3 v2) {
    vec3 difference = {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
    return difference;
}

float dot(vec3 v1, vec3 v2) {
    float dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    return dot;
}

vec3 cross(vec3 v1, vec3 v2) {
    vec3 cross = {
        v1.y * v2.z - v1.z * v2.y, 
        v1.z * v2.x - v1.x * v2.z, 
        v1.x * v2.y - v1.y * v2.x
    };
    return cross;
}

vec3 normalize(vec3 v1) {
    float length = 1.0 / sqrtf(dot(v1, v1));
    return scale(v1, length);
}

vec3 multiply(vec3 v1, vec3 v2) {
    vec3 product = {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z
    };
    return product;
}

vec3 random_in_unit_sphere() {
    vec3 rand3 = {1.0, 1.0, 1.0};

    do {
        rand3.x = random_f() * 2.0 - 1.0;
        rand3.y = random_f() * 2.0 - 1.0;
        rand3.z = random_f() * 2.0 - 1.0;
    } while (dot(rand3, rand3) > 1.0);

    return normalize(rand3);
}

vec3 reflect(vec3 v1, vec3 n) {
    return subtract(v1, scale(n, 2.0*dot(v1,n)));
}

vec3 lerp(vec3 v1, vec3 v2, float lerpval){
    return add(v1, (scale(subtract(v2, v1), lerpval)));
}
