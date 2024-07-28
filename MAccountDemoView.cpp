// MAccountDemoView.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MAccountDemoView.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

class MyButton {
public:
    MyButton(HINSTANCE hInstance, HWND hParent, int x, int y, int width, int height, int id, LPCWSTR text)
        : hInstance(hInstance), hParent(hParent), id(id) {
        WNDCLASS wc = { 0 };
        wc.lpfnWndProc = ButtonProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = L"MY_BUTTON";
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        RegisterClass(&wc);

        hWndButton = CreateWindowEx(
            0, L"MY_BUTTON", text, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            x, y, width, height, hParent, (HMENU)id, hInstance, this);

        if (!hWndButton) {
            MessageBox(hParent, L"Button creation failed!", L"Error", MB_OK | MB_ICONERROR);
        }
    }

    HWND getHandle() const {
        return hWndButton;
    }

    int getId() const {
        return id;
    }

    static LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        MyButton* pThis;
        if (message == WM_NCCREATE) {
            pThis = static_cast<MyButton*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        }
        else {
            pThis = reinterpret_cast<MyButton*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        if (pThis) {
            switch (message) {
            case WM_COMMAND:
                if (HIWORD(wParam) == BN_CLICKED) {
                    MessageBox(pThis->hParent, L"Button Clicked", L"Notification", MB_OK);
                }
                break;
            case WM_DRAWITEM:
                pThis->drawItem(reinterpret_cast<LPDRAWITEMSTRUCT>(lParam));
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        else {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    void drawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
        if (lpDrawItemStruct->CtlType == ODT_BUTTON) {
            HDC hdc = lpDrawItemStruct->hDC;
            RECT rect = lpDrawItemStruct->rcItem;
            SetBkMode(hdc, TRANSPARENT);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FrameRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);
            DrawText(hdc, L"Click Me", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }

private:
    HINSTANCE hInstance;
    HWND hParent;
    HWND hWndButton;
    int id;
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CPLUSCPLUSDESKTP001, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPLUSCPLUSDESKTP001));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPLUSCPLUSDESKTP001));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CPLUSCPLUSDESKTP001);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Create a MyButton instance
    MyButton* myButton = new MyButton(hInstance, hWnd, 10, 10, 100, 30, 101, L"Click Me");

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT lpDrawItemStruct = reinterpret_cast<LPDRAWITEMSTRUCT>(lParam);
        if (lpDrawItemStruct->CtlType == ODT_BUTTON) {
            MyButton* pButton = reinterpret_cast<MyButton*>(GetWindowLongPtr(lpDrawItemStruct->hwndItem, GWLP_USERDATA));
            if (pButton) {
                pButton->drawItem(lpDrawItemStruct);
            }
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps); // Corretto per passare hWnd invece di hdc
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
