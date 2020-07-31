// ---------------- Includes
#include "stdafx.h"
#include "Renderer.h"
#include "PlanetClass.h"

#pragma comment(lib, "d2d1")

// ---------------- Functions
HRESULT Renderer::Initialize()
{
	return D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
}

void Renderer::DeInitialize()
{
	m_pFactory.Release();
}

HRESULT Renderer::CreateGraphicsResources(HWND hWnd)
{
	HRESULT hr = S_OK;
	if (m_pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = m_pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_pRenderTarget
		);

		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::White),
				D2D1::BrushProperties(),
				&m_pFill
			);

			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				D2D1::BrushProperties(),
				&m_pStroke
			);
		}
	}
	return hr;
}

void Renderer::DiscardGraphicsResources()
{
	m_pRenderTarget.Release();
	m_pFill.Release();
	m_pStroke.Release();
}

void Renderer::Resize(RECT &inRc)
{
	if (m_pRenderTarget != NULL)
	{
		D2D1_SIZE_U size = D2D1::SizeU(inRc.right, inRc.bottom);

		m_pRenderTarget->Resize(size);
	}
}

void Renderer::Render(PlanetSet & inPlanets)
{
	m_SzFWorldSize = m_pRenderTarget->GetSize();

	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->Clear(D2D1::ColorF(0.93f, 0.93f, 0.93f));

	for (auto planet : inPlanets)
	{
		RenderPlanet(planet);
	}

	HRESULT hr = m_pRenderTarget->EndDraw();
	if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
	{
		DiscardGraphicsResources();
	}
}

void Renderer::SetWorldZoom(int zDelta)
{
	m_Scaler.addZoom(1.0 / (0.08E9 * zDelta));
}

void Renderer::setPlanetToDraw(PlanetClass & inPlanet)
{
	m_Scaler.setPlanetToScale(inPlanet.getPosition());
	m_ellipse.point.x = m_Scaler.w_x + (m_SzFWorldSize.width / 2.0f);
	m_ellipse.point.y = m_Scaler.w_y + (m_SzFWorldSize.height / 2.0f);
	FLOAT radius = max(m_Scaler.minWorldWeight,
		min(m_Scaler.maxWorldWeight,
			FLOAT(inPlanet.getMass() * m_Scaler.fWorldWeightScale)
		)
	);
	m_ellipse.radiusX = m_ellipse.radiusY = radius;
}

void Renderer::RenderPlanet(PlanetClass & inPlanet)
{
	setPlanetToDraw(inPlanet);
	m_pFill->SetColor(inPlanet.getColor());
	m_pRenderTarget->FillEllipse(m_ellipse, m_pFill);
	m_pRenderTarget->DrawEllipse(m_ellipse, m_pStroke);
}
// ---------------- End of File