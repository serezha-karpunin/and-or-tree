//#include "tree.h"

//Tree::Tree()
//{
//    this->root.setName("Авто");
//    this->root.setType(And);
//}

//Node<QString> Tree::getRoot() const
//{
//    return root;
//}

//QString Tree::getName() const
//{
//    return name;
//}

//void Tree::setName(const QString &value)
//{
//    name = value;
//}

//void Tree::addNode(int parentID, QString name, Type type)
//{
//    root.addNode(parentID, name, type);
//}

//void Tree::deleteNode(int id)
//{
//    if(id == root.getId())
//        this->clear();
//    root.deleteNode(id);
//    //Переместить к использованию Tree::deleteNode, т.к. здесь ловить исключение не надо
////    try
////    {
////    }
////    catch(TreeException& e)
////    {
////        QMessageBox::critical(nullptr, "Error", e.what(), QMessageBox::Ok);
////    }
//}

//void Tree::clear()
//{
//    root = Node<QString>();
//}

//qint32 Tree::size()
//{
//    return root.size();
//}


////Node *Tree::find(QString name)
////{
////    parent.find(name);

////}


////Tree::Tree(std::initializer_list<int> values)/* :
////    size(values.size()),
////    data(new int[size])*/
////{
////    std::copy(values.begin(), values.end(), data.get());
////}

//Tree::iterator Tree::begin()
//{
//    return TreeIterator(this, &root);
////    return iterator(data.get());
//}

//Tree::iterator Tree::end()
//{
//    Node<QString> * last = &this->root;
//    while(last->children.size())
//    {
//        auto save = last->children.end();
//        save--;
//        last = &*(save);
//    }
//    return iterator(this, last);
//}

////Tree::const_iterator Tree::begin() const
////{
////    return const_iterator(data.get());
////}

////Tree::const_iterator Tree::end() const
////{
////    return const_iterator(data.get() + size);
////}

//QDataStream& operator<<(QDataStream& os, const Tree& tree)
//{
//    os << tree.name;
//    os << tree.root;
//    return os;
//}

//QDataStream& operator>>(QDataStream& is, Tree& tree)
//{
//    is >> tree.name;
//    is >> tree.root;
//    return is;
//}
