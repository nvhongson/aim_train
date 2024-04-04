#include <iostream>
#include <windows.h>

// Function to draw a crosshair at the specified coordinates with the specified color
void drawCrosshair(HDC hdc, int x, int y, COLORREF color) {
    // Set color
    SetDCPenColor(hdc, color);

    // Draw horizontal line
    MoveToEx(hdc, x - 10, y, NULL);
    LineTo(hdc, x + 10, y);

    // Draw vertical line
    MoveToEx(hdc, x, y - 10, NULL);
    LineTo(hdc, x, y + 10);
}

// Callback function to handle mouse messages
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_LBUTTONDOWN) {
            std::cout << "Left mouse button clicked!" << std::endl;
        } else if (wParam == WM_RBUTTONDOWN) {
            std::cout << "Right mouse button clicked!" << std::endl;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Set up mouse hook
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

    // Get device context for the entire screen
    HDC hdc = GetDC(NULL);

    // Main loop to draw the crosshair and handle messages
    MSG msg;
    COLORREF crosshairColor = RGB(255, 0, 0); // Initial color is red

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_MOUSEMOVE) {
            // Get mouse coordinates
            int mouseX = LOWORD(msg.lParam);
            int mouseY = HIWORD(msg.lParam);

            // Erase previous crosshair by redrawing the background (white)
            PatBlt(hdc, mouseX - 11, mouseY - 11, 22, 22, WHITENESS);

            // Draw crosshair at current mouse position with the current color
            drawCrosshair(hdc, mouseX, mouseY, crosshairColor);
        } else if (msg.message == WM_KEYDOWN) {
            // Change crosshair color when 'C' key is pressed
            if (msg.wParam == 'C') {
                // Randomize color
                crosshairColor = RGB(rand() % 256, rand() % 256, rand() % 256);
            }
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Release device context and unhook mouse hook
    ReleaseDC(NULL, hdc);
    UnhookWindowsHookEx(mouseHook);

    return 0;
}
