#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

// phong reflection model
class Material
{
  private:
  public:
	glm::vec3 ka;        // ambient
	glm::vec3 kd;        // diffuse
	glm::vec3 ks;        // specular
	float     shininess; // specular power
	
	Material(/* args */);
	Material(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess);
	~Material();
};

#endif
