#ifndef PLAIN_PBM_EDITOR_H
#define PLAIN_PBM_EDITOR_H

#include "PbmEditor.h"

class PlainPbmEditor : public PbmEditor
{
private:
	bool isValidExtension(std::string line) override;
	void readPixels(std::ifstream & in) override;
	void openReadFile(std::ifstream & in, const char * fileName) override;
	
	void addFileFormat(std::ofstream & out) override;
	void openWriteFile(std::ofstream & out, const char * fileName) override;
	void writePixels(std::ofstream & out) override;

public:

	PlainPbmEditor();
	PlainPbmEditor(const char * fileName);
	PlainPbmEditor(const unsigned int width, const unsigned int height);
};

#endif