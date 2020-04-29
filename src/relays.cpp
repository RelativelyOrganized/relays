#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

#include "./simulation.h"

using namespace Relays;

bool _quit = false;

void leave(int /*signal_value*/)
{
    _quit = true;
}

int main(int /*argc*/, char** /*argv*/)
{
    struct sigaction signals;
    signals.sa_handler = leave;
    signals.sa_flags = 0;
    sigaction(SIGINT, &signals, nullptr);
    sigaction(SIGTERM, &signals, nullptr);

    std::cout << "Running a default (empty...) circuit\n";

    auto simulation = Simulation();
    simulation.run();

    while (!_quit)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "Stopping the simulation...\n";
    simulation.stop();
    std::cout << "Simulation stopped\n";

    return 0;
}
