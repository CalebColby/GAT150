#include "Object.h"

namespace neu
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

		//Json::Read(value, "name", name);

	}
}