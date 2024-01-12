#pragma once

#include "Component.h"
#include "Link.h"
#include "Image.h"

#include <string>
#include <string_view>
#include <filesystem>
#include <vector>
#include <map>
#include <functional>

class FileBrowser : public Component {
public:
	FileBrowser(std::string_view initialPath, int x = 0, int y = 0);
	virtual ~FileBrowser();

	void setCurrentPath(std::string_view path);
	std::string getSelectedFile();

	virtual void onClick(int mouseX, int mouseY, int mouseButton) override;

	void addFilter(std::string fileExtension);

private:
	void setupUI();

	void onLinkClick(int linkNumber);

private:
	// Normally you would calculate this value dynamically, probably using the height of this component, but again this is the way the original editor does it
	static constexpr int MAX_FILES_DISPLAYED = 33;

	std::vector<std::filesystem::path> currentDirectoryPaths;

	std::filesystem::path currentPath;

	std::filesystem::path selectedFile;

	std::vector<Link*> pathLinks;
	std::vector<Image*> directoryArrowImages;

	std::vector<std::string> fileFilter;
};

