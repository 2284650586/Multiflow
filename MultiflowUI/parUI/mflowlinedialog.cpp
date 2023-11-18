#include "mflowlinedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include <qcombobox.h>
#include <QStandardItem>
#include <QTableView>
#include <QScrollArea>
#include <QFileDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QLineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>


MFlowlineDialog::MFlowlineDialog(const std::shared_ptr<MFlowline>& flowline, QString name, QWidget* parent)
    : QDialog(parent), _flowline(flowline) {
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    setMinimumHeight(700);
    setMinimumWidth(870);
    mName = name;
    setupUI();
    createTableModel();
    updateName();
    updateDialogFromMFlowline();
}

MFlowlineDialog::~MFlowlineDialog() {
}

void MFlowlineDialog::setupUI() {
    // 创建UI组件
    flowlineNameLabel = new QLabel("名称:", this);
    flowlineNameLineEdit = new QLineEdit(this);

    flowlineTypeLabel = new QLabel("流动类型:", this);
    flowlineTypeComboBox = new QComboBox(this);
    flowlineTypeComboBox->addItem("管道流动");
    flowlineTypeComboBox->addItem("环形空间流动");

    flowlineModeLabel = new QLabel("管线模式:", this);
    flowlineModeComboBox = new QComboBox(this);
    flowlineModeComboBox->addItem("简单模式");
    flowlineModeComboBox->addItem("详细模式");

    flowlineEnvLabel = new QLabel("管线环境:", this);
    flowlineEnvComboBox = new QComboBox(this);
    flowlineEnvComboBox->addItem("陆地管线");
    flowlineEnvComboBox->addItem("海底管线");

    // 设置浮点数输入验证器，允许输入小数
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setDecimals(15);

    pipInsideDiameterLabel = new QLabel("管道内径(mm):", this);
    pipInsideDiameterLineEdit = new QLineEdit(this);
    pipInsideDiameterLineEdit->setValidator(doubleValidator);

    pipWallThicknessLabel = new QLabel("管道壁厚(mm):", this);
    pipWallThicknessLineEdit = new QLineEdit(this);
    pipWallThicknessLineEdit->setValidator(doubleValidator);

    pipeRoughnessLabel = new QLabel("管道粗糙度(mm):", this);
    pipeRoughnessLineEdit = new QLineEdit(this);
    pipeRoughnessLineEdit->setValidator(doubleValidator);

    profileHorizontalDistanceLabel = new QLabel("水平距离(Km):", this);
    profileHorizontalDistanceLineEdit = new QLineEdit(this);
    profileHorizontalDistanceLineEdit->setValidator(doubleValidator);

    profileElevationDifferenceLabel = new QLabel("高程差(Km):", this);
    profileElevationDifferenceLineEdit = new QLineEdit(this);
    profileElevationDifferenceLineEdit->setValidator(doubleValidator);

    heatTransferCoefficientLabel = new QLabel("传导系数(J/(s.degC.m^2)):", this);
    heatTransferCoefficientLineEdit = new QLineEdit(this);
    heatTransferCoefficientLineEdit->setValidator(doubleValidator);

    okButton = new QPushButton("确认", this);
    okButton->setMaximumHeight(40);
    okButton->setMaximumWidth(200);
    cancelButton = new QPushButton("取消", this);
    cancelButton->setMaximumWidth(40);
    cancelButton->setMaximumWidth(200);

    // 创建一个Qt Charts折线图
    lineSeries = new QLineSeries();
    scatterSeries = new QScatterSeries();

    // 设置Qt Charts的标题和轴标签等
    QChart* chart = new QChart();
    chart->addSeries(lineSeries);
    chart->addSeries(scatterSeries);
    chart->setTitle("Flowline Chart");

    // 创建并设置新的坐标轴
    QValueAxis* axisX = new QValueAxis(this);
    axisX->setTitleText("Horizontal Distance (Km)");
    axisX->setRange(0, 300); // 设置x轴范围为0到300
    axisX->setTickCount(4); // 设置x轴刻度数量为4，即每个100取一个点
    chart->addAxis(axisX, Qt::AlignBottom);
    lineSeries->attachAxis(axisX);
    scatterSeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis(this);
    axisY->setTitleText("Elevation Difference (Km)");
    axisY->setRange(0, 5); // 设置y轴范围为0到5
    axisY->setTickCount(11); // 设置y轴刻度数量为11，即每隔0.5取一个点
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisY);
    scatterSeries->attachAxis(axisY);

    // 创建Qt Charts的视图并设置大小
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 设置折线图和散点图的样式
    lineSeries->setColor(QColor("#007ACC")); // 设置折线图的颜色
    lineSeries->setPen(QPen(QColor("#007ACC"), 2)); // 设置折线图的线条宽度

    scatterSeries->setColor(QColor("#FF0000")); // 设置散点图的颜色
    scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle); // 设置散点图的形状为圆圈
    scatterSeries->setMarkerSize(10); // 设置散点图的大小


    // 设置布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* hLayout = new QHBoxLayout(this);


    // 使用 QGridLayout 实现左对齐的布局
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(flowlineNameLabel, 0, 0);
    gridLayout->addWidget(flowlineNameLineEdit, 0, 1);
    gridLayout->addWidget(flowlineTypeLabel, 1, 0);
    gridLayout->addWidget(flowlineTypeComboBox, 1, 1);
    gridLayout->addWidget(flowlineModeLabel, 2, 0);
    gridLayout->addWidget(flowlineModeComboBox, 2, 1);
    gridLayout->addWidget(flowlineEnvLabel, 3, 0);
    gridLayout->addWidget(flowlineEnvComboBox, 3, 1);
    gridLayout->addWidget(pipInsideDiameterLabel, 4, 0);
    gridLayout->addWidget(pipInsideDiameterLineEdit, 4, 1);
    gridLayout->addWidget(pipWallThicknessLabel, 5, 0);
    gridLayout->addWidget(pipWallThicknessLineEdit, 5, 1);
    gridLayout->addWidget(pipeRoughnessLabel, 6, 0);
    gridLayout->addWidget(pipeRoughnessLineEdit, 6, 1);
    gridLayout->addWidget(profileHorizontalDistanceLabel, 7, 0);
    gridLayout->addWidget(profileHorizontalDistanceLineEdit, 7, 1);
    gridLayout->addWidget(profileElevationDifferenceLabel, 8, 0);
    gridLayout->addWidget(profileElevationDifferenceLineEdit, 8, 1);
    gridLayout->addWidget(heatTransferCoefficientLabel, 9, 0);
    gridLayout->addWidget(heatTransferCoefficientLineEdit, 9, 1);

    hLayout->addLayout(gridLayout);


    // 设置整个布局的右侧滚动区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // 在滚动区域内放置一个 QTableView
    tableView = new QTableView(this);
    scrollArea->setWidget(tableView);

    // 创建添加行和删除行的按钮
    addRowButton = new QPushButton("添加行", this);
    deleteRowButton = new QPushButton("删除行", this);
    importButton = new QPushButton("导入CSV", this);
    exportButton = new QPushButton("导出CSV", this);

    // 创建按钮布局
    QVBoxLayout* buttonsLayoutInScrollArea = new QVBoxLayout;
    buttonsLayoutInScrollArea->addWidget(addRowButton);
    buttonsLayoutInScrollArea->addWidget(deleteRowButton);
    buttonsLayoutInScrollArea->addWidget(importButton);
    buttonsLayoutInScrollArea->addWidget(exportButton);

    // 创建一个水平布局，用于放置滚动区域和按钮布局
    QHBoxLayout* scrollAreaLayout = new QHBoxLayout(this);
    scrollAreaLayout->addWidget(scrollArea);
    scrollAreaLayout->addLayout(buttonsLayoutInScrollArea);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(scrollAreaLayout);
    vLayout->addWidget(chartView, 4);

    hLayout->addLayout(vLayout, 2);

    // 将gridLayout和scrollAreaLayout添加到主布局中
    mainLayout->addLayout(hLayout);

    // 创建按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // 连接按钮信号槽
    connect(okButton, &QPushButton::clicked, this, &MFlowlineDialog::acceptDialog);
    connect(cancelButton, &QPushButton::clicked, this, &MFlowlineDialog::rejectDialog);

    connect(addRowButton, &QPushButton::clicked, this, &MFlowlineDialog::addRow);
    connect(deleteRowButton, &QPushButton::clicked, this, &MFlowlineDialog::deleteRow);
    connect(importButton, &QPushButton::clicked, this, &MFlowlineDialog::importFromCsv);
    connect(exportButton, &QPushButton::clicked, this, &MFlowlineDialog::exportToCsv);

    // 设置样式表（如果需要的话）
    setStyleSheet(
        "QDialog { background-color: #f0f0f0; }"
        "QLabel { font-weight: bold; color: #333333; }"
        "QLineEdit { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QComboBox { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #367c39; }"

        "QTableView { background-color: #ffffff; border: 1px solid #cccccc; }"
        "QHeaderView::section { background-color: #f0f0f0; font-weight: bold; }"
        "QTableView::item:selected { background-color: #a8c8e4; }"

        "QChartView { background-color: white; }"
        "QChartView::rubberBand { background: rgba(168, 200, 228, 50%); }"
    );
}


void MFlowlineDialog::updateDialogFromMFlowline() {
    if (_flowline) {
        // 设置流动类型
        if (_flowline->getFlowlineType() == MFlowline::Pipe)
            flowlineTypeComboBox->setCurrentIndex(0);
        else
            flowlineTypeComboBox->setCurrentIndex(1);

        // 设置管线模式
        if (_flowline->getFlowlineMode() == MFlowline::Simple)
            flowlineModeComboBox->setCurrentIndex(0);
        else
            flowlineModeComboBox->setCurrentIndex(1);

        // 设置管线环境
        if (_flowline->getFlowlineEnviroment() == MFlowline::Land)
            flowlineEnvComboBox->setCurrentIndex(0);
        else
            flowlineEnvComboBox->setCurrentIndex(1);

        // 设置其余参数
        pipInsideDiameterLineEdit->setText(QString::number(_flowline->getPipInsideDiameter()));
        pipWallThicknessLineEdit->setText(QString::number(_flowline->getPipWallThickness()));
        pipeRoughnessLineEdit->setText(QString::number(_flowline->getPipeRoughness()));
        profileHorizontalDistanceLineEdit->setText(QString::number(_flowline->getProfileHorizontalDistance()));
        profileElevationDifferenceLineEdit->setText(QString::number(_flowline->getProfileElevatiaonDifference()));
        heatTransferCoefficientLineEdit->setText(QString::number(_flowline->getHeatTransferCoefficient()));


        dataModel->removeRows(0, dataModel->rowCount());

        // 加载数据到数据模型
        auto parList = _flowline->getParList();
        for (auto* par: parList) {
            double hd1, evl, hd2, tempear;
            hd1 = par->getHd1();
            evl = par->getElevation();
            hd2 = par->getHd2();
            tempear = par->getTemperature();

            // 只有当参数值不等于0x7FFFFFFF时，才加载数据
            QList<QStandardItem*> rowItems;
            if (hd1 != 0x7FFFFFFF)
                rowItems.append(new QStandardItem(QString::number(hd1)));
            if (evl != 0x7FFFFFFF)
                rowItems.append(new QStandardItem(QString::number(evl)));
            if (hd2 != 0x7FFFFFFF)
                rowItems.append(new QStandardItem(QString::number(hd2)));
            if (tempear != 0x7FFFFFFF)
                rowItems.append(new QStandardItem(QString::number(tempear)));

            if (!rowItems.isEmpty()) {
                dataModel->appendRow(rowItems);
                updateChartFromTable();
            }
        }
    }
}

void MFlowlineDialog::updateMFlowlineFromDialog() {
    if (_flowline) {
        mName = flowlineNameLineEdit->text();
        // 获取流动类型
        if (flowlineTypeComboBox->currentIndex() == 0)
            _flowline->setFlowlineType(MFlowline::Pipe);
        else
            _flowline->setFlowlineType(MFlowline::Annulus);

        // 获取管线模式
        if (flowlineModeComboBox->currentIndex() == 0)
            _flowline->setFlowlineMode(MFlowline::Simple);
        else
            _flowline->setFlowlineMode(MFlowline::Detailed);

        // 获取管线环境
        if (flowlineEnvComboBox->currentIndex() == 0)
            _flowline->setFlowlineEnviroment(MFlowline::Land);
        else
            _flowline->setFlowlineEnviroment(MFlowline::Subsea);

        // 获取其余参数
        _flowline->setPipInsideDiameter(pipInsideDiameterLineEdit->text().toDouble());
        _flowline->setPipWallThickness(pipWallThicknessLineEdit->text().toDouble());
        _flowline->setPipeRoughness(pipeRoughnessLineEdit->text().toDouble());
        _flowline->setProfileHorizontalDistance(profileHorizontalDistanceLineEdit->text().toDouble());
        _flowline->setProfileElevatiaonDifference(profileElevationDifferenceLineEdit->text().toDouble());
        _flowline->setHeatTransferCoefficient(heatTransferCoefficientLineEdit->text().toDouble());

        _flowline->clearPar();

        // 获取表格中的数据并存储到 mFlowline 中
        int rowCount = dataModel->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            QString hd1 = dataModel->item(row, 0) ? dataModel->item(row, 0)->text() : "";
            QString evl = dataModel->item(row, 1) ? dataModel->item(row, 1)->text() : "";
            QString hd2 = dataModel->item(row, 2) ? dataModel->item(row, 2)->text() : "";
            QString tempear = dataModel->item(row, 3) ? dataModel->item(row, 3)->text() : "";

            double d_hd1 = 0x7FFFFFFF;
            double d_evl = 0x7FFFFFFF;
            double d_hd2 = 0x7FFFFFFF;
            double d_tempear = 0x7FFFFFFF;

            if (!hd1.isEmpty()) d_hd1 = hd1.toDouble();
            if (!evl.isEmpty()) d_evl = evl.toDouble();
            if (!hd2.isEmpty()) d_hd2 = hd2.toDouble();
            if (!tempear.isEmpty()) d_tempear = tempear.toDouble();

            _flowline->addPar(d_hd1, d_evl, d_hd2, d_tempear);
        }
    }
}

void MFlowlineDialog::updateName() {
    if (!mName.isEmpty()) {
        flowlineNameLineEdit->setText(mName);
    }
}

QString MFlowlineDialog::getName() {
    return mName;
}

void MFlowlineDialog::acceptDialog() {
    updateMFlowlineFromDialog();
    accept();
}

void MFlowlineDialog::rejectDialog() {
    reject();
}

void MFlowlineDialog::createTableModel() {
    dataModel = new QStandardItemModel(this);

    // 设置表头
    QStringList headerLabels = {"水平距离1", "高程", "水平距离2", "环境温度"};
    dataModel->setHorizontalHeaderLabels(headerLabels);

    tableView->setModel(dataModel);
    connect(dataModel, &QStandardItemModel::dataChanged, this, &MFlowlineDialog::updateChartFromTable);
}

void MFlowlineDialog::addRow() {
    int newRow = dataModel->rowCount();
    dataModel->insertRow(newRow);
}

void MFlowlineDialog::deleteRow() {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        int rowToDelete = selectedRows.first().row();
        dataModel->removeRow(rowToDelete);
    }
}

void MFlowlineDialog::importFromCsv() {
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
                }
                else {
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

void MFlowlineDialog::exportToCsv() {
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
                    }
                    else {
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

void MFlowlineDialog::updateChartFromTable() {
    // 清空原有的数据
    lineSeries->clear();
    scatterSeries->clear();

    // 遍历表格数据，提取x坐标和y坐标，然后将点添加到Qt Charts中
    for (int row = 0; row < dataModel->rowCount(); ++row) {
        QString xStr = dataModel->item(row, 0) ? dataModel->item(row, 0)->text() : "";
        QString yStr = dataModel->item(row, 1) ? dataModel->item(row, 1)->text() : "";


        // 检查点是否为空
        if (!xStr.isEmpty() && !yStr.isEmpty()) {
            double x = xStr.toDouble();
            double y = yStr.toDouble();

            lineSeries->append(x, y);
            scatterSeries->append(x, y);
        }
    }
}
