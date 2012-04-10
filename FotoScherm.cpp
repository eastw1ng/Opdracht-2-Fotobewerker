/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "FotoScherm.h"

FotoScherm::FotoScherm()
{
	//ophalen van de schermgrootte
	MAExtent screenSize = maGetScrSize();

	//Skin instellen
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//bepaal grootte van het scherm
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//het optiescherm
	this->optieScherm = new OptieScherm( this, screenWidth / 2, screenHeight / 2, "default");

	//Stel een achtergrond label in
	this->achtergrondLabel = new Label(0,0,screenWidth,screenHeight,NULL);

	image = new Image(0, 0, 0, 0, this->achtergrondLabel, false, false, RES_IMAGE);

	//Stel een tekst label in
	Font* font = new Font(RES_FONT);
	this->imageTekst = new Label(10,screenHeight-26,screenWidth-20,20,this->achtergrondLabel,"Opties", 0, font);
	this->imageTekst->setBackgroundColor(0x000000);
	this->imageTekst->setHorizontalAlignment(Label::HA_CENTER);

	this->setMain(achtergrondLabel);
}

FotoScherm::~FotoScherm(){}

//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );

	//haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() ); //this->optieScherm->getImagetekst()

	//zet de positie, hoogte en breedte van de afbeelding
	int breedte = this->optieScherm->getBreedte();
	int hoogte = this->optieScherm->getHoogte();

	image->setPosition(screenWidth/2-breedte/2,screenHeight/2-hoogte/2);
	image->setWidth(breedte);
	image->setHeight(hoogte);
}

//afvangen invoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	if (MAK_FIRE == keyCode )
	{
		optieScherm->show();
	}
}

//handelt touch events af
void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	//bij touch, laat optiescherm zien
	Point p;
	p.set(point.x, point.y);

	if(this->achtergrondLabel->contains(p)){
		optieScherm->show();
	}
}


