#include "Item/Item.h"
#include "Components/BoxComponent.h"

AItem::AItem()
{
    PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
    SetRootComponent(ItemMesh);

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->SetupAttachment(ItemMesh);
}

void AItem::BeginPlay()
{
    Super::BeginPlay();
}
