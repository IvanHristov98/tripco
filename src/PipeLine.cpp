#include "PipeLine.h"

//void PipeLine::destroyEditor()
//{}

void PipeLine::listOptions()
{
	std::cout << "# To convert to grayscale type in> --grayscale" << std::endl;
	std::cout << "# To convert to monochrome type in> --monochrome" << std::endl;
	std::cout << "# To generate a histogram type in> --histogram=<channel>" << std::endl;
	std::cout << "Possible values for <channel> red, green, blue, multi" << std::endl;
}

PipeLine::PipeLine()
{
	this->isOpen = false;
}

PipeLine::~PipeLine()
{
}

void PipeLine::commandReader(std::string commandLine)
{
	if (!this->areValidFileFormats(commandLine)) { return; }

	if (!this->areValidCommands(commandLine)) { return; }

	std::stringstream commands(commandLine);
	std::string sample;

	while (!commands.eof())
	{
		commands >> sample;

		if (sample[0] != '-') { this->executer(sample, commandLine); }
	}

	commands.clear();
	commands.str("");
}

void PipeLine::executer(std::string path, std::string commandLine)
{
	std::stringstream commands(commandLine);
	std::string sample;

	while (!commands.eof())
	{
		commands >> sample;

		if (sample == "--grayscale") { this->grayscale(path); }

		if (sample == "--monochrome") { this->monochrome(path); }

		if (sample.find("histogram") == 2) 
		{
			this->histogram(path, sample);
		}
	}

	commands.clear();
	commands.str("");
}

void PipeLine::grayscale(std::string path)
{
	EditorTypes type = this->getEditorType(path);
	FileEditor * editor;

	if (type == EditorTypes::Unspecified)
	{
		std::cout << "# Invalid file." << std::endl;
		return;
	}
	else
	{
		EditorFactory factory;
		editor = factory.createEditor(type);
	}

	editor->open(path.c_str());

	GrayscaleFilter * filter = new GrayscaleFilter(editor);

	filter->filter();

	filter->saveAs((this->buildNewName(path, "_grayscale")).c_str());

	if (filter != nullptr) { delete filter; }
	if (editor != nullptr) { delete editor; }
}

void PipeLine::monochrome(std::string path)
{
	EditorTypes type = this->getEditorType(path);
	FileEditor * editor;

	if (type == EditorTypes::Unspecified)
	{
		std::cout << "# Invalid file." << std::endl;
		return;
	}
	else
	{
		EditorFactory factory;
		editor = factory.createEditor(type);
	}

	editor->open(path.c_str());

	MonochromeFilter * filter = new MonochromeFilter(editor);

	filter->filter();

	filter->saveAs((this->buildNewName(path, "_monochrome")).c_str());

	if (filter != nullptr) { delete filter; }
	if (editor != nullptr) { delete editor; }
}

void PipeLine::histogram(std::string path, std::string sample)
{
	EditorTypes type = this->getEditorType(path);
	FileEditor * editor;

	if (type == EditorTypes::Unspecified)
	{
		std::cout << "# Invalid file." << std::endl;
		return;
	}
	else
	{
		EditorFactory factory;
		editor = factory.createEditor(type);
	}

	editor->open(path.c_str());

	Histogram histogram(editor);

	RGB colour = this->getColourNum(sample);

	switch (colour)
	{
	case Multi:
		histogram.generate();
		break;
	case Red:
		histogram.generate(true, false, false);
		break;
	case Green:
		histogram.generate(false, true, false);
		break;
	case Blue:
		histogram.generate(false, false, true);
		break;
	default:
		break;
	}
	
	histogram.saveAs((this->buildNewName(path, ("_histogram_" + this->getColour(sample)))).c_str());

	if (editor != nullptr) { delete editor; }
}

std::string PipeLine::buildNewName(std::string path, std::string suffix)
{
	std::size_t dotPos = path.find_last_of('.');

	return path.insert(dotPos, suffix);
}

EditorTypes PipeLine::getEditorType(std::string path)
{
	std::ifstream in(path, std::ios::in);

	if (in.is_open())
	{
		std::string format;

		in >> format;

		if (format == "P1") { return EditorTypes::PlainPBM; }
		if (format == "P2") { return EditorTypes::PlainPGM; }
		if (format == "P3") { return EditorTypes::PlainPPM; }
		if (format == "P4") { return EditorTypes::RawPBM; }
		if (format == "P5") { return EditorTypes::RawPGM; }
		if (format == "P6") { return EditorTypes::RawPPM; }
	}
	else
	{
		std::cout << "# Invalid format" << std::endl;
	}

	in.close();

	return EditorTypes::Unspecified;
}

RGB PipeLine::getColourNum(std::string command)
{
	std::string colour = this->getColour(command);

	if (colour == "red") { return RGB::Red; }
	if (colour == "green") { return RGB::Green; }
	if (colour == "blue") { return RGB::Blue; }

	return RGB::Multi;
}

std::string PipeLine::getColour(std::string command)
{
	std::size_t dotPos = command.find_last_of('=');

	return command.substr(dotPos + 1, std::string::npos);
}

bool PipeLine::areValidCommands(std::string commandLine)
{
	std::stringstream commands(commandLine);
	std::string sample;

	while (!commands.eof())
	{
		commands >> sample;

		if (!this->areAvailableCommands(sample))
		{
			std::cout << "# Error invalid command line. Invalid file command." << std::endl;
			return false;
		}
	}

	commands.clear();
	commands.str("");

	return true;
}

bool PipeLine::areAvailableCommands(std::string command)
{
	if (command == "--grayscale") { return true; }
	if (command == "--monochrome") { return true; }
	if (command.find("histogram")) { return true; }

	return false;
}

bool PipeLine::areValidFileFormats(std::string commandLine)
{
	std::stringstream commands(commandLine);
	std::string sample;

	while (!commands.eof())
	{
		commands >> sample;

		if (sample[0] != '-')
		{
			if (!this->isValidExtension(sample))
			{
				std::cout << "# Error invalid command line. Invalid file name." << std::endl;
				return false;
			}
		}
	}

	commands.clear();
	commands.str("");

	return true;
}

bool PipeLine::isValidExtension(std::string path)
{
	std::string format;

	try
	{
		std::size_t dotPos = path.find_last_of('.');
		format = path.substr(dotPos, std::string::npos);
	}
	catch (const std::exception&)
	{
		std::cout << "# Invalid format" << std::endl;
		return false;
	}

	if (format == ".pbm") { return true; }
	if (format == ".pgm") { return true; }
	if (format == ".ppm") { return true; }

	return false;
}

void PipeLine::load()
{
	std::cout << "================= MAIN MENU * TRIPCO =================" << std::endl;
	std::cout << "* Totally Radical Image Processing Compact Overrider *" << std::endl;

	while (true)
	{
		std::string commandLine;
		
		std::cout << std::endl;
		std::cout << "# To list all commands type in> --list" << std::endl;
		std::cout << "# To quit type in> --exit" << std::endl;
		std::cout << "* If statement contains the command --exit none of the other inserted commands will be executed." << std::endl;
		std::cout << "# Type here> ";
		std::getline(std::cin, commandLine);
		std::cout << std::endl;

		std::stringstream input(commandLine);

		while (!input.eof())
		{
			std::string sample;
			input >> sample;

			if (sample == "--exit")
			{
				goto END_OF_PROGRAM;
			}

			if (sample == "--list") { this->listOptions(); }
		}

		this->commandReader(commandLine);
	}

	END_OF_PROGRAM:
	std::cout << "Successfully exited TRIPCO 1.0.0" << std::endl;
}