#pragma once

#include "component\well\mwelldeviation.hpp"
#include "component\well\MWellCasingParameter.hpp"
#include "component/well/MWellTunbing.h"
#include "component\well\MWellPacker.hpp"
#include "component\well\MWellHeat.hpp"

class MWell {
public:
    MWell();

    ~MWell();

    MWellDeviation* getDeviation() const;

    void setDeviation(MWellDeviation* newDeviation);

    void addCasing(MWellCasingParameter* casing) { casingList.append(casing); }
    void addTubing(MWellTunbing* tubing) { tubingList.append(tubing); }
    void addPacker(MWellPacker* packer) { packerList.append(packer); }

    void clearCasingList() {
        qDeleteAll(casingList);
        casingList.clear();
    }

    void clearTubingList() {
        qDeleteAll(tubingList);
        tubingList.clear();
    }

    void clearPackerList() {
        qDeleteAll(packerList);
        packerList.clear();
    }

    int getCasingListCount() { return casingList.count(); }
    int getTubingListCount() { return tubingList.count(); }
    int getPackerListCount() { return packerList.count(); }


    MWellHeat* getHeat() const;

    void setHeat(MWellHeat* newHeat);

private:
    MWellDeviation* deviation = nullptr;
    MWellHeat* heat = nullptr;
    QList<MWellCasingParameter*> casingList;
    QList<MWellTunbing*> tubingList;
    QList<MWellPacker*> packerList;
};
