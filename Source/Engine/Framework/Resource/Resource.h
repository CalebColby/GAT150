#pragma once
#include <string>
#include <memory>

namespace neu
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	};

	template<typename T = Resource>
	using res_t = std::shared_ptr<T>;

	
}