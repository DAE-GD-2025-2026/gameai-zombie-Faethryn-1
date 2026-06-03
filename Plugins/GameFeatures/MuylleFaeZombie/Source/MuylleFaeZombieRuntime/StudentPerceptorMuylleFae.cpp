// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorMuylleFae.h"


UStudentPerceptorMuylleFae::UStudentPerceptorMuylleFae()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorMuylleFae::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorMuylleFae::OnPerceptionUpdated);
	}
}

void UStudentPerceptorMuylleFae::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	OnPerceptedSomething.Broadcast(Actor, Stimulus);
}
