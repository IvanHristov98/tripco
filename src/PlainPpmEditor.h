#ifndef PLAIN_PPM_EDITOR_H
#define PLAIN_PPM_EDITOR_H

#include "PpmEditor.h"

class PlainPpmEditor : public PpmEditor
{
private:
	bool isValidExtension(std::string line) override;
	void readPixels(std::ifstream & in) override;
	void openReadFile(std::ifstream & in, const char * fileName) override;

	void addFileFormat(std::ofstream & out) override;
	void openWriteFile(std::ofstream & out, const char * fileName) override;
	void writePixels(std::ofstream & out) override;

public:

	PlainPpmEditor();
	PlainPpmEditor(const char * fileName);
	PlainPpmEditor(const unsigned int width, const unsigned int height);
};

#endif