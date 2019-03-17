#include "RawPbmEditor.h"


bool RawPbmEditor::isValidExtension(std::string line)
{
	return line == "P4";
}

void RawPbmEditor::readPixels(std::ifstream & in)
{
	char aux;

	for (unsigned int i = 0; i < this->sizeInPixels + 1; i++)
	{
		in.read((char *)&aux, 1);
		this->bytes.push_back((unsigned char)aux);
	}
}

void RawPbmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in | std::ios::binary);
}

void RawPbmEditor::addFileFormat(std::ofstream & out)
{
	out << "P4\n";
}

void RawPbmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out | std::ios::binary);
}

void RawPbmEditor::writePixels(std::ofstream & out)
{
	char aux;

	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		aux = (char)bytes.at(i);
		out.write((const char*)&aux, 1);
	}
}

RawPbmEditor::RawPbmEditor() : PbmEditor()
{
	this->type = EditorTypes::RawPBM;
}

RawPbmEditor::RawPbmEditor(const char * fileName) : PbmEditor(fileName)
{
	this->type = EditorTypes::RawPBM;
}

RawPbmEditor::RawPbmEditor(const unsigned int width, const unsigned int height) : PbmEditor(width, height)
{
	this->type = EditorTypes::RawPBM;
}