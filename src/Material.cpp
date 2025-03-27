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
