#include <chrono>
#include <iostream>
#include <thread>
#include <Reloadable.hpp>

#include <jet/live/Live.hpp>
#include <jet/live/Utility.hpp>

class SimpleCallbackLogger : public jet::ILiveListener
{
public:
    void onCodePreLoad() override
    {
        std::cout << "    Preloading callback" << std::endl;
    }

    void onCodePostLoad() override
    {
        std::cout << "    Postloading callback" << std::endl;
    }
};

int main(int argc, char** argv)
{
    auto* reloadable = new Reloadable;

    jet::Live live(jet::make_unique<SimpleCallbackLogger>(), {});

    auto startTime = std::chrono::steady_clock::now();

    std::cout << "Running update cycle for 30 seconds. Change sources and see output" << std::endl;
    while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(30))
    {
        live.update();
        if (live.tryReload())
        {
            std::cout << "    Reloading started" << std::endl;
        }

        std::cout << "Returned value: " << reloadable->getValue() << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Time's up. Finishing" << std::endl;

    delete reloadable;
}