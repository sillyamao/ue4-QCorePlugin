// 宝吉网络-1234567890


#include "ComponentBPLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

USceneComponent*  UComponentBPLibrary::AddDynamicComponent( UObject * WorldContextObject,
															USceneComponent*parentCOM, 
															TSubclassOf< USceneComponent> COMClass,
														    const FTransform &tran )
{
	// USceneComponent* childActorCOM = NewObject<USceneComponent>(parentCOM->GetAttachmentRootActor(), COMClass);
	// 
	// childActorCOM->RegisterComponent();
	// 
	// childActorCOM->AttachToComponent(parentCOM,  FAttachmentTransformRules::KeepRelativeTransform);


	// childActorComponent->SetChildActorClass(*MyActorClass);
	// temp_imageCom->AttachToComponent(parentCOM, FAttachmentTransformRules::KeepRelativeTransform);
	// childActorCOM;
	return  nullptr; 
}