#include "PlainPgmEditor.h"


bool PlainPgmEditor::isValidExtension(std::string line)
{
	return line == "P2";
}

void PlainPgmEditor::readPixels(std::ifstream & in)
{
	unsigned int aux;
	
	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		in >> aux;
		this->gray.push_back((unsigned char)aux);
	}
}

void PlainPgmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in);
}

void PlainPgmEditor::addFileFormat(std::ofstream & out)
{
	out << "P2\n";
}

void PlainPgmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out);
}

void PlainPgmEditor::writePixels(std::ofstream & out)
{
	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		if (i % this->width == 0 && i != 0) { out << "\n"; }
		out << " " << (unsigned int)this->gray.at(i);
	}
}

PlainPgmEditor::PlainPgmEditor() : PgmEditor()
{
	this->type = EditorTypes::PlainPGM;
}

PlainPgmEditor::PlainPgmEditor(const char * fileName) : PgmEditor(fileName)
{
	this->type = EditorTypes::PlainPGM;
}

PlainPgmEditor::PlainPgmEditor(const unsigned int width, const unsigned int height) : PgmEditor(width, height)
{
	this->type = EditorTypes::PlainPGM;
}