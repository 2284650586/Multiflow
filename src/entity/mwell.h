#ifndef MWELL_H
#define MWELL_H

#include "component/well/mwelldeviation.h"
#include "component/well/mwellcasing.h"
#include "component/well/mwelltunbing.h"
#include "component/well/mwellpacker.h"
#include "component/well/mwellheat.h"

class MWell
{
public:
    MWell();
    ~MWell();

    MWellDeviation *getDeviation() const;
    void setDeviation(MWellDeviation *newDeviation);

    void addCasing(MWellCasing *casing) { casingList.append(casing); }
    void addTubing(MWellTunbing *tubing) { tubingList.append(tubing); }
    void addPacker(MWellPacker *packer) { packerList.append(packer); }

    void clearCasingList() { qDeleteAll(casingList); casingList.clear(); }
    void clearTubingList() { qDeleteAll(tubingList); tubingList.clear(); }
    void clearPackerList() { qDeleteAll(packerList); packerList.clear(); }

    int getCasingListCount() { return casingList.count(); }
    int getTubingListCount() { return tubingList.count(); }
    int getPackerListCount() { return packerList.count(); }



    MWellHeat *getHeat() const;

    void setHeat(MWellHeat *newHeat);

private:
    MWellDeviation *deviation = nullptr;
    MWellHeat *heat = nullptr;
    QList<MWellCasing*> casingList;
    QList<MWellTunbing*> tubingList;
    QList<MWellPacker*> packerList;
};

#endif // MWELL_H
