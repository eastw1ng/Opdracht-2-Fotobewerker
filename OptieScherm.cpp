/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "OptieScherm.h"

OptieScherm::OptieScherm( Screen* parent, int breedte, int hoogte, char* naam)
{
	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//ophalen van de schermgrootte
	MAExtent screenSize = maGetScrSize();

	//bepaal grootte van het scherm
	this->screenWidth = EXTENT_X( screenSize );
	this->screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	this->font = new Font(RES_FONT);
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//Aanmaken van de layout
	this->mainLayout = createMainLayout();
	this->softKeys = mainLayout->getChildren()[1];
	this->listBox = (ListBox*) mainLayout->getChildren()[0];

	//stel achtergrondkleur in
	this->achtergrondKleur = 0xff0000;
	this->afbbreedte = breedte;
	this->afbhoogte = hoogte;
	this->naam = naam;

	this->listBox->add(makeLabel("  Rood knopje", 30));
	this->listBox->add(makeLabel("  Groen knopje", 30));
	this->listBox->add(makeLabel("  Blauw knopje", 30));

	//stel grootte plaatje in m.b.v. editbox

	//stel naam plaatje in m.b.v. editbocx
	Label* label;
	EditBox* editBox;

	char b [10]; //Buffer breedte
	char h [10]; //Buffer hoogte

	itoa (afbbreedte, b, 10); //Zet integer om naar string
	itoa (afbhoogte, h, 10);//Zet integer om naar string

	//Optie: Naam
	label = makeLabel("  Naam van het plaatje", 50);
	editBox = new EditBox(5, 16, label->getWidth()-10, 64-24-10, label, naam, 0, font, true, true);
	editBox->setDrawBackground(false);
	label->addWidgetListener(this);
	this->tekst = editBox;
	this->listBox->add(label);

	//Optie: Breedte
	label = makeLabel("  Breedte van het plaatje", 50);
	editBox = new EditBox(5, 16, label->getWidth()-10, 64-24-10, label, b, 0, font, true, false);
	editBox->setDrawBackground(false);
	label->addWidgetListener(this);
	this->breedte = editBox;
	this->listBox->add(label);

	//Optie: Hoogte
	label = makeLabel("  Hoogte van het plaatje", 50);
	editBox = new EditBox(5, 16, label->getWidth()-10, 64-24-10, label, h, 0, font, true, false);
	editBox->setDrawBackground(false);
	label->addWidgetListener(this);
	this->hoogte = editBox;
	this->listBox->add(label);

	//Stel de standaard main in
	this->setMain(this->mainLayout);
}

//Maakt een nieuwe main layout voor het optiescherm
Layout* OptieScherm::createMainLayout(){
	Layout* mainLayout = new Layout(0,0,screenWidth,screenHeight,NULL,1,2);
	mainLayout->setDrawBackground(true);
	mainLayout->setBackgroundColor(0x000000);

	Widget *softKeys = createSoftKeyBar(30, "Toepassen");
	ListBox* listBox = new ListBox(0, 0, screenWidth, screenHeight-softKeys->getHeight(), mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(skin);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);
	listBox->setPaddingTop(15);
	listBox->setPaddingBottom(15);

	mainLayout->add(softKeys);

	return mainLayout;
}

//Maakt een menu met het knop TOEVOEGEN
Widget* OptieScherm::createSoftKeyBar(int height, const char* center) {
	Layout *layout = new Layout(0, 0, screenWidth, height, NULL, 1, 1);
	Label *label;

	label = new Label(0,0, screenWidth, height, NULL, center, 0, font);
	label->setHorizontalAlignment(Label::HA_CENTER);
	label->setDrawBackground(false);
	layout->add(label);

	return layout;
}

//Maakt een label en geeft hem terug
Label* OptieScherm::makeLabel(String s, int height){
	Label* result = new Label(0,0,screenWidth,height,NULL,s, 0, font);
	result->setSkin( skin );
	return result;
}

//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	return this->achtergrondKleur;
}

//Vraagt hoogte op
int OptieScherm::getHoogte()
{
	return this->afbhoogte;
}

//Vraagt breedte op
int OptieScherm::getBreedte()
{
	return this->afbbreedte;
}

//geef ingestelde imagetekst van de editbox terug
char* OptieScherm::getImagetekst()
{
	//verander editBox naar jouw editboxs
	return naam; //caption is de text in een editbox
}

//Handelt key events af
void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	switch(keyCode) {
			case MAK_UP:
				listBox->selectPreviousItem();
				toggleEditSelection(listBox->getChildren()[listBox->getSelectedIndex()]);
				break;
			case MAK_DOWN:
				listBox->selectNextItem();
				toggleEditSelection(listBox->getChildren()[listBox->getSelectedIndex()]);
				break;
			case MAK_FIRE:
				//laat bij MAK_FIRE knop indrukken de parent (FotoScherm dus) weer zien
				parent->show();
				break;
	}
}

//Als een element een subelement heeft, selecteer dat subelement (In dit geval is dat een edit box)
void OptieScherm::toggleEditSelection(Widget* w){
	//Deselecteer automatisch het oud geselecteerd element
	if(selectedEdit){
		selectedEdit->setSelected(false);
	}

	//Selecteer een nieuw subelement als die bestaat
	if(w->getChildren()[0]){
		selectedEdit = w->getChildren()[0];
		selectedEdit->setSelected(true);
	}
}

//Handelt touch events af
void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	int selected;
	Point p;
	p.set(point.x, point.y);

	if(listBox->contains(p)) {
		for(int i = 0; i < listBox->getChildren().size(); i++) {
			if(listBox->getChildren()[i]->contains(p)) {
				listBox->setSelectedIndex(i);
				selected = i;

				toggleEditSelection(listBox->getChildren()[i]);

				break;
			}
		}
		if(selected){
			switch(selected) {
				case 0:
					this->achtergrondKleur = 0xff0000;
					break;
				case 1:
					this->achtergrondKleur = 0x00ff00;
					break;
				case 2:
					this->achtergrondKleur = 0x0000ff;
					break;
			}
		}
	}else if(softKeys->contains(p)){
		if(softKeys->getChildren()[0]->contains(p)) {
			this->afbbreedte = atoi(breedte->getCaption().c_str());
			this->afbhoogte = atoi(hoogte->getCaption().c_str());
			this->naam = const_cast<char*>(tekst->getCaption().c_str());

			parent->show();
		}
	}
}

OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
}
