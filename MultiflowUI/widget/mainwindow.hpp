#pragma once

#include "widget/SplashDialog.hpp"
#include "TView/mulitem.h"
#include "TWidget/ttabwidget.h"
#include "TWidget/ttreewidget.h"
#include "TView/tgraphicsview.h"
#include "shared.hpp"

// TODO: 这个对QMessageBox的包含看上去并没有在mainwindow中用到
// TODO: 但是如果去掉，会出现大量来自Qt的qmessagebox.h内部的报错
// TODO: 也许前面一系列头文件有互相包含的问题吧？暂时没找到原因
// TODO: 尽量不使用 class xxx; 的前置声明，而是使用 #include 的方式，应该会好一些
#include <QMessageBox>

#include <QObject>
#include <QAction>
#include <QSplitter>
#include <QMenu>
#include <QButtonGroup>


class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent, int argc, const char* argv[]);

    ~MainWindow() override = default;

private:
    int _argc;
    const char** _argv;

    // Action
    QAction* newFileAction;
    QAction* aboutAppAction;
    QAction* newWellAction;
    QAction* newSourceAction;
    QAction* newSinkAction;
    QAction* newJunctionAction;
    QAction* deleteAction;

    // Menu
    QMenu* newFileMenu;
    QMenu* aboutMenu;

    // Widget
    TTabWidget* tabWidget;
    TTreeWidget* treeWidget;
    std::unique_ptr<SplashDialog> _splashDialog;

    // Bar
    QToolBar* itemToolBar;
    QToolBar* otherToolBar;
    QStatusBar* statusBar;

    // Button
    QButtonGroup* pointerTypeGroup;

    QToolButton* pointerButton;
    QToolButton* linePointerButton;

    QComboBox* sceneScaleCombo;

    // 布局
    QSplitter* splitterTreeTab;

    void createActions();

    void createToolBar();

    void createWidget();

    void createMenu();

    void createStatusBar();

    /**
     * @brief 禁用工具栏，及其子控件
     * @author z
     */
    void disableToolbars();

    /**
     * @brief 启用工具栏
     * @author z
     */
    void enableToolbars();

    void setViewScale(TGraphicsView* view, const QString& scale);

    void loadAndShowSplashScreen();

signals:
    void onLoadStart();

    void onLoadUpdate(const QString& statusMessage);

    void onLoadFinish();

private slots:
    void onAboutApp();

    void createGraphicsView();

    void createMulItem();

    void pointerGroupClicked();

    void sceneScaleChanged(const QString& scale);

    void mulItemInserted(MulItem* item);

    void linePointerInserted();

    void deleteItem();

    void setPointerCursor();

    void closeTab(int index);

    void tabChanged(int index);

    /**
     * @brief 初始化程序开始运行
     */
    void showLoadingDialog();

    /**
     * @brief 初始化程序加载状态改变
     */
    void updateLoadingDialog(const QString& statusMessage) const;

    /**
     * @brief 初始化程序运行结束
     */
    void closeLoadingDialog() const;
};
