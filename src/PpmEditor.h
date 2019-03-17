#ifndef PPM_EDITOR_H
#define PPM_EDITOR_H

#include "ImageEditor.h"

#include <vector>
#include <string>
#include <sstream>

class PpmEditor : public ImageEditor
{
private:
	// Initialize object with default values
	void init() override;

	/**
	Reads a PPM image from fileName

	@param const char * fileName Name of file to read from.
	*/
	void read(const char * fileName) override;

	/**
	Writes a PPM image to fileName

	@param const char * fileName Name of file to be written to.
	*/
	void write(const char * fileName) override;

	void readHeader(std::ifstream & in) override;

public:
	// TODO : Getters and setters probably?
	// Containers to store RGB values
	std::vector<unsigned char> red;
	std::vector<unsigned char> green;
	std::vector<unsigned char> blue;

	// Maximum colour value (Default 255)
	unsigned int maxColourValue;

	void fill(const unsigned int width, const unsigned int height, unsigned int maxColourValue = 255) override;

	PpmEditor();

	/**
	Opens a fileName and reads it

	@param const char * fileName Name of file to be read.
	*/
	PpmEditor(const char * fileName);

	/**
	Generating an empty image object with rgb values set to 0 by default.

	@param const unsigned int width Width of image.
	@param const unsigned int height Height of image.
	*/
	PpmEditor(const unsigned int width, const unsigned int height, unsigned int maxColourValue = 255);

	unsigned int getMaxColourValue() const;
	unsigned int getAvgColourValuePerPixel(unsigned int pos) const override;
};

#endif