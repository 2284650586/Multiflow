#pragma once

#include <QMainWindow>

class MWell;
class QStandardItemModel;
class ReadOnlyDelegate;
class GradeDelegate;
class GeometryDelegate;
class CompVIPRDelegate;
class CompHIPRDelegate;
class QGraphicsScene;
class QLabel;
class QComboBox;
class QLineEdit;

struct cement {
    double cementTop = 0x7FFFFFF;
    double cementDensity = 0x7FFFFFF;
    double cementThermal = 0x7FFFFFF;
};

struct fluid {
    QString fluidType = "";
    double fluidDensity = 0x7FFFFFF;
    double fluidThermal = 0x7FFFFFF;
};


namespace Ui {
class MWellWindow;
}

class MWellWindow : public QMainWindow {
    Q_OBJECT

public:
    MWellWindow(MWell* well, QString name, QWidget* parent = nullptr);

    ~MWellWindow();

private:
    QString mName;
    MWell* mWell;

    QStandardItemModel* casingModel;
    QStandardItemModel* tubingModel;
    QStandardItemModel* packerModel;
    QStandardItemModel* gasLiftModel;
    QStandardItemModel* pumpModel;
    QStandardItemModel* compHModel;
    QStandardItemModel* compVModel;
    QStandardItemModel* twoDModel;
    QStandardItemModel* threeDModel;

    QStandardItemModel* HTCCalculateMode;
    QStandardItemModel* HTCCalATIMultMode;
    QStandardItemModel* UMultATIMultMode;

    ReadOnlyDelegate* readOnlyDelegate;
    GradeDelegate* gradeDelegate;
    GeometryDelegate* geometryDelegate;
    CompVIPRDelegate* compVIPRDelegate;
    CompHIPRDelegate* compHIPRDelegate;

    QMap<int, cement> cementMap;
    QMap<int, fluid> fluidMap;

    QGraphicsScene* scene;

    void drawCasing();

    void removeCasing();

    void initUI();

    void initModel();

    void initConnect();

    void initValidator();

    void initStatus();

    void addCasingRow();

    void deleteCasingRow();

    void addTubingRow();

    void deleteTubingRow();

    void addPackerRow();

    void deletePackerRow();

    void addGasLiftRow();

    void deleteGasLiftRow();

    void addPumpRow();

    void deletePumpRow();

    void addCompRow();

    void deleteCompRow();

    void add2DRow();

    void delete2DRow();

    void add3DRow();

    void delete3DRow();

    void addHeatRow();

    void deleteHeatRow();

    void handleCasingRowClicked(const QModelIndex& index);

    void handleTubingRowClicked(const QModelIndex& index);

    void handle2DTV(int index);

    void handle3DTV(int index);

    void handleHeadRaionButton();

    void exportToCsv();

    void importFromCsv();

    void setPara();

    void setDeviationSurvey();

    void setTubular();

    void setSubTubular();

    void setFluidType(int index);

    void setPacker();

    void setHeat();

private slots:
    void emitItemNameChange(QString name);

signals:
    void itemNameChange(QString name);

private:
    Ui::MWellWindow* ui;

protected:
    void closeEvent(QCloseEvent* event) override;
};
