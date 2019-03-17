#include "MonochromeFilter.h"


EditorTypes MonochromeFilter::limitFilterTypes(FileEditor * source)
{
	if (source->getEditorType() == EditorTypes::RawPGM)
	{
		return EditorTypes::PlainPGM;
	}

	if (source->getEditorType() == EditorTypes::RawPPM)
	{
		return EditorTypes::PlainPPM;
	}

	return source->getEditorType();
}

unsigned char MonochromeFilter::byteSplitter(unsigned char sym, unsigned int maxColourValue)
{
	if ((unsigned int)sym > (maxColourValue / 2)) { return 1; }
	return 0;
}

bool MonochromeFilter::ppmIsMonochrome(FileEditor * source)
{
	if (source->getEditorType() == EditorTypes::PlainPPM || source->getEditorType() == EditorTypes::RawPPM)
	{
		for (size_t i = 0; i < ((ImageEditor *)source)->getSizeInPixels(); i++)
		{
			if (((PpmEditor *)source)->red[i] != 0 || ((PpmEditor *)source)->red[i] != 1) { return false; }

			if (((PpmEditor *)source)->green[i] != 0 || ((PpmEditor *)source)->green[i] != 1) { return false; }

			if (((PpmEditor *)source)->blue[i] != 0 || ((PpmEditor *)source)->blue[i] != 1) { return false; }
		}
	}

	return true;
}

bool MonochromeFilter::pgmIsMonochrome(FileEditor * source)
{
	if (source->getEditorType() == EditorTypes::PlainPGM || source->getEditorType() == EditorTypes::RawPGM)
	{
		for (size_t i = 0; i < ((ImageEditor *)source)->getSizeInPixels(); i++)
		{
			if (((PgmEditor *)source)->gray[i] != 0 || ((PgmEditor *)source)->gray[i] != 1) { return false; }
		}
	}

	return true;
}

MonochromeFilter::MonochromeFilter()
{
	this->result = nullptr;
}

MonochromeFilter::MonochromeFilter(FileEditor * source)
{
	this->result = nullptr;
	this->open(source);
}

MonochromeFilter::~MonochromeFilter()
{
	if (this->result != nullptr) { delete this->result; }
}

void MonochromeFilter::delimitFill()
{
	switch (this->type)
	{
	case EditorTypes::PlainPGM:
	case EditorTypes::RawPGM:
		((PgmEditor *)this->result)->fill(((PgmEditor *)this->source)->getWidth(), ((PgmEditor *)this->source)->getHeight(), 1);
		break;
	case EditorTypes::PlainPPM:
	case EditorTypes::RawPPM:
		((PpmEditor *)this->result)->fill(((PpmEditor *)this->source)->getWidth(), ((PpmEditor *)this->source)->getHeight(), 1);
		break;
	}
}

void MonochromeFilter::open(FileEditor * source)
{
	this->source = source;

	EditorFactory factory;
	this->type = this->limitFilterTypes(source);

	this->result = factory.createEditor(this->type);

	bool isMonochrome;

	switch (this->type)
	{
	case EditorTypes::PlainPBM:
	case EditorTypes::RawPBM:
		isMonochrome = true;

		break;
	case EditorTypes::PlainPGM:
	case EditorTypes::RawPGM:
		if (this->pgmIsMonochrome(source)) { isMonochrome = true; }
		else { isMonochrome = false; }

		break;
	case EditorTypes::PlainPPM:
	case EditorTypes::RawPPM:
		if (this->ppmIsMonochrome(source)) { isMonochrome = true; }
		else { isMonochrome = false; }

		break;
	}

	if (isMonochrome) { std::cout << "# Error. Image is already monochrome." << std::endl; }
	else
	{
		std::cout << "# Successfully opened " << source->getFileName() << " for monochrome filtering." << std::endl;
		this->delimitFill();
	}
}

void MonochromeFilter::filter()
{
	for (unsigned int i = 0; i < ((ImageEditor *)this->result)->getSizeInPixels(); i++)
	{
		unsigned char src = ((ImageEditor *)this->source)->getAvgColourValuePerPixel(i);
		unsigned char resultByte;

		switch (this->type)
		{
		case EditorTypes::PlainPGM:
		case EditorTypes::RawPGM:
			resultByte = this->byteSplitter(src, ((PgmEditor *)this->source)->getMaxColourValue());

			((PgmEditor *)this->result)->gray[i] = resultByte;

			break;
		case EditorTypes::PlainPPM:
		case EditorTypes::RawPPM:
			resultByte = this->byteSplitter(src, ((PpmEditor *)this->source)->getMaxColourValue());

			((PpmEditor *)this->result)->red[i] = resultByte;
			((PpmEditor *)this->result)->green[i] = resultByte;
			((PpmEditor *)this->result)->blue[i] = resultByte;

			break;
		default:
			std::cout << "# Nothing available to filter." << std::endl;
			break;
		}
	}
}

void MonochromeFilter::saveAs(const char * fileName)
{
	this->result->saveAs(fileName);
}