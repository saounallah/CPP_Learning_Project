#pragma once
#include "aircraft_manager.hpp"
#include "aircraft_factory.hpp"
#include "GL/opengl_interface.hpp"
#include "config.hpp"

struct ContextInitializer
{
public:
    ContextInitializer(int argc, char** argv)
    {
        MediaPath::initialize(argv[0]);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
};

class Airport;
struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    ContextInitializer initializer;
    Airport* airport = nullptr;
    AircraftManager* aircraftManager;
    AircraftFactory* aircraft_factory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_aircraft() const;
    void create_keystrokes() const;
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
