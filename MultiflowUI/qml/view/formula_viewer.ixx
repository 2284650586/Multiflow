//
// Created by miku on 11/7/2023.
//

module;

#include "formula_viewer.moc"
#include "shared.hpp"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QUrl>

export module formula_viewer;

import qml_formula;

export namespace qml {

export class WindowFormulaViewer : public QObject {
Q_OBJECT

    Q_PROPERTY(QVariantList formulae READ formulae NOTIFY onFormulaeUpdated)
    Q_PROPERTY(int selectedFormulaIndex MEMBER _selectedFormulaIndex NOTIFY onSelectFormula)

public:
    explicit WindowFormulaViewer(QObject* parent = nullptr) {
        // Wrap Formula in QmlFormula.
        std::transform(
            gFormulae.begin(), gFormulae.end(), std::back_inserter(_qmlFormulae),
            [](const auto& formula) { return QmlFormula{formula}; });

        gpQmlApplicationEngine->rootContext()->setContextProperty(
            "vmFormulaViewer", this);

        // Window shows as the engine loads.
        gpQmlApplicationEngine->load(QUrl("qrc:/qml/components/window/FormulaViewer.qml"));
    }

    ~WindowFormulaViewer() override = default;

    QVariantList formulae() const {
        QVariantList ret{};
        for (const QmlFormula& f: _qmlFormulae) {
            ret << QVariant::fromValue(f);
        }
        return ret;
    }

private:
    QVector<QmlFormula> _qmlFormulae;
    int _selectedFormulaIndex = -1;

signals:

    void onSelectFormula(int index);

    void onFormulaeUpdated();
};

}
