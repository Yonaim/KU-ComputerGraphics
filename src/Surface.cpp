#include "Surface.hpp"
#include <glm/glm.hpp>

Surface::Surface(/* args */)
{
}

Surface::Surface(glm::vec3 pos, std::shared_ptr<Material> material)
	: pos(pos), material(std::move(material))
{
}

Surface::~Surface()
{
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
	std::shared_ptr<Material>                material = hit->material;

	while (it < lights.end())
	{
		glm::vec3 l = glm::normalize((*it)->pos - hit->point); // shadow ray

		// ambient
		glm::vec3 ambient = material->ka * (*it)->color;

		// diffuse
		glm::vec3 diffuse
			= material->kd * (*it)->color * glm::max(glm::dot(n, l), 0.0f);

		// specular
		glm::vec3 h = glm::normalize(l + v);
		glm::vec3 specular
			= material->ks * (*it)->color
			  * glm::pow(glm::max(glm::dot(n, h), 0.0f), material->shininess);

		color += ambient + diffuse + specular;
		it++;
	}
	return (glm::clamp(color, 0.0f, 1.0f));
}
