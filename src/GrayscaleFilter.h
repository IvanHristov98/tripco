#ifndef GRAY_SCALE_FILTER_H
#define GRAY_SCALE_FILTER_H

#include "EditorFactory.h"

class GrayscaleFilter
{
private:
	FileEditor * source;
	FileEditor * result;
	EditorTypes type;

	bool ppmIsGrayscale(FileEditor * source);

	void delimitFill();

public:
	GrayscaleFilter();
	GrayscaleFilter(FileEditor * source);
	~GrayscaleFilter();

	void open(FileEditor * source);
	//void close();
	void saveAs(const char * fileName);

	void filter();
};

#endif
