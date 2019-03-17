#include "FileEditor.h"


FileEditor::FileEditor()
{
	this->init();
	this->type = EditorTypes::File;
}

void FileEditor::init()
{
	this->isOpen = false;
	this->binaryState = false;
}

bool FileEditor::isBinary(std::ifstream & in)
{
	const int ASCII_MAX = 127;
	int i = 0;

	while ((i = in.get()) != EOF && i <= ASCII_MAX);

	return i != EOF;
}

void FileEditor::printBinaryState()
{
	if (this->binaryState)
	{
		std::cout << "# File type> binary" << std::endl;
	}
	else
	{
		std::cout << "# File type> text" << std::endl;
	}
}

void FileEditor::clearAllBufferData() 
{
	this->buffer.clear();
}

void FileEditor::generateFile(const char * fileName)
{
	std::ofstream out(fileName, std::ios::out | std::ios::binary);

	out.close();
	std::cout << "No file named " << fileName << " existed! Generated " << fileName << std::endl;
}

void FileEditor::read(const char * fileName)
{
	std::ifstream in(fileName, std::ios::in);

	std::string tmpBuffer;

	this->clearAllBufferData();

	while (!in.eof()) 
	{ 
		// Keeping new lines from original file
		if (!this->buffer.empty()) { this->buffer += "\n"; }

		std::getline(in, tmpBuffer);

		this->buffer += tmpBuffer;
	}
	
	std::cout << "# Success reading> " << fileName << std::endl;

	in.close();
}

void FileEditor::write(const char * fileName)
{
	std::ofstream out(fileName, std::ios::out);

	out << this->buffer;
	out.close();

	std::cout << "# Successfully saved changes to " << fileName << std::endl;
}

void FileEditor::open(const char * fileName)
{
	std::ifstream in(fileName, std::ios::in | std::ios::binary);

	if (in.is_open())
	{ 
		std::cout << "# Success openening> " << fileName << "" << std::endl; 
	}
	else
	{
		this->generateFile(fileName);
	}

	// Define whether file is text or binary
	this->binaryState = this->isBinary(in);

	// Closing it following a strict RAII order of method design
	in.close();

	this->printBinaryState();

	this->read(fileName);

	// Finally setting the state of the file to being opened
	this->isOpen = true;
	this->fileName = fileName;
}

void FileEditor::close()
{
	if (this->isOpen)
	{
		this->clearAllBufferData();
		this->isOpen = false;

		std::cout << "# Successfully closed " << this->fileName << std::endl;
		this->fileName.clear();
	}
	else { std::cout << "# No file is opened." << std::endl; }
}

void FileEditor::save()
{
	this->saveAs(this->fileName.c_str());
}

void FileEditor::saveAs(const char * fileName)
{
	if (!this->isOpen)
	{
		std::cout << "# No file is opened." << std::endl;
		return;
	}

	this->write(fileName);
	std::cout << "# Successfully saved changes to " << fileName << std::endl;
}

EditorTypes FileEditor::getEditorType() const
{
	return this->type;
}

std::string FileEditor::getFileName() const
{
	return this->fileName;
}