#ifndef MOON_H
#define MOON_H

#include "object.h"
#include "graphics_headers.h"

using namespace std;

class Moon: public Object
{
public:
	Moon();
	Moon(float orbitRadius);
	Moon(float spinSpeed, float orbitSpeed);
	Moon(float orbitRadius, float spinSpeed, float orbitSpeed);
	~Moon();

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