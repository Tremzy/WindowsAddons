#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <Lmcons.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.top += 500;
            rect.right -= 20;
            DrawText(hdc, "Contact for more support!", -1, &rect, DT_RIGHT | DT_BOTTOM);
            rect.top -= 470;
            rect.right -= 340;
            char username[UNLEN+1];
            DWORD username_len = UNLEN+1;
            GetUserName(username, &username_len);
            DrawText(hdc, ("Hello, " + std::string(username)).c_str(), -1, &rect, DT_RIGHT | DT_BOTTOM);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_CLOSE:
            std::cout << "Debug :  Destroying window" << std::endl;
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            std::cout << "Debug :  Destroying window" << std::endl;
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1)
            {
                std::cout << "Debug :  Opening Discord..." << std::endl;
                system("start https://discord.gg/HdrqeKG7b7");
            }
            else if (LOWORD(wParam) == 2){
                auto msbox = MessageBox(hwnd, "Download Vcruntime140.dll? Press Yes or No...", "Process", MB_OKCANCEL | MB_ICONQUESTION);
                if (msbox == IDOK){
                    std::cout << "Debug :  Downloading packages..." << std::endl;
                    system("start https://www.dll-files.com/download/7a2b8cfcd543f6e4ebca43162b67d610/vcruntime140.dll.html?c=NEZvY3NUSlQ1T3l4MzkyRFNXS2d3Zz09");
                    Sleep(7000);
                    auto msbox = MessageBox(hwnd, "Install the downloaded packages? Press Yes or No", "Process", MB_YESNO | MB_ICONQUESTION);
                    if (msbox == IDYES){
                        std::cout << "Debug :  Installing packages" << std::endl;
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserName(username, &username_len);
                        std::string command = "cd C:\\Users\\" + std::string(username) + "\\Downloads & tar -xf vcruntime140.zip & copy /Y vcruntime140.dll C:\\Windows\\System32 & copy /Y vcruntime140.dll C:\\Windows\\System";
                        auto cmdresult = system(command.c_str());
                        std::cout << command << std::endl;
                }
                else {
                    std::cout << "Debug :  Canceling process..." << std::endl;
                }
                }
            }
            else if(LOWORD(wParam) == 3){
                exit(EXIT_SUCCESS);
            }
            else if(LOWORD(wParam) == 4){
                HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
                SetCursor(hCursor);
                SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                std::cout << "Debug :  Cursor changed to IDC_ARROW" << std::endl;
            }
            else if(LOWORD(wParam) == 5){
                HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);
                SetCursor(hCursor);
                SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                std::cout << "Debug :  Cursor changed to IDC_HAND" << std::endl;
            }
            else if(LOWORD(wParam) == 6){
                HCURSOR hCursor = LoadCursor(NULL, IDC_CROSS);
                SetCursor(hCursor);
                SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                std::cout << "Debug :  Cursor changed to IDC_CROSS" << std::endl;
            }
            else if(LOWORD(wParam) == 7){
                HCURSOR hCursor = LoadCursor(NULL, IDC_UPARROW);
                SetCursor(hCursor);
                SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                std::cout << "Debug :  Cursor changed to IDC_UPARROW" << std::endl;
            }
            else if (LOWORD(wParam) == 8){
                auto msbox = MessageBox(hwnd, "Download MSVCP140.DLL? Press OK or Cancel...", "Process", MB_OKCANCEL | MB_ICONQUESTION);
                if (msbox == IDOK){
                    std::cout << "Debug :  Downloading packages..." << std::endl;
                    system("start https://www.dll-files.com/download/7b92a6cb5d2cad407c457ab12d2b211d/msvcp140.dll.html?c=OGM2VmNid2swaXhXUjNLbCs2TmNkZz09");
                    Sleep(7000);
                    auto msbox = MessageBox(hwnd, "Install the downloaded packages?", "Process", MB_YESNO | MB_ICONQUESTION);
                    if (msbox == IDYES){
                        std::cout << "Debug :  Installing packages" << std::endl;
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserName(username, &username_len);
                        std::string command = "cd C:\\Users\\" + std::string(username) + "\\Downloads & tar -xf msvcp140.zip & copy /Y msvcp140.dll C:\\Windows\\System32 & copy /Y msvcp140.dll C:\\Windows\\System";
                        system(command.c_str());
                        std::cout << command << std::endl;
                    }
                    else {
                        std::cout << "Debug :  Canceling process..." << std::endl;
                    }
                }
                else {
                    std::cout << "Debug :  Canceling process..." << std::endl;
                }
            }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char* className = "MyWindowClass";
    const char* windowName = "WindowsAddons";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, className, windowName,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
        return 0;
    // Vcruntime button
    std::cout << "Debug :  Creating Vcruntime GUI button..." << std::endl;
    HWND button = CreateWindow("BUTTON", "Download VCRUNTIME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 300, 80, 200, 50, hwnd, (HMENU)2, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Msvcp button
    std::cout << "Debug :  Creating MSVCP GUI button..." << std::endl;
    HWND button3 = CreateWindow("BUTTON", "Download MSVCP", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 300, 160, 200, 50, hwnd, (HMENU)8, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Exit button
    std::cout << "Debug :  Creating Exit GUI button..." << std::endl;
    HWND button1 = CreateWindow("BUTTON", "Exit", WS_ACTIVECAPTION | WS_BORDER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 300, 400, 200, 50, hwnd, (HMENU)3, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Menu
    std::cout << "Debug :  Creating menu GUI options..." << std::endl;
    HMENU aboutmenu = CreateMenu();
    HMENU cursormenu = CreateMenu();
    HMENU subcmenu1 = CreatePopupMenu();
    HMENU subamenu = CreatePopupMenu();
    std::cout << "Debug :  Adding menu GUI options..." << std::endl;
    AppendMenu(cursormenu, MF_STRING | MF_POPUP, (UINT_PTR)subcmenu1, "Cursor");
    AppendMenu(subcmenu1, MF_STRING, 4, "Pointer");
    AppendMenu(subcmenu1, MF_STRING, 5, "Hand");
    AppendMenu(subcmenu1, MF_STRING, 6, "Cross");
    AppendMenu(subcmenu1, MF_STRING, 7, "Uparrow");
    AppendMenu(aboutmenu, MF_STRING | MF_POPUP, (UINT_PTR)subamenu, "About");
    AppendMenu(subamenu, MF_STRING, 1, "Discord");
    std::cout << "Debug :  Creating main menu GUI option..." << std::endl;
    HMENU mainmenu = CreateMenu();
    std::cout << "Debug :  Adding main menu GUI option..." << std::endl;
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)aboutmenu, "About");
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)cursormenu, "Cursor");
    SetMenu(hwnd, mainmenu);

    ShowWindow(hwnd, nCmdShow);
    // READY
    std::cout << "Debug :  APPLICATION READY" << std::endl;

    // Return values
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}