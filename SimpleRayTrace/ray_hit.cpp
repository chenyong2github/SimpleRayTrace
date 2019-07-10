#include "pch.h"
#include <stdlib.h>
#include <stdio.h>

#include "ray_hit.h"

RayHit* RayHitCreate(Color surfaceColor, 
                     Color surfaceSpecularColor,
                     float surfacePhongExponent,
                     Color reflectiveColor,
                     Vec3 point, 
                     Vec3 normal, 
                     float t)
{
    RayHit* hit = (RayHit*) malloc(sizeof(RayHit));

    hit->surfaceColor = surfaceColor;
    hit->surfaceSpecularColor = surfaceSpecularColor;
    hit->surfacePhongExponent = surfacePhongExponent;
    hit->reflectiveColor = reflectiveColor;
    hit->point = point;
    hit->normal = normal;
    hit->t = t;

    return hit;
}

char* RayHitToString(RayHit* rayHit)
{
    return NULL;
}
