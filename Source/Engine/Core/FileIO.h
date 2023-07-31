#pragma once
#include <filesystem>
#include <string>

namespace neu {
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path);
	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);
	bool overwriteFile(const std::filesystem::path& path, std::string& saveData);
}
