#include "Object.h"

namespace neu
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

		//Json::Read(value, "name", name);

		return true;
	}
}