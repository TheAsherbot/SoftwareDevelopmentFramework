#pragma once

#include <iostream>
#include <string>
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

			virtual void SetBackgroundColor(int color) = 0;

			virtual void DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy, int color) = 0;
			virtual void DrawSquare(float x, float y, float width, float height, int color) = 0;
			virtual void DrawImage(float x, float y, float width, float height, int color, std::string imageFilePath) = 0;

			virtual void Update(float deltaTime) = 0;
		protected:
			static Renderer2D* instance;
		public:
			static Renderer2D& GetInstance()
			{
				if (instance != nullptr)
					return *instance;
				else
				{
					std::cout << "ERROR! Render does not exist!" << std::endl;
					__debugbreak();
					return *((Renderer2D*)NULL);
				}
			}
		};
	}
}