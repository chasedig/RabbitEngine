#pragma once
namespace RBT
{
	class Listener
	{
		friend class Event;
		typedef void (*EventFunction)();

		protected:
			Listener(EventFunction f)
			{
				this->attached_function = f;
			}
			EventFunction attached_function;
	};
}