// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

AAgent::AAgent(){
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));	
	RootComponent = Mesh;
	Velocity = FVector(0.0f);
}

void AAgent::BeginPlay(){
	Super::BeginPlay();
	//Velocity = FVector(0.05f);
}

void AAgent::Init( UStaticMeshComponent *mesh, int id ) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized.") );
	Mesh->SetStaticMesh( mesh->GetStaticMesh() );
}

void AAgent::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	FVector loc = GetActorLocation();
	SetActorLocation( loc + Velocity );
}

