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

#include <memory>
#include <cmath>
#include "ray_tracer.h"
#include "illuminated_object.h"
#include "scene.h"
#include "plane.h"
#include "rtriangle.h"

RayTracer::RayTracer(const Vector4f& eye, Screen& screen):_eye(eye), _screen(screen)
{
    // set the screen one unit in front of the eye centered
}

void RayTracer::trace(const Scene& scene)
{
	Vector4f missColor(0.0f, 0.0, 0.0, 1.0f);

	for (int x = 0; x < _screen.getWidth(); x++)
	{
		for (int y = 0; y < _screen.getHeight(); y++)
		{
			// anti-alias by shooting 4 rays through each pixel (supersampling)
			float xCorners[4] = {0, 0, .75, .75};
			float yCorners[4] = {0, .75, 0, .75};
			Vector4f averageColor(0.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < STOCHASTIC_ANTIALIASING; i++)
			{
				// get the direction from the eye to the pixel
				Vector4f pixCenter = _screen.getPointInPixel(x, y, xCorners[i], yCorners[i]); //_screen->getPointInPixel(x, y);
				Vector4f dirToPixel = sub(pixCenter, _eye);
				normalize(&dirToPixel);

				// create a ray that passes through each pixel
				LightRay pixRay(_eye, dirToPixel, 0);

				//float t = sphereA.rayStrikesObject(pixRay);
				//if(t != -1)
				const std::shared_ptr<IlluminatedObject> object = scene.closestObj(pixRay);
				if (object != NULL)
				{
					object->getIntensity(pixRay, scene);
					//_screen->setPixel(x, y, hitColor);
					//_screen->setPixel(x, y, object->getColor());
					//_screen->setPixel(x, y, pixRay.getColor());
					averageColor = add(averageColor, pixRay.getColor());
					//cout << "Hit at: " << t << endl;
				} 
				else
				{
					averageColor = add(averageColor, missColor);
					//_screen->setPixel(x, y, missColor);
				}
			}
			averageColor.scale(1.0f / STOCHASTIC_ANTIALIASING);
			_screen.setPixel(x, y, averageColor);
		}
	}
}