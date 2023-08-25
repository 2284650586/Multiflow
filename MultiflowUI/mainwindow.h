#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"

QT_BEGIN_NAMESPACE

class QAction;
class QToolBar;
class QSplitter;
class QMenu;
class QStatusBar;
class QGraphicsItem;
class QComboBox;
class QButtonGroup;
class QToolButton;

QT_END_NAMESPACE

class TTabWidget;
class TTreeWidget;
class MulItem;
class TGraphicsView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    //Action
    QAction *newFileAction;
    QAction *aboutAppAction;
    QAction *newWellAction;
    QAction *newSourceAction;
    QAction *newSinkAction;
    QAction *newJunctionAction;
    QAction *deleteAction;

    //Menu
    QMenu *newFileMenu;
    QMenu *aboutMenu;

    //Widget
    TTabWidget *tabWidget;
    TTreeWidget *treeWidget;

    //Bar
    QToolBar *itemToolBar;
    QToolBar *otherToolBar;
    QStatusBar *statusBar;

    //Button
    QButtonGroup *pointerTypeGroup;

    QToolButton *pointerButton;
    QToolButton *linePointerButton;

    QComboBox *sceneScaleCombo;

    //布局
    QSplitter *splitterTreeTab;


private:
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

    void setViewScale(TGraphicsView *view, const QString &scale);


private slots:
    void onAboutApp();

    void createGraphicsView();
    void createMulItem();

    void pointerGroupClicked();
    void sceneScaleChanged(const QString &scale);
    void mulItemInserted(MulItem *item);
    void linePointerInserted();

    void deleteItem();


    void setPointerCursor();

    void closeTab(int index);
    void tabChanged(int index);



};
#endif // MAINWINDOW_H
