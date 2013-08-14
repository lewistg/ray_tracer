/**
 * Copyright (c) 2013, Ty G. Lewis 
 * All rights reserved.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Ty G. Lewis BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LAMBERT_LIGHT_H_
#define _LAMBERT_LIGHT_H_

#include "graphics_vector.h"

/**
 * A lambert light possessing a diffuse, ambient,
 * and specular component.
 */
class LambertLight
{
    public:
	/**
	 * Constructor
         */
	LambertLight();
	
	/**
	 * Sets the diffuse component of the lighting
         * @param diffuseComps - The diffuse components
	 * @pre size(diffuseComps) = 4
         */
	void setDiffuse(const mvl::GVector4f& diffuseComps);

	
	/**
	 * Gets the diffuse component of light
         */
	mvl::GVector4f getDiffuse();	
	
	/**
	 * Sets the ambient component of the lighting
         * @param ambComps - The diffuse components
	 * @pre size(ambComps) = 4
         */
	void setAmbient(const mvl::GVector4f& ambComps);
	
	/**
	 * Gets the ambient component of light
         */
	mvl::GVector4f getAmbient();

	/**
	 * Sets the shine of the color of the light
         * @param pos
         */
	 void setSpecular(const mvl::GVector4f& specularComps);
	 
	 /**
	  * Gets the specular components of the light
          */
	 mvl::GVector4f getSpecular();
	
	/**
	 * Sets the position of the light
         * @param pos - The position of the light
	 * @pre size(pos) = 4
         */
	void setPos(const mvl::GVector3f& pos);
	
	/**
	 * Gets the position of the light
	 */
	mvl::GVector3f getPos() const;
	
    private:
	/**The diffuse components*/
	mvl::GVector4f _diffuseComps;
	/**The ambient components*/
	mvl::GVector4f _ambientComps;
	/**The specular components*/
	mvl::GVector4f _specularComps;
	/**The position of the light*/
	mvl::GVector3f _pos;
};

#endif