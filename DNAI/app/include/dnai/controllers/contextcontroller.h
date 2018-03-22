#ifndef CONTEXTCONTROLLER_H
#define CONTEXTCONTROLLER_H
#include "icontroller.h"
#include "dnai/models/class.h"
#include "datacomeventfactory.h"

namespace dnai
{
	namespace controllers
	{
        class ContextController : public AController<models::Class, Reply::EntityDeclared const&>
		{
		public:
			ContextController();

			QQuickItem* createView() override;

		protected:
            bool create(Reply::EntityDeclared const& reply);
        private:
	        IClone* clone() const override;
        protected:
            commands::ICommand* createCommand() const override;
		};

	}
}

#endif //CONTEXTCONTROLLER_H
