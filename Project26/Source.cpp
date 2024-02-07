#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool movingWindow = false;
int speed = 5;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    const WCHAR className[] = L"FirstWindow";
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = className;

    if (!RegisterClassEx(&wc)) {
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0, className, L"My first window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    SetTimer(hWnd, 1, 50, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
    return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_RETURN:
            SetWindowPos(hwnd, NULL, 0, 0, 300, 300, SWP_NOZORDER | SWP_SHOWWINDOW);
            movingWindow = true;
            break;
        case VK_ESCAPE:
            movingWindow = false;
            break;
        }
        break;
    case WM_TIMER:
        if (movingWindow) {
            RECT rect;
            GetWindowRect(hwnd, &rect);
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);

            static int direction = 0;
            switch (direction) {
            case 0:
                if (rect.right + speed <= screenWidth) {
                    rect.left += speed;
                    rect.right += speed;
                }
                else {
                    direction = 1;
                }
                break;
            case 1:
                if (rect.bottom + speed <= screenHeight) {
                    rect.top += speed;
                    rect.bottom += speed;
                }
                else {
                    direction = 2;
                }
                break;
            case 2:
                if (rect.left - speed >= 0) {
                    rect.left -= speed;
                    rect.right -= speed;
                }
                else {
                    direction = 3;
                }
                break;
            case 3:
                if (rect.top - speed >= 0) {
                    rect.top -= speed;
                    rect.bottom -= speed;
                }
                else {
                    direction = 0;
                }
                break;
            }

            MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
