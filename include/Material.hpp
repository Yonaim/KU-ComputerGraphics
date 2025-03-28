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

	glm::vec3 calculateAmbient(const glm::vec3 &lightColor) const;
	glm::vec3 calculateDiffuse(const glm::vec3 &lightColor,
							   const glm::vec3 &normal,
							   const glm::vec3 &lightDirection) const;
	glm::vec3 calculateSpecular(const glm::vec3 &lightColor,
								const glm::vec3 &normal,
								const glm::vec3 &lightDirection,
								const glm::vec3 &viewDirection) const;
};

#endif
