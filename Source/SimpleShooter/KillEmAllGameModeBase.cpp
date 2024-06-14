// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController() );
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AShooterAIController* ShooterAIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!ShooterAIController->IsDead())
        {
            return;
        }       
    }
    
    EndGame(true);
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for (AController * Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = bIsPlayerWinner == Controller->IsPlayerController();
            Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}