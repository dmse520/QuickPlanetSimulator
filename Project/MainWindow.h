#pragma once

// ---------------- Includes
#include "BaseWindow.h"
#include "PlanetDynamics.h"
#include "GlobalDecl.h"
#include "Renderer.h"

//	This is a class representating Main Window
class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow()
	{
		// Sun
		m_planets.push_back(PlanetClass()
			.setInitialPosition(0.0, 0.0)
			.setInitialVelocity(0.0, 0.0)
			.setColor(0.901f, 1.0f, 0.0f)
			.setMass(1.98E30)
		);
		// Mercury
		m_planets.push_back(PlanetClass()
			.setInitialPosition(46.0E9, 0)
			.setInitialVelocity(0.0, 47.362E3)
			.setColor(0.39f, 0.39f, 0.39f)
			.setMass(3.3E23)
		);
		// Venus
		m_planets.push_back(PlanetClass()
			.setInitialPosition(1.07E11, 0)
			.setInitialVelocity(0.0, 35.02E3)
			.setColor(0.55f, 0.27f, 0.07f)
			.setMass(4.86E24)
		);
		// Earth
		m_planets.push_back(PlanetClass()
			.setInitialPosition(1.496E11, 0)
			.setInitialVelocity(0.0, 29.78E3)
			.setColor(0.02f, 0.62f, 0.84f)
			.setMass(5.97E24)
		);
		// Mars
		m_planets.push_back(PlanetClass()
			.setInitialPosition(2.06E11, 0)
			.setInitialVelocity(0.0, 24.0E3)
			.setColor(0.84f, 0.20f, 0.07f)
			.setMass(6.41E23)
		);
		// Jupiter
		m_planets.push_back(PlanetClass()
			.setInitialPosition(816.62E9, 0)
			.setInitialVelocity(0.0, -15.78E3)
			.setColor(0.9f, 0.45f, 0.0f)
			.setMass(1.89E27)
		);

		m_Dynamics.initialize(m_planets);
	}

	void WaitTimer();

	PCWSTR ClassName() const { return TEXT("Sample Window Class"); }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	Renderer		m_Renderer;
	HANDLE			m_hTimer;

	BOOL InitializeTimer();

	// Planets
	PlanetDynamics m_Dynamics;
	PlanetSet m_planets;
};

