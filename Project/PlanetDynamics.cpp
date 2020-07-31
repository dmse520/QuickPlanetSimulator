// ---------------- Includes
#include "stdafx.h"
#include "PlanetDynamics.h"
#include <cmath>

using namespace PlanetDynamicName;

// ---------------- Functions

double Calculator::giveHypo(const Vector first, const Vector second)
{
	double dist_x = first.x - second.x;
	double dist_y = first.y - second.y;
	return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

double Calculator::givePlanetForceKoef(double inHypo, double inForceActingMass)
{
	return GravityConst * inForceActingMass *
		(1 / pow(inHypo, 3));
}

Vector PlanetDynamics::computeAccelerationFromPlanet(PlanetClass inPlanet, PlanetClass inActingPlanet)
{
	double planet_hypo = Calculator::giveHypo(
		inPlanet.m_position, inActingPlanet.m_position
	);

	double force_koef = Calculator::givePlanetForceKoef(planet_hypo, inActingPlanet.m_mass);
	return Vector(inPlanet.m_position * (-1 * force_koef));
}

void PlanetDynamics::computeIteration(PlanetSet & inPlanets)
{
	auto planetParameter = Parameters.begin();
	for (auto &planet : inPlanets)
	{
		planet.m_position
			.addX(SimulationTime_delta * planetParameter->m_HalfVel.x)
			.addY(SimulationTime_delta * planetParameter->m_HalfVel.y);

		Vector accel;
		for (auto &actingPlanet : inPlanets)
		{
			if (planet == actingPlanet)
				continue;
			accel += computeAccelerationFromPlanet(planet, actingPlanet);
		}

		planetParameter->m_HalfVel += accel * SimulationTime_delta;
		++planetParameter;
	}
}

void PlanetDynamics::initialize(PlanetSet & inPlanets)
{
	for (auto &planet : inPlanets)
	{
		Vector accel;
		for (auto &actingPlanet : inPlanets)
		{
			if (planet == actingPlanet)
				continue;
			accel += computeAccelerationFromPlanet(planet, actingPlanet);
		}

		Parameters.push_back(DynamicParams());
		auto planetParameter = Parameters.end() - 1;
		planetParameter->m_HalfVel = planet.m_initialVel + accel * (SimulationTime_delta / 2);
	}
}

// ---------------- End of File