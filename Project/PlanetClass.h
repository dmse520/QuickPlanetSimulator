#pragma once

// ---------------- Includes
#include <d2d1.h>
#include <utility>

#include "Vector.h"

//	Class for storing planet specific info
class PlanetClass
{
	using M_TYPE = double;
	using Vector = PlanetDynamicName::Vector;
	Vector m_position;
	M_TYPE m_mass;
	Vector m_initialVel;
	D2D1_COLOR_F m_Color;

	friend class PlanetDynamics;
public:
	PlanetClass& setInitialPosition(M_TYPE x, M_TYPE y)
	{
		m_position.setX(x).setY(y);
		return *this;
	}

	PlanetClass& setMass(M_TYPE inMass)
	{
		m_mass = inMass;
		return *this;
	}

	M_TYPE getMass() const
	{
		return m_mass;
	}

	const Vector getPosition() const
	{
		return m_position;
	}

	PlanetClass& setInitialVelocity(M_TYPE x, M_TYPE y)
	{
		m_initialVel.setX(x).setY(y);
		return *this;
	}

	const Vector getInitialPosition() const
	{
		return m_initialVel;
	}

	PlanetClass& setColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha = 1.0f)
	{
		m_Color = D2D1::ColorF(red, green, blue, alpha);
		return *this;
	}

	const D2D1_COLOR_F & getColor() const
	{
		return m_Color;
	}

	friend bool operator==(const PlanetClass lhs, const PlanetClass rhs)
	{
		bool ret = true;
		ret &= (lhs.m_position == rhs.m_position);
		ret &= (lhs.m_mass == rhs.m_mass);
		ret &= (lhs.m_initialVel == rhs.m_initialVel);
		return ret;
	}
};