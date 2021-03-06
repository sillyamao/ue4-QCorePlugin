// 宝吉网络-1234567890

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ComponentBPLibrary.generated.h"

/**
 * 组件相关的一些通用功能
 */
UCLASS()
class QCOREPLUGIN_API UComponentBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "QCore | Component Function", meta = (HidePin = "WorldContextObject",
																				  DefaultToSelf = "WorldContextObject",
																				  DeterminesOutputType = "ActorClass"))
	static class UChildActorComponent* AddDynamicActorChildComponent(UObject * WorldContextObject,
																	 class USceneComponent*parentCOM,
																	 class TSubclassOf<class AActor> ActorClass,
																	 const FTransform &tran);

	UFUNCTION(BlueprintCallable, Category = "QCore | Component Function", meta = (	HidePin = "WorldContextObject",
																					DefaultToSelf = "WorldContextObject"))
		static void RestoreDecalSize(UObject * WorldContextObject, class UDecalComponent* decal, FVector extend);

};
