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
	Plane(const mvl::GVector3f& pointOnPlane, const mvl::GVector3f& normal);
	
	/**
	 * Override
         */
	virtual float rayStrikesObject(const Ray& ray);
	
	/**
	 * Getter for the normal of the plane
         * @return 
         */
	mvl::GVector3f getNormal() const;
	
    protected:
	/**
	 * Override
         */
	virtual mvl::GVector3f getNormal(const mvl::GVector3f& pointOnObj) const;
	
    private:
	/**Constants from the plane equation*/
	float _D;
	
	/**Normal*/
	mvl::GVector3f _normal;
};

#endif