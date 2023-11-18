#pragma once

#include "widget/SplashDialog.hpp"
#include "TView/MAbstractItem.hpp"
#include "TWidget/MTabWidget.h"
#include "TWidget/MTreeWidget.h"
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
    QAction* newFileAction{};
    QAction* aboutAppAction{};
    QAction* newWellAction{};
    QAction* newSourceAction{};
    QAction* newSinkAction{};
    QAction* newJunctionAction{};
    QAction* deleteAction{};
    QAction* _openFormulaViewerAction{};
    QAction* _exitAction{};

    // Menu
    QMenu* _newFileMenu{};
    QMenu* _toolsMenu{};
    QMenu* _aboutMenu{};

    // Widget
    MTabWidget* tabWidget{};
    MTreeWidget* treeWidget{};
    std::unique_ptr<SplashDialog> _splashDialog;

    // Bar
    QToolBar* itemToolBar{};
    QToolBar* otherToolBar{};
    QStatusBar* statusBar{};

    // Button
    QButtonGroup* pointerTypeGroup{};

    QToolButton* pointerButton{};
    QToolButton* linePointerButton{};

    QComboBox* sceneScaleCombo{};

    // 布局
    QSplitter* splitterTreeTab{};

    void createActions();

    void createToolBar();

    void createWidget();

    void createMenu();

    void createStatusBar();

    /**
     * @brief 禁用工具栏，及其子控件
     * @author z
     */
    void disableToolbars() const;

    /**
     * @brief 启用工具栏
     * @author z
     */
    void enableToolbars() const;

    static void setViewScale(TGraphicsView* view, const QString& scale);

    void loadAndShowSplashScreen();

signals:
    void onLoadStart();

    void onLoadUpdate(const QString& statusMessage);

    void onLoadFinish();

private slots:
    void onAboutApp();

    void onUserExit();

    void createGraphicsView();

    void createMulItem();

    static void openFormulaViewer();

    void pointerGroupClicked() const;

    void sceneScaleChanged(const QString& scale) const;

    void mulItemInserted(const MAbstractItem* item);

    void linePointerInserted();

    void deleteItem();

    void setPointerCursor();

    void closeTab(int index) const;

    void tabChanged(int index) const;

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
