// L.Q 2019


#include "BusinssNetAPI.h"

#include "Runtime/Core/Public/Misc/FileHelper.h"

#include "IImageWrapperModule.h"
#include "ModuleManager.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"

//
//void setTextureFromLoadImg(FHttpRequestPtr _request, FHttpResponsePtr _response, bool bWasSuccessful)
//{
//	if (!bWasSuccessful && !_response.IsValid())
//	{
//		UE_LOG(LogTemp, Warning, TEXT(" !bWasSuccessful && !_response.IsValid() "));
//		return;
//	}
//
//	IImageWrapperModule& temp_img_module = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//	TSharedPtr<IImageWrapper> temp_imgWrapper = temp_img_module.CreateImageWrapper(EImageFormat::JPEG);
//
//	TArray<uint8> temp_fileData = _response->GetContent();
//
//
//	if (!temp_imgWrapper.IsValid() ||
//		!temp_imgWrapper->SetCompressed(temp_fileData.GetData(), temp_fileData.Num()))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ImageWrapper can't Set Compressed or ImageWrapper is InValid"));
//		return;
//	}
//
//	const TArray<uint8>* temp_unCompressedRGBA = NULL;
//
//	if (!temp_imgWrapper->GetRaw(ERGBFormat::BGRA, 8, temp_unCompressedRGBA))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("can't get Raw temp_unCompressedRGBA"));
//		return;
//	}
//
//	auto m_texture = UTexture2D::CreateTransient(temp_imgWrapper->GetWidth(), temp_imgWrapper->GetHeight());
//
//	auto temp_dataPtr = static_cast<uint8*>(m_texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
//
//	FMemory::Memcpy(temp_dataPtr, temp_unCompressedRGBA, temp_unCompressedRGBA->Num());
//
//
//	m_texture->PlatformData->Mips[0].BulkData.Unlock();
//	m_texture->UpdateResource();
//	//m_texture->UpdateResourceW();
//}
//

static const FString api_UploadImage = TEXT("http://localhost:63664/api/Test/UploadImageFromCS?size=%d&filename=%s");

FHttpRequestPtr UBusinssNetAPI::UploadImage()
{
	TArray<uint8> binrary_data;
	TArray<FString> arr_path;

//#if UE_BUILD_DEVELOPMENT
	arr_path.Add(TEXT("d:/left.jpg"));
	arr_path.Add(TEXT("d:/top.jpg"));
	arr_path.Add(TEXT("d:/back.jpg"));
//#endif

	for (FString path : arr_path) 
	{
		FString left, right;

		path.Split(TEXT("/"), &left, &right, ESearchCase::IgnoreCase, ESearchDir::FromEnd);		
		
		FString fileName = FGenericPlatformHttp::UrlEncode( right );
		FFileHelper::LoadFileToArray(binrary_data, *path /* TEXT("d:/11.zip") */ );

		FString url = FString::Printf(*api_UploadImage, binrary_data.Num(), *fileName);
		TSharedRef<IHttpRequest> req = UNetAPI::createUploadImageRequest(url, binrary_data);

		req->OnProcessRequestComplete().BindLambda([=](	FHttpRequestPtr Request ,
														FHttpResponsePtr Response ,
														bool bConnectedSuccessfully )
			{
				UE_LOG(LogTemp, Log, TEXT("[UploadImage] : complated {%s}"), *api_UploadImage);
				UE_LOG(LogTemp, Log, TEXT("[UploadImage] : complated {%d}"), bConnectedSuccessfully);
			});

		if (req->ProcessRequest())
		{
			UE_LOG(LogTemp, Log, TEXT("[UploadImage] : starting......"));
		}

	}
	return nullptr;
}