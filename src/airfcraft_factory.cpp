#include "aircraft_factory.hpp"

#include "airport_type.hpp"
#include "geometry.hpp"

#include <cassert>
#include <cstdlib>
#include <string>

void AircraftFactory::init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .1f, .04f, MediaPath { "concorde_af.png" } };
}

bool AircraftFactory::exists(const std::string& flight_number) const
{
    return flight_numbers.find(flight_number) != flight_numbers.end();
}

Aircraft* AircraftFactory::create_aircraft(Airport* airport, const AircraftType& type)
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    
    while (exists(flight_number))
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport->get_tower() };
    return aircraft;
}  
    
Aircraft* AircraftFactory::create_random_aircraft(Airport* airport)
{
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}

void AircraftFactory::get_airlines(int index)
{
    assert(index>=0 && "invalide input égale à 0") ;
    assert(index<8 && "invalide input supèrieure à 7");
    std::cout << airlines[index] << " : "
              << std::count_if(flight_numbers.begin(), flight_numbers.end(),
                               [this, index](std::string flight)
                               { return airlines[index].compare(0, 2, flight, 0, 2) == 0; })
              << std::endl;
}