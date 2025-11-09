#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>

class Console {
    public:
        Console();

        static void clearConsole();
        static void waitForKeyPress();
        static void showInfoMessage(const std::string &message);
        static void showInfoMessage(const char* message);

    private:
    
};

#endif // CONSOLE_H