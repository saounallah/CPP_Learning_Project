#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    initializer { ContextInitializer(argc, argv) },
    aircraft_factory { new AircraftFactory() }
{
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}
void TowerSimulation::create_aircraft() const
{
    Aircraft* aircraft = aircraft_factory->create_random_aircraft(airport);
    aircraftManager->add_aircraft(aircraft);
}
void TowerSimulation::create_keystrokes() const
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); }); 
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    GL::keystrokes.emplace('a', []() { GL::framerate_increase();; });
    GL::keystrokes.emplace('d', []() { GL::framerate_decrease(); });
    GL::keystrokes.emplace('p', []() { GL::framerate_pause(); });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& ks_pair : GL::keystrokes)
    {
        std::cout << ks_pair.first << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    
    GL::Displayable::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
    GL::move_queue.emplace(&aircraftManager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();

    GL::loop();
}
