#include "aircraft_manager.hpp"

bool AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            if ((*it)->move())
            {
                it = aircrafts.erase(it);
            }
            else
            {
                ++it;
            }
        }
        return true;
}

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}
