#ifndef INPUT_H
#define INPUT_H

#include "io.h"

namespace dnai
{
	namespace views
	{
		class Input : public Io
		{
		public:
			explicit Input(QQuickItem *parent = nullptr);

			/**
			* \brief Refresh BackendIO for Input
			*/
            void refreshBackendIo() override;

			/**
			* \brief Override componentComplete, and init some values
			*/
            void componentComplete() override;

			/**
			* \brief Override findIo, return the IO under the point p of the Node n
			* \param n
			* \param p
			* \return Io *
			*/
            LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) override;
            void updateLink() override;
			void unlinkAll() override;
            void asyncUnlinkAll() override;

		protected:
            void afterRealease(Link *l) override;
		};
	}
}

#endif // INPUT_H
