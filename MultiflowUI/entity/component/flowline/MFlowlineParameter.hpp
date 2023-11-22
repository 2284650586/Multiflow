#pragma once

struct MFlowlineParameter {
    MFlowlineParameter(double hd1, double elevation, double hd2, double temperature)
        : hd1(hd1),
          elevation(elevation),
          hd2(hd2),
          temperature(temperature)
    {
    }

    const double hd1;
    const double elevation;
    const double hd2;
    const double temperature;
};
