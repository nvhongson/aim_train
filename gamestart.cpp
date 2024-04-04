#include <iostream>
#include <windows.h>

int main() {
    // Launch the aim training program
    if (!ShellExecute(NULL, "open", "Aim_train.exe", NULL, NULL, SW_SHOWNORMAL)) {
        std::cerr << "Error: Unable to start Aim_train.exe" << std::endl;
        return 1;
    }

    std::cout << "Aim training program started successfully!" << std::endl;

    return 0;
}
