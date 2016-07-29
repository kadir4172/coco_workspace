#include "../Classes/AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;
    std::cout << "appdelegate adresi:" << &app << std::endl;
    std::cout << "application adresi:" << Application::getInstance() << std::endl;
    std::cout << "Oyun baslatiliyor" << std::endl;
    return Application::getInstance()->run();
}
