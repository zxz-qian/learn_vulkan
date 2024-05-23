#include <vulkan/vulkan.h>

#include "iostream"
#include "stdexcept"
#include "cstdlib"
#include "Application.hpp"

int main()
{
    Application app;

    try
    {
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}