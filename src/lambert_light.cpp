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

#include "lambert_light.h"
#include "matrix_state.h"

LambertLight::LambertLight()
	{}


void LambertLight::setDiffuse(const Vector4f& diffuseComps)
{
    _diffuseComps = Vector4f(diffuseComps);
}

Vector4f LambertLight::getDiffuse()
{
    return _diffuseComps;
}

void LambertLight::setAmbient(const Vector4f& ambComps)
{
    _ambientComps = Vector4f(ambComps);
}


Vector4f LambertLight::getAmbient()
{
    return _ambientComps;
}

void LambertLight::setSpecular(const Vector4f& specularComps)
{
    _specularComps = specularComps;
}

Vector4f LambertLight::getSpecular()
{
    return _specularComps;
}

void LambertLight::setPos(const Vector4f& pos)
{
    _pos = Vector4f(pos);
    //_pos = mult(MatrixState::getInstance().getActiveModelViewMatrix(), _pos);
}

Vector4f LambertLight::getPos() const
{
    return _pos;
}