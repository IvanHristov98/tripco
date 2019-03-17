#include "PbmEditor.h"

void PbmEditor::init()
{
	FileEditor::init();

	this->width = 0;
	this->height = 0;
}

PbmEditor::PbmEditor()
{
	this->init();
}

PbmEditor::PbmEditor(const char * fileName)
{
	this->init();
	this->open(fileName);
}

PbmEditor::PbmEditor(const unsigned int width, const unsigned int height)
{
	this->fill(width, height);
}

void PbmEditor::read(const char * fileName)
{
	std::ifstream in;
	this->openReadFile(in, fileName);

	if (!in.is_open())
	{
		std::cout << "# Unable to open " << fileName << "." << std::endl;
	}
	else
	{
		this->readHeader(in);

		this->sizeInPixels = this->width * this->height;

		this->bytes.reserve(this->sizeInPixels);

		this->readPixels(in);
	}

	in.close();
}

void PbmEditor::write(const char * fileName)
{
	std::ofstream out;
	this->openWriteFile(out, fileName);
	
	if (out.is_open())
	{
		this->addFileFormat(out);
		out << "# Generated by TRIPCO\n";

		// In order to match the NetPBM standarts
		out << this->width << " " << this->height << "\n";

		this->writePixels(out);
	}
	else
	{
		std::cout << "# Unable to open " << fileName << " for changes." << std::endl;
	}
	
	out.close();
}

void PbmEditor::readHeader(std::ifstream & in)
{
	const int NUMBER_OF_SPECIFICATIONS = 2;
	std::string line;

	std::getline(in, line);
	std::stringstream stream(line);

	std::string format;
	stream >> format;

	if (!this->isValidExtension(format))
	{
		std::cout << "# Unrecognized file format." << std::endl;
		return;
	}

	// Array to hold specifications
	unsigned int specs[NUMBER_OF_SPECIFICATIONS] = {};
	unsigned int i = 0;

	while (true)
	{
		while (!stream.eof())
		{
			stream >> specs[i++];
		}

		if (i == NUMBER_OF_SPECIFICATIONS) { break; }

		std::getline(in, line);

		// Loop while it is a comment or an empty line
		while (line[0] == '#' || line.empty())
		{
			std::getline(in, line);
		}

		// Reset stream
		stream.str(std::string());
		stream.clear();
		stream.str(line);
	}

	// Finally save data
	this->width = specs[0];
	this->height = specs[1];
}

void PbmEditor::fill(const unsigned int width, const unsigned int height, unsigned int maxColourValue)
{
	FileEditor::init();

	this->width = width;
	this->height = height;

	this->numRows = this->height;
	this->numCols = this->width;

	this->sizeInPixels = this->width * this->height;

	// Fill bytes container with 0's
	this->bytes.resize(this->sizeInPixels);

	// Setting file state to being opened
	this->isOpen = true;
}

unsigned int PbmEditor::getAvgColourValuePerPixel(unsigned int pos) const
{
	try
	{
		return this->bytes.at(pos);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}