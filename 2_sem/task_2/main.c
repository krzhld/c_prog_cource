#include "main.h"
#include "calculations.h"
#include "drawing.h"

#define MAX_LOADSTRING 100

int curIter = 0;
int maxIter = 0;
int stagesInstallPoints = 0;
SEGMENTTYPE* lineSegments;

HINSTANCE hInst;                           
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    lineSegments = (SEGMENTTYPE*)malloc(sizeof(SEGMENTTYPE));

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TASK2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK2));

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK2));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TASK2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd) 
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            static HPEN hPen;
            hPen = CreatePen(PS_SOLID, 3, VIOLET);
            SelectObject(hdc, hPen);

            if (stagesInstallPoints == 1)
                Rope(hdc, lineSegments);
            
            if (stagesInstallPoints > 1)
                DrawTriangle(hdc, curIter, lineSegments);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            free(lineSegments);
            break;

        case VK_LEFT:
            if (stagesInstallPoints > 1)
            { 
                if (curIter > 0)
                    --curIter;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;

        case VK_RIGHT:
            if (stagesInstallPoints > 1)
            {
                ++curIter;
                if (curIter > maxIter)
                {
                    maxIter = curIter;
                    lineSegments = (SEGMENTTYPE*)realloc(lineSegments, sizeof(SEGMENTTYPE) * GeomProgr(curIter));
                    CalculateTriangles(curIter, lineSegments);
                }

                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
    }
    break;
    
    case WM_LBUTTONDOWN:
    {
        if (stagesInstallPoints == 0)
        {
            lineSegments[0].pt1.x = LOWORD(lParam);
            lineSegments[0].pt1.y = HIWORD(lParam);
        }

        if (stagesInstallPoints == 1)
        {
            lineSegments[0].pt2.x = LOWORD(lParam);
            lineSegments[0].pt2.y = HIWORD(lParam);
            Orientation(lineSegments + 0);
        }

        ++stagesInstallPoints;
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (stagesInstallPoints == 1)
        {
            lineSegments[0].pt2.x = LOWORD(lParam);
            lineSegments[0].pt2.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
