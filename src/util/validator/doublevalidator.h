#ifndef DOUBLEVALIDATOR_H
#define DOUBLEVALIDATOR_H

#include <QValidator>

class DoubleValidator : public QValidator
{
public:
    DoubleValidator(QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override
    {
        Q_UNUSED(pos);

        if (input.isEmpty())
            return Intermediate; // 允许为空

        bool isDouble = false;
        input.toDouble(&isDouble);

        return isDouble ? Acceptable : Invalid;
    }
};

#endif // DOUBLEVALIDATOR_H
