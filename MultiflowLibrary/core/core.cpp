#include "core.h"

#include <stdexcept>

#include <QDebug>

ML::MultiflowLibrary()
{
    throw std::runtime_error(
        "Wrong use of MultiflowLibrary: call static methods directly instead.");
}

void ML::initialize()
{
    qDebug() << "Multiflow Core Library Initialized.";
}

int ML::add(int x, int y)
{
    return x + y;
}
