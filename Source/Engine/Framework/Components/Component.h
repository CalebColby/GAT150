#pragma once

#include "Framework/Object.h"

namespace neu
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;


		Actor* GetOwner() { return m_owner; }
	protected:
		class Actor* m_owner = nullptr;
	};
}