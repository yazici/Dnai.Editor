#ifndef DNAI_MODELS_GUI_DECLARABLE_ENTITY_H
#define DNAI_MODELS_GUI_DECLARABLE_ENTITY_H

#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/models/gui/data/entity.h"
#include "dnai/interfaces/ientity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				template<class T, class U>
				class Entity : public interfaces::IEntity, public interfaces::IModelData<T>, public interfaces::ASerializable<U>
				{
					//IModelData implementation
				public:
					Entity() = default;
                    ~Entity() override = default;

                    bool setData(const T& data) override
					{
						if (m_data == data)
							return false;
						m_data = data;
						return true;
					}

                    int index() const override
					{
						return m_data.index;
					}

                    bool setIndex(const int index) override
					{
						if (m_data.index == index)
							return false;
						m_data.index = index;
						return true;
					}

                    QUuid listIndex() const override
					{
						return m_data.listIndex;
					}

                    bool setListIndex(QUuid listIndex) override
					{
						if (m_data.listIndex == listIndex)
							return false;
						m_data.listIndex = listIndex;
						return true;
					}

                    const QString& description() const override
					{
						return m_data.description;
					}

                    bool setDescription(const QString& description) override
					{
						if (m_data.description == description)
							return false;
						m_data.description = description;
						return true;
					}

                    bool expanded() const override
					{
						return m_data.expanded;
					}

                    bool setExpanded(bool exp) override
					{
						if (m_data.expanded == exp)
							return false;
						m_data.expanded = exp;
						return true;
					}

                    const T& data() const override
					{
						return m_data;
					}

                    void serialize(QJsonObject& obj) const override
					{
//						obj["expanded"] = m_data.expanded;
						obj["description"] = m_data.description;
						obj["index"] = m_data.index;
						obj["listIndex"] = m_data.listIndex.toString();
					}
				protected:
                    void _deserialize(const QJsonObject& obj) override
					{
//						m_data.expanded = obj["expanded"].toBool();
						m_data.description = obj["description"].toString();
						m_data.index = obj["index"].toInt();
						m_data.listIndex = QUuid(obj["listIndex"].toString());
					}

				protected:
					T m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DECLARABLE_ENTITY_H
