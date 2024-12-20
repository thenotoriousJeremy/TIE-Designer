// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrbitingPawn.generated.h"

UCLASS()
class TIEDIE_API AOrbitingPawn : public APawn
{
    GENERATED_BODY()

public:
    AOrbitingPawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void StartOrbit();
    void StopOrbit();
    void RotateCameraYaw(float AxisValue); // Separate yaw rotation
    void RotateCameraPitch(float AxisValue); // Separate pitch rotation
    void Zoom(float AxisValue);

    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* Camera;

    FVector OrbitCenter;             // Fixed point around which to orbit
    float OrbitDistance;             // Current distance from orbit center
    float OrbitSpeed;                // Speed multiplier for orbiting
    float ZoomSpeed;                 // Speed of zooming in/out
    float MinZoomDistance;           // Minimum zoom distance
    float MaxZoomDistance;           // Maximum zoom distance

    bool bIsOrbiting;                // Tracks if orbiting is active
};
