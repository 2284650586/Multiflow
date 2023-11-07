//
// Created by miku on 11/6/2023.
//

#include "qml_formula.hpp"

QmlFormula::QmlFormula(const ml::Formula& formula)
    : _formula(formula), _name(formula.name().c_str()),
      _description(formula.description().c_str()),
      _expression(formula.expression()) {

}
