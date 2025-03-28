#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
	// free allocated memory for surfaces
	// because the materials are shared pointer, don't need to free them
	std::vector<Surface *>::const_iterator it = this->surfaces.begin();
	while (it < this->surfaces.end())
	{
		delete (*it);
		it++;
	}
	this->surfaces.clear();

	// free allocated memory for lights
	std::vector<PointLight *>::const_iterator it2 = this->lights.begin();
	while (it2 < this->lights.end())
	{
		delete (*it2);
		it2++;
	}
	this->lights.clear();
}

void Scene::setBackgroundColor(glm::vec3 color)
{
	this->background = color;
}

void Scene::addSurface(Surface *surface)
{
	this->surfaces.push_back(surface);
}

Camera &Scene::getCamera()
{
	return (this->camera);
}

std::vector<Surface *> &Scene::getSurfaces()
{
	return (this->surfaces);
}

std::vector<PointLight *> &Scene::getLights()
{
	return (this->lights);
}

// if the shadow ray hit any surface, return true
// shadow ray: from the hit point to the light source
static bool is_blocked(Ray &shadow_ray, float t_max, Surface *hit_surface,
					   std::vector<Surface *> &surfaces)
{
	std::vector<Surface *>::const_iterator it = surfaces.begin();

	while (it < surfaces.end())
	{
		hitRecord hit_curr;
		bool      is_hit;

		hit_curr.surface = NULL;
		is_hit = (*it)->intersect(&hit_curr, shadow_ray, 0.001f, t_max);
		if (is_hit && hit_curr.surface != hit_surface)
			return (true);
		it++;
	}
	return (false);
}

static bool is_in_shadow(hitRecord *hit, std::vector<PointLight *> lights,
						 std::vector<Surface *> &surfaces)
{
	std::vector<PointLight *>::const_iterator it = lights.begin();

	while (it < lights.end())
	{
		const glm::vec3 light_pos      = (*it)->pos;
		const glm::vec3 shadow_ray_dir = glm::normalize(light_pos - hit->point);
		Ray             shadow_ray(hit->point, shadow_ray_dir);
		float           shadow_ray_t = glm::length(light_pos - hit->point);

		if (is_blocked(shadow_ray, shadow_ray_t, hit->surface, surfaces))
			return (true);
		it++;
	}
	return (false);
}

// find the hitted surface with smallest t
glm::vec3 Scene::trace(Ray &ray, float tMin, float tMax)
{
	std::vector<Surface *>::const_iterator it = this->surfaces.begin();
	hitRecord                              hit_closest;

	hit_closest.surface = NULL;
	hit_closest.t       = tMax;
	while (it < this->surfaces.end())
	{
		hitRecord hit_curr;
		bool      is_hit;

		hit_curr.surface = NULL;
		hit_curr.t       = tMax;
		is_hit = (*it)->intersect(&hit_curr, ray, tMin, hit_closest.t);
		if (is_hit && hit_curr.t < hit_closest.t)
			hit_closest = hit_curr;
		it++;
	}

	if (hit_closest.surface != NULL)
	{
		if (is_in_shadow(&hit_closest, this->lights, this->surfaces))
			return (hit_closest.surface->getMaterial()->calculateAmbient(
				glm::vec3(1.0f, 1.0f, 1.0f))); // ambient light
		else
			return (hit_closest.surface->shade(&hit_closest, this->lights));
	}
	else
		return (this->background);
}
