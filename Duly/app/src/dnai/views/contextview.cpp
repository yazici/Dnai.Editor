#include "dnai/views/contextview.h"
#include "dnai/dulyapp.h"

dnai::views::ContextView::ContextView(QObject* parent) : QObject(parent), m_view(nullptr), m_progess(1)
{
}

dnai::views::ContextView::ContextView(const QString &qmlview, QObject* parent) : QObject(parent), m_view(nullptr), m_progess(0)
{
	initView(qmlview);
	updateProgress(1);
}

QQuickItem* dnai::views::ContextView::getView() const
{
	return m_view;
}

void dnai::views::ContextView::addModel(QObject* model, const QString& name)
{
	if (!m_models.contains(name))
		m_models[name] = model;
}

QObject* dnai::views::ContextView::getModel(const QString& name) const
{
	if (m_models.contains(name))
		return m_models[name];
	return nullptr;
}

void dnai::views::ContextView::initView(const QString& path)
{
	m_view = dynamic_cast<QQuickItem*>(DulyApp::createQmlObject(path));
}

void dnai::views::ContextView::updateProgress(float percent)
{
	if (percent > 1)
		percent = 1;
	else if (percent < 0)
		percent = 0;
	m_progess = percent;
}
