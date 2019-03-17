#include "RawPgmEditor.h"


bool RawPgmEditor::isValidExtension(std::string line)
{
	return line == "P5";
}

void RawPgmEditor::readPixels(std::ifstream & in)
{
	char aux;
	
	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		in.read((char *)&aux, 1);
		this->gray.push_back((unsigned char)aux);
	}
}

void RawPgmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in | std::ios::binary);
}

void RawPgmEditor::addFileFormat(std::ofstream & out)
{
	out << "P5\n";
}

void RawPgmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out | std::ios::binary);
}

void RawPgmEditor::writePixels(std::ofstream & out)
{
	char aux;

	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		aux = (char)gray.at(i);
		out.write((const char*)&aux, 1);
	}
}

RawPgmEditor::RawPgmEditor() : PgmEditor()
{
	this->type = EditorTypes::RawPGM;
}

RawPgmEditor::RawPgmEditor(const char * fileName) : PgmEditor(fileName)
{
	this->type = EditorTypes::RawPGM;
}

RawPgmEditor::RawPgmEditor(const unsigned int width, const unsigned int height) : PgmEditor(width, height)
{
	this->type = EditorTypes::RawPGM;
}