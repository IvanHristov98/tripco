#ifndef PBM_EDITOR_H
#define PBM_EDITOR_H

#include "ImageEditor.h"

#include <vector>
#include <string>
#include <sstream>

class PbmEditor : public ImageEditor
{
protected:
	// Initialize object with default values
	void init() override;

	void read(const char * fileName) override;

	void write(const char * fileName) override;

	void readHeader(std::ifstream & in) override;

public:
	// TODO : Getters and setters
	// Container to store byte values
	std::vector<unsigned char> bytes;

	void fill(const unsigned int width, const unsigned int height, unsigned int maxColourValue = 0) override;

	PbmEditor();
	PbmEditor(const char * fileName);
	PbmEditor(const unsigned int width, const unsigned int height);

	unsigned int getAvgColourValuePerPixel(unsigned int pos) const override;
};

#endif