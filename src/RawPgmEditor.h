#ifndef RAW_PGM_EDITOR_H
#define RAW_PGM_EDITOR_H

#include "PgmEditor.h"

#include <vector>
#include <string>
#include <sstream>

class RawPgmEditor : public PgmEditor
{
private:
	bool isValidExtension(std::string line) override;
	void readPixels(std::ifstream & in) override;
	void openReadFile(std::ifstream & in, const char * fileName) override;

	void addFileFormat(std::ofstream & out) override;
	void openWriteFile(std::ofstream & out, const char * fileName) override;
	void writePixels(std::ofstream & out) override;

public:

	RawPgmEditor();
	RawPgmEditor(const char * fileName);
	RawPgmEditor(const unsigned int width, const unsigned int height);
};

#endif