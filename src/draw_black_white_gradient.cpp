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

#include "draw_black_white_gradient.h"


DrawBlackWhiteGradient::DrawBlackWhiteGradient(Raster* raster):DrawCommand(raster)
	{}

DrawBlackWhiteGradient::~DrawBlackWhiteGradient()
	{}

void DrawBlackWhiteGradient::draw(Vertex* vertices, int numVertices)
{	
	float initColor[] = {0, 0, 0, 0};
	Vector4f colorVector(initColor);
	
	float brightnessStep = 1.0f / (DrawCommand::getRaster()->getWidth() - 1);
	float colorStepData[] = {brightnessStep, brightnessStep, 
								brightnessStep, brightnessStep};
	Vector4f colorStep(colorStepData);
	
	for(int h = 0; h < DrawCommand::getRaster()->getHeight(); h++)
	{
		for(int w = 0; w < DrawCommand::getRaster()->getWidth(); w++)
		    DrawCommand::plotPoint(w, h, 1, colorVector);
		
		colorVector += colorStep;
	}	
}