#pragma once

#include "Vector2.h"
#include "Vector2f.h"

namespace Framework
{
	namespace Rendering
	{

		class Renderer2D
		{
		public:
			Renderer2D()
			{

			};
			~Renderer2D()
			{

			};

			virtual void Init() = 0;
			virtual void CreateWindow(int height, int width, const char* title, int x, int y) = 0;

			virtual void BackgroundColor(int color) = 0;

			virtual void DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy, int color) = 0;
			// virtual void DrawTriangle(Vector2 a, Vector2 b, Vector2 c, int color) = 0;

			virtual void Update(float deltaTime) = 0;
		private:

		};
	}
}