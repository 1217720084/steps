#include "header/power_system_database.h"
#include "header/device/device.h"
#include <istream>
#include <iostream>

using namespace std;

DEVICE::DEVICE(STEPS& toolkit)
{
    set_toolkit(toolkit);
    ownership.clear();
}

DEVICE::~DEVICE()
{
    ;
}

void DEVICE::set_toolkit(STEPS& toolkit)
{
    this->toolkit = (&toolkit);
}

STEPS& DEVICE::get_toolkit() const
{
    return (*toolkit);
}

void DEVICE::set_ownership(const OWNERSHIP& os)
{
    this->ownership = os;
}

OWNERSHIP DEVICE::get_ownership() const
{
    return this->ownership;
}

unsigned int DEVICE::get_owner_count() const
{
    return ownership.get_owner_count();
}

unsigned int DEVICE::get_owner_of_index(unsigned int index) const
{
    return ownership.get_owner_of_index(index);
}

double DEVICE::get_fraction_of_owner_of_index(unsigned int index) const
{
    return ownership.get_fraction_of_owner_of_index(index);
}

string DEVICE::get_device_name() const
{
    return get_device_id().get_device_name();
}
