#pragma once

#include <QDialog>
#include "..\entity\MFlowline.hpp"

class QStandardItemModel;
class QTableView;
class QScrollArea;
class QLabel;
class QLineEdit;
class QComboBox;
class QChartView;
class QLineSeries;
class QScatterSeries;

class MFlowlineDialog : public QDialog {
    Q_OBJECT

public:
    MFlowlineDialog(MFlowline* flowline, QString name, QWidget* parent = nullptr);

    ~MFlowlineDialog();

private slots:
    void acceptDialog();

    void rejectDialog();

    void updateChartFromTable();

    void createTableModel();

    void addRow();

    void deleteRow();

    void importFromCsv();

    void exportToCsv();

private:
    void setupUI();

    void updateDialogFromMFlowline();

    void updateMFlowlineFromDialog();

    void updateName();

    MFlowline* _flowline{}; // 指向MFlowline对象的指针
    QString mName;

    QLabel* flowlineNameLabel;
    QLineEdit* flowlineNameLineEdit;

    QLabel* flowlineTypeLabel;
    QComboBox* flowlineTypeComboBox;

    QLabel* flowlineModeLabel;
    QComboBox* flowlineModeComboBox;

    QLabel* flowlineEnvLabel;
    QComboBox* flowlineEnvComboBox;

    QLabel* pipInsideDiameterLabel;
    QLineEdit* pipInsideDiameterLineEdit;

    QLabel* pipWallThicknessLabel;
    QLineEdit* pipWallThicknessLineEdit;

    QLabel* pipeRoughnessLabel;
    QLineEdit* pipeRoughnessLineEdit;

    QLabel* profileHorizontalDistanceLabel;
    QLineEdit* profileHorizontalDistanceLineEdit;

    QLabel* profileElevationDifferenceLabel;
    QLineEdit* profileElevationDifferenceLineEdit;

    QLabel* heatTransferCoefficientLabel;
    QLineEdit* heatTransferCoefficientLineEdit;

    QScrollArea* scrollArea;
    QTableView* tableView;
    QPushButton* addRowButton;
    QPushButton* deleteRowButton;
    QPushButton* importButton;
    QPushButton* exportButton;

    QStandardItemModel* dataModel;

    QPushButton* okButton;
    QPushButton* cancelButton;

    QChartView* chartView;
    QLineSeries* lineSeries;
    QScatterSeries* scatterSeries;

public:
    QString getName();
};
