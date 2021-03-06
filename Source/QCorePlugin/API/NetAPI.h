// L.Q 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "NetAPI.generated.h"

/**
 * 
 */
UCLASS()
class QCOREPLUGIN_API UNetAPI : public UObject
{
	GENERATED_BODY()
public:
	//Setting.eg timeout/delay time/once read max buffer
	static FHttpModule* GetHttpModule();

	static FHttpManager& GetHttpMgr();


	//UFUNCTION()
	static TSharedRef<IHttpRequest> createRequest(const FString &_url,
														FString _method = TEXT("GET"),
														FString _content = TEXT(""),
														FString _contentType = TEXT("text/html;charset=UTF-8"));


	static TSharedRef<IHttpRequest> createRequestRange( const FString& _url,
																int32 ContentLength,
																int32 From,
																int32 To,
																FString _method = TEXT("GET"));

	static TSharedRef<IHttpRequest> createUploadImageRequest(const FString& _url, TArray<uint8>& rawData);
	
	#pragma region event
	DECLARE_EVENT_OneParam(FString,FEvent_OnRequestCreated, const TSharedRef<IHttpRequest>& )
	static const FEvent_OnRequestCreated& OnRequestCreated();

	DECLARE_EVENT_ThreeParams(FString,FEvent_OnRequestComplated, FHttpRequestPtr /*Request*/, FHttpResponsePtr /*Response*/, bool /*bConnectedSuccessfully*/)
	static const FEvent_OnRequestComplated& OnRequestComplated();

protected:

#pragma endregion event

};