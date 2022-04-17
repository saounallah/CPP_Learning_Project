#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <string>
#include <unordered_set>

struct AircraftType;

class AircraftFactory
{
private:

    const std::string airlines[8]          = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::set<std::string> flight_numbers;

public:
    AircraftFactory(){}
    void init_aircraft_types();
    bool exists(const std::string& flight_number) const;
    Aircraft* create_aircraft(Airport* airport, const AircraftType& type);
    Aircraft* create_random_aircraft(Airport* airport);
    void get_airlines(int index);
};

