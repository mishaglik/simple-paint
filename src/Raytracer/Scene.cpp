#include "Scene.hpp"


Scene::~Scene()
{
    for(RenderObject* obj : objectPool_)
        delete obj;
}


ssize_t Scene::addObject(RenderObject* object)
{
    objectPool_.push_back(object);
    return objectPool_.size() - 1;
}

//Linear search maaaay be optimized. But it's too hard now.
//TODO: Optimize linear search.
const RTObjs::RenderObject* Scene::getObjectOnRay(const Ray& ray) const
{
    size_t crossObj = 0;
    double distance = RTObjs::NoIntersection;

    for(size_t i = 0; i < objectPool_.size(); ++i)
    {
        double curDistance = objectPool_[i]->getIntersection(ray);
        if(!mgm::isZero(curDistance) && curDistance < distance) 
        {
            distance = curDistance;
            crossObj = i;
        }
    }
    
    if(distance == RTObjs::NoIntersection) // It seems unsafe but NoInertsecton is +INF so it's ok. We NEED EXACT comparasion.
        return nullptr;
    
    return objectPool_[crossObj];
}


