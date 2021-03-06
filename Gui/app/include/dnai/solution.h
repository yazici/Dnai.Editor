#ifndef DNAI_SOLUTION_H
#define DNAI_SOLUTION_H

#include "interfaces/isolution.h"
#include "interfaces/iserializable.h"
#include <QAbstractListModel>
#include "models.h"
#include <QQuickItem>

namespace dnai
{
	class Project;

	class Solution : public QAbstractListModel, public interfaces::ISolution, public interfaces::ASerializable<Solution>
	{
        Q_OBJECT
		Q_PROPERTY(QQuickItem *selectedEntity READ selectedEntity WRITE setSelectedEntity NOTIFY selectedEntityChanged)
	public:
		enum ROLES
		{
			ITEM = Qt::UserRole + 1,
			NAME,
			DESCRIPTION
		};

		Solution();
        Solution(const QString filename);
        ~Solution();
		Q_INVOKABLE void save() override;
        Q_INVOKABLE bool isProjectsSaved();
		void load(const QString& path) override;
        virtual QString path() const override;
		void close() override;
		const QString& version() const override;
		void setVersion(const QString& version) override;
		const QString& name() const override;
		void setName(const QString& name) override;
		const QString& description() const override;
		void setDescription(const QString& desc) override;
		const QJsonObject& jsonData() const override;
		const QList<IProject*>& projects() const override;
		void addProject(IProject*) override;
		IProject *seletedProject() const override;
		bool selectProject(IProject*) override;
		void serialize(QJsonObject& obj) const override;
		const QString& fileName() const override;
		void setFileName(const QString& name) override;
		Q_INVOKABLE int getRoleKey(QString rolename) const;
		Q_INVOKABLE bool selectProject(dnai::Project*);
		Q_INVOKABLE dnai::Project *selectedProject() const;

		QQuickItem *selectedEntity() const;
		void setSelectedEntity(QQuickItem *entity);

	signals:
		void selectedEntityChanged(QQuickItem *entity);

	protected:
		void _deserialize(const QJsonObject& obj) override;

	public:
		int rowCount(const QModelIndex& parent) const override;
		QVariant data(const QModelIndex& index, int role) const override;

	private:
		IProject* m_selectedProject;
		QList<IProject*> m_projects;
		QJsonObject m_data;
		QString m_description;
		QString m_name;
		QString m_version;
		QFile *m_file;
		QString m_filename;
		QQuickItem* m_selectedEntity;
		virtual QHash<int, QByteArray> roleNames() const override;
	};
}


#endif //DNAI_SOLUTION_H
