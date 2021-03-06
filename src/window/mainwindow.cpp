#include "mainwindow.h"
#include "addtreepopup.h"
#include "ui_mainwindow.h"
#include "widget/search/searchcriteriawidget.h"
#include "service/search.h"
#include <QLayoutItem>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addTreePopup(new AddTreePopup),
    stateManager(new StateManager)
{
    initializeWidget();
    defineConnects();
    restoreState();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete addTreePopup;
    delete nodeEditor;
    delete stateManager;
    delete searchCriteriaBoxLayout;
    delete searchResultBoxLayout;
}

void MainWindow::handleAddTreeButtonClick()
{
    addTreePopup->show();
}

void MainWindow::openEditor(Tree<QString> *tree)
{
    ui->stackedWidget->setCurrentIndex(1);
    graphWidget->configure(tree);
}

void MainWindow::handleAddSearchCriteriaButtonClick()
{
    QVector<Tree<QString>*> trees = stateManager->getTrees();
    QMap<QString, QSet<QString>> possibleSearchCriteria = findProperties(trees);
    searchCriteriaBoxLayout->addSearchCriteriaWidget(new SearchCriteriaWidget(possibleSearchCriteria));
}

void MainWindow::handleSearchButtonClick()
{
    QMap<QString, QString> searchCriteria = searchCriteriaBoxLayout->getSearchCriteria();
    QVector<Tree<QString>*> searchResult = findTrees(stateManager->getTrees(), searchCriteria);
    searchResultBoxLayout->configure(searchResult);
}

void MainWindow::handleCloseEditorButtonClick()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::refreshListView()
{
    auto trees = stateManager->getTrees();
    listViewBoxLayout->configure(trees);
}

void MainWindow::initializeWidget(){
    ui->setupUi(this);

    nodeEditor = new NodeEditor();
    graphWidget = new GraphWidget();

    searchCriteriaBoxLayout = new SearchCriteriaBoxLayout();
    searchResultBoxLayout = new SearchResultBoxLayout();
    listViewBoxLayout = new ListViewBoxLayout();

    ui->editorLayout->addWidget(nodeEditor);
    ui->graphicsView->setScene(graphWidget->scene());
    ui->searchCriteriaBoxLayoutWrapper->addLayout(searchCriteriaBoxLayout);
    ui->searchCriteriaBoxLayoutWrapper->addStretch(1);
    ui->listViewBoxLayoutWrapper->addLayout(listViewBoxLayout);
    ui->listViewBoxLayoutWrapper->addStretch(1);

    ui->searchResultBoxLayoutWrapper->addLayout(searchResultBoxLayout);
    ui->searchResultBoxLayoutWrapper->addStretch(1);
}

void MainWindow::defineConnects(){
    QObject::connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(handleAddTreeButtonClick()));
    QObject::connect(ui->addSearchCriteriaButton, SIGNAL(clicked(bool)), this, SLOT(handleAddSearchCriteriaButtonClick()));
    QObject::connect(ui->searchButton, SIGNAL(clicked(bool)), this, SLOT(handleSearchButtonClick()));
    QObject::connect(ui->closeEditorButton, SIGNAL(clicked(bool)), this, SLOT(handleCloseEditorButtonClick()));

    QObject::connect(listViewBoxLayout, SIGNAL(shouldOpenTreeEditor(Tree<QString>*)), this, SLOT(openEditor(Tree<QString>*)));
    QObject::connect(listViewBoxLayout, SIGNAL(shouldRemoveTree(Tree<QString>*)), stateManager, SLOT(removeTree(Tree<QString>*)));

    QObject::connect(addTreePopup, SIGNAL(createTree(QString)), stateManager, SLOT(createTree(QString)));
    QObject::connect(stateManager, SIGNAL(treeCreated()), this, SLOT(refreshListView()));
    QObject::connect(stateManager, SIGNAL(treeRemoved()), this, SLOT(refreshListView()));
    QObject::connect(graphWidget, SIGNAL(shouldChangeNodeEditor(Tree<QString>*, Node<QString>*, bool)), nodeEditor, SLOT(configure(Tree<QString>*, Node<QString>*, bool)));

    QObject::connect(nodeEditor, SIGNAL(shouldRefreshGraphWidget()), graphWidget, SLOT(refreshWidget()));
}

void MainWindow::restoreState()
{
    stateManager->deserializeState();
}
