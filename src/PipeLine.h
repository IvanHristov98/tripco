#ifndef PIPE_LINE_H
#define PIPE_LINE_H

#include "EditorFactory.h"
#include "GrayscaleFilter.h"
#include "MonochromeFilter.h"
#include "Histogram.h"

#include <sstream>
#include <string>

enum commands
{
	Grayscale,
	Monochrome,
	Histo
};

class PipeLine
{
private:
	bool isOpen;

	/*void destroyEditor();*/

	void listOptions();

	void commandReader(std::string commandLine);
	bool areValidCommands(std::string commandLine);
	bool areAvailableCommands(std::string command);
	bool areValidFileFormats(std::string commandLine);
	bool isValidExtension(std::string path);

	void executer(std::string path, std::string commandLine);

	void grayscale(std::string path);
	void monochrome(std::string path);
	void histogram(std::string path, std::string sample);

	EditorTypes getEditorType(std::string path);
	std::string buildNewName(std::string path, std::string suffix);
	RGB getColourNum(std::string command);
	std::string getColour(std::string command);

public:
	PipeLine();
	~PipeLine();

	void load();
};

#endif