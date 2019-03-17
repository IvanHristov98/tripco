#ifndef IMAGE_EDITOR_H
#define IMAGE_EDITOR_H

#include "FileEditor.h"

class ImageEditor : public FileEditor
{
protected:
	// Number of the rows and columns in the PBM file
	unsigned int numRows;
	unsigned int numCols;

	ImageEditor();

	// Check for a valid extension
	virtual bool isValidExtension(std::string line) = 0;
	// Reads pixels
	virtual void readPixels(std::ifstream & in) = 0;
	// Opens a file for reading by fileName
	virtual void openReadFile(std::ifstream & in, const char * fileName) = 0;
	
	// Adds a file format
	virtual void addFileFormat(std::ofstream & out) = 0;
	// Opens a file for writing by fileName
	virtual void openWriteFile(std::ofstream & out, const char * fileName) = 0;
	// Writes pixels
	virtual void writePixels(std::ofstream & out) = 0;

	virtual void readHeader(std::ifstream & in) = 0;

	// Image  width and height
	unsigned int width;
	unsigned int height;

	unsigned int sizeInPixels;

public:

	unsigned int getNumRows() const;
	unsigned int getNumCols() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;

	unsigned int getSizeInPixels() const;
	// Returns the average value of each set of pixels in group of vectors
	virtual unsigned int getAvgColourValuePerPixel(unsigned int pos) const = 0;
	// Fills pixels
	virtual void fill(const unsigned int width, const unsigned int height, unsigned int maxColourValue) = 0;
};

#endif