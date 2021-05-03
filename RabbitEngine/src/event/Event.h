#pragma once
#include <vector>
#include <event/Listener.h>
namespace RBT
{
	class Event
	{
		std::vector<Listener*> observers;
		public:
			void Connect(RBT::Listener::EventFunction func)
			{
				Listener* listener = new Listener(func);
				this->observers.push_back(listener);
			}
			void Fire()
			{
				for (Listener* observer : observers)
				{
					observer->attached_function();
				}
			}
	};
}