// Fill out your copyright notice in the Description page of Project Settings.


#include "PongCamera.h"

#include "Camera/CameraComponent.h"

APongCamera::APongCamera()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}
