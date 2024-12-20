// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitingPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

AOrbitingPawn::AOrbitingPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set default values
    OrbitCenter = FVector(0.f, 0.f, 0.f);
    OrbitDistance = 500.f;
    OrbitSpeed = 2.f;
    ZoomSpeed = 50.f;
    MinZoomDistance = 200.f;
    MaxZoomDistance = 3000.f;

    bIsOrbiting = false;

    // Create a spring arm and attach it to the root component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = OrbitDistance;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.f;

    // Create a camera and attach it to the spring arm
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AOrbitingPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AOrbitingPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AOrbitingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind the "Orbit" action to start and stop orbiting
    PlayerInputComponent->BindAction("Orbit", IE_Pressed, this, &AOrbitingPawn::StartOrbit);
    PlayerInputComponent->BindAction("Orbit", IE_Released, this, &AOrbitingPawn::StopOrbit);

    // Bind the "Zoom" axis for zooming with the scroll wheel
    PlayerInputComponent->BindAxis("Zoom", this, &AOrbitingPawn::Zoom);

    // Bind mouse movement for yaw (horizontal rotation) and pitch (vertical rotation)
    PlayerInputComponent->BindAxis("Turn", this, &AOrbitingPawn::RotateCameraYaw);
    PlayerInputComponent->BindAxis("LookUp", this, &AOrbitingPawn::RotateCameraPitch);
}

void AOrbitingPawn::StartOrbit()
{
    bIsOrbiting = true;
}

void AOrbitingPawn::StopOrbit()
{
    bIsOrbiting = false;
}

void AOrbitingPawn::RotateCameraYaw(float AxisValue)
{
    if (bIsOrbiting)
    {
        FRotator NewRotation = SpringArm->GetComponentRotation();
        NewRotation.Yaw += AxisValue * OrbitSpeed;
        SpringArm->SetWorldRotation(NewRotation);
    }
}

void AOrbitingPawn::RotateCameraPitch(float AxisValue)
{
    if (bIsOrbiting)
    {
        FRotator NewRotation = SpringArm->GetComponentRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue * OrbitSpeed, -80.f, 80.f);
        SpringArm->SetWorldRotation(NewRotation);
    }
}

void AOrbitingPawn::Zoom(float AxisValue)
{
    OrbitDistance = FMath::Clamp(OrbitDistance - AxisValue * ZoomSpeed, MinZoomDistance, MaxZoomDistance);
    SpringArm->TargetArmLength = OrbitDistance;
}
