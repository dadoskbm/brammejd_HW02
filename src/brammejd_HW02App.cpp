#pragma once

#include "MainHeader.h"


using namespace ci;
using namespace ci::app;
using namespace std;

void brammejd_HW02App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(AppWidth, AppHeight);
	(*settings).setResizable(false);
}

void brammejd_HW02App::insertAfter(node* where, Rect* newRect){
	
	node* ourNode = new node;
	where->next->prev = ourNode;
	ourNode ->rect = newRect;
	ourNode ->next = where ->next;
	ourNode ->prev = where;
	where ->next = ourNode;
}

void brammejd_HW02App::Delete(node* deleteMe){
	if(deleteMe->rect == NULL){
		console() << "At Sentinel Node" << endl;
	} else {
		node* tempPrev = deleteMe->prev;
		node* tempNext = deleteMe->next;
		tempPrev->next = tempNext;
		tempNext->prev = tempPrev;
	    delete deleteMe;
	}
}

void resetBackground(uint8_t* dataArray, Color8u BGColor){
	for(int i = 0; i < AppHeight; i++){
		for(int j = 0; j < AppWidth; j++){
			int offset = 3*(j + i*TEXTURESIZE);
			dataArray[offset] = BGColor.r;
			dataArray[offset+1] = BGColor.g;
			dataArray[offset+2] = BGColor.b;
	
		}
	}
}



void brammejd_HW02App::mouseDown( MouseEvent event )
{
	Delete(sentinel->next);
}

void brammejd_HW02App::keyDown( KeyEvent event ){
	if(event.getCode() == KeyEvent::KEY_RIGHT){
		if(currentX <= 750 && currentY <= 560){
			currentX += rand.nextInt(19)+1;
			currentY += rand.nextInt(9)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_LEFT){
		if(currentX > 20 && currentY > 10){
			currentX -= rand.nextInt(19)+1;
			currentY -= rand.nextInt(9)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_UP){
		if(currentX > 10 && currentY > 20){
			currentX -= rand.nextInt(9)+1;
			currentY -= rand.nextInt(19)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	} else if(event.getCode() == KeyEvent::KEY_DOWN){
		if(currentX < 760 && currentY < 550){
			currentX += rand.nextInt(9)+1;
			currentY += rand.nextInt(19)+1;
			insertAfter(sentinel, new Rect(rand.nextInt(29)+1, rand.nextInt(29)+1, currentX, currentY,
						new Color8u(rand.nextInt(255),rand.nextInt(255),rand.nextInt(255)), rand.nextBool()));
		}
	}
}

void brammejd_HW02App::setup()
{
	BGColor = Color8u(255,255,255);

	currentX = 0;
	currentY = 0;

	sentinel = new node;
	sentinel->next = sentinel;
	sentinel->rect = NULL;
	sentinel->prev = sentinel;

	mySurface = new Surface(TEXTURESIZE, TEXTURESIZE, false);
	dataArray = mySurface->getData();
	

	frameNumber = 0;
	
	insertAfter(sentinel, new Rect(20, 20,  currentX,  currentY, new Color8u(0,0,0), true));

}

void brammejd_HW02App::update()
{
	
	//Must continuously reset entire background to black to avoid possibly logically deleted shapes from appearing
	//resetBackground(dataArray, BGColor);
	dataArray = mySurface->getData();
	for(node* currentNode = sentinel->next; currentNode->rect != NULL; currentNode = currentNode->next){
		currentNode->rect->drawRect(dataArray);
	}
}

void brammejd_HW02App::draw()
{
	gl::draw(*mySurface);
}

CINDER_APP_BASIC( brammejd_HW02App, RendererGl )
