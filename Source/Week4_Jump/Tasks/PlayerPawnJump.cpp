// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnJump.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerPawnJump::APlayerPawnJump()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	// FOR SetSimulatePhysics I LOOKED INTO SOLUTIONS, BUT IT STILL DOESN'T WORK FOR ME
	CapsuleComponent->SetSimulatePhysics(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	RootComponent = SpringArmComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void APlayerPawnJump::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawnJump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnJump::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerPawnJump::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawnJump::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawnJump::MoveRight);
}

void APlayerPawnJump::MoveForward(float Value)
{
	FVector ForwardVector = FVector(Value * MovementSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	AddActorWorldOffset(ForwardVector);
}

void APlayerPawnJump::MoveRight(float Value)
{
	FVector RightVector = FVector(0, Value * MovementSpeed * GetWorld()->DeltaTimeSeconds, 0);
	AddActorWorldOffset(RightVector);
}

void APlayerPawnJump::Jump()
{
	if (JumpCount < MaxJumpsCount)
	{
		FVector JumpVector = FVector(0, 0, JumpForce);
		CapsuleComponent->AddImpulse(JumpVector, "", true);

		JumpCount++;
	}
}


// FOR THIS (OnHit) SOLUTION I LOOKED INTO PlayerPawnJumpSolution, cause was stuck in implementing it 

void APlayerPawnJump::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float HitDirection = Hit.Normal.Z;

	if (HitDirection > 0)
	{
		JumpCount--;
	}
}
