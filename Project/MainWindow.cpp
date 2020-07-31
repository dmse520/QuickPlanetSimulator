// ---------------- Includes
#include "stdafx.h"
#include "MainWindow.h"
#include "PlanetDynamics.h"

// ---------------- Functions
BOOL MainWindow::InitializeTimer()
{
	m_hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (m_hTimer == NULL)
		return FALSE;

	LARGE_INTEGER li = { 0 };

	if (!SetWaitableTimer(m_hTimer, &li, (1000 / glSimulationFps) , NULL, NULL, FALSE))
	{
		CloseHandle(m_hTimer);
		m_hTimer = NULL;
		return FALSE;
	}

	return TRUE;
}

void MainWindow::WaitTimer()
{
	// Wait until timer expires
	if (MsgWaitForMultipleObjects(1, &m_hTimer, FALSE, INFINITE, QS_ALLINPUT)
			== WAIT_OBJECT_0)
	{
		m_Dynamics.computeIteration(m_planets);
		InvalidateRect(m_hWnd, NULL, FALSE);
	}
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(m_Renderer.Initialize()
			|| !InitializeTimer()))
		{
			return -1; // Fail CreateWindowsEx
		}
		return 0;

	case WM_DESTROY:
		m_Renderer.DeInitialize();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			HRESULT hr = m_Renderer.CreateGraphicsResources(m_hWnd);
			if (SUCCEEDED(hr))
			{
				PAINTSTRUCT ps;
				BeginPaint(m_hWnd, &ps);

				m_Renderer.Render(m_planets);

				EndPaint(m_hWnd, &ps);
			}
		}
		return 0;

	case WM_SIZE:
		{
			RECT rc;
			GetClientRect(m_hWnd, &rc);
			m_Renderer.Resize(rc);
			InvalidateRect(m_hWnd, NULL, FALSE);
		}
		return 0;

	case WM_MOUSEWHEEL:
		{
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			m_Renderer.SetWorldZoom(zDelta);
		}
		return 0;

	default:
		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	return TRUE;
}
// ---------------- End of File