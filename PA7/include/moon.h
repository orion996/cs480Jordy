#ifndef MOON_H
#define MOON_H

#include "object.h"
#include "graphics_headers.h"
#include <string>

using namespace std;

class Moon: public Object
{
public:
	Moon();
	Moon(float orbitRadius);
	Moon(float spinSpeed, float orbitSpeed);
	Moon(float orbitRadius, float spinSpeed, float orbitSpeed);
    Moon(float orbitRadius, float spinSpeed, float orbitSpeed, string name, float scaleV);
	~Moon();

	void Update(unsigned int dt);
    //void UpdateUranRing(unsigned int dt);

	float GetOrbitRadius();
	float GetSpinSpeed();
	float GetOrbitSpeed();

	void SetOrbitRadius(float orbitRadius);
	void SetSpinSpeed(float spinSpeed);
	void SetOrbitSpeed(float orbitSpeed);
	void SetSpinAngle(float spinAngle);

private:
	float m_orbitRadius;
	float m_spinSpeed;
	float m_orbitSpeed;
	float m_spinAngle;
};

#endif