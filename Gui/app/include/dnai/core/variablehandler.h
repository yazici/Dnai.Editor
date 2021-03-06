#ifndef DNAI_CORE_VARIABLEHANDLER_H
#define DNAI_CORE_VARIABLEHANDLER_H

#include <QObject>
#include <list>

#include "entitymanager.h"
#include "core.h"

namespace dnai
{
    namespace gcore
    {
        class VariableHandler : public QObject
        {
            Q_OBJECT

        public:
            VariableHandler(EntityManager &manager);
            virtual ~VariableHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);

        public:
            Q_INVOKABLE void setType(quint32 variable, quint32 type, bool save = true);
            Q_INVOKABLE void setValue(quint32 variable, QString const &value, bool save = true);

        private:
            void refreshVariables();
            models::gui::declarable::Variable *getVariableData(::core::EntityID variable, bool throws = false);

        public:
            void onTypeSet(::core::EntityID variable, ::core::EntityID type);
            void onSetTypeError(::core::EntityID variable, ::core::EntityID type, QString const &message);

            void onValueSet(::core::EntityID variable, QString const &value);
            void onSetValueError(::core::EntityID variable, QString const &value, QString const &message);

        signals:
            void typeSet(dnai::models::Entity *variable, dnai::models::Entity *type);
            void valueSet(dnai::models::Entity *variable, QString value);

        private:
            EntityManager &manager;

        private:
            std::list<models::Entity *> m_pendingVar;
        };
    }
}

#endif // DNAI_CORE_VARIABLEHANDLER_H
