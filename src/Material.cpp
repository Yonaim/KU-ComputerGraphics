#include "Material.hpp"

Material::Material(/* args */)
{
}

Material::~Material()
{
}

Material::Material(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess)
	: ka(ka), kd(kd), ks(ks), shininess(shininess)
{
}

// Ambient lighting calculation
glm::vec3 Material::calculateAmbient(const glm::vec3 &lightColor) const
{
	return (ka * lightColor);
}

// Diffuse lighting calculation
glm::vec3 Material::calculateDiffuse(const glm::vec3 &lightColor,
									 const glm::vec3 &normal,
									 const glm::vec3 &lightDirection) const
{
	return (kd * lightColor * glm::max(glm::dot(normal, lightDirection), 0.0f));
}

// Specular lighting calculation
glm::vec3 Material::calculateSpecular(const glm::vec3 &lightColor,
									  const glm::vec3 &normal,
									  const glm::vec3 &lightDirection,
									  const glm::vec3 &viewDirection) const
{
	glm::vec3 h = glm::normalize(lightDirection + viewDirection);
	return (ks * lightColor
			* glm::pow(glm::max(glm::dot(normal, h), 0.0f), shininess));
}
