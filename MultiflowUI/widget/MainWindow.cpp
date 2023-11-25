#include "MainWindow.hpp"
#include "constants.hpp"
#include "service/FormulaService.hpp"
#include "service/EntityService.hpp"
#include "qml/main.hpp"
#include "graphics_view/MGraphicsScene.hpp"
#include "graphics_view/MArrow.hpp"

#include "MultiflowLibrary/logging/logging.hpp"

#include <QSplitter>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QTimer>
#include <QComboBox>
#include <QToolBar>
#include <QMessageBox>
#include <FluentUIExt/src/FluApp.h>
#include <qml/utils/UIUtils.hpp>

constexpr int LoadingDialogTimeoutMillis = 1000;


MainWindow::MainWindow(QWidget* parent, const int argc, const char* argv[])
    : QMainWindow(parent), _argc(argc), _argv(argv) {
    loadAndShowSplashScreen();
}

void MainWindow::loadAndShowSplashScreen() {
    connect(this, &MainWindow::onLoadStart, this, &MainWindow::showLoadingDialog);
    connect(this, &MainWindow::onLoadUpdate, this, &MainWindow::updateLoadingDialog);
    connect(this, &MainWindow::onLoadFinish, this, &MainWindow::closeLoadingDialog);

    emit onLoadStart();
    emit onLoadUpdate("加载图标资源...");
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));

    emit onLoadUpdate("加载主窗口...");
    resize(1300, 800);
    createActions();
    createToolBar();
    createMenu();
    createStatusBar();
    createWidget();

    emit onLoadUpdate("加载公式数据...");
    log_info("Loading formulae.");
    FormulaService::getInstance()->parseAndLoadFormulae();

    emit onLoadUpdate("加载实体数据...");
    log_info("Loading entities.");
    EntityService::getInstance()->parserAndLoadEntities();

    emit onLoadUpdate("加载 QML 引擎...");
    log_info("Initializing QML engine.");
    qml::initialize(_argc, _argv);

    emit onLoadUpdate("欢迎使用 " + tr(AppName) + "！");

    // 加载框关闭如果太快了，用户就感受不到我们的热情
    QTimer::singleShot(
        LoadingDialogTimeoutMillis, this, &MainWindow::onLoadFinish);
}

void MainWindow::showLoadingDialog() {
    _splashDialog = SplashDialog::createAndShow();
}

void MainWindow::updateLoadingDialog(const QString& statusMessage) const {
    _splashDialog->updateStatus(statusMessage);
}

void MainWindow::closeLoadingDialog() const {
    _splashDialog->close();
}

void MainWindow::createActions() {
    newFileAction = new QAction(QIcon(":/resources/image/file.png"), "新建项目(&N)", this);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::createGraphicsView);

    aboutAppAction = new QAction(tr("关于 ") + AppName, this);
    connect(aboutAppAction, &QAction::triggered, this, &MainWindow::onAboutApp);

    deleteAction = new QAction(QIcon(":/resources/image/delete.png"), "删除(&D)", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    newWellAction = new QAction(QIcon(":/resources/image/Well.png"), "新建井(&W)", this);
    newWellAction->setData(MItemKind::Well);
    connect(newWellAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newSourceAction = new QAction(QIcon(":/resources/image/source.png"), "新建源(&S)", this);
    newSourceAction->setData(MItemKind::Source);
    connect(newSourceAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newSinkAction = new QAction(QIcon(":/resources/image/sink.png"), "新建 S&ink", this);
    newSinkAction->setData(MItemKind::Sink);
    connect(newSinkAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newJunctionAction = new QAction(QIcon(":/resources/image/junction.png"), "新建接合点(&C)", this);
    newJunctionAction->setData(MItemKind::Junction);
    connect(newJunctionAction, &QAction::triggered, this, &MainWindow::createMulItem);

    _exitAction = new QAction(tr("退出(&X)"), this);
    connect(_exitAction, &QAction::triggered, this, &MainWindow::onUserExit);

    _openFormulaViewerAction = new QAction(tr("打开公式查看器(&F)"), this);
    connect(_openFormulaViewerAction, &QAction::triggered, this, &MainWindow::openFormulaViewer);
}

void MainWindow::onUserExit() {
    if (UIUtils::confirm(
        QString("确认要退出 %1 嘛？").arg(AppName),
        "退出", "取消")) {
        close();
    }
}

void MainWindow::createToolBar() {
    itemToolBar = new QToolBar(this);
    itemToolBar->setIconSize(QSize(40, 40));
    itemToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    itemToolBar->addActions({newWellAction, newSourceAction, newSinkAction, newJunctionAction});
    addToolBar(Qt::TopToolBarArea, itemToolBar);

    otherToolBar = new QToolBar(this);
    otherToolBar->setIconSize(QSize(40, 40));
    otherToolBar->addAction(deleteAction);
    addToolBar(Qt::TopToolBarArea, otherToolBar);

    disableToolbars();

    sceneScaleCombo = new QComboBox;
    sceneScaleCombo->addItems({tr("50%"), tr("75%"), tr("100%"), tr("125%"), tr("150%")});
    sceneScaleCombo->setCurrentIndex(2);

    QFont font = sceneScaleCombo->font();
    font.setPixelSize(20);
    sceneScaleCombo->setFont(font);

    otherToolBar->addWidget(sceneScaleCombo);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &MainWindow::sceneScaleChanged);

    pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/resources/image/pointer.png"));

    linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/resources/image/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, MGraphicsScene::SetPointer);
    pointerTypeGroup->addButton(linePointerButton, MGraphicsScene::InsertLine);

    connect(pointerTypeGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::pointerGroupClicked);

    otherToolBar->addWidget(pointerButton);
    otherToolBar->addWidget(linePointerButton);
}

void MainWindow::disableToolbars() const {
    itemToolBar->setEnabled(false);
    otherToolBar->setEnabled(false);
}

void MainWindow::enableToolbars() const {
    itemToolBar->setEnabled(true);
    otherToolBar->setEnabled(true);
}

void MainWindow::createMenu() {
    QFont font;
    font.setPointSize(12);
    menuBar()->setFont(font);

    _newFileMenu = menuBar()->addMenu("文件(&F)");
    _newFileMenu->setFont(font);
    _newFileMenu->addAction(newFileAction);
    _newFileMenu->addSeparator();
    _newFileMenu->addAction(_exitAction);

    _toolsMenu = menuBar()->addMenu("工具(&U)");
    _toolsMenu->setFont(font);
    _toolsMenu->addAction(_openFormulaViewerAction);

    _aboutMenu = menuBar()->addMenu("关于(&A)");
    _aboutMenu->setFont(font);
    _aboutMenu->addAction(aboutAppAction);
}

void MainWindow::createStatusBar() {
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::createWidget() {
    treeWidget = new MTreeWidget(this);
    tabWidget = new MTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setStyleSheet("background-color: #E0E0E0; border: #E0E0E0;");

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    splitterTreeTab = new QSplitter(Qt::Horizontal, this);

    treeWidget->setMaximumWidth(300);

    splitterTreeTab->addWidget(treeWidget);
    splitterTreeTab->addWidget(tabWidget);

    setCentralWidget(splitterTreeTab);
    centralWidget()->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::onAboutApp() {
    // TODO
    QMessageBox::information(this, tr(AppName), tr(""));
}

/**
 * @brief 新建新场景的时候调用，设置一些按钮的状态
 */
void MainWindow::createGraphicsView() {
    treeWidget->initializeItems();
    enableToolbars();
    pointerButton->setChecked(true);

    auto* tView = new MGraphicsView(this);
    auto* tScene = new MGraphicsScene(tView);

    tScene->setSceneRect(QRectF(0, 0, tabWidget->width() + 200, tabWidget->height() + 200));
    tScene->setBackgroundBrush(QPixmap(":/resources/image/background3.png"));
    tView->setScene(tScene);

    auto* layout = new QHBoxLayout{};
    layout->addWidget(tView);

    tabWidget->insertTab(tabWidget->count(), tView, QString("场景 %1").arg(tabWidget->count() + 1));

    connect(tScene, &MGraphicsScene::mulItemInserted, this, &MainWindow::mulItemInserted);
    connect(tScene, &MGraphicsScene::linePointerInserted, this, &MainWindow::linePointerInserted);
    connect(tScene, &MGraphicsScene::setPointerCursor, this, &MainWindow::setPointerCursor);
}

void MainWindow::openFormulaViewer() {
    qml::navigate("/formula-viewer");
}

void MainWindow::createMulItem() {
    const auto* action = qobject_cast<QAction*>(sender());
    int type = action->data().toInt();
    const auto* view = tabWidget->currentTGraphicsView();
    auto* scene = view->scene();
    scene->setMode(MGraphicsScene::InsertItem);
    scene->setItemType(static_cast<MItemKind>(type));
    setCursor(Qt::CrossCursor);
}

void MainWindow::pointerGroupClicked() const {
    const auto* view = tabWidget->currentTGraphicsView();
    view->scene()->setMode(static_cast<MGraphicsScene::Mode>(pointerTypeGroup->checkedId()));
}

void MainWindow::mulItemInserted(const MAbstractItem* item) {
    Q_UNUSED(item)

    unsetCursor();
    const auto* view = tabWidget->currentTGraphicsView();
    view->scene()->setMode(MGraphicsScene::SetPointer);
}

void MainWindow::linePointerInserted() {
    unsetCursor();
}

void MainWindow::setPointerCursor() {
    unsetCursor();
}

void MainWindow::closeTab(const int index) const {
    if (index == -1) {
        return;
    }
    const auto* tabItem = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete tabItem;

    if (tabWidget->count() == 0) {
        sceneScaleCombo->setCurrentIndex(2);
        disableToolbars();
        treeWidget->clearItems();
    }
}

void MainWindow::tabChanged(const int index) const {
    if (index == -1) {
        return;
    }
    auto* view = tabWidget->widgetAt(index);
    const QString scale = view->getScale();
    if (scale.isEmpty()) {
        sceneScaleCombo->setCurrentIndex(2);
        view->setScale(sceneScaleCombo->currentText());
        return;
    }
    //sceneScaleCombo->setCurrentText(scale);
    setViewScale(view, scale);
}

void MainWindow::sceneScaleChanged(const QString& scale) const {
    if (tabWidget->count() == 0) {
        return;
    }
    auto* view = dynamic_cast<MGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    setViewScale(view, scale);
}

void MainWindow::setViewScale(MGraphicsView* view, const QString& scale) {
    const double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    const QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
    view->setScale(scale);
}

void MainWindow::deleteItem() {
    const auto* view = tabWidget->currentTGraphicsView();
    auto* scene = view->scene();
    const auto itemCount = scene->selectedItems().count();
    if (itemCount == 0) {
        return;
    }
    if (
        QMessageBox::question(this, "删除确认", QString("确定要删除该 %1 项吗？").arg(itemCount))
        == QMessageBox::Yes
    ) {
        std::ranges::for_each(scene->selectedItems(), [scene](QGraphicsItem* item) {
            if (item->type() == MAbstractItem::ArrowType::Type) {
                scene->removeItem(item);
                const auto* arrow = qgraphicsitem_cast<MAbstractItem::ArrowType*>(item);
                arrow->getStartItem()->removeArrow(arrow);
                arrow->getEndItem()->removeArrow(arrow);
            }
        });
        std::ranges::for_each(scene->selectedItems(), [scene](QGraphicsItem* item) {
            if (item->type() == MAbstractItem::Type)
                qgraphicsitem_cast<MAbstractItem*>(item)->removeAllArrows();
            scene->removeItem(item);
        });
        scene->update();
    }
}
