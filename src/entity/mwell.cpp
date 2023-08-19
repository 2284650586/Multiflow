#include "mwell.h"

MWell::MWell()
{
    
}

MWell::~MWell()
{
    if (deviation != nullptr) {
        delete deviation;
        deviation = nullptr;
    }
    if (heat != nullptr) {
        delete heat;
        heat = nullptr;
    }
    qDeleteAll(casingList);
    qDeleteAll(tubingList);
    qDeleteAll(packerList);
}

MWellDeviation *MWell::getDeviation() const
{
    return deviation;
}

void MWell::setDeviation(MWellDeviation *newDeviation)
{
    deviation = newDeviation;
}

MWellHeat *MWell::getHeat() const
{
    return heat;
}

void MWell::setHeat(MWellHeat *newHeat)
{
    heat = newHeat;
}
