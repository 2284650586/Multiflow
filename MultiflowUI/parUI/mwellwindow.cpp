#include "mwellwindow.h"
#include "ui_mwellwindow.h"
#include "entity/mwell.h"
#include "util/delegate/readonlydelegate.h"
#include "util/delegate/gradedelegate.h"

#include <QGroupBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <util/delegate/comphiprdelegate.h>
#include <util/delegate/compviprdelegate.h>
#include <util/delegate/geometrydelegate.h>

MWellWindow::MWellWindow(MWell* well, QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWellWindow)
{
    _well = well;
    mName = name;
    ui->setupUi(this);
    this->resize(1350, 700);

    ui->wellNameLineEdit->setText(mName);
    readOnlyDelegate = new ReadOnlyDelegate(this);
    gradeDelegate = new GradeDelegate(this);
    geometryDelegate = new GeometryDelegate(this);
    compVIPRDelegate = new CompVIPRDelegate(this);
    compHIPRDelegate = new CompHIPRDelegate(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    QGraphicsPixmapItem *wellHeat = new QGraphicsPixmapItem(QPixmap(":/resources/image/header.png"));

    wellHeat->setPos(-20, -300);
    wellHeat->setScale(0.7);

    scene->addItem(wellHeat);

    initUI();
    initModel();
    initConnect();
    initValidator();
    initStatus();
    initWellData();
}

MWellWindow::~MWellWindow()
{
    delete ui;
}

void MWellWindow::initUI()
{
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    ui->tabWidget->setTabText(0, "General");
    ui->tabWidget->setTabText(1, "Deviation survey");
    ui->tabWidget->setTabText(2, "Heat transfer");
    ui->tabWidget->setTabText(3, "Tubulars");
    ui->tabWidget->setTabText(4, "Downhole equipment");
    ui->tabWidget->setTabText(5, "Artificial lift");
    ui->tabWidget->setTabText(6, "Completions");
    ui->tabWidget->setCurrentIndex(0);

    ui->tabWidgetComp->setTabText(0, "Horizontal");
    ui->tabWidgetComp->setTabText(1, "Vertical");
    ui->tabWidgetComp->setCurrentIndex(0);

    ui->surveyStack->setCurrentIndex(0);
    ui->tubularsStack->setVisible(false);

    ui->timeLable->setVisible(false);
    ui->timeLineEdit->setVisible(false);
    ui->heatTV->setVisible(false);
    ui->addRowHeat->setVisible(false);
    ui->deleteRowHeat->setVisible(false);
    ui->importCSVHeat->setVisible(false);
    ui->exportCSVHeat->setVisible(false);


    setStyleSheet(
        "QMainWindow { background-color: #f0f0f0; }" // 设置 QWidget 的背景颜色
        "QLabel { font-weight: bold; color: #333333; }"
        "QLineEdit { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QComboBox { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #367c39; }"
        "QTabView {background-color: #ffffff;}"
        "QTableView { background-color: #ffffff; border: 1px solid #cccccc; }"
        "QHeaderView::section { background-color: #f0f0f0; font-weight: bold; }"
        "QTableView::item:selected { background-color: #a8c8e4; }"
        "QLineEdit:disabled { background-color: lightGray; color: black;}"
        );
}

void MWellWindow::initModel()
{
    casingModel = new QStandardItemModel(this);
    QStringList headerCasing = {"Name", "Grade", "Density (g/cm3)", "Thermal conductivity (W/(m.k))", "To MD (m)", "ID (m)", "Wall thickness (mm)", "Roughness (mm)"};
    casingModel->setHorizontalHeaderLabels(headerCasing);
    ui->casingTV->setModel(casingModel);
    ui->casingTV->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->casingTV->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->casingTV->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    ui->casingTV->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    ui->casingTV->setItemDelegateForColumn(1, gradeDelegate);

    tubingModel = new QStandardItemModel(this);
    QStringList headerTubing = {"Name", "Grade", "Density (g/cm3)", "Thermal conductivity (W/(m.k))", "To MD (m)", "ID (m)", "Wall thickness (mm)", "Roughness (mm)"};
    tubingModel->setHorizontalHeaderLabels(headerTubing);
    ui->tubingTV->setModel(tubingModel);
    ui->tubingTV->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tubingTV->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tubingTV->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    ui->tubingTV->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    ui->tubingTV->setItemDelegateForColumn(1, gradeDelegate);

    packerModel = new QStandardItemModel(this);
    QStringList headerPacker = {"Name", "Measured depth (m)"};
    packerModel->setHorizontalHeaderLabels(headerPacker);
    ui->packerTV->setModel(packerModel);
    ui->packerTV->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    gasLiftModel = new QStandardItemModel(this);
    QStringList headerGasLift = {"Gas lift", "Active", "MD", "Injection basis", "Inj. quantity", "Injection unit", "Port size"};
    gasLiftModel->setHorizontalHeaderLabels(headerGasLift);
    ui->gasTV->setModel(gasLiftModel);

    pumpModel = new QStandardItemModel(this);
    QStringList headerPump = {"Equipment", "Name", "Active", "MD"};
    pumpModel->setHorizontalHeaderLabels(headerPump);
    ui->pumpTV->setModel(pumpModel);

    compHModel = new QStandardItemModel(this);
    QStringList headerCompH = {"Name", "Fluid entry", "Top MD", "Middle MD", "Bottom MD", "IPR model"};
    compHModel->setHorizontalHeaderLabels(headerCompH);
    ui->compHTV->setModel(compHModel);
    ui->compHTV->setItemDelegateForColumn(5, compHIPRDelegate);

    compVModel = new QStandardItemModel(this);
    QStringList headerCompV = {"Name", "Fluid entry", "Top MD", "Middle MD", "Bottom MD", "IPR model"};
    compVModel->setHorizontalHeaderLabels(headerCompV);
    ui->compVTV->setModel(compVModel);
    ui->compVTV->setItemDelegateForColumn(5, compVIPRDelegate);


    twoDModel = new QStandardItemModel(this);
    QStringList header2D = {"MD (m)", "TVD (m)", "Horizontal displacement (m)", "Angle (deg)"};
    twoDModel->setHorizontalHeaderLabels(header2D);
    ui->twoDTV->setModel(twoDModel);
    ui->twoDTV->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    threeDModel = new QStandardItemModel(this);
    QStringList header3D = {"MD (m)", "TVD (m)", "Horizontal displacement (m)", "Angle (deg)", "Azimuth (deg)", "Max. dogleg severity  (deg/m)"};
    threeDModel->setHorizontalHeaderLabels(header3D);
    ui->threeDTV->setModel(threeDModel);
    ui->threeDTV->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->threeDTV->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);

    HTCCalculateMode = new QStandardItemModel(this);
    QStringList headerHTCCal = {"MD (m)", "Ground density (kg/m3)", "Groud k (W/m.K)", "Ground Cp (J/(kg.K))"};
    HTCCalculateMode->setHorizontalHeaderLabels(headerHTCCal);

    HTCCalATIMultMode = new QStandardItemModel(this);
    QStringList headerHTcCalATIMul = {"MD (m)", "Ambient temperature (degC)", "Ground density (kg/m3)", "Ground K (W/(m.K))", "Ground Cp (J/(kg.K))"};
    HTCCalATIMultMode->setHorizontalHeaderLabels(headerHTcCalATIMul);

    UMultATIMultMode = new QStandardItemModel(this);
    QStringList headerUMultATIMult = {"MD (m)", "Ambient temperature (degC)", "U value (J/(s.degC.m2))"};
    UMultATIMultMode->setHorizontalHeaderLabels(headerUMultATIMult);

    ui->heatTV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void MWellWindow::initConnect()
{
    //general connect
    connect(ui->wellNameLineEdit, &QLineEdit::textChanged, this, &MWellWindow::emitItemNameChange);

    //deviation connect
    connect(ui->surveyType, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->surveyStack, &QStackedWidget::setCurrentIndex);

    connect(ui->DP2D, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MWellWindow::handle2DTV);
    connect(ui->DP3D, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MWellWindow::handle3DTV);

    connect(ui->importCSV2D, &QPushButton::clicked, this, &MWellWindow::importFromCsv);
    connect(ui->exportCSV2D, &QPushButton::clicked, this, &MWellWindow::exportToCsv);

    connect(ui->addRow2D, &QPushButton::clicked, this, &MWellWindow::add2DRow);
    connect(ui->deleteRow2D, &QPushButton::clicked, this, &MWellWindow::delete2DRow);

    connect(ui->addRow3D, &QPushButton::clicked, this, &MWellWindow::add3DRow);
    connect(ui->deleteRow3D, &QPushButton::clicked, this, &MWellWindow::delete3DRow);

    //tubular connect
    connect(ui->cementDensityLineEdit, &QLineEdit::editingFinished, this, &MWellWindow::setSubTubular);
    connect(ui->cementTopLineEdit, &QLineEdit::editingFinished, this, &MWellWindow::setSubTubular);
    connect(ui->cementThermalLineEdit, &QLineEdit::editingFinished, this, &MWellWindow::setSubTubular);
    connect(ui->FluidTypeCom, &QComboBox::currentIndexChanged, this, &MWellWindow::setFluidType);
    connect(ui->FluidDensityLineEdit, &QLineEdit::editingFinished, this, &MWellWindow::setSubTubular);
    connect(ui->FluidThermalLineEdit, &QLineEdit::editingFinished, this, &MWellWindow::setSubTubular);

    //casing connect
    connect(ui->addRowCasing, &QPushButton::clicked, this, &MWellWindow::addCasingRow);
    connect(ui->deleteRowCasing, &QPushButton::clicked, this, &MWellWindow::deleteCasingRow);
    connect(ui->importCSVCasing, &QPushButton::clicked, this, &MWellWindow::importFromCsv);
    connect(ui->exportCSVCasing, &QPushButton::clicked, this, &MWellWindow::exportToCsv);
    connect(ui->casingTV, &QTableView::clicked, this, &MWellWindow::handleCasingRowClicked);

    //tubing connect
    connect(ui->addRowTubing, &QPushButton::clicked, this, &MWellWindow::addTubingRow);
    connect(ui->deleteRowTubing, &QPushButton::clicked, this, &MWellWindow::deleteTubingRow);
    connect(ui->importCSVTubing, &QPushButton::clicked, this, &MWellWindow::importFromCsv);
    connect(ui->exportCSVTubing, &QPushButton::clicked, this, &MWellWindow::exportToCsv);
    connect(ui->tubingTV, &QTableView::clicked, this, &MWellWindow::handleTubingRowClicked);

    //packer connect
    connect(ui->addRowPacker, &QPushButton::clicked, this, &MWellWindow::addPackerRow);
    connect(ui->deleteRowPacker, &QPushButton::clicked, this, &MWellWindow::deletePackerRow);
    connect(ui->importCSVPacker, &QPushButton::clicked, this, &MWellWindow::importFromCsv);
    connect(ui->exportCSVPacker, &QPushButton::clicked, this, &MWellWindow::exportToCsv);

    //Heat Transfer connect
    connect(ui->HTCSpecify, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);
    connect(ui->HTCCalculate, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);
    connect(ui->USingle, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);
    connect(ui->UMultiple, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);
    connect(ui->ATISingle, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);
    connect(ui->ATIMultiple, &QRadioButton::clicked, this, &MWellWindow::handleHeadRaionButton);

    connect(ui->addRowHeat, &QPushButton::clicked, this, &MWellWindow::addHeatRow);
    connect(ui->deleteRowHeat, &QPushButton::clicked, this, &MWellWindow::deleteHeatRow);
    connect(ui->importCSVHeat, &QPushButton::clicked, this, &MWellWindow::importFromCsv);
    connect(ui->exportCSVHeat, &QPushButton::clicked, this, &MWellWindow::exportToCsv);

    //Component
    connect(ui->addRowCompH, &QPushButton::clicked, this, &MWellWindow::addCompRow);
    connect(ui->deleteRowCompH, &QPushButton::clicked, this, &MWellWindow::deleteCompRow);
    connect(ui->addRowCompV, &QPushButton::clicked, this, &MWellWindow::addCompRow);
    connect(ui->deleteRowCompV, &QPushButton::clicked, this, &MWellWindow::deleteCompRow);

    //other
    connect(ui->addRowGasLeft, &QPushButton::clicked, this, &MWellWindow::addGasLiftRow);
    connect(ui->deleteRowGasLeft, &QPushButton::clicked, this, &MWellWindow::deleteGasLiftRow);

    connect(ui->addRowPump, &QPushButton::clicked, this, &MWellWindow::addPumpRow);
    connect(ui->deleteRowPump, &QPushButton::clicked, this, &MWellWindow::deletePumpRow);

}

void MWellWindow::initWellData()
{
    if (_well->getDeviation() == nullptr) {
        _well->setDeviation(new MWellDeviation());
    }
    if (_well->getHeat() == nullptr) {
        _well->setHeat(new MWellHeat());
    }
}

void MWellWindow::initValidator()
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setDecimals(15);

    ui->WDVertical->setValidator(doubleValidator);
    ui->WD2D->setValidator(doubleValidator);
    ui->WD3D->setValidator(doubleValidator);

}

void MWellWindow::initStatus()
{
    handle2DTV(0);
    handle3DTV(0);
}

void MWellWindow::addCasingRow()
{
    int newRow = casingModel->rowCount();
    casingModel->insertRow(newRow);
    drawCasing();
}

void MWellWindow::deleteCasingRow()
{
    QModelIndexList selectedRows = ui->casingTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        casingModel->removeRow(rowToDelete);
        cementMap.remove(rowToDelete);
    }
    removeCasing();
}

void MWellWindow::drawCasing()
{

}

void MWellWindow::removeCasing()
{

}

void MWellWindow::addTubingRow()
{
    int newRow = tubingModel->rowCount();
    tubingModel->insertRow(newRow);
}

void MWellWindow::deleteTubingRow()
{
    QModelIndexList selectedRows = ui->tubingTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        tubingModel->removeRow(rowToDelete);
        fluidMap.remove(rowToDelete);
    }
}

void MWellWindow::addPackerRow()
{
    int newRow = packerModel->rowCount();
    packerModel->insertRow(newRow);
}

void MWellWindow::deletePackerRow()
{
    QModelIndexList selectedRows = ui->packerTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        packerModel->removeRow(rowToDelete);
    }
}

void MWellWindow::addGasLiftRow()
{
    int newRow = gasLiftModel->rowCount();
    gasLiftModel->insertRow(newRow);
}

void MWellWindow::deleteGasLiftRow()
{
    QModelIndexList selectedRows = ui->gasTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        gasLiftModel->removeRow(rowToDelete);
    }
}

void MWellWindow::addPumpRow()
{
    int newRow = pumpModel->rowCount();
    pumpModel->insertRow(newRow);
}

void MWellWindow::deletePumpRow()
{
    QModelIndexList selectedRows = ui->pumpTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        pumpModel->removeRow(rowToDelete);
    }
}

void MWellWindow::addCompRow()
{
    if (ui->tabWidgetComp->currentIndex() == 0) {
        int newRow = compHModel->rowCount();
        compHModel->insertRow(newRow);
    }
    if (ui->tabWidgetComp->currentIndex() == 1) {
        int newRow = compVModel->rowCount();
        compVModel->insertRow(newRow);
    }
}

void MWellWindow::deleteCompRow()
{
    if (ui->tabWidgetComp->currentIndex() == 0) {
        QModelIndexList selectedRows = ui->compHTV->selectionModel()->selectedRows();
        if (!selectedRows.isEmpty())
        {
            int rowToDelete = selectedRows.first().row();
            compHModel->removeRow(rowToDelete);
        }
    }
    if (ui->tabWidgetComp->currentIndex() == 1) {
        QModelIndexList selectedRows = ui->compVTV->selectionModel()->selectedRows();
        if (!selectedRows.isEmpty())
        {
            int rowToDelete = selectedRows.first().row();
            compVModel->removeRow(rowToDelete);
        }
    }
}

void MWellWindow::add2DRow()
{
    int newRow = twoDModel->rowCount();
    twoDModel->insertRow(newRow);
}

void MWellWindow::delete2DRow()
{
    QModelIndexList selectedRows = ui->twoDTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        twoDModel->removeRow(rowToDelete);
    }
}

void MWellWindow::add3DRow()
{
    int newRow = threeDModel->rowCount();
    threeDModel->insertRow(newRow);
}

void MWellWindow::delete3DRow()
{
    QModelIndexList selectedRows = ui->threeDTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty())
    {
        int rowToDelete = selectedRows.first().row();
        threeDModel->removeRow(rowToDelete);
    }
}

void MWellWindow::addHeatRow()
{
    QStandardItemModel *currentModel = dynamic_cast<QStandardItemModel*>(ui->heatTV->model());
    if (currentModel == HTCCalculateMode) {
        int newRow = HTCCalculateMode->rowCount();
        HTCCalculateMode->insertRow(newRow);
    }
    if (currentModel == HTCCalATIMultMode) {
        int newRow = HTCCalATIMultMode->rowCount();
        HTCCalATIMultMode->insertRow(newRow);
    }
    if (currentModel == UMultATIMultMode) {
        int newRow = UMultATIMultMode->rowCount();
        HTCCalculateMode->insertRow(newRow);
    }
}

void MWellWindow::deleteHeatRow()
{
    QStandardItemModel *currentModel = dynamic_cast<QStandardItemModel*>(ui->heatTV->model());
    QModelIndexList selectedRows = ui->heatTV->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        if (currentModel == HTCCalculateMode) {
            int rowToDelete = selectedRows.first().row();
            HTCCalculateMode->removeRow(rowToDelete);
        }
        if (currentModel == HTCCalATIMultMode) {
            int rowToDelete = selectedRows.first().row();
            HTCCalATIMultMode->removeRow(rowToDelete);
        }
        if (currentModel == UMultATIMultMode) {
            int rowToDelete = selectedRows.first().row();
            UMultATIMultMode->removeRow(rowToDelete);
        }
    }
}

void MWellWindow::handleCasingRowClicked(const QModelIndex &index)
{
    ui->tubularsStack->setVisible(true);
    ui->tubularsStack->setCurrentIndex(0);

    ui->cementDensityLineEdit->clear();
    ui->cementThermalLineEdit->clear();
    ui->cementTopLineEdit->clear();

    if (cementMap.contains(index.row())) {
        cement temp = cementMap[index.row()];
        if (temp.cementTop != 0x7FFFFFF) ui->cementTopLineEdit->setText(QString::number(temp.cementTop));
        if (temp.cementDensity != 0x7FFFFFF) ui->cementDensityLineEdit->setText(QString::number(temp.cementDensity));
        if (temp.cementThermal != 0x7FFFFFF) ui->cementThermalLineEdit->setText(QString::number(temp.cementThermal));
    } else {
        cement temp;
        cementMap.insert(index.row(), temp);
    }
}

void MWellWindow::handleTubingRowClicked(const QModelIndex &index)
{
    ui->tubularsStack->setVisible(true);
    ui->tubularsStack->setCurrentIndex(1);

    ui->FluidDensityLineEdit->clear();
    ui->FluidThermalLineEdit->clear();
    ui->FluidTypeCom->setCurrentIndex(0);

    if (fluidMap.contains(index.row())) {
        fluid temp = fluidMap[index.row()];
        if (temp.fluidType != "") ui->FluidTypeCom->setCurrentText(temp.fluidType);
        if (temp.fluidDensity != 0x7FFFFFF) ui->FluidDensityLineEdit->setText(QString::number(temp.fluidDensity));
        if (temp.fluidThermal != 0x7FFFFFF) ui->FluidThermalLineEdit->setText(QString::number(temp.fluidThermal));
    } else {
        fluid temp;
        fluidMap.insert(index.row(), temp);
    }
}

void MWellWindow::handle2DTV(int index)
{
    for (int i = 0; i < 4; i++) {
        ui->twoDTV->setItemDelegateForColumn(i, nullptr);
    }
    if (index == 0) {
        ui->twoDTV->setItemDelegateForColumn(0, readOnlyDelegate);
        ui->twoDTV->setItemDelegateForColumn(2, readOnlyDelegate);
    } else if (index == 1) {
        ui->twoDTV->setItemDelegateForColumn(1, readOnlyDelegate);
        ui->twoDTV->setItemDelegateForColumn(2, readOnlyDelegate);
    } else if (index == 2) {
        ui->twoDTV->setItemDelegateForColumn(2, readOnlyDelegate);
        ui->twoDTV->setItemDelegateForColumn(3, readOnlyDelegate);
    }
}

void MWellWindow::handle3DTV(int index)
{
    for (int i = 0; i < 4; i++) {
        ui->threeDTV->setItemDelegateForColumn(i, nullptr);
    }
    if (index == 0) {
        ui->threeDTV->setItemDelegateForColumn(0, readOnlyDelegate);
        ui->threeDTV->setItemDelegateForColumn(2, readOnlyDelegate);
    } else if (index == 1) {
        ui->threeDTV->setItemDelegateForColumn(1, readOnlyDelegate);
        ui->threeDTV->setItemDelegateForColumn(2, readOnlyDelegate);
    } else if (index == 2){
        ui->threeDTV->setItemDelegateForColumn(2, readOnlyDelegate);
        ui->threeDTV->setItemDelegateForColumn(3, readOnlyDelegate);
    }
}

void MWellWindow::handleHeadRaionButton()
{
    ui->ULabel->setVisible(true);
    ui->UGroupBox->setVisible(true);
    ui->timeLable->setVisible(false);
    ui->timeLineEdit->setVisible(false);
    ui->STAWLabel->setVisible(true);
    ui->STAWLineEdit->setVisible(true);
    ui->averageULabel->setVisible(true);
    ui->averageULineEdit->setVisible(true);
    ui->heatTV->setVisible(false);
    ui->heatTV->setModel(nullptr);
    ui->addRowHeat->setVisible(false);
    ui->deleteRowHeat->setVisible(false);
    ui->importCSVHeat->setVisible(false);
    ui->exportCSVHeat->setVisible(false);

    if (ui->HTCCalculate->isChecked() && ui->ATISingle->isChecked()) {
        ui->timeLable->setVisible(true);
        ui->timeLineEdit->setVisible(true);
        ui->ULabel->setVisible(false);
        ui->UGroupBox->setVisible(false);
        ui->averageULabel->setVisible(false);
        ui->averageULineEdit->setVisible(false);
        ui->heatTV->setVisible(true);
        ui->heatTV->setModel(HTCCalculateMode);
        ui->addRowHeat->setVisible(true);
        ui->deleteRowHeat->setVisible(true);
        ui->importCSVHeat->setVisible(true);
        ui->exportCSVHeat->setVisible(true);
    }
    if (ui->HTCCalculate->isChecked() && ui->ATIMultiple->isChecked()) {
        ui->timeLable->setVisible(true);
        ui->timeLineEdit->setVisible(true);
        ui->ULabel->setVisible(false);
        ui->UGroupBox->setVisible(false);
        ui->STAWLabel->setVisible(false);
        ui->STAWLineEdit->setVisible(false);
        ui->averageULabel->setVisible(false);
        ui->averageULineEdit->setVisible(false);
        ui->heatTV->setVisible(true);
        ui->heatTV->setModel(HTCCalATIMultMode);
        ui->addRowHeat->setVisible(true);
        ui->deleteRowHeat->setVisible(true);
        ui->importCSVHeat->setVisible(true);
        ui->exportCSVHeat->setVisible(true);
    }
    if (ui->HTCSpecify->isChecked() && ui->UMultiple->isChecked() && ui->ATIMultiple->isChecked()) {
        ui->averageULabel->setVisible(false);
        ui->averageULineEdit->setVisible(false);
        ui->STAWLineEdit->setVisible(false);
        ui->STAWLabel->setVisible(false);
        ui->heatTV->setVisible(true);
        ui->heatTV->setModel(UMultATIMultMode);
        ui->addRowHeat->setVisible(true);
        ui->deleteRowHeat->setVisible(true);
        ui->importCSVHeat->setVisible(true);
        ui->exportCSVHeat->setVisible(true);
    }
}

void MWellWindow::emitItemNameChange(QString name)
{
    emit itemNameChange(name);
}

void MWellWindow::importFromCsv()
{
    QStandardItemModel *dataModel;
    if (sender()->objectName() == "importCSV2D") dataModel = twoDModel;
    if (sender()->objectName() == "importCSV3D") dataModel = threeDModel;
    if (sender()->objectName() == "importCSVCasing") dataModel = casingModel;
    if (sender()->objectName() == "importCSVTubing") dataModel = tubingModel;
    if (sender()->objectName() == "importCSVPacker") dataModel = packerModel;
    if (sender()->objectName() == "importCSVHeat") {
        QStandardItemModel *currentModel = dynamic_cast<QStandardItemModel*>(ui->heatTV->model());
        if (currentModel == HTCCalculateMode) {
            dataModel = HTCCalculateMode;
        }
        if (currentModel == HTCCalATIMultMode) {
            dataModel = HTCCalATIMultMode;
        }
        if (currentModel == UMultATIMultMode) {
            dataModel = UMultATIMultMode;
        }
    }

    QString filePath = QFileDialog::getOpenFileName(this, "选择CSV文件", "", "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            dataModel->removeRows(0, dataModel->rowCount());
            int row = 0;
            QStringList headerLabels;

            while (!in.atEnd()) {
                QString line = in.readLine();

                // 分割行数据
                QStringList values = line.split(",");

                if (row == 0) {
                    // 如果是第一行，保存表头数据，并将表头与tableView的表头进行比较
                    headerLabels = values;

                    // 检查表头是否与tableView的表头一致
                    if (headerLabels.size() != dataModel->columnCount()) {
                        // 表头列数不匹配，结束导入
                        QMessageBox::warning(this, "错误", "导入的表头与表格列数不匹配，请检查CSV文件的格式。");
                        break;
                    }

                    for (int col = 0; col < headerLabels.size(); ++col) {
                        if (headerLabels.at(col) != dataModel->horizontalHeaderItem(col)->text()) {
                            // 表头内容不匹配，结束导入
                            QMessageBox::warning(this, "错误", "导入的表头与表格表头不匹配，请检查CSV文件的格式。");
                            break;
                        }
                    }
                } else {
                    // 如果不是第一行，将数据导入表格中
                    for (int col = 0; col < values.size(); ++col) {
                        QStandardItem* item = new QStandardItem(values[col]);
                        dataModel->setItem(row - 1, col, item);
                    }
                }
                ++row;
            }
            file.close();
        }
    }
}

void MWellWindow::exportToCsv()
{
    QStandardItemModel *dataModel;
    if (sender()->objectName() == "exportCSV2D") dataModel = twoDModel;
    if (sender()->objectName() == "exportCSV3D") dataModel = threeDModel;
    if (sender()->objectName() == "exportCSVCasing") dataModel = casingModel;
    if (sender()->objectName() == "exportCSVTubing") dataModel = tubingModel;
    if (sender()->objectName() == "exportCSVPacker") dataModel = packerModel;
    if (sender()->objectName() == "exportCSVHeat") {
        QStandardItemModel *currentModel = dynamic_cast<QStandardItemModel*>(ui->heatTV->model());
        if (currentModel == HTCCalculateMode) {
            dataModel = HTCCalculateMode;
        }
        if (currentModel == HTCCalATIMultMode) {
            dataModel = HTCCalATIMultMode;
        }
        if (currentModel == UMultATIMultMode) {
            dataModel = UMultATIMultMode;
        }
    }

    QString filePath = QFileDialog::getSaveFileName(this, "保存CSV文件", "", "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // 写入表头
            QStringList headerLabels;
            for (int col = 0; col < dataModel->columnCount(); ++col) {
                headerLabels.append(dataModel->headerData(col, Qt::Horizontal).toString());
            }
            out << headerLabels.join(",") << "\n";

            // 写入实际数据
            for (int row = 0; row < dataModel->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < dataModel->columnCount(); ++col) {
                    QStandardItem* item = dataModel->item(row, col);
                    if (item) {
                        QString value = item->text();
                        rowData.append(value);
                    } else {
                        // 处理空指针情况，可以插入默认值或者其他处理逻辑
                        rowData.append("");
                    }
                }
                out << rowData.join(",") << "\n";
            }
            file.close();
        }
    }
}

void MWellWindow::setPara()
{
    setDeviationSurvey();
    setTubular();
}

void MWellWindow::setDeviationSurvey()
{
    MWellDeviation *tempDeviation = _well->getDeviation();
    tempDeviation->clearPar();
    if (ui->surveyType->currentText() == "vertical") {
        tempDeviation->setSurVeytype(MWellDeviation::SurveyType::Vertical);
        tempDeviation->setWellHeadDpeth(ui->WDVertical->text().toDouble());
        tempDeviation->setBottomDepth(ui->BDVertical->text().toDouble());
    } else if (ui->surveyType->currentText() == "2D") {
        tempDeviation->setSurVeytype(MWellDeviation::SurveyType::TwoD);
        tempDeviation->setDepType(MWellDeviation::DependentPara(ui->DP2D->currentIndex()));
        tempDeviation->setCalMedthod(ui->CM2D->text());
        tempDeviation->setWellHeadDpeth(ui->WD2D->text().toDouble());
        tempDeviation->setWellHeadDpeth(ui->BD2D->text().toDouble());
        int rowCount = twoDModel->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            MDeviationPar *para = new MDeviationPar();
            if (twoDModel->item(row, 0) != nullptr) para->setMD(twoDModel->item(row, 0)->text().toDouble());
            if (twoDModel->item(row, 1) != nullptr) para->setTVD(twoDModel->item(row, 1)->text().toDouble());
            if (twoDModel->item(row, 2) != nullptr) para->setHorizontalDisplacement(twoDModel->item(row, 2)->text().toDouble());
            if (twoDModel->item(row, 3) != nullptr) para->setAngle(twoDModel->item(row, 3)->text().toDouble());
            if (twoDModel->item(row, 4) != nullptr) para->setAzimuth(twoDModel->item(row, 4)->text().toDouble());
            if (twoDModel->item(row, 5) != nullptr) para->setMaxDog(twoDModel->item(row, 5)->text().toDouble());
            tempDeviation->addPar(para);
        }
    } else if (ui->surveyType->currentText() == "3D") {
        tempDeviation->setSurVeytype(MWellDeviation::SurveyType::ThreeD);
        tempDeviation->setDepType(MWellDeviation::DependentPara(ui->DP3D->currentIndex()));
        tempDeviation->setCalMedthod(ui->CM3D->text());
        tempDeviation->setWellHeadDpeth(ui->WD3D->text().toDouble());
        tempDeviation->setWellHeadDpeth(ui->BD3D->text().toDouble());
        int rowCount = threeDModel->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            MDeviationPar *para = new MDeviationPar();
            if (threeDModel->item(row, 0) != nullptr) para->setMD(threeDModel->item(row, 0)->text().toDouble());
            if (threeDModel->item(row, 1) != nullptr) para->setTVD(threeDModel->item(row, 1)->text().toDouble());
            if (threeDModel->item(row, 2) != nullptr) para->setHorizontalDisplacement(threeDModel->item(row, 2)->text().toDouble());
            if (threeDModel->item(row, 3) != nullptr) para->setAngle(threeDModel->item(row, 3)->text().toDouble());
            if (threeDModel->item(row, 4) != nullptr) para->setAzimuth(threeDModel->item(row, 4)->text().toDouble());
            if (threeDModel->item(row, 5) != nullptr) para->setMaxDog(threeDModel->item(row, 5)->text().toDouble());
            tempDeviation->addPar(para);
        }
    }
}

void MWellWindow::setTubular()
{
    _well->clearCasingList();
    _well->clearTubingList();
    int casingRowCount = casingModel->rowCount();
    int tubingRowCount = tubingModel->rowCount();
    for (int row = 0; row < casingRowCount; ++row) {
        MWellCasing *temp = new MWellCasing();
        if (casingModel->item(row, 0) != nullptr) temp->setName(casingModel->item(row, 0)->text());
        if (casingModel->item(row, 1) != nullptr) temp->setGrade(casingModel->item(row, 1)->text());
        if (casingModel->item(row, 2) != nullptr) temp->setDensity(casingModel->item(row, 2)->text().toDouble());
        if (casingModel->item(row, 3) != nullptr) temp->setThermal(casingModel->item(row, 3)->text().toDouble());
        if (casingModel->item(row, 4) != nullptr) temp->setToMD(casingModel->item(row, 4)->text().toDouble());
        if (casingModel->item(row, 5) != nullptr) temp->setInnerDiameter(casingModel->item(row, 5)->text().toDouble());
        if (casingModel->item(row, 6) != nullptr) temp->setWallThickness(casingModel->item(row, 6)->text().toDouble());
        if (casingModel->item(row, 7) != nullptr) temp->setRoughness(casingModel->item(row, 7)->text().toDouble());
        if (cementMap[row].cementTop != 0x7FFFFFF) temp->setCementTop(cementMap[row].cementTop);
        if (cementMap[row].cementDensity != 0x7FFFFFF) temp->setCementDensity(cementMap[row].cementDensity);
        if (cementMap[row].cementThermal != 0x7FFFFFF) temp->setCementTheramlCond(cementMap[row].cementThermal);
        _well->addCasing(temp);
    }
    for (int row = 0; row < tubingRowCount; ++row) {
        MWellTunbing *temp = new MWellTunbing();
        if (tubingModel->item(row, 0) != nullptr) temp->setName(tubingModel->item(row, 0)->text());
        if (tubingModel->item(row, 1) != nullptr) temp->setGrade(tubingModel->item(row, 1)->text());
        if (tubingModel->item(row, 2) != nullptr) temp->setDensity(tubingModel->item(row, 2)->text().toDouble());
        if (tubingModel->item(row, 3) != nullptr) temp->setThermal(tubingModel->item(row, 3)->text().toDouble());
        if (tubingModel->item(row, 4) != nullptr) temp->setToMD(tubingModel->item(row, 4)->text().toDouble());
        if (tubingModel->item(row, 5) != nullptr) temp->setInnerDiameter(tubingModel->item(row, 5)->text().toDouble());
        if (tubingModel->item(row, 6) != nullptr) temp->setWallThickness(tubingModel->item(row, 6)->text().toDouble());
        if (tubingModel->item(row, 7) != nullptr) temp->setRoughness(tubingModel->item(row, 7)->text().toDouble());
        if (fluidMap[row].fluidType != "") temp->setFluidType(fluidMap[row].fluidType);
        if (fluidMap[row].fluidDensity != 0x7FFFFFF) temp->setFluidDensity(fluidMap[row].fluidDensity);
        if (fluidMap[row].fluidThermal != 0x7FFFFFF) temp->setFluidThermalCond(fluidMap[row].fluidThermal);
        _well->addTubing(temp);
    }
}

void MWellWindow::setSubTubular()
{
    int casingRowIndex = ui->casingTV->currentIndex().row();
    int tubingRowIndex = ui->tubingTV->currentIndex().row();

    if (sender()->objectName() == "cementDensityLineEdit")
        cementMap[casingRowIndex].cementDensity = ui->cementDensityLineEdit->text().toDouble();
    if (sender()->objectName() == "cementTopLineEdit")
        cementMap[casingRowIndex].cementTop = ui->cementTopLineEdit->text().toDouble();
    if (sender()->objectName() == "cementThermalLineEdit")
        cementMap[casingRowIndex].cementThermal = ui->cementThermalLineEdit->text().toDouble();

    if (sender()->objectName() == "FluidDensityLineEdit")
        fluidMap[tubingRowIndex].fluidDensity = ui->FluidDensityLineEdit->text().toDouble();
    if (sender()->objectName() == "FluidThermalLineEdit")
        fluidMap[tubingRowIndex].fluidThermal = ui->FluidThermalLineEdit->text().toDouble();
}

void MWellWindow::setFluidType(int index)
{
    Q_UNUSED(index)
    int tubingRowIndex = ui->tubingTV->currentIndex().row();
    fluidMap[tubingRowIndex].fluidType = ui->FluidTypeCom->currentText();
}

void MWellWindow::setPacker()
{
    _well->clearPackerList();
    int rowCount = packerModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        MWellPacker *packer = new MWellPacker();
        if (packerModel->item(row, 0) != nullptr) packer->setName(packerModel->item(row, 0)->text());
        if (packerModel->item(row, 1) != nullptr) packer->setMeasuredDepth(packerModel->item(row, 1)->text().toDouble());
        _well->addPacker(packer);
    }
}

void MWellWindow::setHeat()
{
    MWellHeat *heat = _well->getHeat();
    heat->clearHtcCalAtiMultList();
    heat->clearUMultAtiMultList();
    heat->clearHtcCalList();

    heat->setTime(ui->timeLineEdit->text().toDouble());
    heat->setAverageUValue(ui->averageULineEdit->text().toDouble());
    heat->setSoilTemperatureWellhead(ui->STAWLineEdit->text().toDouble());

    int htcCalAtiMultRowCount = HTCCalATIMultMode->rowCount();
    int uMultiAtiMulRowCount = UMultATIMultMode->rowCount();
    int htcCalRowCount = HTCCalculateMode->rowCount();

    for (int row = 0; row < htcCalAtiMultRowCount; ++row) {
        HTCCalATIMult *temp = new HTCCalATIMult();
        if (HTCCalATIMultMode->item(row, 0) != nullptr) temp->setMD(HTCCalATIMultMode->item(row, 0)->text().toDouble());
        if (HTCCalATIMultMode->item(row, 1) != nullptr) temp->setAmbientTemperature(HTCCalATIMultMode->item(row, 1)->text().toDouble());
        if (HTCCalATIMultMode->item(row, 2) != nullptr) temp->setGroundDensity(HTCCalATIMultMode->item(row, 2)->text().toDouble());
        if (HTCCalATIMultMode->item(row, 3) != nullptr) temp->setGroundK(HTCCalATIMultMode->item(row, 3)->text().toDouble());
        if (HTCCalATIMultMode->item(row, 4) != nullptr) temp->setGourndCp(HTCCalATIMultMode->item(row, 4)->text().toDouble());
        heat->addHtcCalAtiMul(temp);
    }

    for (int row = 0; row < uMultiAtiMulRowCount; ++row) {
        UMultATIMult *temp = new UMultATIMult();
        if (UMultATIMultMode->item(row, 0) != nullptr) temp->setMD(UMultATIMultMode->item(row, 0)->text().toDouble());
        if (UMultATIMultMode->item(row, 1) != nullptr) temp->setAmbientTemperature(UMultATIMultMode->item(row, 1)->text().toDouble());
        if (UMultATIMultMode->item(row, 2) != nullptr) temp->setUValue(UMultATIMultMode->item(row, 2)->text().toDouble());
        heat->addUMultAtiMul(temp);
    }

    for (int row = 0; row < htcCalRowCount; ++row) {
        HTCCalculate *temp = new HTCCalculate();
        if (HTCCalculateMode->item(row, 0) != nullptr) temp->setMD(HTCCalculateMode->item(row, 0)->text().toDouble());
        if (HTCCalculateMode->item(row, 1) != nullptr) temp->setGroundDensity(HTCCalculateMode->item(row, 1)->text().toDouble());
        if (HTCCalculateMode->item(row, 2) != nullptr) temp->setGroundK(HTCCalculateMode->item(row, 2)->text().toDouble());
        if (HTCCalculateMode->item(row, 3) != nullptr) temp->setGroundCp(HTCCalculateMode->item(row, 3)->text().toDouble());
        heat->addHtcCal(temp);
    }

}

void MWellWindow::closeEvent(QCloseEvent *event)
{
    setPara();
    setTubular();
    setPacker();
    setHeat();
    QMainWindow::closeEvent(event);
}
