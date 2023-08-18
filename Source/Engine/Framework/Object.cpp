#include "Object.h"

namespace neu
{
	void Object::Read(const json_t& value)
	{
		READ_DATA(value, name);

		//Json::Read(value, "name", name);

	}
}