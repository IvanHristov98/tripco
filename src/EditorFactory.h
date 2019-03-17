#ifndef EDITOR_FABRIC_H
#define EDITOR_FABRIC_H

#include "PlainPpmEditor.h"
#include "RawPpmEditor.h"
#include "RawPgmEditor.h"
#include "PlainPgmEditor.h"
#include "RawPbmEditor.h"
#include "PlainPbmEditor.h"

class EditorFactory
{
public:
	EditorFactory() {}

	FileEditor * createEditor(EditorTypes type)
	{
		switch (type)
		{
		case File:
			return new FileEditor();
			break;
		case PlainPBM:
			return new PlainPbmEditor();
			break;
		case PlainPGM:
			return new PlainPgmEditor();
			break;
		case PlainPPM:
			return new PlainPpmEditor();
			break;
		case RawPBM:
			return new RawPbmEditor();
			break;
		case RawPGM:
			return new RawPgmEditor();
			break;
		case RawPPM:
			return new RawPpmEditor();
			break;
		default:
			break;
		}
	}
};

#endif
