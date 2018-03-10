#ifndef DNAI_MODELS_GENERICTREEITEM_H
#define DNAI_MODELS_GENERICTREEITEM_H

#include <QModelIndex>

namespace dnai
{
	namespace models
	{
		template <class T>
		class GenericTreeItem : public QObject
		{
		public:
			GenericTreeItem(QObject *parent = nullptr) : QObject(parent) {}
			explicit GenericTreeItem(const QList<QVariant> &data, T *parentItem = nullptr) : QObject(nullptr) {}
            virtual ~GenericTreeItem() = default;
			void appendChild(T *child) { m_childItems.append(child); }
			T *child(int row) const { return m_childItems.at(row); }
			const QList<T*> &children() const { return m_childItems; }

			int childCount() const { return m_childItems.count(); }
			int columnCount() const { return m_itemData.count(); }

			QVariant data(int column) const { return m_itemData.at(column); }
			int row() const
			{
//				if (m_parentItem)
//                                    return m_parentItem->m_childItems.indexOf(static_cast<T *const&>(this));
				return 0;
			}
			T *parentItem() { return m_parentItem; }
			const QModelIndex &idxmodel() const { return m_idx; }
			void setIdx(const QModelIndex &ref)
			{
				if (ref == m_idx)
					return;
				m_idx = ref;
			}

		private:
			QList<T*> m_childItems;
			QList<QVariant> m_itemData;
			T *m_parentItem;
			QModelIndex m_idx;

		};
	}
}

#endif //DNAI_MODELS_GENERICTREEITEM_H
