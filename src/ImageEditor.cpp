#include "ImageEditor.h"

ImageEditor::ImageEditor()
{
}

unsigned int ImageEditor::getNumRows() const
{
	return this->numRows;
}

unsigned int ImageEditor::getNumCols() const
{
	return this->numCols;
}

unsigned int ImageEditor::getWidth() const
{
	return this->width;
}

unsigned int ImageEditor::getHeight() const
{
	return this->height;
}

unsigned int ImageEditor::getSizeInPixels() const
{
	return this->sizeInPixels;
}