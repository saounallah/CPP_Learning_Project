#include "aircraft_manager.hpp"
#include <algorithm>

bool AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),[](std::unique_ptr<Aircraft>& aircraft)
                    { return !aircraft->move() || aircraft->get_fuel() == 0; }),
                    aircrafts.end());
}

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}
