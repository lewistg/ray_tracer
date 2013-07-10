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

#include "camera.h"

Camera::Camera(const Eye& eye):
	_eye(eye),
	_screen(640, 480, .002, 
		add(scale(eye.getDir(), 1), eye.getLocation()), // camera center
		_eye.getDir(), _eye.getUp())
{
    /*Vector4f screenCenter = add(scale(eye.getDir(), 20), eye.getLocation());
    Screen cameraScreen(640, 480, .1, screenCenter, _eye.getDir(), _eye.getUp());
    
    Screen screen(640, 480, .1, 
	Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
	Vector4f(0.0f, 0.0f, -1.0f, 1.0f),
	Vector4f(0.0f, 1.0f, 0.0f, 1.0f));*/
}

Eye Camera::getEye()
{
    return _eye;
}

Screen& Camera::getScreen()
{
    return _screen;
}