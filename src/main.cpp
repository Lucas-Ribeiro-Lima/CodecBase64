#include <iostream>

#include "ArgParser.h"
#include "CodexManager.h"


int main(int argc, char* argv[])
{
    ArgParser options{argc, argv};

    if (options.hasError()) return -1;

    std::cout
        << " =========== Codex =========== \n"
        << "Mode: " << (options.isDecode() ? "Decode" : "Encode")
        << std::endl;

    CodexManager codex(options);
    try
    {
        codex.process();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "Finishing execution" << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
    }

    return 0;
}
