#include <glm/glm.hpp>
#include <iostream>

void printVec3(const glm::vec3 &v)
{
	std::cout << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")"
			  << std::endl;
}
