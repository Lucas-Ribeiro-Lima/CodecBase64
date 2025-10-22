#include <iostream>

#include "ArgParser.h"
#include "CodexManager.h"


int main(int argc, char* argv[])
{
    ArgParser options{argc, argv};

    if (options.hasError()) return -1;

    CodexManager codex(options);
    try
    {
        codex.execute();
    }
    catch (...)
    {
        return -2;
    }

    return 0;
}
