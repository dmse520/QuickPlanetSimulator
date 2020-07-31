#pragma once
#include "Vector.h"

//	Class for setting world scale
class WorldScaler
{
	double fWorldScale;

public:
	float w_x, w_y;
	double fWorldWeightScale;
	const float maxWorldWeight = 50;
	const float minWorldWeight = 2;

	void setPlanetToScale(const PlanetDynamicName::Vector inPos)
	{
		w_x = float(inPos.x * fWorldScale);
		w_y = float(inPos.y * fWorldScale);
	}

	void setWorldScale(float inScale)
	{
		fWorldScale = inScale;
	}

	void setWorldScale(double inScale)
	{
		fWorldWeightScale = inScale;
	}

	void addZoom(double inZoom)
	{
		if((fWorldScale + inZoom) > 0)
			fWorldScale += inZoom;
	}
};