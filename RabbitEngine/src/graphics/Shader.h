#pragma once
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
namespace RBT
{
	class Shader
	{
		public:
			int program;
			int vs, fs;

			Shader(std::string vs_filename, std::string fs_filename);
			void bind();
			void unbind();
			void setMat4Uniform(std::string name, glm::mat4 uniform);
		private:
			int getUniformLocation(std::string name);


	};
}
