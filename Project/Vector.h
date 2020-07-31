#pragma once

// ---------------- Includes

namespace PlanetDynamicName
{
	//	Class for Vector manipulation in PlanetDynamics namespace
	class Vector
	{
	public:
		Vector()
			: x(0.0), y(0.0)
		{}

		using M_TYPE = double;
		Vector(M_TYPE inX, M_TYPE inY)
			: x(inX), y(inY)
		{}

		Vector& setX(M_TYPE inX)
		{
			x = inX;
			return *this;
		}

		Vector& setY(M_TYPE inY)
		{
			y = inY;
			return *this;
		}

		Vector& addX(M_TYPE inX)
		{
			x += inX;
			return *this;
		}

		Vector& addY(M_TYPE inY)
		{
			y += inY;
			return *this;
		}

		Vector& operator+=(const Vector plusVector)
		{
			x += plusVector.x;
			y += plusVector.y;
			return *this;
		}

		friend Vector operator+(Vector lhs, const Vector rhs)
		{
			lhs += rhs;
			return lhs;
		}

		Vector& operator*=(const M_TYPE mul)
		{
			x *= mul;
			y *= mul;
			return *this;
		}

		friend Vector operator*(Vector lhs, const M_TYPE mul)
		{
			lhs *= mul;
			return lhs;
		}

		friend bool operator==(const Vector lhs, const Vector rhs)
		{
			if (lhs.x == rhs.x)
				if (lhs.y == rhs.y)
					return true;
			return false;
		}

		M_TYPE x, y;
	};
}