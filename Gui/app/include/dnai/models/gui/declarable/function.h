#ifndef DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
#define DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>

#include "dnai/interfaces/ientity.h"
#include "dnai/interfaces/iinstruction.h"
#include "dnai/models/gui/data/function.h"
#include "dnai/models/gui/flow.h"

namespace dnai
{
	namespace models
	{
        class Entity;

		namespace gui
		{
			class EntityList;
			namespace declarable
			{
				class Function : public QObject, public Entity<data::Function, Function>
                {
					Q_OBJECT
					Q_PROPERTY(dnai::models::gui::EntityList *inputModels READ inputModels WRITE setInputModels NOTIFY inputModelsChanged)
					Q_PROPERTY(dnai::models::gui::EntityList *outputModels READ outputModels WRITE setOutputModels NOTIFY outputModelsChanged)
                    Q_PROPERTY(qint32 entryPointX READ entryPointX WRITE setEntryPointX)
                    Q_PROPERTY(qint32 entryPointY READ entryPointY WRITE setEntryPointY)

				public:
					explicit Function(QObject *parent = nullptr);
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;

				public:
					//Implementation of IInstruction
					const QList<models::Entity*> &inputs() const;
					bool setInputs(const QList<models::Entity*>& inputs);

					const QList<models::Entity*> &outputs() const;
					bool setOutputs(const QList<models::Entity*>& outputs);

					const QList<models::gui::Instruction *> &instructions() const;

					const QList<dnai::models::gui::IoLink *> &iolinks() const;
					bool setIoLinks(const QList<dnai::models::gui::IoLink *> &);
					void appendIoLink(dnai::models::gui::IoLink *);
					void removeIoLink(dnai::models::gui::IoLink* link);
                    Q_INVOKABLE dnai::models::gui::IoLink *findIOLink(QUuid const &instruction, QString const &input) const;

					const QList<dnai::models::gui::FlowLink *> &flowlinks() const;
					bool setFlowLinks(const QList<dnai::models::gui::FlowLink *> &);
					void appendFlowLink(dnai::models::gui::FlowLink *);
					void removeFlowLink(dnai::models::gui::FlowLink* link);
                    Q_INVOKABLE dnai::models::gui::FlowLink *findFlowLink(QUuid const &from, quint32 outPin, QUuid const &to = QUuid()) const;

					Q_INVOKABLE void addInput(models::Entity *var);
					Q_INVOKABLE void addOutput(models::Entity *var);
					Q_INVOKABLE void removeInput(const QString &name);
					Q_INVOKABLE void removeOutput(const QString &name);

					Q_INVOKABLE void moveInputUp(int index);
					Q_INVOKABLE void moveOutputUp(int index);

					Q_INVOKABLE void moveInputDown(int index);
					Q_INVOKABLE void moveOutputDown(int index);

					EntityList *inputModels() const;
					EntityList *outputModels() const;
					void setInputModels(EntityList* inputs);
					void setOutputModels(EntityList* outputs);

					void addInstruction(Instruction *instruction);
                    void removeInstruction(Instruction *instruction);
                    Instruction* getInstruction(const QUuid& uuid);

					Q_INVOKABLE quint32 getInputId(QString const &name) const;
					Q_INVOKABLE quint32 getOutputId(QString const &name) const;

                    models::Entity *getInput(QString const &name) const;
                    models::Entity *getOutput(QString const &name) const;

                    models::gui::Instruction *getInstruction(quint32 uid) const;
                    models::gui::Instruction *getInstruction(const QUuid &guid) const;

                    bool hasInput(QString const &name, QUuid const &type = QUuid()) const;
                    bool hasOutput(QString const &name, QUuid const &type = QUuid()) const;

                    models::gui::Instruction *entryPoint() const;
                    void setEntryPoint(QUuid uid);

                    qint32 entryPointX() const;
                    void setEntryPointX(qint32 x);

                    qint32 entryPointY() const;
                    void setEntryPointY(qint32 y);

				signals:
					void inputModelsChanged(dnai::models::gui::EntityList* inputs);
					void outputModelsChanged(dnai::models::gui::EntityList* outputs);

				private:
					EntityList *m_finputs;
					EntityList *m_foutputs;
                    QHash<QUuid, Instruction*> m_functionsHash;

                private:
                    struct EntryPoint
                    {
                        qint32 x = 0;
                        qint32 y = 0;
                        QUuid guid;
                    };

                    EntryPoint m_entryPoint;
				};
            }
        }
    }
}

#endif //DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
