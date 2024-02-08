// Fill out your copyright notice in the Description page of Project Settings.


#include "CrackedEdge.h"

FCrackedEdge::FCrackedEdge()
	: ImageForDisplay(nullptr)
	, amount(0)
{
}

FCrackedEdge::FCrackedEdge(FCrackedEdge & other)
{
	this->amount = other.amount;
	this->ImageForDisplay = other.ImageForDisplay;
}
