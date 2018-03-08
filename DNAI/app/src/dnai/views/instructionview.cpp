#include "dnai/views/instructionview.h"

dnai::views::InstructionView::InstructionView(QQuickItem* parent) : ContextView("qrc:/resources/Components/NodeCanvas.qml", parent)
{
}

dnai::views::CanvasNode* dnai::views::InstructionView::canvas() const
{
	return dynamic_cast<CanvasNode*>(getView());
}

dnai::models::Instruction* dnai::views::InstructionView::instructionModel() const
{
    return dynamic_cast<dnai::models::Instruction *>(getModel("instructionModel"));
}

void dnai::views::InstructionView::setInstructionModel(dnai::models::Instruction* model)
{
	if (instructionModel() == model)
		return;
	addModel(static_cast<QObject*>(model), "instructionModel");
	instructionModelChanged(model);
}
