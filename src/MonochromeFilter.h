#ifndef MONOCHROME_FILTER_H
#define MONOCHROME_FILTER_H

#include "EditorFactory.h"

class MonochromeFilter
{
private:
	FileEditor * source;
	FileEditor * result;
	EditorTypes type;

	EditorTypes limitFilterTypes(FileEditor * source);
	bool ppmIsMonochrome(FileEditor * source);
	bool pgmIsMonochrome(FileEditor * source);

	void delimitFill();
	unsigned char byteSplitter(unsigned char sym, unsigned int maxColourValue);

public:
	MonochromeFilter();
	MonochromeFilter(FileEditor * source);
	~MonochromeFilter();

	void open(FileEditor * source);
	void saveAs(const char * fileName);

	void filter();
};

#endif