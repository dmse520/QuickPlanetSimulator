#pragma once

// ---------------- Includes
#include "GlobalDecl.h"
#include "PlanetClass.h"
#include "Vector.h"
#include <array>

namespace PlanetDynamicName
{
	//	Class for computing dynamic specific 
	class Calculator
	{
	public:
		static constexpr double GravityConst = 6.67E-11;

		static double giveHypo(const Vector first, const Vector second);

		static double givePlanetForceKoef(double inHypo, double inForceActingMass);

	};
}

//	Class for computing dynamic parameters of planets
class PlanetDynamics
{
	struct DynamicParams
	{
		PlanetDynamicName::Vector m_HalfVel;
	};

	// 10 days * seconds per day in one second of program running
	const double SimulationTime_delta = 10 * 86.4E3 / glSimulationFps;
	std::vector<DynamicParams> Parameters;

	PlanetDynamicName::Vector computeAccelerationFromPlanet(PlanetClass inPlanet, PlanetClass inActingPlanet);

public:
	void computeIteration(PlanetSet &inPlanets);
	void initialize(PlanetSet &inPlanets);
};