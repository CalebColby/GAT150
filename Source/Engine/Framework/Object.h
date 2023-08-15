#pragma once

#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	bool Read(const rapidjson::Value& value); \
	class Register \
		{ \
		public: \
			Register() \
			{ \
				Factory::Instance().Register<classname>(#classname); \
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
			m_name{name}
		{}
		virtual ~Object() {	OnDestroy(); }

		CLASS_DECLARATION(Object);

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string m_name;
	};
}