#include "Histogram.h"


float Histogram::getApproxIntensityPercentage(unsigned int colourIntensity, RGB type)
{
	unsigned int numMatches = 0;
	unsigned int numPixels = ((PpmEditor *)this->source)->getSizeInPixels();

	for (unsigned int i = 0; i < numPixels; i++)
	{
		switch (type)
		{
		case Red:
			if ((unsigned int)((PpmEditor *)this->source)->red[i] == colourIntensity) { numMatches++; }

			break;
		case Green:
			if ((unsigned int)((PpmEditor *)this->source)->green[i] == colourIntensity) { numMatches++; }

			break;
		case Blue:
			if ((unsigned int)((PpmEditor *)this->source)->blue[i] == colourIntensity) { numMatches++; }

			break;
		}
		
	}

	return ((float)numMatches / numPixels) * 100;
}

unsigned int Histogram::shiftOpacity(float opacity, unsigned int shade)
{
	return shade * (1-opacity);
}

bool Histogram::isValidEditor(EditorTypes type)
{
	if (type == EditorTypes::PlainPPM) { return true; }
	if (type == EditorTypes::RawPPM) { return true; }

	return false;
}

void Histogram::fill()
{

	PpmEditor * castedSource = (PpmEditor *)this->source;

	this->histogram.fill(255, 100, castedSource->getMaxColourValue());
}

unsigned int * Histogram::getIntensity(RGB colour)
{
	unsigned int numIntensities = ((PpmEditor *)this->source)->getMaxColourValue();

	unsigned int * intensity = new unsigned int[numIntensities];

	unsigned int size = ((PpmEditor *)this->source)->getSizeInPixels();

	for (unsigned int i = 0; i < numIntensities; i++)
	{
		float aproxVal = this->getApproxIntensityPercentage(i, colour);

		if (aproxVal > 0 && aproxVal <= 1) { intensity[i] = 1; }
		else
		{
			intensity[i] = (unsigned int)aproxVal;
		}
	}

	return intensity;
}

void Histogram::fillWhite()
{
	const unsigned int DEFAULT_WHITE_SHADE = 255;

	for (unsigned int i = 0; i < this->histogram.getSizeInPixels(); i++)
	{
		this->histogram.red[i] = DEFAULT_WHITE_SHADE;
		this->histogram.green[i] = DEFAULT_WHITE_SHADE;
		this->histogram.blue[i] = DEFAULT_WHITE_SHADE;
	}
}

void Histogram::fillRed(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity)
{
	this->histogram.red[pixelPos] = defaultColourIntensity;
	unsigned int maxColourValue = this->histogram.getMaxColourValue();

	if ((this->histogram.getHeight() - numRow) == height)
	{
		this->histogram.green[pixelPos] = 0;
		this->histogram.blue[pixelPos] = 0;
	}
	else if ((this->histogram.getHeight() - numRow) < height)
	{
		this->histogram.green[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.green[pixelPos] %= maxColourValue;

		this->histogram.blue[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.blue[pixelPos] %= maxColourValue;
	}
}

void Histogram::fillGreen(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity)
{
	this->histogram.green[pixelPos] = defaultColourIntensity;
	unsigned int maxColourValue = this->histogram.getMaxColourValue();

	if ((this->histogram.getHeight() - numRow) == height)
	{
		this->histogram.red[pixelPos] = 0;
		this->histogram.blue[pixelPos] = 0;
	}
	else if ((this->histogram.getHeight() - numRow) < height)
	{
		this->histogram.red[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.red[pixelPos] %= maxColourValue;

		this->histogram.blue[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.blue[pixelPos] %= maxColourValue;
	}
}

void Histogram::fillBlue(unsigned int numRow, unsigned int numCol, unsigned int height, unsigned int pixelPos, const unsigned int defaultColourIntensity)
{
	this->histogram.blue[pixelPos] = defaultColourIntensity;
	unsigned int maxColourValue = this->histogram.getMaxColourValue();

	if ((this->histogram.getHeight() - numRow) == height)
	{
		this->histogram.red[pixelPos] = 0;
		this->histogram.green[pixelPos] = 0;
	}
	else if ((this->histogram.getHeight() - numRow) < height)
	{
		this->histogram.red[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.red[pixelPos] %= maxColourValue;

		this->histogram.green[pixelPos] += this->shiftOpacity(0.3);
		this->histogram.green[pixelPos] %= maxColourValue;
	}
}

Histogram::Histogram()
{
}

Histogram::Histogram(FileEditor * source)
{
	this->open(source);
}

void Histogram::open(FileEditor * source)
{
	this->source = source;

	if (!this->isValidEditor(this->source->getEditorType()))
	{
		std::cout << "# Invalid editor type. Only PPM files are allowed." << std::endl;
		return;
	}

	this->fill();
}

void Histogram::generate(bool isRed, bool isGreen, bool isBlue)
{
	std::cout << "Please wait... Processing data... This might take a while..." << std::endl;

	unsigned int * redIntensity = nullptr;
	unsigned int * greenIntensity = nullptr;
	unsigned int * blueIntensity = nullptr;

	if (isRed) { redIntensity = this->getIntensity(RGB::Red); }

	if (isGreen) { greenIntensity = this->getIntensity(RGB::Green); }

	if (isBlue) { blueIntensity = this->getIntensity(RGB::Blue); }

	this->fillWhite();

	int pixelPos = 0;

	for (unsigned int i = 0; i < this->histogram.getHeight(); i++)
	{
		for (unsigned int j = 0; j < this->histogram.getWidth(); j++)
		{
			if (isRed) { this->fillRed(i, j, redIntensity[j], pixelPos); }

			if (isGreen) { this->fillGreen(i, j, greenIntensity[j], pixelPos); }

			if (isBlue) { this->fillBlue(i, j, blueIntensity[j], pixelPos); }

			pixelPos++;
		}
	}

	if (greenIntensity != nullptr) { delete[] greenIntensity; }
	if (redIntensity != nullptr) { delete[] redIntensity; }
	if (blueIntensity != nullptr) { delete[] blueIntensity; }

	std::cout << "Done processing data." << std::endl;
}

void Histogram::saveAs(const char * fileName)
{
	this->histogram.saveAs(fileName);

	std::cout << "File successfully saved as " << fileName << "." << std::endl;
}