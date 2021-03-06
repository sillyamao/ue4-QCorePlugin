// L.q


#include "NetAPI.h"

#include "HttpManager.h"
FHttpModule* UNetAPI::GetHttpModule()
{
	static FHttpModule* httpModule = NULL;

	if (httpModule == NULL )
	{
		httpModule = &FHttpModule::Get();

		httpModule->SetHttpTimeout( 60 * 5 );
		httpModule->SetMaxReadBufferSize( 1024 * 1024 * 50 );
		httpModule->SetHttpDelayTime( 0.001 );
	}
	return httpModule;
}

FHttpManager& UNetAPI::GetHttpMgr()
{
	return UNetAPI::GetHttpModule()->GetHttpManager();
}

TSharedRef<IHttpRequest> UNetAPI::createRequest(const FString& _url, FString _method, FString _content, FString _contentType)
{
	TSharedRef<IHttpRequest> ret_request = UNetAPI::GetHttpModule()->CreateRequest();
	UNetAPI::GetHttpMgr().AddRequest(ret_request);
	
	OnRequestCreated().Broadcast(ret_request);
	
	ret_request->OnProcessRequestComplete().BindLambda([&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
	{
		UNetAPI::GetHttpMgr().RemoveRequest(Request.ToSharedRef());
		UNetAPI::OnRequestComplated().Broadcast(Request, Response,bConnectedSuccessfully);
	});

	ret_request->SetHeader(TEXT("Accept"),TEXT("*/*"));
	ret_request->SetHeader(TEXT("Content-Type"), _contentType);
	ret_request->SetURL(_url);

	ret_request->SetVerb(_method);

	if ( _method == TEXT("POST") )
	{
		ret_request->SetContentAsString(_content);
	}
	
	return ret_request;
}

TSharedRef<IHttpRequest> UNetAPI::createRequestRange( const FString& _url,
															int32 ContentLength, 
															int32 From, 
															int32 To, 
															FString _method /*= TEXT("GET")*/
															 )
{
	TSharedRef<IHttpRequest> ret_request = UNetAPI::GetHttpModule()->CreateRequest();
	UNetAPI::GetHttpMgr().AddRequest(ret_request);

	OnRequestCreated().Broadcast(ret_request);
	ret_request->OnProcessRequestComplete().BindLambda([&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
	{
		UNetAPI::GetHttpMgr().RemoveRequest(Request.ToSharedRef());
		UNetAPI::OnRequestComplated().Broadcast(Request, Response, bConnectedSuccessfully);
	});

	FString RangeVal = FString::Printf(TEXT(" bytes=%d-%d"), From, To);
	ret_request->SetHeader(TEXT( "Range" ), RangeVal);
	ret_request->SetVerb(_method);
	ret_request->SetURL(_url);

	return ret_request;
}

TSharedRef<IHttpRequest> UNetAPI::createUploadImageRequest(const FString& _url, TArray<uint8>& rawData)
{
	TSharedRef<IHttpRequest> ret_request = UNetAPI::GetHttpModule()->CreateRequest();
	UNetAPI::GetHttpMgr().AddRequest(ret_request);

	OnRequestCreated().Broadcast(ret_request);
	
	ret_request->OnProcessRequestComplete().BindLambda([&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
	{
		UNetAPI::GetHttpMgr().RemoveRequest(Request.ToSharedRef());
	});

	ret_request->SetURL(_url);
	ret_request->SetHeader(TEXT("Content-Type"), TEXT("text/html;charset=UTF-8"));

	ret_request->SetVerb(TEXT("POST"));
	ret_request->SetContent(rawData);

	return ret_request;
}

const UNetAPI::FEvent_OnRequestCreated& UNetAPI::OnRequestCreated()
{
	static FEvent_OnRequestCreated Event_OnRequestCreated;
	return Event_OnRequestCreated;
}

const UNetAPI::FEvent_OnRequestComplated& UNetAPI::OnRequestComplated()
{
	static FEvent_OnRequestComplated Event_OnRequestComplated;
	return Event_OnRequestComplated;
}
