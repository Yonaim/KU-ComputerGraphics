#include "Surface.hpp"
#include <glm/glm.hpp>

Surface::Surface(/* args */)
{
}

Surface::Surface(glm::vec3 pos, Material *material)
	: pos(pos), material(material)
{
}

Surface::~Surface()
{
}

Material *Surface::getMaterial() const
{
	return (this->material);
}

void Surface::setPosition(glm::vec3 pos)
{
	this->pos = pos;
}

bool Surface::intersect(hitRecord *hit, Ray &ray, float tMin, float tMax) const
{
	// virtual function
	// each surface has a different equation
	return (false);
}

// use phong shading model to calculate the color
glm::vec3 Surface::shade(hitRecord                 *hit,
						 std::vector<PointLight *> &lights) const
{
	glm::vec3 color = glm::vec3(0, 0, 0);
	glm::vec3 v     = glm::normalize(hit->ray.direction) * -1.0f;
	glm::vec3 n     = glm::normalize(hit->normal);
	std::vector<PointLight *>::const_iterator it       = lights.begin();
	Material                                 *material = hit->material;

	color += material->calculateAmbient(
		glm::vec3(1.0f, 1.0f, 1.0f)); // ambient light
	while (it < lights.end())
	{
		glm::vec3 l = glm::normalize((*it)->pos - hit->point); // shadow ray

		glm::vec3 diffuse  = material->calculateDiffuse((*it)->color, n, l);
		glm::vec3 specular = material->calculateSpecular((*it)->color, n, l, v);

		color += diffuse + specular;
		it++;
	}
	return (glm::clamp(color, 0.0f, 1.0f));
}