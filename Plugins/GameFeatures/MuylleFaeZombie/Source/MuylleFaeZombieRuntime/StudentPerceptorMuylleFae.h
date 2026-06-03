// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "StudentPerceptorMuylleFae.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUYLLEFAEZOMBIERUNTIME_API UStudentPerceptorMuylleFae : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptorMuylleFae();
	
	virtual void BeginPlay() override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStudentPerceptedSomething, AActor*, Actor, FAIStimulus, stimulus);
	UPROPERTY(BlueprintAssignable, Category="Perception")
	FOnStudentPerceptedSomething OnPerceptedSomething;
	
	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	
};
