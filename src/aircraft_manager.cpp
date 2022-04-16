#include "aircraft_manager.hpp"
#include <algorithm>
bool AircraftManager::move()
{
    auto toDelete = std::remove_if(aircrafts.begin(), aircrafts.end(), [](const auto& item) { return item->move(); });
    aircrafts.erase(toDelete, aircrafts.end());
    return true;
}

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}
