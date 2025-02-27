#include "aircraft_manager.hpp"
#include <algorithm>

bool AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
        [](std::unique_ptr<Aircraft>& aircraft1, std::unique_ptr<Aircraft>& aircraft2)
        {
            if (aircraft1->has_terminal() && aircraft2->has_terminal())
            {
                return aircraft1->get_fuel() < aircraft2->get_fuel();
            }
            if (aircraft1->has_terminal())
            {
                return true;
            }
            if (aircraft2->has_terminal())
            {
                return false;
            }
            return aircraft1->get_fuel() < aircraft2->get_fuel();
        });
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),[](std::unique_ptr<Aircraft>& aircraft)
                    { return !aircraft->move() || aircraft->get_fuel() == 0; }),
                    aircrafts.end());
}

void AircraftManager::add_aircraft(Aircraft* aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

int AircraftManager::get_required_fuel() const
{
    return std::reduce(aircrafts.begin(), aircrafts.end(), 0,
                           [](int acc, const std::unique_ptr<Aircraft>& cur)
                           {
                               if (!cur->is_low_on_fuel() || cur->is_served())
                                   return acc;
                               return acc + 3000 - cur->get_fuel();
                           });
}
