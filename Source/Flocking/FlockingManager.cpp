// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingManager.h"
#include "Agent.h"
#include "Kismet/KismetMathLibrary.h"

#define AGENT_COUNT 10

void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh ) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));
    
    World = world;
    float incr = (PI * 2.f) / AGENT_COUNT;
    for( int i = 0; i < AGENT_COUNT; i++ ) {
        if( World != nullptr ) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin( incr * i ) * 150.f;
            location.Y = FMath::Cos( incr * i ) * 150.f;
            location.Z = 100.f;
            
            AAgent * agent = World->SpawnActor<AAgent>( location, rotation );
            agent->Init( mesh, i );
            Agents.Add( agent );
        }
    }

    initialized = true;
}

/*

	PROCEDURE rule3(boid bJ)

		Vector pvJ

		FOR EACH BOID b
			IF b != bJ THEN
				pvJ = pvJ + b.velocity
			END IF
		END

		pvJ = pvJ / N-1

		RETURN (pvJ - bJ.velocity) / 8

	END PROCEDURE

*/

void UFlockingManager::Flock() {
  //UE_LOG(LogTemp,Warning,TEXT("OH THEY FLOCKING"));
  FVector v1, v2,v3;

  for (int i = 0; i < Agents.Num(); i++) {
    
    v1 = FVector(0,0,0);
    v2 = FVector(0,0,0);
    v3 = FVector(0,0,0);

    UE_LOG(LogTemp,Warning,TEXT("about to get actor"));

    AAgent * currentAgent = Agents[i];
    if (currentAgent == NULL) {
      UE_LOG(LogTemp,Warning,TEXT("whoops we gots a null agent"));
      return;
    }
    UE_LOG(LogTemp,Warning,TEXT("got the actor"));

    //FVector position = currentAgent->GetActorLocation();

    //UE_LOG(LogTemp,Warning,TEXT("got location"), i);

    for (int j = 0; j < Agents.Num(); j++) {

      UE_LOG(LogTemp,Warning,TEXT("into next loop"));
      if (!(j == i)) {
        FVector jPos = Agents[j]->GetActorLocation();
        UE_LOG(LogTemp,Warning,TEXT("got jPos"));
        v1 = v1 + jPos;
        FVector dif = (jPos - currentAgent->GetActorLocation());
        UE_LOG(LogTemp,Warning,TEXT("used location"));
        if (dif.Size() < 100) {
          v2 = v2 - dif;
        }
        v3 = v3 + Agents[j]->Velocity;
      }
    }
        
    v1 = v1 / (Agents.Num() - 1);
    v1 = (v1 - currentAgent->GetActorLocation()) / 400;
    UE_LOG(LogTemp,Warning,TEXT("also used location"));

    v3 = v3 / (Agents.Num() - 1);
    v3 = ( v3 - currentAgent->Velocity) / 32;

    currentAgent->Velocity = currentAgent->Velocity + v1 + v2 + v3;
  }
}