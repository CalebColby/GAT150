#pragma once

#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	virtual void Read(const neu::json_t& value); \
	virtual std::unique_ptr<Object> Clone() { return std::move(std::make_unique<classname>(*this));  }	\
	class Register \
		{ \
		public: \
			Register() \
			{ \
				neu::Factory::Instance().Register<classname>(#classname); \
			} \
		};

#define CLASS_REGISTER(classname) classname::Register register_class; 

namespace neu
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) :
			name{name}
		{}
		virtual ~Object() {	OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	public:
		std::string name;
		bool active = true;
	};
}