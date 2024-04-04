#include <iostream>
#include <windows.h>

// Function to draw a crosshair at the specified coordinates
void drawCrosshair(HDC hdc, int x, int y) {
    // Draw horizontal line
    MoveToEx(hdc, x - 10, y, NULL);
    LineTo(hdc, x + 10, y);

    // Draw vertical line
    MoveToEx(hdc, x, y - 10, NULL);
    LineTo(hdc, x, y + 10);
}

// Function to generate a random number within a specified range
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // Set up mouse hook
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, NULL, NULL, 0);

    // Get device context for the entire screen
    HDC hdc = GetDC(NULL);

    // Main loop to draw the crosshair and handle messages
    MSG msg;
    COLORREF crosshairColor = RGB(255, 0, 0); // Initial color is red

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_MOUSEMOVE) {
            // Erase previous crosshair by redrawing the background (white)
            PatBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WHITENESS);

            // Generate random coordinates for the crosshair
            int mouseX = randomInRange(0, GetSystemMetrics(SM_CXSCREEN));
            int mouseY = randomInRange(0, GetSystemMetrics(SM_CYSCREEN));

            // Draw crosshair at current random position with the current color
            drawCrosshair(hdc, mouseX, mouseY);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Release device context and unhook mouse hook
    ReleaseDC(NULL, hdc);
    UnhookWindowsHookEx(mouseHook);

    return 0;
}
