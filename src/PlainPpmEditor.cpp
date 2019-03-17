#include "PlainPpmEditor.h"


bool PlainPpmEditor::isValidExtension(std::string line)
{
	return line == "P3";
}

void PlainPpmEditor::readPixels(std::ifstream & in)
{
	unsigned int aux;

	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		in >> aux;
		this->red.push_back((unsigned char)aux);

		in >> aux;
		this->green.push_back((unsigned char)aux);

		in >> aux;
		this->blue.push_back((unsigned char)aux);
	}
}

void PlainPpmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in);
}

void PlainPpmEditor::addFileFormat(std::ofstream & out)
{
	out << "P3\n";
}

void PlainPpmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out);
}

void PlainPpmEditor::writePixels(std::ofstream & out)
{
	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		if (i % this->width == 0 && i != 0) { out << "\n"; }

		out << " " << (unsigned int)this->red.at(i);
		out << " " << (unsigned int)this->green.at(i);
		out << " " << (unsigned int)this->blue.at(i);
	}
}

PlainPpmEditor::PlainPpmEditor() : PpmEditor()
{
	this->type = EditorTypes::PlainPPM;
}

PlainPpmEditor::PlainPpmEditor(const char * fileName) : PpmEditor(fileName)
{
	this->type = EditorTypes::PlainPPM;
}

PlainPpmEditor::PlainPpmEditor(const unsigned int width, const unsigned int height) : PpmEditor(width, height)
{
	this->type = EditorTypes::PlainPPM;
}