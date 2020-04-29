// 宝吉网络-1234567890


#include "NetAPI.h"

#include "Http.h"

FHttpModule* UNetAPI::GetHttpModule()
{
	static FHttpModule* httpModule = NULL;

	if (httpModule == NULL )
	{
		httpModule = &FHttpModule::Get();



		httpModule->SetHttpTimeout( 60 );
		httpModule->SetMaxReadBufferSize( 1024 * 1024 * 50 );
		httpModule->SetHttpDelayTime( 0.001 );

		//header
		//temp_module->AddDefaultHeader(TEXT("Cache-Control"), TEXT("no-cache"));
	}
	return httpModule;
}

FHttpManager& UNetAPI::GetHttpMgr()
{
	return UNetAPI::GetHttpModule()->GetHttpManager();
}

TSharedRef<IHttpRequest> UNetAPI::createRequst(FString _url, FString _method, FString _content, FString _contentType)
{
	TSharedRef<IHttpRequest> ret_request = UNetAPI::GetHttpModule()->CreateRequest();

	ret_request->SetHeader(TEXT("Content-Type"), _contentType);
	ret_request->SetURL(_url);

	ret_request->SetVerb(_method);

	if ( _method == TEXT("POST") )
	{
		ret_request->SetContentAsString(_content);
	}

	return ret_request;
}

TSharedRef<IHttpRequest> UNetAPI::createUploadImageRequest(FString _url, TArray<uint8>& rawData)
{
	TSharedRef<IHttpRequest> ret_request = UNetAPI::GetHttpModule()->CreateRequest();

	ret_request->SetURL(_url);
	ret_request->SetHeader(TEXT("Content-Type"), TEXT("text/html;charset=UTF-8"));

	ret_request->SetVerb(TEXT("POST"));
	ret_request->SetContent(rawData);

	return ret_request;
}