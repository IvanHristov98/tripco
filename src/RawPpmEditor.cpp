#include "RawPpmEditor.h"


bool RawPpmEditor::isValidExtension(std::string line)
{
	return line == "P6";
}

void RawPpmEditor::readPixels(std::ifstream & in)
{
	char aux;
	
	for (unsigned int i = 0; i <this->sizeInPixels; i++)
	{
		in.read((char *)&aux, 1);
		this->red.push_back((unsigned char)aux);
	
		in.read((char *)&aux, 1);
		this->green.push_back((unsigned char)aux);
	
		in.read((char *)&aux, 1);
		this->blue.push_back((unsigned char)aux);
	}
}

void RawPpmEditor::openReadFile(std::ifstream & in, const char * fileName)
{
	in.open(fileName, std::ios::in | std::ios::binary);
}

void RawPpmEditor::addFileFormat(std::ofstream & out)
{
	out << "P6\n";
}

void RawPpmEditor::openWriteFile(std::ofstream & out, const char * fileName)
{
	out.open(fileName, std::ios::out | std::ios::binary);
}

void RawPpmEditor::writePixels(std::ofstream & out)
{
	char aux;

	for (unsigned int i = 0; i < this->sizeInPixels; i++)
	{
		aux = (char)red.at(i);
		out.write((const char*)&aux, 1);
	
		aux = (char)green.at(i);
		out.write((const char*)&aux, 1);
	
		aux = (char)blue.at(i);
		out.write((const char*)&aux, 1);
	}
}

RawPpmEditor::RawPpmEditor() : PpmEditor()
{
	this->type = EditorTypes::RawPPM;
}

RawPpmEditor::RawPpmEditor(const char * fileName) : PpmEditor(fileName)
{
	this->type = EditorTypes::RawPPM;
}

RawPpmEditor::RawPpmEditor(const unsigned int width, const unsigned int height) : PpmEditor(width, height)
{
	this->type = EditorTypes::RawPPM;
}