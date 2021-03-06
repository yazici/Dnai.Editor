#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include <QQuickItem>

namespace dnai
{
	namespace views
	{
		class CustomShape : public QQuickItem
		{
			Q_OBJECT

		public:
			Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
			Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
			Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
			Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)

		public:
			explicit CustomShape(QQuickItem *parent = nullptr);
			virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

		public:
			qreal radius() const { return m_radius; }
			qreal borderWidth() const { return m_borderWidth; }
			const QColor &fillColor() const { return m_fillColor; }
			const QColor &borderColor() const { return m_borderColor; }

		public:
			void setRadius(qreal radius);
			virtual void setBorderWidth(qreal w);
			virtual void setFillColor(const QColor &color);
			virtual void setBorderColor(const QColor &color);

			void resetRadius();
			void resetBorderWidth();
			void resetBorderColor();
			void resetFillColor();
			void resetPos();
			void resetShape();

		signals:
			void radiusChanged(qreal radius);
			void borderWidthChanged(qreal w);
			void fillColorChanged(const QColor &color);
			void borderColorChanged(const QColor &color);


		protected:
			qreal m_radius;
			qreal m_borderWidth;
			QColor m_fillColor;
			QColor m_borderColor;

			qreal m_saveRadius;
			qreal m_saveBorderWidth;
			QColor m_saveFillColor;
			QColor m_saveBorderColor;
			QPointF m_savePos;
		};
	}
}

#endif // CUSTOMSHAPE_H
