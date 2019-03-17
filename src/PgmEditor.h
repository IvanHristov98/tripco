#ifndef PGM_EDITOR_H
#define PGM_EDITOR_H

#include "ImageEditor.h"

#include <vector>
#include <string>
#include <sstream>

class PgmEditor : public ImageEditor
{
protected:
	// Maximum colour value (Default 255)
	unsigned int maxColourValue;

	// Initialize object with default values
	void init() override;

	void read(const char * fileName) override;

	void write(const char * fileName) override;

	void readHeader(std::ifstream & in) override;

public:
	//Container to store gray values
	std::vector<unsigned char> gray;

	void fill(const unsigned int width, const unsigned int height, unsigned int maxColourValue = 255);

	PgmEditor();
	PgmEditor(const char * fileName);
	PgmEditor(const unsigned int width, const unsigned int height, unsigned int maxColourValue = 255);

	unsigned int getMaxColourValue() const;
	unsigned int getAvgColourValuePerPixel(unsigned int pos) const override;
};

#endif