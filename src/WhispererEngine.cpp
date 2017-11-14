//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"

#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

int main()
{
    py::scoped_interpreter guard{};

    PyRun_SimpleString("import sys;print(sys.version)");
    try
    {
        std::cout << "Initializing server..." << std::endl;
        auto* server = new Server(8888);
        std::cout << "Starting server..." << std::endl;
        server->Start();
        std::cout << "Server started!" << std::endl;

        // Exit if the user enters quit
        std::string line;
        while (std::getline(std::cin, line) && line != "quit")
        {
            std::cout << "Unknown command: '" << line << "'" << std::endl;
        }

        std::cout << "Shutting down..." << std::endl;
        server->Stop();
        std::cout << "Bye!" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    Py_Finalize();
}
