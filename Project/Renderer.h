#pragma once

// ---------------- Includes
#include <Windows.h>
#include <d2d1.h>
#include <atlbase.h>

#include "PlanetDynamics.h"
#include "GlobalDecl.h"
#include "WorldScaler.h"

//	This is a class representating Render Engine
class Renderer
{
	CComPtr<ID2D1Factory>			m_pFactory;
	CComPtr<ID2D1HwndRenderTarget>	m_pRenderTarget;

	CComPtr<ID2D1SolidColorBrush>	m_pFill;
	CComPtr<ID2D1SolidColorBrush>	m_pStroke;

	WorldScaler				m_Scaler;
	D2D1_SIZE_F				m_SzFWorldSize;

	D2D1_ELLIPSE			m_ellipse;

	void RenderPlanet(PlanetClass &inPlanet);
	inline void setPlanetToDraw(PlanetClass &inPlanet);

public:
	Renderer() : 
		m_pFactory(NULL), m_pRenderTarget(NULL),
		m_pFill(NULL), m_pStroke(NULL)
	{
		m_Scaler.setWorldScale(1.0f / 6E9f); // sets scale as 1 pixel is x meters
		m_Scaler.setWorldScale(5.0 / 5.97E24); // sets scale where 5 points is equal to Earth
	}

	HRESULT Initialize();
	void DeInitialize();
	HRESULT CreateGraphicsResources(HWND hWnd);
	void DiscardGraphicsResources();
	void Resize(RECT &inRc);
	void Render(PlanetSet & inPlanets);
	void SetWorldZoom(int zDelta);
};

