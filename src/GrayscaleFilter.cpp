#include "GrayscaleFilter.h"


bool GrayscaleFilter::ppmIsGrayscale(FileEditor * source)
{
	if (source->getEditorType() == EditorTypes::PlainPPM || source->getEditorType() == EditorTypes::RawPPM)
	{
		for (size_t i = 0; i < ((ImageEditor *)source)->getSizeInPixels(); i++)
		{
			if (((PpmEditor *)source)->red[i] != ((PpmEditor *)source)->green[i] || ((PpmEditor *)source)->green[i] != ((PpmEditor *)source)->blue[i])
			{
				return false;
			}
		}
	}
		
	return true;
}

void GrayscaleFilter::delimitFill()
{
	PpmEditor * castedSource = (PpmEditor *)this->source;

	((PpmEditor *)this->result)->fill(castedSource->getWidth(), castedSource->getHeight(), castedSource->getMaxColourValue());
}

GrayscaleFilter::GrayscaleFilter()
{
	this->result = nullptr;
}

GrayscaleFilter::GrayscaleFilter(FileEditor * source)
{
	this->result = nullptr;
	this->open(source);
}

GrayscaleFilter::~GrayscaleFilter()
{
	if (this->result != nullptr) { delete this->result; }
}

void GrayscaleFilter::filter()
{
	for (unsigned int i = 0; i < ((ImageEditor *)this->result)->getSizeInPixels(); i++)
	{
		unsigned char src = ((ImageEditor *)this->source)->getAvgColourValuePerPixel(i);

		switch (this->type)
		{
		case EditorTypes::PlainPPM:
		case EditorTypes::RawPPM:
			((PpmEditor *)this->result)->red[i] = src;
			((PpmEditor *)this->result)->green[i] = src;
			((PpmEditor *)this->result)->blue[i] = src;

			break;
		default:
			std::cout << "# Nothing available to filter." << std::endl;
			break;
		}
	}
}

void GrayscaleFilter::open(FileEditor * source)
{
	this->source = source;

	EditorFactory factory;
	this->result = factory.createEditor(source->getEditorType());

	this->type = source->getEditorType();

	if ((this->type == EditorTypes::PlainPPM || this->type == EditorTypes::RawPPM) && !this->ppmIsGrayscale(source))
	{
		std::cout << "# Successfully opened " << source->getFileName() << " for grayscale filtering." << std::endl;
		// Generates an empty file object
		this->delimitFill();

	}
	else
	{
		std::cout << "# Error. Image is already grayscale or monochrome." << std::endl;
	}
}

void GrayscaleFilter::saveAs(const char * fileName)
{
	this->result->saveAs(fileName);
}