#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "EditorFactory.h"

enum RGB
{
	Multi,
	Red,
	Green,
	Blue
};

class Histogram
{
private:
	FileEditor * source;
	PlainPpmEditor histogram;

	// Checks if an editor is valid
	bool isValidEditor(EditorTypes type);
	void fill();

	unsigned int * getIntensity(RGB colour);

	// Fill all pixels white
	void fillWhite();
	// Fill pixels by colour
	void fillRed(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity = 255);
	void fillGreen(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity = 255);
	void fillBlue(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity = 255);

	float getApproxIntensityPercentage(unsigned int colourIntensity, RGB colour);
	unsigned int shiftOpacity(float opacity, unsigned int shade = 255);

public:
	Histogram();
	Histogram(FileEditor * source);
	~Histogram() {}

	// Opens source
	void open(FileEditor * source);
	// Saves histogram by name
	void saveAs(const char * fileName);
	// Generates a new histogram
	void generate(bool isRed = true, bool isGreen = true, bool isBlue = true);
};

#endif