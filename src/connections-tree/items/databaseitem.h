#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "treeitem.h"
#include "connections-tree/operations.h"
#include <QtConcurrent>

namespace ConnectionsTree {

class NamespaceItem;

class DatabaseItem : public QObject, public TreeItem
{
    Q_OBJECT

public:
    DatabaseItem(const QString& displayName, unsigned int index, int keysCount, QSharedPointer<Operations> operations, const TreeItem *parent);

    QString getDisplayName() const override;
    QIcon getIcon() const override;
    QList<QSharedPointer<TreeItem>> getAllChilds() const override;
    uint childCount() const override;
    QSharedPointer<TreeItem> child(int row) const override;
    const TreeItem* parent() const override;

    bool onClick(ParentView& treeView, QWeakPointer<QTabWidget> tabs) override;
    void onWheelClick(ParentView& treeView, QWeakPointer<QTabWidget> tabs) override;
    QSharedPointer<QMenu> getContextMenu(ParentView& treeView, QWeakPointer<QTabWidget> tabs) override;

    bool isLocked() const override {return false;}

    void loadKeys();

signals:
    void keysLoaded();

protected slots:
    void onKeysRendered();

private:
    class KeysTreeRenderer
    {
    public:        

        QList<QSharedPointer<TreeItem>> renderKeys(QSharedPointer<Operations> operations,
                                                   Operations::RawKeysList keys,
                                                   QRegExp filter,
                                                   QString namespaceSeparator);

    private:                  
         void renderNamaspacedKey(QSharedPointer<NamespaceItem> currItem,
                                  const QString& notProcessedKeyPart,
                                  const QString& fullKey,
                                  QSharedPointer<Operations> operations,
                                  const QString& namespaceSeparator,
                                  QList<QSharedPointer<TreeItem>>& m_result
                                  );
    };

private:
    QString m_name;
    unsigned int m_index;
    int m_keysCount;
    bool m_locked;
    QSharedPointer<Operations> m_operations;
    QList<QSharedPointer<TreeItem>> m_keys;
    QFutureWatcher<QList<QSharedPointer<TreeItem>>> m_keysLoadingWatcher;
    KeysTreeRenderer m_keysRenderer;
};

}

#endif // DATABASEITEM_H
