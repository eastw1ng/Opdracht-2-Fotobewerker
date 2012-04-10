/*
 * OptieScherm.h
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#ifndef OPTIESCHERM_H_
#define OPTIESCHERM_H_


#include <MAUTIL/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/EditBox.h>
#include <MAUI/ListBox.h>
#include <MAUTIL/Vector.h>
#include <MAUI/Layout.h>
#include <MAUI/Widget.h>

#include "mastdlib.h"
#include "conprint.h"
#include "MAHeaders.h"


using namespace MAUtil;
using namespace MAUI;


class OptieScherm : public Screen, WidgetListener
{
private:
	ListBox* listBox;
	Layout* mainLayout;
	Widget* softKeys;
	Widget* selectedEdit;
	Screen* parent;
	Label* achtergrondLabel;
	Vector<Label*> kleurLabels;
	Label* roodLabel;
	Label* groenLabel;
	Label* blauwLabel;
	char* naam;
	EditBox* breedte;
	EditBox* hoogte;
	EditBox* tekst;
	int achtergrondKleur;
	int afbhoogte;
	int afbbreedte;
	int screenWidth;
	int screenHeight;

	Font* font;
	WidgetSkin* skin;

	//todo: voeg editboxen en waardes toe die opgeslagen moeten worden

public:
	OptieScherm( Screen* parent, int hoogte, int breedte, char* naam);
	virtual ~OptieScherm();

	void toggleEditSelection(Widget* w);
	void keyPressEvent(int keyCode, int nativeCode);
	void pointerPressEvent(MAPoint2d point);

	Layout* createMainLayout();
	Widget* createSoftKeyBar(int height, const char *center);
	Label* makeLabel(String s, int height);
	int getAchtergrondOptie();
	int getHoogte();
	int getBreedte();
	char* getImagetekst(); //geeft text van editbox terug
};

#endif /* OPTIESCHERM_H_ */
