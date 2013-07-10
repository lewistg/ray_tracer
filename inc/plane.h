#ifndef _PLANE_H_
#define _PLANE_H_

#include "illuminated_object.h"


/**
 * Represents a plane
 */
class Plane:public IlluminatedObject
{
    public:
	/**
	 * Constructor
         */
	Plane(const Vector4f& pointOnPlane, const Vector4f& normal);
	
	/**
	 * Override
         */
	virtual float rayStrikesObject(const Ray& ray);
	
	/**
	 * Getter for the normal of the plane
         * @return 
         */
	Vector4f getNormal() const;
	
    protected:
	/**
	 * Override
         */
	virtual Vector4f getNormal(const Vector4f& pointOnObj) const;
	
    private:
	/**Constants from the plane equation*/
	float _D;
	
	/**Normal*/
	Vector4f _normal;
};

#endif