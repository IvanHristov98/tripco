#ifndef RAW_PBM_EDITOR_H
#define RAW_PBM_EDITOR_H

#include "PbmEditor.h"

class RawPbmEditor : public PbmEditor
{
private:
	bool isValidExtension(std::string line) override;
	void openReadFile(std::ifstream & in, const char * fileName) override;
	void readPixels(std::ifstream & in) override;

	void addFileFormat(std::ofstream & out) override;
	void openWriteFile(std::ofstream & out, const char * fileName) override;
	void writePixels(std::ofstream & out) override;

public:

	RawPbmEditor();

	RawPbmEditor(const char * fileName);

	RawPbmEditor(const unsigned int width, const unsigned int height);
};

#endif