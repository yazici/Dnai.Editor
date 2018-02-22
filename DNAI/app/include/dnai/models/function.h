#ifndef MODEL_FUNCTION_H
#define MODEL_FUNCTION_H

#include <QList>
#include "dnai/models/common.h"
#include "dnai/models/variable.h"
#include "dnai/models/input.h"
#include "dnai/models/output.h"
#include "dnai/models/node.h"
#include "dnai/models/position.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Function: public Common, public Position, virtual public IModel
{
public:
	Function(qint32 uid, QString const& name, QString const& description, QVector2D const& position, int index, int listindex,
	         QObject* parent = nullptr);
    virtual ~Function();

private:
    QList<Variable*> m_variables;
    QList<Input*> m_inputs;
    QList<Output*> m_outputs;
    QList<Node*> m_nodes;

public:
    QList<Variable*> variables() const;
    QList<Input*> inputs() const;
    QList<Output*> outputs() const;
    QList<Node*> nodes() const;

public:
    void addVariable(Variable *);
    void addInput(Input *);
    void addOutput(Output *);
    void addNode(Node *);

public:
    void removeVariable(Variable *);
    void removeInput(Input *);
    void removeOutput(Output *);
    void removeNode(Node *);

    // IModel interface
public:
    virtual void serialize(QJsonObject &) const;
    virtual void declare() const;

    // IClone interface
private:
    IClone *clone() const;
};
}
}

#endif // MODEL_FUNCTION_H
