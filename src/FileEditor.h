#ifndef FILE_EDITOR_H
#define FILE_EDITOR_H

#include <iostream>
#include <fstream>
#include <string>

enum EditorTypes
{
	Unspecified,
	File,
	PlainPBM,
	PlainPGM,
	PlainPPM,
	RawPBM,
	RawPGM,
	RawPPM
};

class FileEditor
{
	protected:
		EditorTypes type;

		std::string buffer;
		std::string fileName;

		bool binaryState;
		bool isOpen;

		// Initialize object
		virtual void init();

		/**
		Precises whether a file is binary assuming text files contain only ASCII symbols from 0 to 127

		@param std::ifstream & in File to be iterated.
		*/
		bool isBinary(std::ifstream & in);

		void printBinaryState();

		virtual void clearAllBufferData();

		/**
		Generates a file by a given name

		@param const char * fileName Name of file to be generated.
		*/
		void generateFile(const char * fileName);

		/**
		Reads a regular text file and fills it into a buffer

		@param const char * fileName Name of the file to be opened.
		*/
		virtual void read(const char * fileName);

		/**
		Saves buffer to a text file

		@param const char * fileName Name of the file to be saved to
		*/
		virtual void write(const char * fileName);

	public:
		FileEditor();

		/**
		Opens a file and reads it's content.

		@param const char * fileName Name of file to be opened and read.
		*/
		void open(const char * fileName);

		// Clears buffer and sets isOpen flag to false
		void close();

		// Saves data to local fileName
		void save();

		// Saves data to outer fileName
		void saveAs(const char * fileName);

		EditorTypes getEditorType() const;
		std::string getFileName() const;
};

#endif