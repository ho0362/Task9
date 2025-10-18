// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABaseActor::ABaseActor()
{
 	PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);
    
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

    //이벤트 바인딩
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseActor::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseActor::OnItemEndOverlap);
}

void ABaseActor::OnItemOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if(OtherActor &&OtherActor->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
        ActivateItem(OtherActor);
    }

}
void ABaseActor::OnItemEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OherBodyIndex)
{

}
void ABaseActor::ActivateItem(AActor* Activator) 
{
    UParticleSystemComponent* Particle = nullptr;

    if (PickupParticle)
    {
        Particle = UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            PickupParticle,
            GetActorLocation(),
            GetActorRotation(),
            true
        );
  
    }

    if (PickupSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            PickupSound,
            GetActorLocation()
        );
    }

    if (Particle)
    {
        FTimerHandle DestroyParticleTimerHandle;
        TWeakObjectPtr<UParticleSystemComponent> WeakParticle = Particle;

        GetWorld()->GetTimerManager().SetTimer(
            DestroyParticleTimerHandle,
            [WeakParticle]()
            {
                if (WeakParticle.IsValid())
                {
                    WeakParticle->DestroyComponent();
                }
            },
            2.0f,
            false
        );
    }
}
FName ABaseActor::GetItemType() const 
{
    return ItemType;
}

void ABaseActor::DestroyItem() 
{
    Destroy();
      
}