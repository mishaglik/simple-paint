#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <Raytracer/RenderObject.hpp>
#include <Vector/Vector.hpp>

class Scene
{
    template<class T>
    using Vector = mvc::Vector<T>;
    using RenderObject = RTObjs::RenderObject;
    using Ray = mgm::Ray3f;

    Vector<RenderObject* > objectPool_; 

public:
    Scene() {}

    ~Scene();

    /**
     * @brief add object to Scene. Scene will OWN this object, and destroy it on exit;
     * 
     * @param object - object to add
     * @return ssize_t - index of object. -1 on failture.
     */
    ssize_t addObject(RenderObject* object);

    /**
     * @brief Return first object to intersect ray. nullptr on failture.
     * 
     * @param ray - ray
     * @return const RenderObject* - object to cross. 
     */
    const RenderObject* getObjectOnRay(const Ray& ray) const;

    const Vector<RenderObject* >& objects() const { return objectPool_; }

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

};

#endif /* RAYTRACER_SCENE_HPP */
