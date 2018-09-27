#ifndef PLANET_H
#define PLANET_H

#include "object.h"
#include "graphics_headers.h"

using namespace std;

class Planet: public Object
{
public:
	Planet();
	Planet(float orbitRadius);
	Planet(float spinSpeed, float orbitSpeed);
	Planet(float orbitRadius, float spinSpeed, float orbitSpeed);
	~Planet();

	void Update(unsigned int dt);

	float GetOrbitRadius();
	float GetSpinSpeed();
	float GetOrbitSpeed();

	void SetOrbitRadius(float orbitRadius);
	void SetSpinSpeed(float spinSpeed);
	void SetOrbitSpeed(float orbitSpeed);

private:
	float m_orbitRadius;
	float m_spinSpeed;
	float m_orbitSpeed;
};

#endif