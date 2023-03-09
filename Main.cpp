#include <Windows.h>

LSTATUS WINAPI WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (Msg) {
		case WM_DESTROY: {
			DestroyWindow(hWnd);
			break;
		}
		case WM_CLOSE: {
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}
		default: {
			return DefWindowProcA(hWnd, Msg, wParam, lParam);
		}
	}
	return EXIT_SUCCESS;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	WNDCLASSEXA cl{ NULL };
	HWND hWnd{ NULL };
	MSG msg{ NULL };

	cl.cbSize = sizeof(WNDCLASSEX);
	cl.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	cl.hCursor = LoadCursorA(NULL, IDC_ARROW);
	cl.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	cl.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
	cl.hInstance = hInstance;
	cl.lpfnWndProc = WindowProc;
	cl.lpszClassName = "ClassName";
	cl.lpszMenuName = "MenuName";
	cl.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassExA(&cl)) {
		return EXIT_FAILURE;
	}

	hWnd = CreateWindowExA(cl.style, cl.lpszClassName, "WindowName", WS_OVERLAPPEDWINDOW, 0, 0, 1000, 500, NULL, NULL, hInstance, NULL);

	if (hWnd == INVALID_HANDLE_VALUE) {
		return EXIT_FAILURE;
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while (true) {
		if (GetMessageA(&msg, NULL, NULL, NULL)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else {
			break;
		}
	}

	return EXIT_SUCCESS;
}
