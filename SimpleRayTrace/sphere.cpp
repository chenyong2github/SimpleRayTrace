#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sphere.h"
#include "macros.h"

Sphere* SphereCreate(Vec3 center, 
                     float radius,
                     Color color,
                     Color specularColor,
                     float phongExponent,
                     Color reflectiveColor)
{
    Sphere* sphere = (Sphere*) malloc(sizeof(Sphere));

    sphere->center = center;
    sphere->radius = radius;
    sphere->color = color;
    sphere->specularColor = specularColor;
    sphere->phongExponent = phongExponent;
    sphere->reflectiveColor = reflectiveColor;

    return sphere;
}

RayHit* SphereIntersect(void* surface, Ray* ray)
{
    Sphere* sphere = (Sphere*) surface;
    Vec3 originMinusCenter = Vec3Sub(ray->origin, sphere->center);
    float dotDirection = Vec3Dot(ray->direction, ray->direction);

    // descriminant = (b^2) - a c
    float b = Vec3Dot(ray->direction, originMinusCenter);
    float a = Vec3Dot(ray->direction, ray->direction);
    float c = Vec3Dot(originMinusCenter, originMinusCenter) - 
        sphere->radius * sphere->radius;

    float desc = b * b - a * c;
    if (desc < 0) // No intersection
        return NULL;

    // solve quadratic equation
    float outsideSqrt = Vec3Dot(Vec3Neg(ray->direction), originMinusCenter);
    float t1 = (outsideSqrt - sqrt(desc)) / dotDirection;
    float t2 = (outsideSqrt + sqrt(desc)) / dotDirection;

    // prepare ray hit result
    float smallerT = min(t1, t2);
    Vec3 point = RayEvaluatePoint(ray, smallerT);
    Vec3 normal = 
        Vec3Scale(Vec3Sub(point, sphere->center), 1 / sphere->radius);

    RayHit* hit = RayHitCreate(sphere->color, sphere->specularColor,
                               sphere->phongExponent, sphere->reflectiveColor,
                               point, normal, smallerT);
    return hit;
}

char* SphereToString(Sphere* sphere)
{
	return NULL;
}
