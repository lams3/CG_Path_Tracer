//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_RAY_H
#define CG_PATH_TRACER_RAY_H

#include "../../dependencies/glm/glm.hpp"

class Ray {
	private:
	glm::vec3 origin, direction;

	public:
	float minDistance;

	void setOrigin(const glm::vec3 &origin);

	const glm::vec3 &getDirection() const;

	void setDirection(const glm::vec3 &direction);

    Ray(glm::vec3 origin, glm::vec3 direction, float minDistance);

    glm::vec3 getOrigin()const;

    glm::vec3 sample(float t)const;
};


#endif //CG_PATH_TRACER_RAY_H
