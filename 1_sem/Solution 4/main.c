#include <windows.h>
#include <gl/gl.h>

#define HEIGHT 8
#define WIDTH 8
#define OFF 0.5

int x1, y1, x2, y2;
int isItFirstClick = 1, isItSecondClick = 1;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

void DrawDesk()
{
    double i, j;
    for (i = 0; i < 8; i += 2)
        for (j = 8; j > 0; j -= 2)
        {
        glBegin(GL_POLYGON);
            glColor3f(1, 1, 1); glVertex2f(i, j);
            glColor3f(1, 1, 1); glVertex2f(i + 1, j);
            glColor3f(1, 1, 1); glVertex2f(i + 1, j - 1);
            glColor3f(1, 1, 1); glVertex2f(i, j - 1);
        glEnd();
        }
        for (i = 1; i < 8; i += 2)
            for (j = 7; j > 0; j -= 2)
        {
        glBegin(GL_POLYGON);
            glColor3f(1, 1, 1); glVertex2f(i, j);
            glColor3f(1, 1, 1); glVertex2f(i + 1, j);
            glColor3f(1, 1, 1); glVertex2f(i + 1, j - 1);
            glColor3f(1, 1, 1); glVertex2f(i, j - 1);
        glEnd();
        }
}

void ScreeToOpenGL (HWND hwnd, int x, int y, float* ox, float* oy)
{
    RECT rct;
    GetClientRect(hwnd, &rct);
    *ox = x / (float)rct.right * WIDTH;
    *oy = HEIGHT - y / (float)rct.bottom * HEIGHT;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          800,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0, 0, 0, 0);
            glLineWidth(10);
            glClear(GL_COLOR_BUFFER_BIT);

            glLoadIdentity();
            glTranslatef(-1, -1, 0);
            glScalef(0.25, 0.25, 1);

            DrawDesk();

            if ((isItFirstClick == 0)&&(isItSecondClick == 0))
            {
                glBegin(GL_POLYGON); // начальный квадрат - синий
                glColor3f(0, 0, 1); glVertex2f(x1, y1);
                glColor3f(0, 0, 1); glVertex2f(x1 + 1, y1);
                glColor3f(0, 0, 1); glVertex2f(x1 + 1, y1 + 1);
                glColor3f(0, 0, 1); glVertex2f(x1, y1 + 1);
                glEnd();

                glBegin(GL_POLYGON); // конечный квадрат - бронзовый
                glColor3f(1, 0.5, 0); glVertex2f(x2, y2);
                glColor3f(1, 0.5, 0); glVertex2f(x2 + 1, y2);
                glColor3f(1, 0.5, 0); glVertex2f(x2 + 1, y2 + 1);
                glColor3f(1, 0.5, 0); glVertex2f(x2, y2 + 1);
                glEnd();

                if (abs(x1 - x2) == abs(y1 - y2))
                {
                glBegin(GL_LINES);
                glColor3f(0.5, 1, 1); glVertex2f(x1 + OFF, y1 + OFF);
                glColor3f(0.5, 1, 1); glVertex2f(x2 + OFF, y2 + OFF);
                glEnd();
                }
                else
                {
                glBegin(GL_LINE_STRIP);
                glColor3f(0.5, 1, 1); glVertex2f(x1 + OFF, y1 + OFF);
                glColor3f(0.5, 1, 1); glVertex2f(x2 + OFF, y1 + OFF);
                glColor3f(0.5, 1, 1); glVertex2f(x2 + OFF, y2 + OFF);
                glEnd();
                }
            }

            SwapBuffers(hDC);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_LBUTTONDOWN:
        {
        if ((isItFirstClick == 1)&&(isItSecondClick == 1))
            {
                POINTFLOAT pf;
                ScreeToOpenGL(hwnd, LOWORD(lParam), HIWORD(lParam), &pf.x, &pf.y);
                isItFirstClick = 0;
                x1 = (int)pf.x;
                y1 = (int)pf.y;
            }
        else if ((isItFirstClick == 0)&&(isItSecondClick == 1))
            {
                POINTFLOAT pf;
                ScreeToOpenGL(hwnd, LOWORD(lParam), HIWORD(lParam), &pf.x, &pf.y);
                x2 = (int)pf.x;
                y2 = (int)pf.y;
                isItFirstClick = 0;
                isItSecondClick = 0;
            }
        }

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}


