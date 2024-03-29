#pragma once

#include "widget/SplashDialog.hpp"
#include "graphics_view/MAbstractItem.hpp"
#include "graphics_view/widget/MTabWidget.hpp"
#include "graphics_view/widget/MTreeWidget.hpp"
#include "graphics_view/MGraphicsView.hpp"
#include "shared.hpp"

#include <QObject>
#include <QAction>
#include <QSplitter>
#include <QMenu>
#include <QButtonGroup>
#include <QToolButton>

#include <memory>

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
    QAction* _openBlackOilManagerAction{};
    QAction* _openPvtCalculatorAction{};
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

    static void setViewScale(MGraphicsView* view, const QString& scale);

    void loadAndShowSplashScreen();

signals:
    void onLoadStart();

    void onLoadUpdate(const QString& statusMessage);

    void onLoadFinish();

public slots:
    static void openFormulaViewer();

    static void openBlackOilManager();

    static void openPvtCalculator();

private slots:
    void onAboutApp();

    void onUserExit();

    void createGraphicsView();

    void createMulItem();

    void createDefaultTab();

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
