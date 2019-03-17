#ifndef RAW_PPM_EDITOR_H
#define RAW_PPM_EDITOR_H

#include "PpmEditor.h"

#include <vector>
#include <string>
#include <sstream>

class RawPpmEditor : public PpmEditor
{
private:
	bool isValidExtension(std::string line) override;
	void readPixels(std::ifstream & in) override;
	void openReadFile(std::ifstream & in, const char * fileName) override;

	void addFileFormat(std::ofstream & out) override;
	void openWriteFile(std::ofstream & out, const char * fileName) override;
	void writePixels(std::ofstream & out) override;

public:

	RawPpmEditor();
	RawPpmEditor(const char * fileName);
	RawPpmEditor(const unsigned int width, const unsigned int height);
};

#endif