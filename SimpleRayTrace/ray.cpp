#include "pch.h"

#include <stdlib.h>
#include <stdio.h>

#include "ray.h"
#include "scene.h"

Ray* RayCreate(Vec3 origin, Vec3 direction)
{
    Ray* ray = (Ray *)malloc(sizeof(Ray));
    ray->origin = origin;
    ray->direction = Vec3Norm(direction);
    return ray;
}

RayHit* RayCast(Ray* ray, float epsilon)
{
    RayHit* closestHit = NULL;

    for (int index = 0; index < globalScene->objectCount; index++) {
        SceneObject* obj = globalScene->objects[index];
        RayHit* hit = SceneObjectIntersect(obj, ray);

        if (hit == NULL)
            continue;

        if (hit->t < epsilon) {
            free(hit);
            continue;
        }

        if (closestHit == NULL) {
            closestHit = hit;
        }
        else if (hit->t < closestHit->t) {
            free(closestHit);
            closestHit = hit;
        }
        else {
            free(hit);
        }
    }

    return closestHit;
}

Vec3 RayEvaluatePoint(Ray* ray, float t)
{
    return Vec3Add(ray->origin, Vec3Scale(ray->direction, t));
}

char* RayToString(Ray* ray)
{
	return NULL;
}
