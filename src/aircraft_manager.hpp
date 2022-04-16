#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = std::vector<std::unique_ptr<Aircraft>>();
    
public:
    AircraftManager() {}
    bool move() override;
    void add_aircraft(Aircraft* aircraft);  
};