#include <Windows.h>

LSTATUS WINAPI WindowProcW(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam){
    switch(Msg) {
    case WM_DESTROY: {
        DestroyWindow(hWnd);
        break;
    }
    case WM_CLOSE: {
        PostQuitMessage(WM_CLOSE);
        break;
    }
    default:
        return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
    WNDCLASSEXW cl{ NULL };
    HWND hWnd{ NULL };
    MSG Msg{ NULL };

    cl.cbSize = sizeof(WNDCLASSEXW);
    cl.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    cl.hCursor = LoadCursorW(NULL, IDC_ARROW);
    cl.hIcon = LoadIconW(NULL, IDI_APPLICATION);
    cl.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
    cl.hInstance = hInstance;
    cl.lpfnWndProc = WindowProcW;
    cl.lpszClassName = L"ClassName";
    cl.lpszMenuName = L"MenuName";
    cl.style = CS_VREDRAW | CS_HREDRAW;

    if (!RegisterClassExW(&cl)) {
        return EXIT_FAILURE;
    }

    hWnd = CreateWindowExW(cl.style, cl.lpszClassName, L"WindowName", WS_OVERLAPPEDWINDOW, 1920/4.5, 1080/4, 1000, 600, NULL, NULL, hInstance, NULL);

    if (hWnd == INVALID_HANDLE_VALUE) {
        return EXIT_FAILURE;
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while (true) {
        if (GetMessageW(&Msg, NULL, NULL, NULL)) {
            TranslateMessage(&Msg);
            DispatchMessageW(&Msg);
        }
        else {
            break;
        }
    }

    return EXIT_SUCCESS;
}
