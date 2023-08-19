#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QSplitter>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDebug>
#include <QTabWidget>
#include <QPixmap>
#include <QGraphicsItem>
#include <QComboBox>
#include <QToolBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>

#include "TWidget/ttreewidget.h"
#include "TWidget/ttabwidget.h"
#include "TView/tgraphicsview.h"
#include "TView/tgraphicsscene.h"
#include "TView/mulitem.h"
#include "TView/tarrow.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    resize(1300, 800);
    createActions();
    createToolBar();
    createMenu();
    createStatusBar();
    createWidget();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    newFileAction = new QAction(QIcon(":/resources/image/file.png"), "新建文件", this);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::createGraphicsView);

    aboutAppAction = new QAction(tr("关于 " APPNAME), this);
    connect(aboutAppAction, &QAction::triggered, this, &MainWindow::onAboutApp);

    deleteAction = new QAction(QIcon(":/resources/image/delete.png"), "删除", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    newWellAction = new QAction(QIcon(":/resources/image/Well.png"), "新建井", this);
    newWellAction->setData(MultiflowKind::Well);
    connect(newWellAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newSourceAction = new QAction(QIcon(":/resources/image/source.png"), "新建源", this);
    newSourceAction->setData(MultiflowKind::Source);
    connect(newSourceAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newSinkAction = new QAction(QIcon(":/resources/image/sink.png"), "新建 Sink", this);
    newSinkAction->setData(MultiflowKind::Sink);
    connect(newSinkAction, &QAction::triggered, this, &MainWindow::createMulItem);

    newJunctionAction = new QAction(QIcon(":/resources/image/junction.png"), "新建接合点", this);
    newJunctionAction->setData(MultiflowKind::Junction);
    connect(newJunctionAction, &QAction::triggered, this, &MainWindow::createMulItem);
}

void MainWindow::createToolBar()
{
    itemToolBar = new QToolBar(this);
    otherToolBar = new QToolBar(this);

    itemToolBar->setIconSize(QSize(40, 40));
    itemToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    otherToolBar->setIconSize(QSize(40, 40));

    addToolBar(Qt::TopToolBarArea, itemToolBar);
    addToolBar(Qt::TopToolBarArea, otherToolBar);

    itemToolBar->addAction(newWellAction);
    itemToolBar->addAction(newSourceAction);
    itemToolBar->addAction(newSinkAction);
    itemToolBar->addAction(newJunctionAction);

    newWellAction->setEnabled(false);
    newSourceAction->setEnabled(false);
    newSinkAction->setEnabled(false);
    newJunctionAction->setEnabled(false);

    sceneScaleCombo = new QComboBox;
    sceneScaleCombo->addItems(
        { tr("50%"), tr("75%"), tr("100%"), tr("125%"), tr("150%") });
    sceneScaleCombo->setCurrentIndex(2);

    QFont font = sceneScaleCombo->font();
    font.setPixelSize(20);
    sceneScaleCombo->setFont(font);

    otherToolBar->addWidget(sceneScaleCombo);
    otherToolBar->addAction(deleteAction);
    deleteAction->setEnabled(false);
    sceneScaleCombo->setEnabled(false);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &MainWindow::sceneScaleChanged);

    pointerButton = new QToolButton;
    pointerButton->setEnabled(false);
    pointerButton->setIcon(QIcon(":/resources/image/pointer.png"));

    linePointerButton = new QToolButton;
    linePointerButton->setEnabled(false);
    linePointerButton->setIcon(QIcon(":/resources/image/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, TGraphicsScene::setPointer);
    pointerTypeGroup->addButton(linePointerButton, TGraphicsScene::InsertLine);

    connect(pointerTypeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::pointerGroupClicked);

    otherToolBar->addWidget(pointerButton);
    otherToolBar->addWidget(linePointerButton);
}

void MainWindow::createMenu()
{
    QFont font;
    font.setPointSize(12);
    menuBar()->setFont(font);

    newFileMenu = menuBar()->addMenu("文件(&F)");
    newFileMenu->addAction(newFileAction);
    newFileMenu->setFont(font);

    aboutMenu = menuBar()->addMenu("关于(&A)");
    aboutMenu->addAction(aboutAppAction);
    aboutMenu->setFont(font);
}

void MainWindow::createStatusBar()
{
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::createWidget()
{
    treeWidget = new TTreeWidget(this);
    tabWidget = new TTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setStyleSheet("background-color: #E0E0E0; border: #E0E0E0;");

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    splitter_tree_tab = new QSplitter(Qt::Horizontal, this);

    treeWidget->setMaximumWidth(300);

    splitter_tree_tab->addWidget(treeWidget);
    splitter_tree_tab->addWidget(tabWidget);

    setCentralWidget(splitter_tree_tab);
    centralWidget()->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::onAboutApp()
{
    QMessageBox::information(this, tr(APPNAME), tr(""));
}

void MainWindow::createGraphicsView()
{
    treeWidget->addItem();
    newWellAction->setEnabled(true);
    newSourceAction->setEnabled(true);
    newSinkAction->setEnabled(true);
    newJunctionAction->setEnabled(true);
    deleteAction->setEnabled(true);
    sceneScaleCombo->setEnabled(true);
    pointerButton->setEnabled(true);
    linePointerButton->setEnabled(true);

    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    linePointerButton->setCheckable(true);

    TGraphicsView *tView = new TGraphicsView(this);
    TGraphicsScene *tScene = new TGraphicsScene(tView);

    tScene->setSceneRect(QRectF(0, 0, tabWidget->width() + 200, tabWidget->height() + 200));
    tScene->setBackgroundBrush(QPixmap(":/resources/image/background3.png"));
    tView->setScene(tScene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tView);

    tabWidget->insertTab(tabWidget->count(), tView, QString("场景%1").arg(tabWidget->count() + 1));

    connect(tScene, &TGraphicsScene::mulItemInserted, this, &MainWindow::mulItemInserted);
    connect(tScene, &TGraphicsScene::linePointerInserted, this, &MainWindow::linePointerInserted);
    connect(tScene, &TGraphicsScene::setPointerCursor, this, &MainWindow::setPointerCursor);
}

void MainWindow::createMulItem()
{
    QAction* action = qobject_cast<QAction*>(sender());
    int type = action->data().toInt();
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    TGraphicsScene *scene = dynamic_cast<TGraphicsScene*>(view->scene());
    scene->setMode(TGraphicsScene::InsertItem);
    scene->setItemType(MultiflowKind(type));
    setCursor(Qt::CrossCursor);
}

void MainWindow::pointerGroupClicked()
{
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    TGraphicsScene *scene = dynamic_cast<TGraphicsScene*>(view->scene());
    scene->setMode(TGraphicsScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::mulItemInserted(MulItem *item)
{
    Q_UNUSED(item);
    unsetCursor();
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    TGraphicsScene *scene = dynamic_cast<TGraphicsScene*>(view->scene());
    scene->setMode(TGraphicsScene::setPointer);
//    treeWidget->addFlowlineItem(item);
}

void MainWindow::linePointerInserted()
{
    unsetCursor();
}

void MainWindow::setPointerCursor()
{
    unsetCursor();
}

void MainWindow::closeTab(int index)
{
    if (index == -1) {
        return;
    }
//    qDebug() << index;
    QWidget* tabItem = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete(tabItem);
    tabItem = nullptr;
//    qDebug() << "123";
    if (tabWidget->count() == 0) {
        sceneScaleCombo->setCurrentIndex(2);
        sceneScaleCombo->setEnabled(false);
        newWellAction->setEnabled(false);
        newSourceAction->setEnabled(false);
        newSinkAction->setEnabled(false);
        newJunctionAction->setEnabled(false);
        deleteAction->setEnabled(false);
        treeWidget->clearItem();
        pointerButton->setEnabled(false);
        linePointerButton->setEnabled(false);
    }
}

void MainWindow::tabChanged(int index)
{
    if (index == -1) {
        return;
    }
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(index));
//    qDebug() << index;
    QString scale = view->getScale();
    if (scale.isEmpty()) {
        sceneScaleCombo->setCurrentIndex(2);
        view->setScale(sceneScaleCombo->currentText());
        return;
    } else {
        //sceneScaleCombo->setCurrentText(scale);
        setViewScale(view, scale);
    }
//    qDebug() << scale;
    setViewScale(view, scale);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    if (tabWidget->count() == 0) {
        return;
    }
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    setViewScale(view, scale);
}

void MainWindow::setViewScale(TGraphicsView *view, const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
    view->setScale(scale);
}

void MainWindow::deleteItem()
{
    TGraphicsView *view = dynamic_cast<TGraphicsView*>(tabWidget->widget(tabWidget->currentIndex()));
    TGraphicsScene *scene = dynamic_cast<TGraphicsScene*>(view->scene());
    if (scene->selectedItems().count() == 0) {
        return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "删除确认", "确定要删除该item项吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QList<QGraphicsItem *> selectedItems = scene->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == TArrow::Type) {
                scene->removeItem(item);
                TArrow *arrow = qgraphicsitem_cast<TArrow *>(item);
                arrow->getStartItem()->removeArrow(arrow);
                arrow->getEndItem()->removeArrow(arrow);
                delete item;
            }
        }
        selectedItems = scene->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == MulItem::Type)
                qgraphicsitem_cast<MulItem *>(item)->removeArrows();
            scene->removeItem(item);
            delete item;
        }
        scene->update();
    }
}
