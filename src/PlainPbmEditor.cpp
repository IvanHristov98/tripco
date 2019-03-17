#include "PlainPbmEditor.h"


bool PlainPbmEditor::isValidExtension(std::string line)
{
	return line == "P1";
}

void PlainPbmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in);
}

void PlainPbmEditor::readPixels(std::ifstream & in)
{
	char aux;

	for (size_t i = 0; i < this->sizeInPixels; i++)
	{
		in >> aux;

		this->bytes.push_back((unsigned char)aux);
	}
}

void PlainPbmEditor::addFileFormat(std::ofstream & out)
{
	out << "P1\n";
}

void PlainPbmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out);
}

void PlainPbmEditor::writePixels(std::ofstream & out)
{
	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		if (i % this->width == 0 && i != 0) { out << "\n"; }
		out << " " << this->bytes.at(i);
	}
}

PlainPbmEditor::PlainPbmEditor() : PbmEditor()
{
	this->type = EditorTypes::PlainPBM;
}

PlainPbmEditor::PlainPbmEditor(const char * fileName) : PbmEditor(fileName)
{
	this->type = EditorTypes::PlainPBM;
}

PlainPbmEditor::PlainPbmEditor(const unsigned int width, const unsigned int height) : PbmEditor (width, height)
{
	this->type = EditorTypes::PlainPBM;
}