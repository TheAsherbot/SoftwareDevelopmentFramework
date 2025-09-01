#pragma once

namespace Framework
{
	namespace Rendering
	{

		class Renderer
		{
		public:
			Renderer()
			{

			};
			~Renderer()
			{

			};

			virtual void Init() = 0;
			virtual void CreateWindow(int height, int width, const char* title, int x, int y) = 0;

			virtual void Render(int x, int y, int color) = 0;
			
		private:

		};
	}
}