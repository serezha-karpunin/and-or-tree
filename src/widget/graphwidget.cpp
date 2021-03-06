#include "graphwidget.h"
#include "edge.h"
#include "treenode.h"
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);

    setScene(scene);
    setMinimumSize(400, 400);
}

void GraphWidget::configure(Tree<QString> *tree)
{
    this->tree = tree;
    scene()->clear();
    drawTreeNode(&(tree->root), 0, -300, 300, true);
}

TreeNode* GraphWidget::drawTreeNode(Node<QString> *node, int level, int w1, int w2, bool isRoot)
{
    TreeNode *treeNode = new TreeNode();
    treeNode->setNode(node);
    treeNode->setIsRoot(isRoot);
    this->scene()->addItem(treeNode);
    treeNode->setPos(w1 + (w2-w1)/2,-200 + level*100);

    TreeNode* childTreeNode;
    int sectorCounter = 0;

    for(auto iter = node->children.begin(); iter!=node->children.end(); ++iter)
    {
        int sectorWidth = (w2 - w1) / node->children.size();
        childTreeNode = drawTreeNode(&(*iter), level + 1, w1 + sectorCounter*sectorWidth, w1 + (sectorCounter+1)*sectorWidth, false);
        this->scene()->addItem(new Edge(treeNode, childTreeNode));
        sectorCounter++;
    }

    QObject::connect(treeNode, SIGNAL(treeNodeClicked(Node<QString>*, bool)), this, SLOT(handleTreeNodeClick(Node<QString>*, bool)));
    return treeNode;
}

void GraphWidget::handleTreeNodeClick(Node<QString> *node, bool isRoot)
{
    emit shouldChangeNodeEditor(tree, node, isRoot);
}

void GraphWidget::refreshWidget()
{
    configure(tree);
}
